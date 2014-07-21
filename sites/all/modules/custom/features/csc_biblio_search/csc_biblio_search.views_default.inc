<?php
/**
 * @file
 * csc_biblio_search.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function csc_biblio_search_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'biblio_search_api';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_database_node_index';
  $view->human_name = 'biblio_search_api';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Contemplative Science Bibliography';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Indexed Node: Zotero Collections */
  $handler->display->display_options['relationships']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['relationships']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['relationships']['field_zotero_collections']['field'] = 'field_zotero_collections';
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['exclude'] = TRUE;
  /* Field: Indexed Node: biblio_year */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '[biblio_year].';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['empty_zero'] = TRUE;
  /* Field: Indexed Node: biblio_publisher */
  $handler->display->display_options['fields']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['exclude'] = TRUE;
  /* Field: citation */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'citation';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[biblio_authors] [biblio_year] [title] [biblio_publisher]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: biblio_abst_e */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['label'] = '';
  $handler->display->display_options['fields']['biblio_abst_e']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Zotero Tags */
  $handler->display->display_options['fields']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_tags']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_tags']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_tags']['bypass_access'] = 0;
  /* Field: Indexed Node: Zotero Collections */
  $handler->display->display_options['fields']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_collections']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_collections']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_collections']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_collections']['bypass_access'] = 0;
  /* Field: linebreak */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'linebreak';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<br>';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Sort criterion: Broken/missing handler */
  $handler->display->display_options['sorts']['author']['id'] = 'author';
  $handler->display->display_options['sorts']['author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['author']['field'] = 'author';
  $handler->display->display_options['sorts']['author']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['author']['expose']['label'] = 'Author';
  /* Sort criterion: Indexed Node: Date created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'biblio' => 'biblio',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'input_required';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Clear';
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'panopoly_wysiwyg_text';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No results';
  $handler->display->display_options['empty']['area']['format'] = 'panopoly_wysiwyg_text';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Indexed Node: Zotero Collections */
  $handler->display->display_options['relationships']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['relationships']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['relationships']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Indexed Node: biblio_year */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '([biblio_year])';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['link_to_entity'] = 0;
  /* Field: Indexed Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] [biblio_year]';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Field: Indexed Node: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['link_to_entity'] = 0;
  /* Field: Indexed Node: biblio_publisher */
  $handler->display->display_options['fields']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['fields']['biblio_publisher']['exclude'] = TRUE;
  /* Field: Indexed Node: biblio_place_published */
  $handler->display->display_options['fields']['biblio_place_published']['id'] = 'biblio_place_published';
  $handler->display->display_options['fields']['biblio_place_published']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_place_published']['field'] = 'biblio_place_published';
  $handler->display->display_options['fields']['biblio_place_published']['label'] = '';
  $handler->display->display_options['fields']['biblio_place_published']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_place_published']['link_to_entity'] = 0;
  /* Field: citation */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'citation';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[biblio_authors] [biblio_year] [title] [biblio_publisher]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: biblio_abst_e */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['label'] = '';
  $handler->display->display_options['fields']['biblio_abst_e']['element_label_colon'] = FALSE;
  /* Field: Indexed Node: Zotero Tags */
  $handler->display->display_options['fields']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['fields']['field_zotero_tags']['label'] = '';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_zotero_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_tags']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_tags']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_tags']['bypass_access'] = 0;
  /* Field: Indexed Node: Zotero Collections */
  $handler->display->display_options['fields']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['fields']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['fields']['field_zotero_collections']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_collections']['element_label_type'] = 'strong';
  $handler->display->display_options['fields']['field_zotero_collections']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_zotero_collections']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['field_zotero_collections']['view_mode'] = 'full';
  $handler->display->display_options['fields']['field_zotero_collections']['bypass_access'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Indexed Node: Sorting Stripped Node Title */
  $handler->display->display_options['sorts']['sort_stripped_node_title']['id'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['field'] = 'sort_stripped_node_title';
  $handler->display->display_options['sorts']['sort_stripped_node_title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_stripped_node_title']['expose']['label'] = 'Stripped Node Title';
  /* Sort criterion: Indexed Node: Sorting Biblio Author */
  $handler->display->display_options['sorts']['sort_biblio_author']['id'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_biblio_author']['field'] = 'sort_biblio_author';
  $handler->display->display_options['sorts']['sort_biblio_author']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_biblio_author']['expose']['label'] = 'Biblio Author';
  /* Sort criterion: Indexed Node: Sorting Custom Publication Year */
  $handler->display->display_options['sorts']['sort_custom_publication_year']['id'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['field'] = 'sort_custom_publication_year';
  $handler->display->display_options['sorts']['sort_custom_publication_year']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['sort_custom_publication_year']['expose']['label'] = 'Custom Publication Year';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group'] = 1;
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['search_api_views_fulltext']['fields'] = array(
    'title' => 'title',
    'search_text_biblio_author' => 'search_text_biblio_author',
    'search_text_biblio_publisher' => 'search_text_biblio_publisher',
    'search_text_biblio_publish_place' => 'search_text_biblio_publish_place',
    'search_text_biblio_abstract' => 'search_text_biblio_abstract',
    'search_text_zotero_tags' => 'search_text_zotero_tags',
  );
  /* Filter criterion: Indexed Node: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'biblio' => 'biblio',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Indexed Node: Zotero Collections */
  $handler->display->display_options['filters']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['value'] = array();
  $handler->display->display_options['filters']['field_zotero_collections']['group'] = 1;
  $handler->display->display_options['filters']['field_zotero_collections']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['operator_id'] = 'field_zotero_collections_op';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['operator'] = 'field_zotero_collections_op';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['identifier'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_zotero_collections']['expose']['reduce'] = 0;
  /* Filter criterion: Indexed Node: Publication Type */
  $handler->display->display_options['filters']['biblio_publication_type']['id'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_publication_type']['field'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['group'] = 1;
  $handler->display->display_options['filters']['biblio_publication_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['operator_id'] = 'biblio_publication_type_op';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['label'] = 'Source Type';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['operator'] = 'biblio_publication_type_op';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['identifier'] = 'biblio_publication_type';
  $handler->display->display_options['filters']['biblio_publication_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_authors */
  $handler->display->display_options['filters']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['group'] = 1;
  $handler->display->display_options['filters']['biblio_authors']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_authors']['expose']['operator_id'] = 'biblio_authors_op';
  $handler->display->display_options['filters']['biblio_authors']['expose']['label'] = 'Authors';
  $handler->display->display_options['filters']['biblio_authors']['expose']['operator'] = 'biblio_authors_op';
  $handler->display->display_options['filters']['biblio_authors']['expose']['identifier'] = 'biblio_authors';
  $handler->display->display_options['filters']['biblio_authors']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_publisher */
  $handler->display->display_options['filters']['biblio_publisher']['id'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_publisher']['field'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['group'] = 1;
  $handler->display->display_options['filters']['biblio_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_publisher']['expose']['operator_id'] = 'biblio_publisher_op';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['label'] = 'Publishers';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['operator'] = 'biblio_publisher_op';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['identifier'] = 'biblio_publisher';
  $handler->display->display_options['filters']['biblio_publisher']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: biblio_place_published */
  $handler->display->display_options['filters']['biblio_place_published']['id'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_place_published']['field'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['group'] = 1;
  $handler->display->display_options['filters']['biblio_place_published']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_place_published']['expose']['operator_id'] = 'biblio_place_published_op';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['label'] = 'Location';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['operator'] = 'biblio_place_published_op';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['identifier'] = 'biblio_place_published';
  $handler->display->display_options['filters']['biblio_place_published']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Zotero Tags */
  $handler->display->display_options['filters']['field_zotero_tags']['id'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['field_zotero_tags']['field'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['group'] = 1;
  $handler->display->display_options['filters']['field_zotero_tags']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['operator_id'] = 'field_zotero_tags_op';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['operator'] = 'field_zotero_tags_op';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['identifier'] = 'field_zotero_tags';
  $handler->display->display_options['filters']['field_zotero_tags']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text biblio authors */
  $handler->display->display_options['filters']['search_text_biblio_author']['id'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_author']['field'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_author']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['operator_id'] = 'search_text_biblio_author_op';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['operator'] = 'search_text_biblio_author_op';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['identifier'] = 'search_text_biblio_author';
  $handler->display->display_options['filters']['search_text_biblio_author']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text abstract */
  $handler->display->display_options['filters']['search_text_biblio_abstract']['id'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['field'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_abstract']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['operator_id'] = 'search_text_biblio_abstract_op';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['label'] = 'Abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['operator'] = 'search_text_biblio_abstract_op';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['identifier'] = 'search_text_biblio_abstract';
  $handler->display->display_options['filters']['search_text_biblio_abstract']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text publish place */
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['id'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['field'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['operator_id'] = 'search_text_biblio_publish_place_op';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['label'] = 'Publish place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['operator'] = 'search_text_biblio_publish_place_op';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['identifier'] = 'search_text_biblio_publish_place';
  $handler->display->display_options['filters']['search_text_biblio_publish_place']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text publisher */
  $handler->display->display_options['filters']['search_text_biblio_publisher']['id'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['field'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['group'] = 1;
  $handler->display->display_options['filters']['search_text_biblio_publisher']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['operator_id'] = 'search_text_biblio_publisher_op';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['label'] = 'Publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['operator'] = 'search_text_biblio_publisher_op';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['identifier'] = 'search_text_biblio_publisher';
  $handler->display->display_options['filters']['search_text_biblio_publisher']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Indexed Node: Search text zotero tags */
  $handler->display->display_options['filters']['search_text_zotero_tags']['id'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['search_text_zotero_tags']['field'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['group'] = 1;
  $handler->display->display_options['filters']['search_text_zotero_tags']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['operator_id'] = 'search_text_zotero_tags_op';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['operator'] = 'search_text_zotero_tags_op';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['identifier'] = 'search_text_zotero_tags';
  $handler->display->display_options['filters']['search_text_zotero_tags']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Publish Year Start */
  $handler->display->display_options['filters']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['ui_name'] = 'Publish Year Start';
  $handler->display->display_options['filters']['biblio_year']['operator'] = '>=';
  $handler->display->display_options['filters']['biblio_year']['group'] = 2;
  $handler->display->display_options['filters']['biblio_year']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_year']['expose']['operator_id'] = 'biblio_year_op';
  $handler->display->display_options['filters']['biblio_year']['expose']['operator'] = 'biblio_year_op';
  $handler->display->display_options['filters']['biblio_year']['expose']['identifier'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['biblio_year']['group_info']['label'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['group_info']['identifier'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['biblio_year']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Publish Year End */
  $handler->display->display_options['filters']['biblio_year_1']['id'] = 'biblio_year_1';
  $handler->display->display_options['filters']['biblio_year_1']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['biblio_year_1']['field'] = 'biblio_year';
  $handler->display->display_options['filters']['biblio_year_1']['ui_name'] = 'Publish Year End';
  $handler->display->display_options['filters']['biblio_year_1']['operator'] = '<=';
  $handler->display->display_options['filters']['biblio_year_1']['group'] = 2;
  $handler->display->display_options['filters']['biblio_year_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['biblio_year_1']['expose']['operator_id'] = 'biblio_year_1_op';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['operator'] = 'biblio_year_1_op';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['identifier'] = 'biblio_year_1';
  $handler->display->display_options['filters']['biblio_year_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['path'] = 'csc-search';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $export['biblio_search_api'] = $view;

  return $export;
}
