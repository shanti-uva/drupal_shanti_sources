<div class="detail-level-container">
  <span>Detail</span>
  <ul class="detail-level-option">
    <li><a id="short-detail" href="#">Short</a></li>
    <li><a id="medium-detail" class="active" href="#">Medium</a></li>
    <li><a id="long-detail" href="#">Long</a></li>
  </ul>
</div>
<div class="custom-sort-container">
  <select id="edit-custom-sort" name="custom_sort" class="form-select">
    <option value="default" selected="selected"><?php print t('Sort by'); ?></option>
    <optgroup label="Title">
      <option value="title_asc">A-Z</option>
      <option value="title_desc">Z-A</option>
    </optgroup>
    <optgroup label="Author">
      <option value="author_asc">A-Z</option>
      <option value="author_desc">Z-A</option>
    </optgroup>
    <optgroup label="Year">
      <option value="year_asc"><?php print $value['publish_year_asc']; ?></option>
      <option value="year_desc"><?php print $value['publish_year_desc']; ?></option>
    </optgroup>
  </select>
</div>