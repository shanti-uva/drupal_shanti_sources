/**
 * @file
 * Custom javascript functionalities for CSC custom views collections.
 */
(function ($) {
  Drupal.behaviors.cscViewsCollections = {
    attach: function (context, settings) {
      // Collections block
      $('#block-csc-views-custom-taxonomy-block .content .item-list a, #block-csc-views-custom-taxonomy-flyout-block .content .item-list a, #block-csc-views-custom-taxonomy-breadcrumb .content .item-list a').removeClass('active');
      $('#block-csc-views-custom-taxonomy-block ul li ul, #block-csc-views-custom-taxonomy-flyout-block ul li ul, #block-csc-views-custom-taxonomy-breadcrumb ul li ul').hide();
      $('#block-csc-views-custom-taxonomy-block ul li a.has-children, #block-csc-views-custom-taxonomy-flyout-block ul li a.has-children, #block-csc-views-custom-taxonomy-breadcrumb ul li a.has-children').after('<a href="#" class="expand-btn glyphicon-plus-sign"></a>');
      $('#block-csc-views-custom-taxonomy-block .expand-btn, #block-csc-views-custom-taxonomy-flyout-block .expand-btn, #block-csc-views-custom-taxonomy-breadcrumb .expand-btn').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $(this).next('ul').toggle();
        if ($(this).next('ul').is(':visible')) {
          $(this).removeClass('glyphicon-plus-sign');
          $(this).addClass('expanded glyphicon-minus-sign');
        }
        else {
          $(this).addClass('glyphicon-plus-sign');
          $(this).removeClass('expanded glyphicon-minus-sign');
        }
      });
      // Breadcrumb child links
      $('#collection-library').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('.breadcrumb-child-container').hide();
        $('.library-dropdown').toggle();
        ($('.library-dropdown').is(':visible')) ? $(this).addClass('active') : $('#collection-library, a.breadcrumb-dropdown-cta').removeClass('active');
      });
      $('a.breadcrumb-dropdown-cta').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('.library-dropdown').hide();
        $(this).next('.breadcrumb-child-container').toggle();
        $('.breadcrumb-child-container').not($(this).next('.breadcrumb-child-container')).hide();
        ($(this).next('.breadcrumb-child-container').is(':visible')) ? $(this).addClass('active') : $('#collection-library, a.breadcrumb-dropdown-cta').removeClass('active');
      });
      // Attach collapsible links to each breadcrumb link with child links
      $('.breadcrumb-child-sub-top a').after('<a href="#" class="expand-btn expanded glyphicon-minus-sign"></a>');
      $('.breadcrumb-child-sub-top a.expand-btn').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $(this).parent().next('div.breadcrumb-child').toggle();
        if ($(this).parent().next('div.breadcrumb-child').is(':visible')) {
          $(this).removeClass('glyphicon-plus-sign');
          $(this).addClass('expanded glyphicon-minus-sign');
        }
        else {
          $(this).addClass('glyphicon-plus-sign');
          $(this).removeClass('expanded glyphicon-minus-sign');
        }
      });
      // Close shown containers if a user clicks anywhere on the page.
      $('body').click(function(e) {
        $('#collection-library, a.breadcrumb-dropdown-cta').removeClass('active');
        if ($('div.breadcrumb-child-container').is(':visible')) $('div.breadcrumb-child-container').hide();
        if ($('div.library-dropdown').is(':visible')) $('div.library-dropdown').hide();
      });
      $('#block-csc-views-custom-taxonomy-flyout-block ul li a.expand-btn').click(function() {
        var adjusted_height = ($('.content-section').height() < $('.extruder-content').height()) ? parseInt($('.extruder-content').height()) + 100 : parseInt($('.extruder-content').height()) + 300;
        $('.content-section').animate({
          height: adjusted_height + 'px',
        });
      });
      // Open collection lists up to the current collection item
      var collectionClassId = '#block-csc-views-custom-taxonomy-flyout-block a.collection-id-' + $.get_query_string_val('field_zotero_collections');
      $(collectionClassId).addClass('current-trail').css('color', '#40adb6');
      $(collectionClassId).parentsUntil('#block-csc-views-custom-taxonomy-flyout-block div').addClass('active-trail');
      $('ul.active-trail').show();
      $('li.active-trail').children('.expand-btn').removeClass('glyphicon-plus-sign');
      $('li.active-trail').children('.expand-btn').addClass('expanded glyphicon-minus-sign');
      $('a.has-children.current-trail').parent().children('ul').show();
    }
  };
})(jQuery);
