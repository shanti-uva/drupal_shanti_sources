/**
 * @file
 * Custom javascript functionalities for CSC custom views module.
 */
(function ($) {
  $(document).ready(function () {
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
    function update_sort_field(sort_type, sort_value) {
      $('#edit-sort-by').find('option[value="' + sort_type + '"]').attr('selected',true);
      $('#edit-sort-order').find('option[value="' + sort_value + '"]').attr('selected',true);
    }
  });
})(jQuery);