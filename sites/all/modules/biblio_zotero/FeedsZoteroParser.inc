<?php

/**
* Class definition for Zotero Parser.
*
* Parses RSS and Atom feeds.
*/
class FeedsZoteroParser extends FeedsSyndicationParser {
   /**
   * Override parent::configDefaults().
   */
   public function configDefaults() {
      $config = parent::configDefaults();
      $config['refresh_zotero_item_type_fields'] = false;
      return $config;
   }
   
   /**
   * Override parent::configForm().
   */
   public function configForm(&$form_state) {
      $form = parent::configForm($form_state);
      
     /* THIS IS HANDY FOR DEBUGGING
     $form['refresh_zotero_item_type_fields'] = array(
         '#type' => 'radios',
         '#title' => t('Refresh the item type fields?'),
         '#options' => array(1 => t('yes'), 0 => t('no')),
         '#default_value' => $this->config['refresh_zotero_item_type_fields'],
         '#description' => t('Refresh the item type fields every time the mappings are requested [e.g. on the mappings settings page]. Zotero occasionally changes the fields available for each item type so it is necessary to update the mapping sources. This will make the mappings page load slowly so it is best to uncheck this after you\'ve updated.'),
         
         ); */
      return $form;
   }
   
   /**
   * Override parent::configFormValidate().
   */
   public function configFormValidate(&$values) {
   }
   
   /**
   * Implementation of FeedsParser::parse().
   */
   public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
      feeds_include_library('common_syndication_parser.inc', 'common_syndication_parser');
      
      $source_config = $source->getConfig();
      $result = new FeedsParserResult();
      $result->collections = $fetcher_result->getCollectionHierarchy();      
      // $result->link = (string)array_shift($feed_simple_xml->link);
      
      // Pull collection key from each page below if exists
      // Use Item Key to ensure only one copy of the items is created
      // Add the collection key to item so we can tag in Processing phase      
      foreach ($fetcher_result->getItemsPages() as $page) { 
        $collection_key = $page['collection_key'];

        if (!is_array($page['page'])) {
          $page['page'] = array($page['page']);
        }

        foreach ($page['page'] as $feed_raw_xml) {

          $feed_simple_xml = simplexml_load_string($feed_raw_xml);
          $namespaces = $feed_simple_xml->getNameSpaces(true);

          foreach ($feed_simple_xml->entry as $entry) {
            $zapi = $entry->children($namespaces['zapi']); 
            $item_key = (string)$zapi->key;
            $item = array();

            if (isset($result->items[$item_key])) {
              //Item already added in another collection, just add collection key
              $item = $result->items[$item_key];
              if (!is_null($collection_key)) {
                $item['collection_keys'][] = $collection_key;
              }              
            }
            else {
              $item['collection_keys'] = $collection_key ? array($collection_key) : array();
               
              $json = (string)$entry->content;
              $data = json_decode($json);
              $item = array_merge($item, (array)$data);
              $item['key'] = $item_key;
              $item['guid'] = $item_key;
               
              $item['url'] = (string)$entry->id;
              $item['published'] = (string)$entry->published;
              $item['updated'] = (string)$entry->updated;
              $item['description'] = ''; //description gets mapped to Full Text of the biblio node so leave it blank
              $item['title'] = (string)$entry->title;
               
              $item['itemType'] = (string)$zapi->itemType;
              $item['creatorSummary'] = (string)$zapi->creatorSummary;
              $item['year'] = (string)$zapi->year;
              $item['numChildren'] = (string)$zapi->numChildren;
              $item['numTags'] = (string)$zapi->numTags;             
              self::addItemTypePrefixes($item);

            }

            $this->addZoteroChildren($source, $item);   
            $result->items[(string)$zapi->key] = $item;            
          }
        }
      }
      $result->title = $result->title ? $result->title : t('Zotero Feed Importer');
      return $result;
   }
   
   /**
   * Return mapping sources.
   * Zotero field names for sources are found here: http://www.zotero.org/support/dev/client_coding/javascript_api/search_fields
   */
   public function getMappingSources() {
      module_load_include('inc', 'biblio_zotero', 'biblio_zotero');
      $refresh = $this->config['refresh_zotero_item_type_fields'];
      $zoteroItemStructure = BiblioZotero::getItemTypeStructure($refresh);
      $sources = array();
      foreach ( $zoteroItemStructure as  $key => $zotero_type ) {
         $item_type = $key;
         $item_type_label = $zotero_type->localized;
         foreach ( $zotero_type->fields as $key => $field) {       
            $source = "$item_type:$key";
            $sources[$source] = array(
               'name' => t("Zotero - $item_type_label - $field->localized"),
               );
         }
      }
      $sources['creators'] = array(
         'name' => t("Zotero - Creators"),
         'description' => t("Zotero creators vary by item type and the mapping is determined in a callback function provided in biblio_zotero.module"),
         'callback' => 'biblio_zotero_feeds_source_creators',
         );

      $sources += parent::getMappingSources();
      return $sources;
   }
   
   /**
   * Fetch children of a top-level item
   * @TODO handle cases where there are more than 99 CHILD items; look for rel='next' value
   **/
   private function addZoteroChildren( FeedsSource $source, &$item ) {
      // get the child items: notes, attachments, and what else?
      
      /** @TODO somehow keep notes metadata, author, tags, etc. **/
      if ( $item['numChildren'] > 0 ) {
         $zapiKey = $item['key'];
         $source_config = $source->getConfig();
         $child_service_url = sprintf( $source_config['FeedsZoteroFetcher']['child_source'],$zapiKey );  // child items url
         if ( ! empty( $source_config['FeedsZoteroFetcher']['api_key'] ) ) {
            $child_service_url .= '&key=' . $source_config['FeedsZoteroFetcher']['api_key'];
         }
         $xml_str = file_get_contents($child_service_url); /** @TODO use authentication if in Fetcher **/ 
         $xml = simplexml_load_string($xml_str);
         $namespaces = $xml->getNameSpaces(true);
         
         foreach ( $xml->entry as $entry ) {
            $child = json_decode( (string) $entry->content );
            $child->author = (string)$entry->author->name;
            $zapi = $entry->children($namespaces['zapi']); 
            $child->key = (string)$zapi->key;
            $child->itemType = (string)$zapi->itemType;
            // for this to work, go to admin/config/content/biblio/fields and in Common fields set biblio_notes to common
            
            switch ( $child->itemType ) {
            case 'note':
               $note = $child->note . PHP_EOL . " - " . $child->author;
               // Concatenate multiple notes into one value; this 'note' field is exposed as a mapping source
               $item['note'] .= strip_tags($note) . PHP_EOL; 
               // This is here so the processor can do something more exciting than concat note text. 
               //@TODO expose 'notes' this with a proper source callback and target callback
               $item['notes'][] = $child; 
               break;
            default:
            }
         }
      }
   }
   
   /**
   * Create unique mapping sources for the different zotero types 
   * since they sometimes map to different biblio fields depending on publication type
   */
   function addItemTypePrefixes(&$item) {
      $no_rename = array('itemType', 'guid','tags','creators', 'collection_keys');
      $item = (array)$item;
      $old_keys = array_keys($item);
      foreach( $old_keys as $old_key) {
         if (in_array($old_key, $no_rename)) {
            continue;
         }
         $new_key = $item['itemType'] . ":" . $old_key;
         $item[$new_key] = $item[$old_key];
         unset($item[$old_key]);
      }
   }
}
