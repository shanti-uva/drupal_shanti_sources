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
    // Restrict input to numbers only
    $('#pager-input').keypress(function(key) {
      if(key.charCode < 48 || key.charCode > 57) return false;
    });
    // Auto submit pager value after delay
    var timer;
    $('#pager-input').on('keyup', function() {
      var text_search = 'search_api_views_fulltext='+ $('#edit-search-api-views-fulltext').val();
      var sort_order = '&sort_order=' + $('#edit-sort-order').val();
      var sort_type = '&sort_by=' + $('#edit-sort-by').val();
      var cutom_sort = '&custom_sort=' + $('#edit-custom-sort').val();
      var pager = ($(this).val() <= parseInt($('#max-page-input').val())) ? '&page=' + ($('#pager-input').val() - 1) : '&page=' + ($('#max-page-input').val() - 1);   
      clearInterval(timer);
      timer = setTimeout(function() {
        window.location.replace(window.location.href.split('?')[0] + '?' + text_search + sort_order + sort_type + cutom_sort + pager);
      }, 2000);
    });
  });
})(jQuery);