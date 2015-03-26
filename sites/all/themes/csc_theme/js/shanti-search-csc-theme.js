(function ($) {
  Drupal.behaviors.cscTheme = {
    attach: function (context, settings) {
      // Keep search flyout open
      if ($("#search-flyout").length) {
        if ($.cookie('flyout-status') && $.cookie('flyout-status') == 'open') {
          $("#search-flyout").openMbExtruder();
          $('.page-csc-search .main-content .content-section .view-content, #block-csc-views-custom-sort-filter, .view-biblio-search-api .attachment').css('width', '74%');
        }
        else {
          $('.page-csc-search .main-content .content-section .view-content, #block-csc-views-custom-sort-filter, .view-biblio-search-api .attachment').css('width', '100%');
        }
      }
      $('#search-flyout div.flap').click(function(e) {
        if ($('#search-flyout').hasClass('isOpened') === true) {
          var flyout_status = 'open';
          $('.page-csc-search .main-content .content-section .view-content, #block-csc-views-custom-sort-filter,.view-biblio-search-api .attachment').animate({width: '74%'});
        }
        else {
          var flyout_status = 'close';
          $('.page-csc-search .main-content .content-section .view-content, #block-csc-views-custom-sort-filter,.view-biblio-search-api .attachment').animate({width: '100%'});
        }
        $.removeCookie('flyout-status');
        $.cookie('flyout-status', flyout_status);
        e.preventDefault();
      });
    }
  };
})(jQuery);
