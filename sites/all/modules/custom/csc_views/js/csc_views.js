/**
 * @file
 * Custom javascript functionalities for CSC custom views module.
 */
(function ($) {
  Drupal.behaviors.cscViews = {
    attach: function (context, settings) {
       // Add custom classes on div containers when results are returned
      if ($('.view-biblio-search-api .view-content').length || $('.view-biblio-search-api .view-empty').length) {
        $('.csc-custom-search-form .views-exposed-form .views-exposed-widgets').append('<a href="#" class="toggle-filter-btn-open">Filter</a><div class="inner-filer-container"><div class="filter-header"><h3>Filter</h3><a href="#" class="toggle-filter-btn">Toggle</a></div></div>');
        $('#edit-biblio-publication-type-wrapper, #edit-biblio-authors-wrapper, #edit-biblio-publisher-wrapper, #edit-biblio-place-published-wrapper, #edit-field-zotero-tags-wrapper, #edit-biblio-year-wrapper, #edit-biblio-year-1-wrapper, .views-submit-button, .views-reset-button').appendTo('.inner-filer-container');
      }
      else {
        $('.view-biblio-search-api .views-exposed-widget').hide();
        $('.views-widget-filter-search_api_views_fulltext, .views-submit-button').show();
      }
      // Load option settings by default
      if ($.isFunction($.cookie)){
        if ($.cookie('detail-level-value') != undefined) $.set_detail_level($.cookie('detail-level-value'));
        if ($.cookie('content-expand') != undefined) $.set_result_content_width($.cookie('content-expand'));
      }
      // Modify select element to consistently show custom drop down field on all browsers
      $('select').each(function(){
        $(this).wrap('<span class="select-wrapper"></span>');
        $(this).after('<span class="holder"></span>');
      });
      $('.detail-level-option a').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        var option = $(this).attr('id');
        $.set_detail_level(option);
        $.cookie('detail-level-value', option);
      });
      var delay = (function(){
        var timer = 0;
        return function(callback, ms){
          clearTimeout (timer);
          timer = setTimeout(callback, ms);
        };
      })();
      // Slide toggle sidebar filter
      var delay_speed = 400;
      $('a.toggle-filter-btn').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('.inner-filer-container').toggle('slide', {direction: 'right'});
        $('a.toggle-filter-btn-open').delay(delay_speed).fadeIn();
        $('.page-csc-search .main-content .content-section .view-content').animate({width: '100%'});
        $('#block-csc-views-custom-sort-filter').animate({width: '90%'});
        $('.custom-footer-pager .custom-footer-pager-right').animate({marginRight: '0%'});
        $('.page-csc-search .attachment.attachment-after').addClass('expanded');
        $.cookie('content-expand', 'true');
      });
      $('a.toggle-filter-btn-open').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('a.toggle-filter-btn-open').fadeOut();
        $('.inner-filer-container').delay(delay_speed).toggle('slide', {direction: 'right'});
        $('.page-csc-search .main-content .content-section .view-content').delay(delay_speed).animate({width: '74%'});
        $('#block-csc-views-custom-sort-filter').delay(delay_speed).animate({width: '73%'});
        $('.custom-footer-pager .custom-footer-pager-right').delay(delay_speed).animate({marginRight: '26%'});
        $('.page-csc-search .attachment.attachment-after').removeClass('expanded');
        $.cookie('content-expand', 'false');
      });
      $('#block-csc-views-custom-taxonomy-block, #block-csc-views-custom-sort-filter, #csc-custom-search-form').show();
    }
  };
  // Returns query string value.
  $.get_query_string_val = function (variable) {
    var query = window.location.search.substring(1);
    var vars = query.split('&');
      for (var i = 0; i < vars.length; i++) {
        var pair = vars[i].split('=');
        if (pair[0] == variable){return pair[1];}
      }
    return(false);
  }
  $.set_detail_level = function (option_value) {
    $('.detail-level-option a').removeClass('active');
    $('.view-biblio-search-api .views-field').hide();
    var option_id = '#' + option_value;
    $(option_id).addClass('active');
    switch (option_value) {
      case 'short-detail':
        $('.view-biblio-search-api .views-field-title').show();
        break;
      case 'medium-detail':
        $('.view-biblio-search-api .views-field-title, .view-biblio-search-api .views-field-biblio-authors').show();
        break;
      case 'long-detail':
        $('.view-biblio-search-api .views-field').show();
        break;
    }
  }
  $.set_result_content_width = function (option_value) {
    if (option_value == 'true') {
      $('.page-csc-search .attachment.attachment-after, .page-csc-search .main-content .content-section .view-content, #block-csc-views-custom-sort-filter, .custom-footer-pager .custom-footer-pager-right').addClass('expanded');
      $('.page-csc-search .inner-filer-container').addClass('minimize');
      $('.page-csc-search .toggle-filter-btn-open').show();
    }
    else {
      $('.page-csc-search .attachment.attachment-after, .page-csc-search .main-content .content-section .view-content, #block-csc-views-custom-sort-filter, .custom-footer-pager .custom-footer-pager-right').removeClass('expanded');
      $('.page-csc-search .inner-filer-container').removeClass('minimize');
      $('.page-csc-search .toggle-filter-btn-open').hide();
    }
  }
})(jQuery);
