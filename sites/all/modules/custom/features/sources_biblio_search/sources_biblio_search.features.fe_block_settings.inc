<?php
/**
 * @file
 * sources_biblio_search.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function sources_biblio_search_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['explore_menu-explore_menu_block'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'explore_menu_block',
    'module' => 'explore_menu',
    'node_types' => array(),
    'pages' => '',
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
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['sources_views-advanced_search_filter'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'advanced_search_filter',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => '',
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
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -19,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  $export['sources_views-custom_sort_filter'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'custom_sort_filter',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => 'sources-search',
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
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -19,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['sources_views-custom_taxonomy_breadcrumb'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'custom_taxonomy_breadcrumb',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => 'sources-search
sources-search/biblio',
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
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'banner',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 1,
  );

  $export['sources_views-fancytree_taxonomy_block'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'fancytree_taxonomy_block',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => '<front>',
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
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -18,
      ),
    ),
    'title' => 'Browse',
    'visibility' => 1,
  );

  $export['sources_views-fancytree_taxonomy_flyout_block'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'fancytree_taxonomy_flyout_block',
    'module' => 'sources_views',
    'node_types' => array(),
    'pages' => '',
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
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => 'search_flyout',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -19,
      ),
    ),
    'title' => '',
    'visibility' => 0,
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
      'responsive_bartik' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'responsive_bartik',
        'weight' => -11,
      ),
      'sources_theme' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'sources_theme',
        'weight' => -17,
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
      'responsive_bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'responsive_bartik',
        'weight' => -11,
      ),
      'sources_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'sources_theme',
        'weight' => 0,
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
      'responsive_bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'responsive_bartik',
        'weight' => 0,
      ),
      'sources_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'sources_theme',
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
      'responsive_bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'responsive_bartik',
        'weight' => -12,
      ),
      'sources_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'sources_theme',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  return $export;
}
