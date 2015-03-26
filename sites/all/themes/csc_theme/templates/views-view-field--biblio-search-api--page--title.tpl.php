<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<div class="<?php print 'source-icon-' . $row->_entity_properties['biblio_publication_type']; ?> title-link-container">
  <?php
    $current_page = (!empty($_GET['page'])) ? intval($_GET['page']) : 0;
    $page = $view->row_index + (25 * $current_page);
    $query_strings = $_SERVER['QUERY_STRING'];
    parse_str($query_strings, $query_string_values);
    $parameters = array_replace($query_string_values, array('page' => $page));
    $year = (!empty($row->_entity_properties['biblio_year'])) ? '(' . $row->_entity_properties['biblio_year'] . ')' : '';
    $parameters['current_nid'] = $row->entity;
    $publication_type = (!empty($row->_entity_properties['entity object']->biblio_type_name)) ? $row->_entity_properties['entity object']->biblio_type_name . ':': '';
    print l($publication_type . ' '. $row->_entity_properties['title'] . ' ' . $year, 'csc-search/biblio', array('query' => $parameters));
  ?>
</div>