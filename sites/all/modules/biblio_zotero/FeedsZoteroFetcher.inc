<?php
 ini_set('max_execution_time', -1);

/**
* @file
* FeedsZoteroFetcher
*/

/**
 * Result of FeedsZoteroHTTPFetcher::fetch().
 * Overriding FeedsHTTPFetcher so we can import results of multiple HTTP requests
 * as required by Zotero's API limitations
 *
 */
class FeedsZoteroHTTPFetcherResult extends FeedsHTTPFetcherResult {
  protected $file_path;
  protected $timeout;
  protected $itemsPages = array();
  protected $collectionsPage;

  /** 
   * Constructor.
   */
  public function __construct($url = NULL) {
    parent::__construct($url);
  }
  public function getItemsPages() {
    return $this->itemsPages;
  }
  /**
   * Return a simple array of all collection keys
   */
  public function getCollectionKeys() {
    $simple_xml = simplexml_load_string($this->collectionsPage);
    $namespaces = $simple_xml->getNameSpaces(true);
    $keys = array();
    foreach ($simple_xml->entry as $entry) { 
      $zapi = $entry->children($namespaces['zapi']); 
      $key  = (string)$zapi->key; 
      $keys[$key] = $key;
    }
    return $keys;
  }
  /**
   * Return a structured array with sub-collections nested underneath their parents
   */
  public function getCollectionHierarchy() {
    $simple_xml = simplexml_load_string($this->collectionsPage);
    $namespaces = $simple_xml->getNameSpaces(true);
    $collections = array();
    foreach ($simple_xml->entry as $entry) { 
      $zapi = $entry->children($namespaces['zapi']); 
      $key  = (string)$zapi->key; 
      $parent = $this->getCollectionParent($entry);
      $collections[$key] = array('key' => $key, 'title' => (string)$entry->title, 'parent' => $parent, 'children' => array());
    }
    //Sort collections into a hierarchical array matching their Zotero structure
    foreach ($collections as $collection) { 
      $parent = $collection['parent'];
      if ($parent && isset($collections[$parent])) {
        //Put collection under its parent's entry
        $collections[$parent]['children'][$collection['key']] = $collection;
        //Remove collection now that we've copied it under its parent
        unset($collections[$collection['key']]);
      }
    }
    return $collections;
  }
  /**
   *  Given a Simple XML Element of the collection entry, return the key of collection's parent
   */
  public function getCollectionParent(SimpleXMLElement $entry) {
    //Search for collection key in XML result
    $link = $entry->xpath("*[@rel='up']"); 
    if ($link) {
      $link  = (string)$link[0]['href'];
      file_put_contents('link', print_r($link, TRUE));
      $matches = array();
      preg_match('#collections/(.*)#', $link, $matches);
      file_put_contents('matches', print_r($matches, TRUE));
      $collection_key = isset($matches[1]) ? $matches[1] : FALSE;
      return $collection_key;
    }
  }
  /**
   *  Add one of the Items pages retrieved from Zotero
   */
  public function addItemsPage($page_xml) {
    $this->itemsPages[] = $this->sanitizeRaw($page_xml);
  }
  /**
   * Set the XML for the collections page retrieve from Zotero
   */
  public function setCollectionsPage($page_xml) {
    $this->collectionsPage = $page_xml;
  }
}




/**
* Fetches data via HTTP.
*/

class FeedsZoteroFetcher extends FeedsHTTPFetcher {
   
