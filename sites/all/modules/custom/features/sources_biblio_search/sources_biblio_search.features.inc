<?php
/**
 * @file
 * sources_biblio_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sources_biblio_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function sources_biblio_search_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function sources_biblio_search_default_search_api_index() {
  $items = array();
  $items['solr_database_node_index'] = entity_import('search_api_index', '{
    "name" : "SOLR Database Node Index",
    "machine_name" : "solr_database_node_index",
    "description" : null,
    "server" : "csc_solr",
    "item_type" : "node",
    "options" : {
      "index_directly" : 0,
      "cron_limit" : "50",
      "fields" : {
        "nid" : { "type" : "integer" },
        "type" : { "type" : "string" },
        "title" : { "type" : "text", "boost" : "8.0" },
        "url" : { "type" : "uri" },
        "status" : { "type" : "boolean" },
        "created" : { "type" : "integer" },
        "author" : { "type" : "integer", "entity_type" : "user" },
        "biblio_authors" : { "type" : "list\\u003Cstring\\u003E" },
        "biblio_publisher" : { "type" : "string" },
        "biblio_place_published" : { "type" : "string" },
        "biblio_year" : { "type" : "integer" },
        "biblio_abst_e" : { "type" : "text" },
        "sort_biblio_author" : { "type" : "string" },
        "sort_stripped_node_title" : { "type" : "string" },
        "sort_custom_publication_year" : { "type" : "string" },
        "biblio_publication_type" : { "type" : "string" },
        "search_text_biblio_author" : { "type" : "text" },
        "search_text_biblio_publisher" : { "type" : "text" },
        "search_text_biblio_publish_place" : { "type" : "text" },
        "search_text_biblio_abstract" : { "type" : "text" },
        "search_text_zotero_tags" : { "type" : "text" },
        "field_zotero_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_zotero_collections" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_biblio_long_title" : { "type" : "text" },
        "field_biblio_long_language" : { "type" : "text" },
        "search_api_language" : { "type" : "string" },
        "search_api_url" : { "type" : "uri" },
        "search_api_viewed" : { "type" : "text" },
        "search_api_access_node" : { "type" : "list\\u003Cstring\\u003E" },
        "body:value" : { "type" : "text" },
        "body:summary" : { "type" : "text" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : { "default" : "0", "bundles" : { "biblio" : "biblio" } }
        },
        "search_api_alter_node_access" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : { "status" : 1, "weight" : "0", "settings" : { "mode" : "search_index" } },
        "search_api_alter_add_url" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_denormalized_entity_grouping" : {
          "status" : 0,
          "weight" : "0",
          "settings" : {
            "fields" : [],
            "group_sort" : "",
            "group_sort_direction" : "asc",
            "truncate" : 1,
            "group_limit" : "1"
          }
        },
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "biblio_abst_e" : true,
              "sort_stripped_node_title" : true,
              "search_text_biblio_author" : true,
              "search_text_biblio_publisher" : true,
              "search_text_biblio_publish_place" : true,
              "search_text_biblio_abstract" : true,
              "search_text_zotero_tags" : true,
              "field_biblio_long_title" : true,
              "field_biblio_long_language" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : { "title" : true, "sort_stripped_node_title" : true },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : { "title" : true },
            "spaces" : "[^\\\\p{L}\\\\p{N}^\\u0027\\u0022]",
            "ignorable" : "[-\\u0022\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 1,
          "weight" : "30",
          "settings" : {
            "fields" : { "title" : true, "sort_stripped_node_title" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}
