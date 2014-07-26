/**
 * @file
 * Custom javascript functionalities for CSC custom views module.
 */
(function ($) {
  Drupal.behaviors.unityTheme = {
    attach: function (context, settings) {
      var publication_start_year = 1492;
      // Default custom sort state
      var sort_by = $('#edit-sort-by').val();
      var sort_order = $('#edit-sort-order').val();
      switch (sort_by) { 
        case 'sort_stripped_node_title':
          var default_sort_value = (sort_order == 'ASC') ? 'title_asc' : 'title_desc';
          break;
        case 'sort_biblio_author':
          var default_sort_value = (sort_order == 'ASC') ? 'author_asc' : 'author_desc';
          break;
        case 'sort_custom_publication_year':
          var default_sort_value = (sort_order == 'ASC') ? 'year_asc' : 'year_desc';
          break;
      }
      $('#edit-custom-sort').find('option[value="' + default_sort_value + '"]').attr('selected',true);
      // Update hidden sort field values based on the selected value of custom sort field.
      $('#edit-custom-sort').change(function() {
        switch ($(this).val()) {
          case 'title_asc':
            update_sort_field('sort_stripped_node_title', 'ASC');
            break;
          case 'title_desc':
            update_sort_field('sort_stripped_node_title', 'DESC');
            break;
          case 'author_asc':
            update_sort_field('sort_biblio_author', 'ASC');
            break;
          case 'author_desc':
            update_sort_field('sort_biblio_author', 'DESC');  
            break;
          case 'year_asc':
            update_sort_field('sort_custom_publication_year', 'ASC');
            break;
          case 'year_desc':
            update_sort_field('sort_custom_publication_year', 'DESC');
            break;
          case 'default':
            update_sort_field('sort_stripped_node_title', 'ASC');  
            break;
        }
      });
      // Restrict input to numbers only
      $('#pager-input').keypress(function(key) {
        if(key.charCode < 48 || key.charCode > 57) return false;
      });
      // Auto submit pager value after 2 sec delay
      var timer;
      $('#pager-input').on('keyup', function() {
        var pager_path = window.location.href;
        var new_pager = ($(this).val() <= parseInt($('#max-page-input').val())) ? '&page=' + ($('#pager-input').val() - 1) : '&page=' + ($('#max-page-input').val() - 1);
        if (get_query_string_val('page')) {
          var old_page_path = get_query_string_val('page');
          var old_pager = '&page=' + old_page_path;
          var new_page_path = pager_path.replace(old_pager, new_pager);
        }
        else {
          var new_page_path = pager_path + new_pager;
        }
        clearInterval(timer);
        timer = setTimeout(function() {
          window.location.replace(new_page_path);
        }, 2000);
      });
      // Collections block
      $('#block-csc-views-custom-taxonomy-block .content .item-list a, #block-csc-views-custom-taxonomy-breadcrumb .content .item-list a').removeClass('active');
      $('#block-csc-views-custom-taxonomy-block ul li ul, #block-csc-views-custom-taxonomy-breadcrumb ul li ul').hide();
      $('#block-csc-views-custom-taxonomy-block ul li a.has-children,#block-csc-views-custom-taxonomy-breadcrumb ul li a.has-children').after('<a href="#" class="expand-btn">[+]</a>');
      $('#block-csc-views-custom-taxonomy-block .expand-btn, #block-csc-views-custom-taxonomy-breadcrumb .expand-btn').click(function(e) {
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
        $('#collection-library').removeClass('active');
        $('a.breadcrumb-dropdown-cta').removeClass('active');
        if ($('div.breadcrumb-child-container').is(':visible')) $('div.breadcrumb-child-container').hide();
        if ($('div.library-dropdown').is(':visible')) $('div.library-dropdown').hide();
      });
      // Advanced search drop down
      $('#edit-biblio-publication-type--2').keyup(function() {
        advanced_search_dropwdown_text_source_type();
      });
      // Open advanced search form
      $('.advanced-search-cta-container').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('#edit-advanced-search-fieldset').toggle();
      });
      $('.form-item-advanced-search-publication-year input[type="radio"]').change(function() {
        if ($('input[name=advanced_search_publication_year]:checked').val() != 'range') {
          $('#edit-biblio-year').val($(this).val());
          $('#edit-biblio-year-1').val($(this).val());
        }
        else {
          $('#edit-biblio-year').val($('#edit-advanced-search-start-year').val());
          $('#edit-biblio-year-1').val($('#edit-advanced-search-end-year').val());
        }
        advanced_search_dropwdown_text_year();
      });
      $('#edit-advanced-search-start-year').keyup(function() {
        $('#edit-biblio-year').val($('#edit-advanced-search-start-year').val());
        advanced_search_dropwdown_text_year();
      });
      $('#edit-advanced-search-end-year').keyup(function() {
        $('#edit-biblio-year-1').val($('#edit-advanced-search-end-year').val());
        advanced_search_dropwdown_text_year();
      });
      var year = new Date();
      var current_year = year.getFullYear();
      var last_year = year.getFullYear() - 1;
      if ($('#edit-biblio-year').val() != '' && $('#edit-biblio-year-1').val() != '') {
        $('#edit-advanced-search-start-year').val($('#edit-biblio-year').val());
        $('#edit-advanced-search-end-year').val($('#edit-biblio-year-1').val());
        advanced_search_dropwdown_text_year();
      }
      $('#edit-advanced-biblio-publication-type').change(function() {
        $('#edit-biblio-publication-type').val($(this).val());
        advanced_search_dropwdown_text_source_type()
      });
      $('#edit-biblio-publication-type').change(function() {
        $('#edit-advanced-biblio-publication-type').val($(this).val());
        advanced_search_dropwdown_text_source_type()
      });
      // Set feild values to default
      $('#edit-reset--2').click(function() {
        $('#edit-advanced-biblio-publication-type, #edit-advanced-search-fieldset .form-text, field-selected-filter').val('');
        $('#edit-advanced-search-publication-year-range').prop('checked',true);
        $('#date-range-slider-dropdown').slider('enable');
        $('#date-range-slider-dropdown').slider({values: [publication_start_year, current_year]});
        $('#date-range-slider-dropdown .start-year, #date-range-slider-dropdown .end-year').fadeIn();
        $('.source-type-selected-filter').text('All');
        $('.field-selected-filter').text('');
        $('.year-selected-filter').text(', ' + publication_start_year + ' - ' + current_year);
        $('#edit-condition-option').val('all');
        $('.form-item-advanced-biblio-publication-type .holder').text('Select Source Type');
        return false;
      });
      // Make enter key submit search form.
      $('#views-exposed-form-biblio-search-api-page input[type="text"], #views-exposed-form-biblio-search-api-page input[type="select"], #views-exposed-form-biblio-search-api-page input[type="radio"]').keypress(function (e) {
        if(e.which == 13) { // Enter key
          $('.csc-custom-search-form').submit();
          return false;  
        }
      });
      var delay = (function(){
        var timer = 0;
        return function(callback, ms){
          clearTimeout (timer);
          timer = setTimeout(callback, ms);
        };
      })();
      $('#edit-search-api-views-fulltext', context).bind('autocomplete', function() {
        alert($(this).val());
      });
      $('#edit-search-api-views-fulltext').keyup(function(e) {
        delay(function(){
          if ($('#edit-search-api-views-fulltext').val() != '' && $('#edit-search-api-views-fulltext').val().length > 2) {
            $('.autocomplete-search-result-container').remove();
            $('.form-item-search-api-views-fulltext').append('<div class="autocomplete-search-result-container"></div>');
            var autocomplete_search_results_publication_type = new Array();
            var autocomplete_search_results_authors = new Array();
            var autocomplete_search_results_publishers = new Array();
            var autocomplete_search_results_publication_place = new Array();
            var autocomplete_search_results_tag = new Array();
            $('#edit-biblio-publication-type option').each(function() {
              retrieve_search_value_option($(this).val(), $(this).text(), autocomplete_search_results_publication_type, 'source-type-group', 'biblio_publication_type');
            });
            append_result(autocomplete_search_results_publication_type, 'Source Type', 'source-type-group-label');
            $('#edit-biblio-authors option').each(function() {
              retrieve_search_value_option($(this).val(), $(this).text(), autocomplete_search_results_authors, 'authors-group', 'biblio_authors');
            });
            append_result(autocomplete_search_results_authors, 'Authors', 'authors-group-label');
            $('#edit-biblio-publisher option').each(function() {
              retrieve_search_value_option($(this).val(), $(this).text(), autocomplete_search_results_publishers, 'publishers-group', 'biblio_publisher');
            });
            append_result(autocomplete_search_results_publishers, 'Publishers', 'publishers-group-label');
            $('#edit-biblio-place-published option').each(function() {
              retrieve_search_value_option($(this).val(), $(this).text(), autocomplete_search_results_publication_place, 'place_published-group', 'biblio_place_published');
            });
            append_result(autocomplete_search_results_publication_place, 'Place of Publication', 'place_published-group-label');
            $('#edit-field-zotero-tags option').each(function() {
              retrieve_search_value_option($(this).val(), $(this).text(), autocomplete_search_results_tag, 'tags-group', 'field_zotero_tags');
            });
            append_result(autocomplete_search_results_tag, 'Tags', 'tags-group-label');
          }
          else {
            $('.autocomplete-search-result-container').remove();
          }
        }, 500 );
      });
      // Clear search text
      $('a.clear-search-text').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('#edit-search-api-views-fulltext-wrapper .form-item-search-api-views-fulltext, #edit-search-api-views-fulltext-wrapper .advanced-search-cta-container').hide();
        $('.clear-search-text').hide();
        $('.autocomplete-search-result-container').remove();
        $('.open-search-field').show();
      });
      // Open search field
      $('a.open-search-field').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('#edit-search-api-views-fulltext-wrapper .form-item-search-api-views-fulltext, #edit-search-api-views-fulltext-wrapper .advanced-search-cta-container').css('display', 'inline-block');
        $(this).hide();
        $('.clear-search-text').show();
      });
      $('div#edit-advanced-search-fieldset').appendTo('#edit-search-api-views-fulltext-wrapper');
      // Date range slider
      var default_start_year = ($('#edit-biblio-year').val() != '') ? $('#edit-biblio-year').val() : publication_start_year;
      var default_end_year = ($('#edit-biblio-year-1').val() != '') ? $('#edit-biblio-year-1').val() : current_year;
      $('#edit-field-zotero-tags-wrapper').append('<label class="publication-year-label">Year</label><div id="date-range-slider"></div>');
      $('#edit-advanced-search-publication-year').append('<label class="publication-year-label">Year</label><div id="date-range-slider-dropdown"></div>');
      $('#date-range-slider, #date-range-slider-dropdown').slider({
        range: true,
        min: publication_start_year,
        max: current_year,
        values: [default_start_year, default_end_year],
        slide: function(event, ui) {
          $('#date-range-slider-dropdown, #date-range-slider').slider('values', 0, ui.values[0]);
          $('#date-range-slider-dropdown, #date-range-slider').slider('values', 1, ui.values[1]);
          $('#edit-advanced-search-publication-year-range').prop('checked',true);
          $('#date-range-slider-dropdown').slider('enable');
          $('#edit-biblio-year').val(ui.values[0]);
          $('#edit-advanced-search-start-year').val(ui.values[0]);
          $('#edit-biblio-year-1').val(ui.values[1]);
          $('#edit-advanced-search-end-year').val(ui.values[1]);
          $('#date-range-slider .start-year-inner, #date-range-slider-dropdown .start-year-inner').text(ui.values[0]);
          $('#date-range-slider .end-year-inner, #date-range-slider-dropdown .end-year-inner').text(ui.values[1]);
        }
      });
      $('.ui-slider-range').append('<div class="start-year"><span class="start-year-inner">' + default_start_year + '</span></div><div class="end-year"><span class="end-year-inner">' + default_end_year + '</span></div>');
      $('#date-range-slider .ui-slider-handle').mouseup(function() {
        $('#date-range-slider .start-year, #date-range-slider .end-year').fadeOut();
      }).mousedown(function() {
        $('#date-range-slider .start-year, #date-range-slider .end-year').fadeIn();
      });
      $('#date-range-slider-dropdown .ui-slider-handle').mouseup(function() {
        $('#date-range-slider-dropdown .start-year, #date-range-slider-dropdown .end-year').fadeOut();
      }).mousedown(function() {
        $('#date-range-slider-dropdown .start-year, #date-range-slider-dropdown .end-year').fadeIn();
      });
      // Set default values
      advanced_search_dropwdown_text_source_type();
      advanced_search_dropwdown_text_year();
      advanced_search_dropwdown_text_field();
      // Update sort fields
      function update_sort_field(sort_type, sort_value) {
        if ($('#edit-sort-by').val() != sort_type || $('#edit-sort-order').val() != sort_value) {
          $('#edit-sort-by').find('option[value="' + sort_type + '"]').attr('selected',true);
          $('#edit-sort-order').find('option[value="' + sort_value + '"]').attr('selected',true);
          $('.csc-custom-search-form').submit();
        }
      }
      // Returns query string value.
      function get_query_string_val(variable) {
      var query = window.location.search.substring(1);
      var vars = query.split('&');
        for (var i = 0; i < vars.length; i++) {
          var pair = vars[i].split('=');
          if(pair[0] == variable){return pair[1];}
        }
        return(false);
      }
      // Update dropdown button source type text
      function advanced_search_dropwdown_text_source_type() {
        var source_type = ($( "#edit-advanced-biblio-publication-type option:selected" ).val() != '') ? $( "#edit-advanced-biblio-publication-type option:selected" ).text() : 'All';
        $('.source-type-selected-filter').text(source_type);
      }
      // Update dropdown button field text
      function advanced_search_dropwdown_text_field() {
        var text_fields = [
          $('#edit-title').val(), 
          $('#edit-search-text-biblio-author').val(),
          $('#edit-search-text-biblio-publisher').val(),
          $('#edit-search-text-biblio-publish-place').val(),
          $('#edit-search-text-biblio-abstract').val(),
          $('#edit-search-text-zotero-tags').val(),
        ];
        text_field_values = [];
        for (var i = 0; i < text_fields.length; i++) {
          if (text_fields[i] != '') {
            text_field_values.push(text_fields[i]);
          }
        }
        if (text_field_values.length == 1) {
          $.each(text_field_values, function( key, value ){
            $('.field-selected-filter').text(', ' + value);
          });
        }
      }
      // Update dropdown button year text
      function advanced_search_dropwdown_text_year() {
        if ($('input[name=advanced_search_publication_year]:checked').val() != 'range') {
          var publish_year = ', ' + $('input[name=advanced_search_publication_year]:checked').val();
          $('#date-range-slider-dropdown').slider('disable');
          $('#date-range-slider-dropdown .start-year, #date-range-slider-dropdown .end-year').fadeOut();
        }
        else {
          var publish_year = ', ' + $('#edit-advanced-search-start-year').val() + ' - ' + $('#edit-advanced-search-end-year').val();
          $('#date-range-slider-dropdown .start-year, #date-range-slider-dropdown .end-year').fadeIn();
          $('#date-range-slider-dropdown').slider('enable');
        }
        $('.year-selected-filter').text(publish_year);
      }
      function retrieve_search_value_option(value, text, option_list, class_name, query_string_name) {
        var query = (query_string_name == 'biblio_publication_type') ? 'biblio_publication_type&=' + value + '&advanced_biblio_publication_type=' + value : query_string_name + '=' + value;
        if(text.toLowerCase().search($('#edit-search-api-views-fulltext').val().toLowerCase()) != -1){
          option_list.push({'html' : '<a href="' + location.protocol + '//' + location.host + location.pathname + '?' + query + '" class="' + class_name + '" id="' + value + '">' + text + '</a>', 'text_value' : text.replace(/[^a-z0-9\s]/gi, '')});
        }
      }
      // Append array result to auto search container result
      function append_result(result_list, group, class_name) {
        if (result_list.length > 0) {
          $('.autocomplete-search-result-container').append('<span class="result-item-type ' + class_name + '">' + group + '</span>');
          result_list.sort(compare);
          for (var i = 0; i < result_list.length; i++){
            $('.autocomplete-search-result-container').append(result_list[i]['html']);
          }
        }
      }
      // Sort text value alphabetically
      function compare(a, b) {
        if (a.text_value < b.text_value) return -1;
        if (a.text_value > b.text_value) {
          return 1;
          return 0;
        }
      }
      // Modify select element to consistently show custom drop down field on all browsers
      $('select').each(function(){
        $(this).wrap('<span class="select-wrapper"></span>');
        $(this).after('<span class="holder"></span>');
      });
      $('select').change(function(){
        var selectedOption = $(this).find(':selected').text();
        if($(this).attr('id') == 'edit-custom-sort' && $(this).val() != 'default') {
          var group = $(this.options[this.selectedIndex]).closest('optgroup').prop('label');
          $(this).next('.holder').text('Sort by ' + group + ':  ' + selectedOption);
        }
        else {
          $(this).next('.holder').text(selectedOption);
        }
      }).trigger('change');
      // Update detail level display of search results
      if($.cookie('detail-level-value') != undefined) set_detail_level($.cookie('detail-level-value'));
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
      $('.view-biblio-search-api .view-filters').addClass('filter-content-right');
      $('.csc-custom-search-form .views-exposed-form .views-exposed-widgets').append('<a href="#" class="toggle-filter-btn-open">Filter</a><div class="inner-filer-container"><div class="filter-header"><h3>Filter</h3><a href="#" class="toggle-filter-btn">Toggle</a></div></div>');
      $('#edit-biblio-publication-type-wrapper, #edit-biblio-authors-wrapper, #edit-biblio-publisher-wrapper, #edit-biblio-place-published-wrapper, #edit-field-zotero-tags-wrapper, #edit-biblio-year-wrapper, #edit-biblio-year-1-wrapper, .views-submit-button, .views-reset-button').appendTo('.inner-filer-container');
    }
    else {
      $('.view-biblio-search-api .views-exposed-widget').hide();
      $('.views-widget-filter-search_api_views_fulltext, .views-submit-button').show();
      $('.view-biblio-search-api .view-filters').show();
    }
    // Slide toggle sidebar filter
    $('a.toggle-filter-btn').click(function(e) {
      e.stopPropagation();
      e.preventDefault();
      $('.inner-filer-container').toggle('slide', {direction: 'right'});
      $('a.toggle-filter-btn-open').delay(400).fadeIn();
    });
    $('a.toggle-filter-btn-open').click(function(e) {
      e.stopPropagation();
      e.preventDefault();
      $('a.toggle-filter-btn-open').fadeOut();
      $('.inner-filer-container').delay(400).toggle('slide', {direction: 'right'});
    });
    $('#block-csc-views-custom-taxonomy-block, #block-csc-views-custom-sort-filter, #csc-custom-search-form').show();
  });
})(jQuery);