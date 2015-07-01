<div id="tree" class="view-wrap">
  <ul class="ui-fancytree fancytree-container fancytree-ext-glyph">
    <?php foreach ($items as $link): ?>
      <li class="fancytree-lastsib">
        <?php print $link; ?>
      </li>
    <?php endforeach;?>
  </ul>
</div>