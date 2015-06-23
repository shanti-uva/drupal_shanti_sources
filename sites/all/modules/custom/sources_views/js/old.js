/**
 * @file
 * Custom javascript functionalities for CSC custom views autocomplete field.
 */
(function ($) {
Drupal.behaviors.sourcesViewsAutocomplete = {
  attach: function (context, settings) {
    console.log(this);
    // Show autocomplete search result
    $('input#edit-advanced-search-api-views-fulltext, input#edit-title, input#edit-search-text-biblio-author, #edit-search-text-biblio-publisher, #edit-search-text-biblio-publish-place, #edit-search-text-zotero-tags', context).bind('autocompleteSelect', function() {
      var autocomplete_value = $(this).val().split('=');
      var filter_type  = autocomplete_value[0];
      var filter_value = autocomplete_value[1];
      var filter_page = autocomplete_value[2];
      switch (filter_type) {
        case 'node':
          window.location.replace(location.protocol + '//' + location.host + '/sources-search/biblio?page=' + filter_page + '&current_nid=' + filter_value);
          break;
        case 'author':
          autocomplete_redirect('search_text_biblio_author', filter_value);
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
      $('#edit-advanced-search-api-views-fulltext, input#edit-title, #edit-search-text-biblio-author, #edit-search-text-biblio-publisher, #edit-search-text-biblio-publish-place, #edit-search-text-zotero-tags').val('');
    });
    // Redirect to selected auto complete search item
    function autocomplete_redirect(query_key, query_value) {
      var filter_path = location.protocol + '//' + location.host + location.pathname + '?' + query_key + '=' + query_value;
      window.location.replace(filter_path);
    }
  }
};

function autocompleteRedirect() {

}


})(jQuery);


