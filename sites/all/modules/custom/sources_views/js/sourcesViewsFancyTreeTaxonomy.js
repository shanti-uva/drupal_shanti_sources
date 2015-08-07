/**
 * @file
 * Custom javascript functionalities for CSC Fancy Tree Integration.
 */
(function ($) {
Drupal.behaviors.sourcesViewsFancyTreeInit = {
  attach: function (context, settings) {
    glyph_options = {
      map: {
        checkbox: "glyphicon glyphicon-unchecked",
        checkboxSelected: "glyphicon glyphicon-check",
        expanderClosed: "glyphicon glyphicon-plus-sign",
        expanderOpen: "glyphicon glyphicon-minus-sign",
      }
    };
    $('.tree').fancytree({
      source: {
        url: Drupal.settings.basePath + 'json/collection-list',
        cache: false
      },
      generateIds: true,
      radio: true,
      extensions: ['filter', 'glyph'],
      glyph: glyph_options,
      icons: false,
      idPrefix: '',
      init: function (event, data) {
        var taxonomyTermId = $.get_query_string_val('field_zotero_collections');
        $('.tree').fancytree('getTree').getNodeByKey(taxonomyTermId).setActive();
      },
      click: function (event, data) {
        var node = data.node;
        var type_of_clicked_element = $.ui.fancytree.getEventTargetType(event.originalEvent);
        if (type_of_clicked_element == 'title') {
          var term_id = node.key;
          redirect_to_collection_page(term_id);
        }
      }
    });
  }
};

function redirect_to_collection_page(term_id) {
  var url = '/sources-search?field_zotero_collections=' + term_id + '&view_mode=collection';
  window.location = url;
}
})(jQuery);
