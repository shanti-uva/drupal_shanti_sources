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
      $('#block-csc-views-custom-taxonomy-block ul li a.has-children, #block-csc-views-custom-taxonomy-flyout-block ul li a.has-children, #block-csc-views-custom-taxonomy-breadcrumb ul li a.has-children').after('<a href="#" class="expand-btn">[+]</a>');
      $('#block-csc-views-custom-taxonomy-block .expand-btn, #block-csc-views-custom-taxonomy-flyout-block .expand-btn, #block-csc-views-custom-taxonomy-breadcrumb .expand-btn').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $(this).next('ul').toggle();
        ($(this).next('ul').is(':visible')) ? $(this).addClass('expanded') : $(this).removeClass('expanded');
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
      $('.breadcrumb-child-sub-top a').after('<a href="#" class="expand-btn expanded">[ - ]</a>');
      $('.breadcrumb-child-sub-top a.expand-btn').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $(this).parent().next('div.breadcrumb-child').toggle();
        ($(this).parent().next('div.breadcrumb-child').is(':visible')) ? $(this).addClass('expanded') : $(this).removeClass('expanded');
      });
      // Close shown containers if a user clicks anywhere on the page.
      $('body').click(function(e) {
        $('#collection-library, a.breadcrumb-dropdown-cta').removeClass('active');
        if ($('div.breadcrumb-child-container').is(':visible')) $('div.breadcrumb-child-container').hide();
        if ($('div.library-dropdown').is(':visible')) $('div.library-dropdown').hide();
      });
    }
  };
})(jQuery);
