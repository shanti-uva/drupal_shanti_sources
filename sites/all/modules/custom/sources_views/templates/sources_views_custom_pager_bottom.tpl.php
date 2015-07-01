<div class="custom-pager">
  <div class="custom-pager-right">
    <ul class="pager">
      <li><?php print $value['first_page_link'] . ' ' . $value['prev_page_link']; ?></li>
      <li>Page</li>
      <li><input type="text" name="pager-input" id="pager-input" value="<?php print $value['current_page']; ?>"/></li>
      <li>OF</li>
      <li><?php print $value['max_page'] . ' ' . $value['next_page_link'] . ' ' . $value['last_page_link']; ?></li>
    </ul>
  </div>
  <input type="hidden" value="<?php print $value['max_page']; ?>" id="max-page-input">
</div>
<?php print $value['min_max_year']; ?>