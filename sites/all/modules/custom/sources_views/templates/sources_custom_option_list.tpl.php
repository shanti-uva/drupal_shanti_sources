<?php if ($option['key'] == 0): ?>
  <span class="result-item-type <?php print $option['type']; ?>-group-label"><?php print $option['header_label']; ?></span>
<?php endif; ?>
<span class="place-published-group">
  <?php print $option['value']; ?>
  <?php if (!empty(print $option['year'])): ?>
    <?php print ' ' . $option['year']; ?>
  <?php endif;?>
  <?php if (!empty(print $option['author'])): ?>
    <?php print '<br/>' . $option['author']; ?>
  <?php endif;?>
</span>


