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
<?php if(!empty($row->_entity_properties['field_zotero_collections'])): ?>
  <ul>
    <?php
      $collections = $row->_entity_properties['field_zotero_collections'];
      end($collections);
      $last_key = key($collections);
      foreach($row->_entity_properties['field_zotero_collections'] as $key => $tid): ?>
      <?php $term = taxonomy_term_load($tid); ?>
      <?php $comma = ($key != $last_key) ? ', ': '';?>
      <li><?php print l($term->name . $comma, 'csc-search', array('query' => array('field_zotero_collections' => $tid))) . '&nbsp;'; ?></li>
    <?php endforeach;?>
  </ul>
<?php endif;?>