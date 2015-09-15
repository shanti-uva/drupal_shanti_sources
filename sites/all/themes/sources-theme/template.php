<?php

/**
 * @file
 * template.php
 */
 
 /**
  *   This is the template.php file for a child sub-theme of the Shanti Sarvaka theme.
  *   Use it to implement custom functions or override existing functions in the theme. 
  */ 

/**
 * Implements HOOK_breadcrumb
 * Customizes output of breadcrumbs
 */
function sources_theme_breadcrumb() {
  return sources_views_custom_breadcrumbs();
}

/**
 * Implements HOOK_preprocess_html().
 */
function sources_theme_preprocess_html(&$variables) {
  drupal_add_js('sites/all/libraries/cookie.js/jquery.cookie.js', 'file');
  if (!sources_theme_is_front_page()) {
    sources_theme_remove_front_page_class($variables);
  }
}

function sources_theme_is_front_page() {
  return (drupal_is_front_page() && !$_SERVER['QUERY_STRING']);
}

function sources_theme_remove_front_page_class(&$variables) {
  if (($key = array_search('front', $variables['classes_array'])) !== FALSE) {
    unset($variables['classes_array'][$key]);
  }
}

/**
 * Implements THEME_preprocess_views_view_fields().
 */
function sources_theme_preprocess_views_view_fields(&$vars) {
  if ($vars['view']->name == 'biblio_search_api') {
    $publication_year = (!empty($vars['row']->_entity_properties['biblio_year'])) ? $vars['row']->_entity_properties['biblio_year'] : '';
    $updated_query_string_parameters = sources_theme_get_updated_query_string_parameters($vars);
    $publication_format = sources_theme_get_publication_type($vars);
    $source_title_info = sources_theme_get_source_title_info($publication_year, $publication_format);
    $custom_title_link_wrapper_prefix = '<div class="source-icon-' . $publication_format . ' title-link-container"><span class="glyphicon shanticon-essays"></span>';
    $custom_title_link_wrapper_suffix = '</div>';
    //Display custom views field output based on current views display.
    switch ($vars['view']->current_display) {
      case 'page':
        $link = l($vars['row']->_entity_properties['title'] . $source_title_info, 'sources-search/biblio', array('query' => $updated_query_string_parameters, 'html' => TRUE));
        $vars['fields']['title']->content = $custom_title_link_wrapper_prefix . $link . $custom_title_link_wrapper_suffix;
        break;
      case 'biblio_full':
        $vars['fields']['biblio_publication_type_1']->content = '<span>' . $publication_format . '</span>';
        break;
    }
  }
}

/**
 * Returns query string parameters with updated node id and page number.
 *
 */
function sources_theme_get_updated_query_string_parameters($vars) {
  $current_page = (!empty($_GET['page'])) ? intval($_GET['page']) : 0;
  $new_page = $vars['view']->row_index + (25 * $current_page);
  $current_query_strings = $_SERVER['QUERY_STRING'];
  parse_str($current_query_strings, $parsed_current_query_strings);
  $parameters = array_replace($parsed_current_query_strings, array('page' => $new_page));
  $parameters['current_nid'] = $vars['row']->entity;
  return $parameters;
}

function sources_theme_get_publication_type($vars) {
  $publication_type_name = '';
  if (!empty($vars['row']->_entity_properties['biblio_publication_type'])) {
    $publication_type_id = $vars['row']->_entity_properties['biblio_publication_type'];
    $publication_type_name = db_query('SELECT name FROM {biblio_types} WHERE tid = :tid', array(':tid' => $publication_type_id))->fetchField();
  }
  return $publication_type_name;
}

/**
 * Returns source title with publication year and format.
 *
 */
function sources_theme_get_source_title_info($year, $publication_format) {
  if (!empty($publication_format)) {
    $publication_format = '<span class="publication-type">' . $publication_format . '</span>';
  }
  $publication_info = array($year, $publication_format);
  $source_title_info = '';
  $info_index = 1;
  foreach ($publication_info as $info) {
    if (!empty($info)) {
      if ($info_index > 1) {
        $source_title_info .= ', ' . $info;
      }
      else {
        $source_title_info .= $info;
      }
      $info_index++;
    }
  }
  $source_title_info = ' (' . $source_title_info . ')';
  return $source_title_info;
}
