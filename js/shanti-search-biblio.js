(function ($) {
  Drupal.behaviors.shantiBiblio = {
    attach: function (context, settings) {
      $('#edit-advanced-search-api-views-fulltext-autocomplete').removeClass('autocomplete-processed');
      $('#edit-advanced-search-api-views-fulltext').keyup(function() {
        Drupal.behaviors.autocomplete.attach(document);
      });
    }
  };
})(jQuery);
