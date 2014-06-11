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
  /* Sort criterion: Indexed Node: Author */
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
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'panopoly_wysiwyg_text';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  $handler->display->display_options['fields']['biblio_year']['link_to_entity'] = 0;
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
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
  /* Filter criterion: Indexed Node: Zotero Collections */
  $handler->display->display_options['filters']['field_zotero_collections']['id'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['table'] = 'search_api_index_database_node_index';
  $handler->display->display_options['filters']['field_zotero_collections']['field'] = 'field_zotero_collections';
  $handler->display->display_options['filters']['field_zotero_collections']['value'] = array();
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
  $handler->display->display_options['path'] = 'csc-search';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $export['biblio_search_api'] = $view;

  return $export;
}
