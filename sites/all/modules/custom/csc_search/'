<?php

/**
 * @file
 * Provide views handlers and plugins that allow usage of PHP.
 */

/**
 * Implements hook_views_data().
 */
function csc_search_views_data() {
  $data['views']['csc_search'] = array(
    'title' => t('CSC Search'),
    'help' => t('Custom CSC Search Functionality'),
    'field' => array(
      'help' => t('CSC Search field'),
      'handler' => 'csc_search_handler_field',
    ),
  );
  return $data;
}