   /**
   * Expose source form.
   */
   public function sourceForm($source_config) {
      $form = array();
      $form['zotero_type'] = array(
         '#type' => 'radios',
         '#title' => t('What type of Zotero library is this?'),
         '#options' => array('group' => 'Group', 'user' => 'User'),
         '#default_value' => isset($source_config['zotero_type']) ? $source_config['zotero_type'] : '',
         '#maxlength' => NULL,
         '#required' => TRUE,
         );
      $form['zotero_id'] = array(
         '#type' => 'textfield',
         '#title' => t('Zotero ID'),
         '#description' => t('Enter the numeric id of your zotero user or group. To find your 
            group id, navigate to your groups\'s settings page and the numeric part of the URL 
            is you group id. Your userID is in
            <a href="https://www.zotero.org/settings/keys">Feeds/API section</a> of your zotero settings.'),
         '#default_value' => isset($source_config['zotero_id']) ? $source_config['zotero_id'] : '',
         '#maxlength' => NULL,
         '#required' => TRUE,
         );
      $form['fetch_collections'] = array(
          '#type' => 'checkbox',
          '#title' => t("Fetch collections"),
          '#description' => t("If selected a user or group's collections will be fetched instead of their library items"),
          '#default_value' => isset($source_config['fetch_collections']) ? $source_config['fetch_collections'] : 0,
         );
      $form['collection_key'] = array(
         '#type' => 'textfield',
         '#title' => t('Collection ID'),
         '#description' => t("Only applicable if Fetch Collections above is selected. If none is entered, all top level collections for the user or group will be retrieved.")
       );
      $form['api_key'] = array(
         '#type' => 'textfield',
         '#title' => t('Zotero API key'),
         '#description' => t('If your group or user account is private, you will need to enter 
            your api key to be allowed to access the library.  Your api key is in
            <a href="https://www.zotero.org/settings/keys">Feeds/API section</a> of your zotero settings.'),
         '#default_value' => isset($source_config['api_key']) ? $source_config['api_key'] : '',
         '#maxlength' => NULL,
         );
      $form['source'] = array(
         '#type' => 'hidden',
         '#title' => t('URL'),
         '#disabled' => TRUE,
         '#description' => t('Enter a feed URL.'),
         '#default_value' => isset($source_config['source']) ? $source_config['source'] : '',
         '#maxlength' => NULL,
         );
      $form['next_index'] = array(
         '#type' => 'hidden',
         '#title' => t('Next Index'),
         '#disabled' => TRUE,
         '#description' => t('The next index to be used as the start parameter for the next import.'),
         '#default_value' => isset($source_config['next_index']) ? $source_config['next_index'] : 0,
         '#maxlength' => NULL,
         );
      $form['child_source'] = array(
         '#type' => 'hidden',
         '#title' => t('Child source'),
         '#disabled' => TRUE,
         '#description' => t('The service url to fetch children of a given zotero item.'),
         '#default_value' => isset($source_config['child_source']) ? $source_config['child_source'] : '',
         '#maxlength' => NULL,
         );
      $form['limit'] = array(
         '#type' => 'textfield',
         '#title' => t('Limit'),
         '#description' => t('How many zotero items to fetch at each import, enter 0 for unlimited'),
         '#default_value' => isset($source_config['limit']) ? $source_config['limit'] : 50,
         '#maxlength' => NULL,
         );
      if ( ! empty($source_config['source'])) {
         $form['source'] = array(
            '#type' => 'markup',
            '#value' => '<p><label>URL</label>: ' . $source_config['source'] . '</p>',
            );
      }
      return $form;
   }
   
   /**
   * Override parent::sourceFormValidate().
   */
   public function sourceFormValidate(&$values) {
      // We need to construct a url that looks like this: 
      // https://api.zotero.org/groups/98765/items
      // or this:
      // https://api.zotero.org/users/12345/items
      
      if (! is_numeric($values['zotero_id'])) {
         $form_key = 'feeds][' . get_class($this) . '][zotero_id';
         form_set_error($form_key, t('The zotero id must be numeric.'));
      }

      if (! is_numeric($values['limit']) || $values['limit'] < 0 ) {
         $form_key = 'feeds][' . get_class($this) . '][limit';
         form_set_error($form_key, t('The value for limit must be a number greater than zero.'));
      }
      
      $this->setConfigSourceUrl($values);
      
      // TODO add option to fetch from zotero without json for use in non-biblio fields, i.e. the standard processor
      // TODO test the accessibility of the API call.
      
      if (!feeds_valid_url($values['source'], TRUE)) {
         $form_key = 'feeds][' . get_class($this) . '][source';
         form_set_error($form_key, t('The URL %source is invalid.', array('%source' => $values['source'])));
      }
   }
   
      /**
   * Override parent::configDefaults().
   */
   public function configDefaults() {
      $defaults = parent::configDefaults();
      return $defaults;
   }
   
   /**
   * Override parent::configForm().
   */
   public function configForm(&$form_state) {
      $form = array();
      return $form; 
   }
   
  /**
   * Implements FeedsFetcher::fetch().
   * Overrides FeedsHTTPFetcher->fetch
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    if ($source_config['fetch_collections']) {
      $result = $this->fetchCollection($source);
    }
    else {
      $result = $this->fetchItems($source);
    }
    return $result;
  }
  public function fetchURL($url) {
    feeds_include_library('http_request.inc', 'http_request');
    $result = http_request_get($url, NULL, NULL, NULL, $this->timeout);
    if (!in_array($result->code, array(200, 201, 202, 203, 204, 205, 206))) {
      throw new Exception(t('Download of @url failed with code !code.', array('@url' => $url, '!code' => $result->code)));
    }
    
    return $result->data;
  }
  public function fetchItems(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    $items_fetched = 0;
    $result = new FeedsZoteroHTTPFetcherResult($source_config['source']);
    $no_limit = ($source_config['limit'] == 0);
    $count = 0;
    while ($items_fetched < $source_config['limit'] || $no_limit) {
      $feed_raw_xml = $this->fetchURL($source_config['source']);
      $result->addItemsPage($feed_raw_xml);
      $index = $source_config['next_index'];
      //alter the config for next fetch before saving new config
      $source_config['next_index'] = $this->getNextIndex($feed_raw_xml) ? $this->getNextIndex($feed_raw_xml) : 0;
      $items_fetched = $source_config['next_index'] - $index;
      $this->setConfigSourceUrl($source_config);
      $source->setConfigFor($this, $source_config);
      $source->save();
      if (!$source_config['next_index']) {
        //No items left to fetch, exit loop
        break;
      }
    }
    return $result;
  }
  /**
   *  Helper function to get all items from a collection, non-recursively
   *  i.e. Does not get items from a collection's sub-collections
   *
   */
  private function getCollectionItems(FeedsSource $source, FeedsFetcherResult &$result, $collection_key) {
    $source_config = $source->getConfigFor($this);
    $zotType = $source_config['zotero_type'] == 'group' ? 'groups' : 'users';
    $next_index = 0;
    $xml = '';
    while ($next_index !== FALSE) {
      $url = sprintf('https://api.zotero.org/%s/%d/collections/%s/items?content=json&start=%d', 
        $zotType, $source_config['zotero_id'], $collection_key, $next_index);
      $xml = $this->fetchURL($url);
      $result->addItemsPage($xml);
      $next_index = $this->getNextIndex($xml);
    }
    return $xml;
  }

  public function getCollections(FeedsSource $source, &$result, $collection_key = NULL) {
    $source_config = $source->getConfigFor($this);
    $zotType = $source_config['zotero_type'] == 'group' ? 'groups' : 'users';
    $xml = '';
    $url = sprintf('https://api.zotero.org/%s/%d/collections', $zotType, $source_config['zotero_id']);
    //If collection key is specified, get all sub-collections, otherwise get all collections in library
    if ($collection_key) {
      $url .= "/$collection_key/collections";
    }
    $xml = $this->fetchURL($url);
    $result->setCollectionsPage($xml); 
    return $xml;
  }

  public function fetchCollection(FeedsSource $source, $collection_key = NULL) {
    $source_config = $source->getConfigFor($this);
    file_put_contents('sourceConfig', print_r($source_config, TRUE));
    $result = new FeedsZoteroHTTPFetcherResult($source_config['source']);
    
    $this->getCollections($source, $result, $source_config['collection_key']);
    file_put_contents('fetchCollection', $xml);
    $collection_keys = $result->getCollectionKeys($xml);
    file_put_contents('collectionKeys', print_r($collection_keys, TRUE));
    foreach ($collection_keys as $key) { 
      $this->getCollectionItems($source, $result, $key);  
    }
    return $result;
  }
  /**
   *  Parses XML response from Zotero to return the numeric index for the next request
   */
  private function getNextIndex($xml) {
    $feed_simple_xml = simplexml_load_string($xml);
    $next = $feed_simple_xml->xpath("*[@rel='next']"); 
    $first = $feed_simple_xml->xpath("*[@rel='first']"); 
    if (!empty($next)) {
      $next_href = (string)$next[0]['href'];
      $pattern = "/start=\d+/";
      preg_match($pattern, $next_href, $matches);
      $next_index = array_pop( explode("=", $matches[0]) );
      return $next_index; 
    }
    else {
      return FALSE; 
    }
  }
  private function setConfigSourceUrl(&$values) {
     $zotType = $values['zotero_type'] == 'group' ? 'groups' : 'users';
      $values['source'] = sprintf('https://api.zotero.org/%s/%d/items/top', $zotType, $values['zotero_id']);
      $values['source'] .= '?content=json';
      //Limit of 99 is imposed by Zotero's API
      $api_limit = ($values['limit'] == 0 || $values['limit'] > 99) ? 99 : $values['limit'];
      $values['source'] .= sprintf('&limit=%d',$api_limit );
      $values['source'] .= sprintf('&start=%d',$values['next_index'] );  // next_index is changed after every fetch
      $values['child_source'] = sprintf('https://api.zotero.org/%s/%d/items/%%s/children', $zotType, $values['zotero_id']); // the last token is replaced during parsing
      $values['child_source'] .= '?content=json&limit=99';
      if ( ! empty( $values['api_key'] ) ) {
         // TODO validate the api_key
         $values['source'] .= '&key=' . $values['api_key'];
         $values['child_source'] .= '&key=' . $values['api_key'];
      }
  }
}
