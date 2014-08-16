/**
 * @file
 * Custom javascript functionalities for CSC custom views autocomplete field.
 */
(function ($) {
Drupal.behaviors.cscViewsAutocomplete = {
  attach: function (context, settings) {
    // Show autocomplete search result
    $('input#edit-search-api-views-fulltext', context).bind('autocompleteSelect', function() {
      var autocomplete_value = $(this).val().split('=');
      switch (autocomplete_value[0]) {
        case 'node':
          window.location.replace(location.protocol + '//' + location.host + '/csc-search/biblio?page=' + autocomplete_value[2] + '&current_nid=' + autocomplete_value[1]);
          break;
        case 'author':
          autocomplete_redirect('biblio_authors', autocomplete_value[1]);
          break;
        case 'publisher':
          autocomplete_redirect('biblio_publisher', autocomplete_value[1]);
          break;
        case 'publishplace':
          autocomplete_redirect('biblio_place_published', autocomplete_value[1]);
          break;
        case 'tag':
          autocomplete_redirect('field_zotero_tags', autocomplete_value[1]);
          break;
      }
      $('#edit-search-api-views-fulltext').css('color', 'white');
    });
    // Redirect to selected auto complete search item
    function autocomplete_redirect(query_key, query_value) {
      var filter_path = location.protocol + '//' + location.host + location.pathname + '?' + query_key + '=' + query_value;
      window.location.replace(filter_path);
    }
  }
};
})(jQuery);
