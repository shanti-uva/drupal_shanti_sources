/**
 * @file
 * Custom javascript functionalities for CSC custom views autocomplete field.
 */
(function ($) {
Drupal.behaviors.cscViewsAutocomplete = {
  attach: function (context, settings) {
    // Show autocomplete search result
    $('input#edit-advanced-search-api-views-fulltext', context).bind('autocompleteSelect', function() {
      var autocomplete_value = $(this).val().split('=');
      var filter_type  = autocomplete_value[0];
      var filter_value = autocomplete_value[1];
      var filter_page = autocomplete_value[2];
      switch (filter_type) {
        case 'node':
          window.location.replace(location.protocol + '//' + location.host + '/csc-search/biblio?page=' + filter_page + '&current_nid=' + filter_value);
          break;
        case 'author':
          autocomplete_redirect('biblio_authors', filter_value);
          break;
        case 'publisher':
          autocomplete_redirect('biblio_publisher', filter_value);
          break;
        case 'publishplace':
          autocomplete_redirect('biblio_place_published', filter_value);
          break;
        case 'tag':
          autocomplete_redirect('field_zotero_tags', filter_value);
          break;
      }
      $('#edit-advanced-search-api-views-fulltext').val('');
    });
    // Redirect to selected auto complete search item
    function autocomplete_redirect(query_key, query_value) {
      var filter_path = location.protocol + '//' + location.host + location.pathname + '?' + query_key + '=' + query_value;
      window.location.replace(filter_path);
    }
  }
};
})(jQuery);
