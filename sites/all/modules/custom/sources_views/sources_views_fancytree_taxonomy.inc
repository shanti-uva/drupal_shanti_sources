<?php
/**
 * @file
 * Integrate taxonomy list with fancytree.
 *
 */

function sources_views_build_json_taxonomy_list() {
  $collection_vocabulary = taxonomy_vocabulary_machine_name_load('collections');
  $vocabulary_id = $collection_vocabulary->vid;
  $output = sources_views_get_taxonomy(sources_views_generate_taxonomy_tree($vocabulary_id, 0));
  drupal_json_output($output);
}

function sources_views_fancytree_taxonomy_list() {
  $all_sources_link = l(t('Sources'), 'sources-search', array(
    'attributes' => array('class' => array('collection-library')),
    'query' => array('field_zotero_collections' => 'All', 'view_mode' => 'collection')
  ));
  return theme('sources_fancytree_taxonomy', array('all_sources_link' => $all_sources_link)); 
}

function sources_views_search_flyout_fancytree_taxonomy_list() {
  return theme('sources_fancytree_taxonomy', array('all_sources_link' => NULL));
}

function sources_views_get_taxonomy($hierarchy) {
  $taxonomy_terms = array();
  foreach ($hierarchy as $term) {
    if (!empty($term->children)) {
      $taxonomy_terms[] = array('key' => $term->tid, 'title' => $term->name, 'children' => sources_views_get_taxonomy($term->children));
    }
    else {
      $taxonomy_terms[] = array('key' => $term->tid, 'title' => $term->name);
    }
  }
  return $taxonomy_terms;
}

function sources_views_generate_taxonomy_tree($vid, $parent = 0) {
  static $results;
  $args = func_get_args();
  $hash = md5(implode('-', $args));
  if (!isset($results[$hash])) {
    $terms = array();
    $data = taxonomy_get_tree($vid, $parent);
    foreach ($data as $term) {
      $terms[$term->tid] = $term;
    }
    $terms = sources_views_nest_taxonomy_term_list($terms, $parent);
    $results[$hash] = $terms;
  }
  return $results[$hash];
}

function sources_views_nest_taxonomy_term_list($terms, $parent) {
  foreach ($terms as $term) {
    $parent_tid = isset($term->parents[0]) ? $term->parents[0] : 0;
    if ($parent_tid) {
      if (isset($terms[$parent_tid])) {
        $terms[$parent_tid]->children[$term->tid] = $term;
        unset($terms[$term->tid]);
      }
      elseif ($parent_tid != $parent) {
        sources_views_nest_taxonomy_terms_child_list($terms, $parent_tid, $term);
        unset($terms[$term->tid]);
      }
    }
  }
  return $terms;
}

function sources_views_nest_taxonomy_terms_child_list(&$terms, $parent_tid, $child) {
  foreach ($terms as &$term) {
    if ($term->tid == $parent_tid) {
      $term->children[$child->tid] = $child;
      break;
    }
    elseif (!empty($term->children)) {
      sources_views_nest_taxonomy_terms_child_list($term->children, $parent_tid, $child);
    }
  }
}
