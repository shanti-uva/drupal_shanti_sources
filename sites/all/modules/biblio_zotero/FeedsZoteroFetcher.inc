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
  protected $collectionsPages = array();

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
    $keys = array();
    $count = 0;
    $key_count = 0;
    foreach ($this->collectionsPages as $collectionsPage) {      
      $count++;
      $simple_xml = simplexml_load_string($collectionsPage);
      if (is_object($simple_xml)) {
        $namespaces = $simple_xml->getNameSpaces(true);
        foreach ($simple_xml->entry as $entry) { 
          $key_count++;
          $zapi = $entry->children($namespaces['zapi']); 
          $key  = (string)$zapi->key; 
          $keys[$key] = $key;
        }
      }
    }
    return $keys;
  }
  /**
   * Return a structured array with sub-collections nested underneath their parents
   */
  public function getCollectionHierarchy() {
    $collections = array();
    foreach ($this->collectionsPages as $collectionsPage) {      
      $simple_xml = simplexml_load_string($collectionsPage);
      if (is_object($simple_xml)) {
        $namespaces = $simple_xml->getNameSpaces(true);        
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
            //The - $collections[$collection['key']] - Syntax is important here because '$collection' is not updated by PHP
            $collections[$parent]['children'][$collection['key']] = $collections[$collection['key']];
            //Remove collection now that we've copied it under its parent
            unset($collections[$collection['key']]);
          }
        }
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
      $matches = array();
      preg_match('#collections/(.*)#', $link, $matches);
      $collection_key = isset($matches[1]) ? $matches[1] : FALSE;
      return $collection_key;
    }
  }
  /**
   *  Add one of the Items pages retrieved from Zotero
   */
  public function addItemsPage($page) {    
    $this->itemsPages[] = $page;
  }

  /**
   * Set the XML for the collections page retrieve from Zotero
   */
  public function setCollectionsPage($page) {
    if (is_array($page)) {
      $this->collectionsPages = array_merge($this->collectionsPages, $page);
    }
    else {
      $this->collectionsPages[] = $page_xml;
    }
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
    $config = $source->getConfigFor($this);
    $result = new FeedsZoteroHTTPFetcherResult($config['source']);
    if ($config['fetch_collections'] && arg(2) != 'edit') {
      $this->getCollections($source, $result, $config['collection_key']);
      $collection_keys = $result->getCollectionKeys();    
      foreach ($collection_keys as $key) { 
        $pages = $this->fetchPages(array('account_type' => $config['zotero_type'], 'account_id' => $config['zotero_id'], 
                                         'start' => $config['next_index'], 'source' => 'collection', 'source_key' => $key));
        $url   = $this->formatUrl(array('account_type' => $config['zotero_type'], 'account_id' => $config['zotero_id'], 
                                         'start' => $config['next_index'], 'source' => 'collection', 'source_key' => $key));
        $result->addItemsPage(array('collection_key' => $key, 'page' => $pages));
      }
      //Get top-level items not in any collection
      $pages = $this->fetchPages(array('account_type' => $config['zotero_type'], 'account_id' => $config['zotero_id'], 'start' => $config['next_index'], 'top' => TRUE));
      $result->addItemsPage(array('collection_key' => NULL, 'page' => $pages));

    }
    else {
      $pages = $this->fetchPages(array('account_type' => $config['zotero_type'], 'account_id' => $config['zotero_id'], 'start' => $config['next_index']));
      $result->addItemsPage(array('collection_key' => NULL, 'page' => $pages));
    }
    return $result;
  }
  /** 
   *  Retrieve XML Pages from Zotero's API
   *
   *  @params - an associative array or parameters
   *    $account_type - either group or user
   *    $account_id - the id of the zotero account to retrieve from
   *    $source - Only set if you want to retrive from specific source such as retrieving all sub-collections or items from a collection
   *    $source_key - the key of the above target
   *    $target - the type of object to fetch, defaults to items
   *    $start - the index at which to start retrieving items
   *    $top - fetch only top level items
   *    $limit - the number of items to fetch
   */
  public function fetchPages($params) {
    extract($params);
    $items_fetched = 0;
    if (!isset($limit)) {
      $limit = 0;
    }
    $no_limit = (!isset($limit) || $limit == 0);
    $count = 0;
    $items_pages = array();
    $index = isset($index) ? $index : 0;
    while ($items_fetched < $limit || $no_limit) {
      $last_index = $index;
      $url = $this->formatUrl($params);
      watchdog('biblio_zotero', $url);
      $page = $this->fetchURL($url);
      $pages[] = $page;
      $next_index = $this->getNextIndex($page);
      $params['start'] = $next_index;
      $items_fetched = $index - $last_index;
      if (!$next_index) {
        //No items left to fetch, exit loop
        break;
      }
    }
    return $pages;
  }
  
  public function getCollections(FeedsSource $source, &$result, $collection_key = NULL) {
    $config = $source->getConfigFor($this);
    $account_type = $config['zotero_type'] == 'group' ? 'groups' : 'users';
    $next_index = 0;
    $xml = '';
    $page = array();
    $top = $collection_key ? FALSE : TRUE;
    //TODO: Allow import from specific collection
    $pages = $this->fetchPages(array('account_type' => $account_type, 'account_id' => $config['zotero_id'],  
                                     'target' => 'collections', $start => $config['next_index'], 'source_key' => $collection_key));
    $result->setCollectionsPage($pages);

    return $pages;
  }

  /** 
   *  format a url for fetching items from zotero
   *  @params - an associative array or parameters
   *    $account_type - either group or user
   *    $account_id - the id of the zotero account to retrieve from
   *    $source - if specified, will retrieve from a specific location - i.e. collections or searches
   *    $source_key - the key of the above target
   *    $target - the type of object to fetch, defaults to items
   *    $start - the index at which to start retrieving items
   *    $top - fetch only top level items
   */
  public function formatUrl($params) {
    extract($params);
    if (!isset($target)) {
      $target = 'items';
    }
    if (!isset($start) || !$start) {
      $start = 0;
    }
    if (isset($account_type) && $account_type == 'user') {
      $account_type = 'users';
    }   
    if (isset($account_type) && $account_type == 'group') {
      $account_type = 'groups';
    }   
    if (isset($source) && $source == 'collection') {
      $source = 'collections';
    }   

    $url = "https://api.zotero.org/$account_type/$account_id";

    if (isset($source) && $source) {
      $url .= "/$source";
    }
    if (isset($source_key) && $source_key) {
      $url .= "/$source_key";
    }
    $url .= "/$target";
    if (isset($top) && $top) {
      $url .= "/top";
    }
    $url .= '?start='. $start;
    $url .= '&content=json';

    return $url;
        
  }

  public function fetchURL($url) {
    feeds_include_library('http_request.inc', 'http_request');
    $result = http_request_get($url, NULL, NULL, NULL, $this->timeout);
    if (!in_array($result->code, array(200, 201, 202, 203, 204, 205, 206))) {
      throw new Exception(t('Download of @url failed with code !code.', array('@url' => $url, '!code' => $result->code)));
    }
    
    return $result->data;
  }

  /**
   *  Parses XML response from Zotero to return the numeric index for the next request
   */
  private function getNextIndex($xml) {
    $feed_simple_xml = simplexml_load_string($xml);    

    if (is_object($feed_simple_xml)) {
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
