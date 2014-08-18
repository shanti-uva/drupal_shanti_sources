/**
 * @file
 * Custom javascript functionalities for CSC custom views custom sort.
 */
(function ($) {
Drupal.behaviors.cscViewsCustomSort = {
  attach: function (context, settings) {
    // Default custom sort state
    var sort_by = $('#edit-sort-by').val();
    var sort_order = $('#edit-sort-order').val();
    switch (sort_by) { 
      case 'sort_stripped_node_title':
        var default_sort_value = (sort_order == 'ASC') ? 'title_asc' : 'title_desc';
        break;
      case 'sort_biblio_author':
        var default_sort_value = (sort_order == 'ASC') ? 'author_asc' : 'author_desc';
        break;
      case 'sort_custom_publication_year':
        var default_sort_value = (sort_order == 'ASC') ? 'year_asc' : 'year_desc';
        break;
    }
    $('#edit-custom-sort').find('option[value="' + default_sort_value + '"]').attr('selected',true);
    // Update hidden sort field values based on the selected value of custom sort field.
    $('#edit-custom-sort').change(function() {
      switch ($(this).val()) {
        case 'title_asc':
          update_sort_field('sort_stripped_node_title', 'ASC');
          break;
        case 'title_desc':
          update_sort_field('sort_stripped_node_title', 'DESC');
          break;
        case 'author_asc':
          update_sort_field('sort_biblio_author', 'ASC');
          break;
        case 'author_desc':
          update_sort_field('sort_biblio_author', 'DESC');  
          break;
        case 'year_asc':
          update_sort_field('sort_custom_publication_year', 'ASC');
          break;
        case 'year_desc':
          update_sort_field('sort_custom_publication_year', 'DESC');
          break;
        case 'default':
          update_sort_field('sort_stripped_node_title', 'ASC');  
          break;
      }
    });
    // Custom sort text display
    $('select').change(function(){
      var selected_option = $(this).find(':selected').text();
      if ($(this).attr('id') == 'edit-custom-sort' && $(this).val() != 'default') {
        var group = $(this.options[this.selectedIndex]).closest('optgroup').prop('label');
        $(this).next('.holder').text('Sort by ' + group + ':  ' + selected_option);
      }
      else {
        $(this).next('.holder').text(selected_option);
      }
    }).trigger('change');
    // Update sort fields
    function update_sort_field(sort_type, sort_value) {
      if ($('#edit-sort-by').val() != sort_type || $('#edit-sort-order').val() != sort_value) {
        var sort_path = window.location.href;
        var new_sort_string = '&sort_by=' + sort_type + '&sort_order=' +  sort_value;
        if ($.get_query_string_val('sort_by') && $.get_query_string_val('sort_order')) {
          var old_sort_string = '&sort_by=' + $.get_query_string_val('sort_by') + '&sort_order=' + $.get_query_string_val('sort_order');
          var new_sort_path = sort_path.replace(old_sort_string, new_sort_string);
        }
        else {
          var new_sort_path = sort_path + new_sort_string;
        }
        window.location.replace(new_sort_path);
      }
    }
  }
};
})(jQuery);
