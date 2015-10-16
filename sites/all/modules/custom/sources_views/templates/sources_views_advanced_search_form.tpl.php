<section id="sources-search" role="search" class="fancytree-processed">
  <section class="input-section">
    <div class="search-group">
      <div class="input-group views-exposed-widgets" id="searcharea">
        <?php print render($form['advanced_search_api_views_fulltext']); ?>
        <span class="input-group-btn">
          <button type="button" class="btn btn-default" id="searchbutton"><span class="icon"></span></button>
          <button type="reset" class="btn searchreset"><span class="icon"></span></button>
        </span>
      </div>
    </div>
    <div class="selected-filter">
      <span class="source-type-selected-filter"></span>
      <span class="field-selected-filter"></span>
      <span class="year-selected-filter"></span>
    </div>
  </section>
  <section class="view-section">
    <ul class="nav nav-tabs">
      <li class="treeview"><a href=".treeview" data-toggle="tab" aria-expanded="true"><span class="icon shanticon-tree"></span>Browse</a></li>
      <li class="listview active"><a href=".listview" data-toggle="tab" aria-expanded="false"><span class="icon shanticon-list"></span>Preferences</a></li>
    </ul>
    <div class="tab-content">
      <!-- TAB - tree view -->
      <div class="treeview tab-pane">
        <div class="taxonomy-list-tree"></div>
      </div>
      <!-- TAB - list view -->
      <div class="listview tab-pane active">
        <?php print drupal_render_children($form); ?>
      </div>
    </div>
  </section>
</section>

