<?php
/**
 * @file
 * csc_biblio_search.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function csc_biblio_search_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['taxonomy_block-taxonomy_block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'taxonomy_block',
    'module' => 'taxonomy_block',
    'node_types' => array(),
    'pages' => 'csc-search*',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'responsive_bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'responsive_bartik',
        'weight' => -11,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['views-zotero_tags-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'zotero_tags-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'csc-search*',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'responsive_bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'responsive_bartik',
        'weight' => -12,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}
