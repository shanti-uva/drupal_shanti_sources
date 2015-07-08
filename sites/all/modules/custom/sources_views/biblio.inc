<?php
/**
 * Returns auto complete search values for content titles with info
 */
function biblio_title_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  if (!empty($string) && strlen($string) >= 3) {
    $titles = biblio_title_list_callback_query('titles', $string);
    $authors = biblio_title_list_callback_query('authors', $string);
    $publishers = biblio_title_list_callback_query('publishers', $string);
    $placed_published = biblio_title_list_callback_query('placed_published', $string);
    $zotero_vocabulary = taxonomy_vocabulary_machine_name_load('zotero_tags');
    $vid = $zotero_vocabulary->vid;
    $tags = biblio_title_list_callback_query('tags', $string, $vid);

    if ($titles->rowCount() != 0) {
      $biblio_full_results = sources_views_get_views_results('biblio_search_api', 'biblio_full');
      foreach ($titles as $title_key => $node) {
        $title_authors = biblio_title_authors($node->nid);
        $current_page = biblio_title_current_page($biblio_full_results, $node->nid);
        $publication_year = ($node->value != 0) ? '(' . $node->value . ')' : '';
        $matches['node=' . $node->nid . '=' . $current_page] = biblio_title_list_callback_option_output('titles', $title_key, $node->title, $publication_year, $title_authors);
      }
    }
    if ($authors->rowCount() != 0) {
      foreach ($authors as $author_key => $author) {
        $matches['author=' . $author->value] = biblio_title_list_callback_option_output('authors', $author_key, $author->value);
      }
    }
    if ($publishers->rowCount() != 0) {
      foreach ($publishers as $publisher_key => $publisher) {
        $matches['publisher=' . $publisher->value] = biblio_title_list_callback_option_output('publishers', $publisher_key, $publisher->value);
      }
    }
    if ($placed_published->rowCount() != 0) {
      foreach ($placed_published as $placed_published_key => $place) {
        $matches['publishplace=' . $place->value] = biblio_title_list_callback_option_output('placed_published', $placed_published_key, $place->value);
      }
    }
    if ($tags->rowCount() != 0) {
      foreach ($tags as $tag_key => $tag) {
        $matches['tag=' . $tag->tid] = biblio_title_list_callback_option_output('tags', $tag_key, $tag->name);
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * Returns list callback query.
 *
 * @param $query_type
 *   The type of query to return.
 *
 * @param $string
 *   The filter string to use on query.
 *
 * @return query result.
 */
function biblio_title_list_callback_query($query_type, $string, $vid = '') {
  switch ($query_type) {
    case 'titles':
      $query = db_query_range('SELECT n.title, n.nid, y.value FROM {node} as n
        LEFT JOIN {search_api_db_database_node_index_biblio_year} as y ON
        n.nid = y.item_id WHERE n.title LIKE :value ORDER BY title ASC',
        0, 3, array(':value' => db_like($string) . '%'));
      break;
    case 'authors':
      $query = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_authors}
        WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
      break;
    case 'publishers':
      $query = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_publisher}
        WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
      break;
    case 'placed_published':
      $query = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_place_published}
        WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
      break;
    case 'tags':
      $query = db_query_range('SELECT name, tid FROM {taxonomy_term_data} WHERE name
        LIKE :name and vid = :vid_val ORDER BY name ASC', 0, 3, array(':name' => db_like($string) . '%', ':vid_val' => $vid));
      break;
  }
  return $query;
}

/**
 * Returns author list based on node id.
 *
 * @param $nid
 *   Node id to be used on querying author list.
 *
 * @return list of author names.
 */
function biblio_title_authors($nid) {
  $title_authors = db_query_range('SELECT value FROM {search_api_db_database_node_index_biblio_authors}
    WHERE item_id = :nid', 0, 3, array(':nid' => $nid));
  $authors = '';
  foreach ($title_authors as $author_data_key => $author_data) {
    $authors .= ($author_data_key != 0) ? ', ' . $author_data->value : $author_data->value;
  }
  return $authors;
}

/**
 * Returns current page of sources result.
 *
 * @param $result
 *   Views result from full page biblio.
 *
 *
 * @return Current page value.
 */
function biblio_title_current_page($result, $nid) {
  foreach ($result as $biblio_full_result_key => $value) {
    if ($value->entity == $nid) {
      $current_page = $biblio_full_result_key;
      return $current_page;
    }
  }
}

/**
 * Returns html format of custom option output.
 *
 * @param $option_type
 *   Type of option to display.
 *
 * @param $key
 *   Array key value.
 *
 * @param $value
 *   Option value.
 *
 * @param $year
 *   Publication year value.
 *
 * @param $author
 *   Author names.
 * 
 * @return custom display output for option list.
 */
function biblio_title_list_callback_option_output($option_type, $key, $value, $year = '', $author = '') {
  switch ($option_type) {
    case 'titles':
      $header_label = t('Titles');
      break;
    case 'authors':
      $header_label = t('Authors');
      break;
    case 'publishers':
      $header_label = t('Publishers');
      break;
    case 'placed_published':
      $header_label = t('Place of Publication');
      break;
    case 'tags':
      $header_label = t('Tags');
      break;
  }
  $option_values = array(
    'type' => $option_type,
    'key' => $key,
    'value' => $value,
    'header_label' => $header_label,
  );
  if (!empty($year)) {
    $option_values = $option_values + array('year' => $year);
  }
  if (!empty($author)) {
    $option_values = $option_values + array('author' => $author);
  }
  return theme('sources_custom_option_list', array('option' => $option_values));
}

/**
 * Returns auto complete search values for plain titles
 */
function biblio_plain_title_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  // Load views for biblio full content
  $biblio_full_results = sources_views_get_views_results('biblio_search_api', 'biblio_full');
  if (!empty($string) && strlen($string) >= 3) {
    $titles = db_query_range('SELECT title, nid FROM {node} WHERE title LIKE :value
      ORDER BY title ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($titles->rowCount() != 0) {
      foreach ($titles as $title_key => $node) {
        // Attach current biblio item page
        foreach ($biblio_full_results as $biblio_full_result_key => $value) {
          if ($value->entity == $node->nid) $current_page = $biblio_full_result_key;
        }
        $matches['node=' . $node->nid . '=' . $current_page] = '<span class="title-group">' . $node->title . '</span>';
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * Returns auto complete search values for content authors
 */
function biblio_author_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  if (!empty($string) && strlen($string) >= 3) {
    $authors = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_authors}
      WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => '%' . db_like($string) . '%'));
    if ($authors->rowCount() != 0) {
      foreach ($authors as $author_key => $author) {
        $matches['author=' . $author->value] = '<span class="authors-group">' . $author->value . '</span>';
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * Returns auto complete search values for content publishers
 */
function biblio_publisher_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  if (!empty($string) && strlen($string) >= 3) {
    $publishers = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_publisher}
      WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($publishers->rowCount() != 0) {
      foreach ($publishers as $publisher_key => $publisher) {
        $matches['publisher=' . $publisher->value] = '<span class="publishers-group">' . $publisher->value . '</span>';
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * Returns auto complete search values for content published places
 */
function biblio_place_published_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  if (!empty($string) && strlen($string) >= 3) {
    $placed_published = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_place_published}
      WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($placed_published->rowCount() != 0) {
      foreach ($placed_published as $placed_published_key => $place) {
        $matches['publishplace=' . $place->value] = '<span class="place-published-group">' . $place->value . '</span>';
      }
    }
  }
  drupal_json_output($matches);
}

/**
 * Returns auto complete search values for content abstracts
 */
function biblio_tags_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  if (!empty($string) && strlen($string) >= 3) {
    $zotero_vocabulary = taxonomy_vocabulary_machine_name_load('zotero_tags');
    $vid = $zotero_vocabulary->vid;
    $tags = db_query_range('SELECT name, tid FROM {taxonomy_term_data} WHERE name
      LIKE :name and vid = :vid_val ORDER BY name ASC', 0, 3, array(':name' => db_like($string) . '%', ':vid_val' => $vid));
    if ($tags->rowCount() != 0) {
      foreach ($tags as $tag_key => $tag) {
        $matches['tag=' . $tag->tid] = '<span class="tags-group">' . $tag->name . '</span>';
      }
    }
  }
  drupal_json_output($matches);
}

