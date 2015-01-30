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

  $export['csc_views-custom_sort_filter'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'custom_sort_filter',
    'module' => 'csc_views',
    'node_types' => array(),
    'pages' => 'csc-search',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'csc_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'csc_theme',
        'weight' => -15,
      ),
      'responsive_bartik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'responsive_bartik',
        'weight' => -12,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['csc_views-custom_taxonomy_block'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'custom_taxonomy_block',
    'module' => 'csc_views',
    'node_types' => array(),
    'pages' => 'csc-search',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'csc_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'csc_theme',
        'weight' => -16,
      ),
      'responsive_bartik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'responsive_bartik',
        'weight' => -10,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['csc_views-custom_taxonomy_breadcrumb'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'custom_taxonomy_breadcrumb',
    'module' => 'csc_views',
    'node_types' => array(),
    'pages' => 'csc-search
csc-search/biblio',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'csc_theme' => array(
        'region' => 'banner',
        'status' => 1,
        'theme' => 'csc_theme',
        'weight' => -16,
      ),
      'responsive_bartik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'responsive_bartik',
        'weight' => -13,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['system-main'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'main',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'csc_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'csc_theme',
        'weight' => -13,
      ),
      'responsive_bartik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'responsive_bartik',
        'weight' => -11,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

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
      'csc_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'csc_theme',
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

  $export['views--exp-biblio_search_api-page'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-biblio_search_api-page',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'csc-search
csc-search/biblio',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'csc_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'csc_theme',
        'weight' => -14,
      ),
      'responsive_bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'responsive_bartik',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
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
      'csc_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'csc_theme',
        'weight' => 3,
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
