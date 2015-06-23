/**
 * @file
 * Custom javascript functionalities for CSC custom views autocomplete field.
 */
(function ($) {
Drupal.behaviors.sourcesViewsAutocomplete = {
  attach: function (context, settings) {
    console.log(this);
    var widget_elements = [
      'input#edit-advanced-search-api-views-fulltext',
      'input#edit-title',
      'input#edit-search-text-biblio-author',
      '#edit-search-text-biblio-publisher',
      '#edit-search-text-biblio-publish-place',
      '#edit-search-text-zotero-tags',
    ];

    var selector = widget_elements.join(', ');

    $(selector, context).bind('autocompleteSelect', function() {
      autocompleteRedirect(this);
    });

    $(selector, context).bind('keypress', function(e) {
      if (e.which == $.ui.keyCode.ENTER) {
        autocomplete_redirect(this);
      }
    });

    function autocomplete_redirect(autocomplete_element) {
      var autocomplete_value = $(autocomplete_element).val().split('=');
      var filter_type  = autocomplete_value[0];
      var filter_value = autocomplete_value[1];
      var filter_page  = autocomplete_value[2];
      var query_keys = {
        author: 'search_text_biblio_author',
        publisher: 'biblio_publisher',
        publishplace: 'biblio_place_published',
        tag: 'field_zotero_tags'
      }

      if (filter_type === 'node') {
        window.location.replace(location.protocol + '//' + location.host + '/sources-search/biblio?page=' + filter_page + '&current_nid=' + filter_value);
      }
      else {
        var query_key = query_keys[filter_type];
        var filter_path = location.protocol + '//' + location.host + location.pathname + '?' + query_key + '=' + query_value;
        window.location.replace(filter_path);
      }
      //clear the node=123 text that populates in the autocomplete filter
      $(selector).val('');
    }
  }
};



})(jQuery);


