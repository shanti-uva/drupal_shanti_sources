<?php
/**
 * Returns auto complete search values for content titles with info
 */
function biblio_title_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  if (!empty($string) && strlen($string) >= 3) {
    $titles = db_query_range('SELECT n.title, n.nid, y.value FROM {node} as n LEFT JOIN {search_api_db_database_node_index_biblio_year} as y ON n.nid = y.item_id WHERE n.title LIKE :value ORDER BY title ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($titles->rowCount() != 0) {
      // Load views for biblio full content
      $biblio_full_results = csc_views_get_views_results('biblio_search_api', 'biblio_full');
      foreach ($titles as $title_key => $node) {
        $title_authors = db_query_range('SELECT value FROM {search_api_db_database_node_index_biblio_authors} WHERE item_id = :nid', 0, 3, array(':nid' => $node->nid));
        $title_author = '';
        // Attach current biblio item page
        foreach ($biblio_full_results as $biblio_full_result_key => $value) {
          if ($value->entity == $node->nid) $current_page = $biblio_full_result_key;
        }
        // Attach authors
        foreach ($title_authors as $author_data_key => $author_data) {
          $title_author .= ($author_data_key != 0) ? ', ' . $author_data->value : $author_data->value;
        }
        // Attach publication year
        $year = ($node->value != 0) ? '(' . $node->value . ')': '';
        $matches['node=' . $node->nid . '=' . $current_page] = ($title_key == 0) ? '<span class="result-item-type title-group-label">' . t('Titles') . '</span><span class="title-group">' . $node->title . ' ' . $year . '<br/>' . $title_author . '</span>' : '<span class="title-group">' . $node->title . ' ' . $year . '<br/>' . $title_author . '</span>';
      }
    }
    $authors = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_authors} WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($authors->rowCount() != 0) {
      foreach ($authors as $author_key => $author) {
        $matches['author=' . $author->value] = ($author_key == 0) ? '<span class="result-item-type authors-group-label">' . t('Authors') . '</span><span class="authors-group">' . $author->value . '</span>' : '<span class="authors-group">' . $author->value . '</span>';
      }
    }
    $publishers = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_publisher} WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($publishers->rowCount() != 0) {
      foreach ($publishers as $publisher_key => $publisher) {
        $matches['publisher=' . $publisher->value] = ($publisher_key == 0) ? '<span class="result-item-type publishers-group-label">' . t('Publishers') . '</span><span class="publishers-group">' . $publisher->value . '</span>' : '<span class="publishers-group">' . $publisher->value . '</span>';
      }
    }
    $placed_published = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_place_published} WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($placed_published->rowCount() != 0) {
      foreach ($placed_published as $placed_published_key => $place) {
        $matches['publishplace=' . $place->value] = ($placed_published_key == 0) ? '<span class="result-item-type place_published-group-label">' . t('Place of Publication') . '</span><span class="place-published-group">' . $place->value . '</span>' : '<span class="place-published-group">' . $place->value . '</span>';
      }
    }
    $zotero_vocabulary = taxonomy_vocabulary_machine_name_load('zotero_tags');
    $vid = $zotero_vocabulary->vid;
    $tags = db_query_range('SELECT name, tid FROM {taxonomy_term_data} WHERE name LIKE :name and vid = :vid_val ORDER BY name ASC', 0, 3, array(':name' => db_like($string) . '%', ':vid_val' => $vid));
    if ($tags->rowCount() != 0) {
      foreach ($tags as $tag_key => $tag) {
        $matches['tag=' . $tag->tid] = ($tag_key == 0) ? '<span class="result-item-type tags-group-label">' . t('Tags') . '</span><span class="tags-group">' . $tag->name . '</span>' : '<span class="tags-group">' . $tag->name . '</span>';
      }
    }
  }
  drupal_json_output($matches);
}



/**
 * Returns auto complete search values for plain titles
 */
function biblio_plain_title_list_callback($string = '') {
  $string = ucfirst($string);
  $matches = array();
  // Load views for biblio full content
  $biblio_full_results = csc_views_get_views_results('biblio_search_api', 'biblio_full');
  if (!empty($string) && strlen($string) >= 3) {
    $titles = db_query_range('SELECT title, nid FROM {node} WHERE title LIKE :value ORDER BY title ASC', 0, 3, array(':value' => db_like($string) . '%'));
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
    $authors = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_authors} WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => '%'. db_like($string) . '%'));
    if ($authors->rowCount() != 0) {
      foreach ($authors as $author_key => $author) {
        $matches[$author->value] = '<span class="authors-group">' . $author->value . '</span>';
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
    $publishers = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_publisher} WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($publishers->rowCount() != 0) {
      foreach ($publishers as $publisher_key => $publisher) {
        $matches[$publisher->value] = '<span class="publishers-group">' . $publisher->value . '</span>';
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
    $placed_published = db_query_range('SELECT DISTINCT value FROM {search_api_db_database_node_index_biblio_place_published} WHERE value LIKE :value ORDER BY value ASC', 0, 3, array(':value' => db_like($string) . '%'));
    if ($placed_published->rowCount() != 0) {
      foreach ($placed_published as $placed_published_key => $place) {
        $matches[$place->value] = '<span class="place-published-group">' . $place->value . '</span>';
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
    $tags = db_query_range('SELECT name, tid FROM {taxonomy_term_data} WHERE name LIKE :name and vid = :vid_val ORDER BY name ASC', 0, 3, array(':name' => db_like($string) . '%', ':vid_val' => $vid));
    if ($tags->rowCount() != 0) {
      foreach ($tags as $tag_key => $tag) {
        $matches[$tag->tid] = '<span class="tags-group">' . $tag->name . '</span>';
      }
    }
  }
  drupal_json_output($matches);
}

function csc_views_exposed_filter_validation($form, &$form_state) {
  if ($form_state['values']['biblio_year'] > $form_state['values']['biblio_year_1']) {
    form_set_error('biblio_year', '"From" year value should be lower than "To" year value');
  }
  if ($form_state['values']['biblio_year_1'] < $form_state['values']['biblio_year']) {
    form_set_error('biblio_year_1', '"To" year value should be higher than "From" year value');
  }
}

