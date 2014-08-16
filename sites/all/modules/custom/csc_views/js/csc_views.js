/**
 * @file
 * Custom javascript functionalities for CSC custom views module.
 */
(function ($) {
  Drupal.behaviors.cscViews = {
    attach: function (context, settings) {
      // Modify select element to consistently show custom drop down field on all browsers
      $('select').each(function(){
        $(this).wrap('<span class="select-wrapper"></span>');
        $(this).after('<span class="holder"></span>');
      });
      // Update detail level display of search results
      if($.isFunction($.cookie)){
        if($.cookie('detail-level-value') != undefined) set_detail_level($.cookie('detail-level-value'));
      }
      $('.detail-level-option a').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        var option = $(this).attr('id');
        set_detail_level(option);
        $.cookie('detail-level-value', option);
      });
      function set_detail_level(option_value) {
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
    }
  };
  $(window).load(function() {
     // Add custom classes on div containers when results are returned
    if($('.view-biblio-search-api .view-content').length || $('.view-biblio-search-api .view-empty').length) {
      $('.csc-custom-search-form .views-exposed-form .views-exposed-widgets').append('<a href="#" class="toggle-filter-btn-open">Filter</a><div class="inner-filer-container"><div class="filter-header"><h3>Filter</h3><a href="#" class="toggle-filter-btn">Toggle</a></div></div>');
      $('#edit-biblio-publication-type-wrapper, #edit-biblio-authors-wrapper, #edit-biblio-publisher-wrapper, #edit-biblio-place-published-wrapper, #edit-field-zotero-tags-wrapper, #edit-biblio-year-wrapper, #edit-biblio-year-1-wrapper, .views-submit-button, .views-reset-button').appendTo('.inner-filer-container');
    }
    else {
      $('.view-biblio-search-api .views-exposed-widget').hide();
      $('.views-widget-filter-search_api_views_fulltext, .views-submit-button').show();
    }
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
    });
    $('a.toggle-filter-btn-open').click(function(e) {
      e.stopPropagation();
      e.preventDefault();
      $('a.toggle-filter-btn-open').fadeOut();
      $('.inner-filer-container').delay(delay_speed).toggle('slide', {direction: 'right'});
    });
    $('#block-csc-views-custom-taxonomy-block, #block-csc-views-custom-sort-filter, #csc-custom-search-form').show();
  });
  // Returns query string value.
  $.get_query_string_val = function (variable) {
    var query = window.location.search.substring(1);
    var vars = query.split('&');
      for (var i = 0; i < vars.length; i++) {
        var pair = vars[i].split('=');
        if(pair[0] == variable){return pair[1];}
      }
    return(false);
  }
})(jQuery);
