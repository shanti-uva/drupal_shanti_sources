/**
 * @file
 * Custom javascript functionalities for CSC custom views search filter.
 */
(function ($) {
  Drupal.behaviors.cscViewsSearchFilter = {
    attach: function (context, settings) {
      // Set default values
      var default_publication_start_year = parseInt($('#unfiltered-earliest-published-year').val());
      var default_publication_end_year = parseInt($('#unfiltered-latest-published-year').val());
      var publication_start_year = ($('#earliest-published-year').length > 0) ? parseInt($('#earliest-published-year').val()) : default_publication_start_year;
      var publication_end_year = ($('#latest-published-year').length > 0) ? parseInt($('#latest-published-year').val()) : default_publication_end_year;
      set_advanced_search_dropwdown_source_type_text();
      set_advanced_search_dropwdown_filter_field_text();
      set_advanced_search_dropwdown_year_text();
      // Advanced search drop down
      $('#edit-biblio-publication-type--2').keyup(function() {
        set_advanced_search_dropwdown_source_type_text();
      });
      // Make enter key submit search form.
      $('#views-exposed-form-biblio-search-api-page input[type="text"], #views-exposed-form-biblio-search-api-page input[type="select"], #views-exposed-form-biblio-search-api-page input[type="radio"]').keypress(function (e) {
        if (e.which == 13) { // Enter key
          $('.csc-custom-search-form').submit();
          return false;  
        }
      });
      // Open advanced search form
      $('.advanced-search-cta-container').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('#edit-advanced-search-fieldset').toggle();
      });
      // Auto clear search input field once opened
      $('#edit-search-api-views-fulltext').focus(function(){
        $('#edit-search-api-views-fulltext').val('');
        $('#edit-search-api-views-fulltext').css('color', '#333333');
      });
      // Hide search text
      $('a.clear-search-text').click(function(e) {
        e.stopPropagation();
        e.preventDefault();
        $('#edit-search-api-views-fulltext-wrapper .form-item-search-api-views-fulltext, #edit-search-api-views-fulltext-wrapper .advanced-search-cta-container').hide();
        $('.clear-search-text, #edit-advanced-search-fieldset').hide();
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
        $('#edit-search-api-views-fulltext').focus();
      });
      $('div#edit-advanced-search-fieldset').appendTo('#edit-search-api-views-fulltext-wrapper');
      // Publication year
      $('.form-item-advanced-search-publication-year input[type="radio"]').change(function() {
        if ($('input[name=advanced_search_publication_year]:checked').val() != 'range') {
          $('#edit-biblio-year, #edit-biblio-year-1, #edit-advanced-search-start-year, #edit-advanced-search-end-year').val($(this).val());
          $('#date-range-slider').slider({values: [$(this).val(), $(this).val()]});
          $('#date-range-slider .start-year-inner').text($(this).val());
          $('#date-range-slider .end-year-inner').text($(this).val());
        }
        else {
          $('#edit-biblio-year').val($('#edit-advanced-search-start-year').val());
          $('#edit-biblio-year-1').val($('#edit-advanced-search-end-year').val());
          $('#date-range-slider-dropdown, #date-range-slider').slider({min: default_publication_start_year, max: default_publication_end_year, values: [publication_start_year, publication_end_year]});
          $('#date-range-slider-dropdown .start-year-inner, #date-range-slider .start-year-inner').text(publication_start_year);
          $('#date-range-slider-dropdown .end-year-inner, #date-range-slider .end-year-inner').text(publication_end_year);
        }
        set_advanced_search_dropwdown_year_text();
      });
      $('#edit-advanced-search-start-year').keyup(function() {
        $('#edit-biblio-year').val($('#edit-advanced-search-start-year').val());
        set_advanced_search_dropwdown_year_text();
      });
      $('#edit-advanced-search-end-year').keyup(function() {
        $('#edit-biblio-year-1').val($('#edit-advanced-search-end-year').val());
        set_advanced_search_dropwdown_year_text();
      });
      if ($('#edit-biblio-year').val() != '' && $('#edit-biblio-year-1').val() != '') {
        $('#edit-advanced-search-start-year').val($('#edit-biblio-year').val());
        $('#edit-advanced-search-end-year').val($('#edit-biblio-year-1').val());
        set_advanced_search_dropwdown_year_text();
      }
      $('#edit-advanced-biblio-publication-type').change(function() {
        $('#edit-biblio-publication-type').val($(this).val());
        set_advanced_search_dropwdown_source_type_text()
      });
      $('#edit-biblio-publication-type').change(function() {
        $('#edit-advanced-biblio-publication-type').val($(this).val());
        set_advanced_search_dropwdown_source_type_text()
      });
      // Date range slider
      var selected_published_year = $('input[name=advanced_search_publication_year]:checked').val();
      if (selected_published_year != 'range') {
        var year_value = parseInt(selected_published_year);
        var default_start_year = year_value;
        var default_end_year = year_value; 
      }
      else {
        var default_start_year = ($('#edit-biblio-year').val() != '') ? $('#edit-biblio-year').val() : publication_start_year;
        var default_end_year = ($('#edit-biblio-year-1').val() != '') ? $('#edit-biblio-year-1').val() : publication_end_year;
      }
      $('#edit-field-zotero-tags-wrapper').append('<label class="publication-year-label">Year</label><div id="date-range-slider"></div>');
      $('#edit-advanced-search-publication-year').append('<label class="publication-year-label">Year</label><div id="date-range-slider-dropdown"></div>');
      $('#date-range-slider, #date-range-slider-dropdown').slider({
        range: true,
        min: default_publication_start_year,
        max: default_publication_end_year,
        values: [default_start_year, default_end_year],
        slide: function(event, ui) {
          var slider_start_year_value = ui.values[0];
          var slider_end_year_value = ui.values[1];
          $('#date-range-slider-dropdown, #date-range-slider').slider('values', 0, slider_start_year_value);
          $('#date-range-slider-dropdown, #date-range-slider').slider('values', 1, slider_end_year_value);
          $('#edit-advanced-search-publication-year-range').prop('checked',true);
          $('#date-range-slider-dropdown').slider('enable');
          $('#edit-biblio-year').val(slider_start_year_value);
          $('#edit-advanced-search-start-year').val(slider_start_year_value);
          $('#edit-biblio-year-1').val(slider_end_year_value);
          $('#edit-advanced-search-end-year').val(slider_end_year_value);
          $('#date-range-slider .start-year-inner, #date-range-slider-dropdown .start-year-inner').text(slider_start_year_value);
          $('#date-range-slider .end-year-inner, #date-range-slider-dropdown .end-year-inner').text(slider_end_year_value);
        }
      });
      (selected_published_year != 'range') ? $('#date-range-slider-dropdown').slider('disable') : $('#date-range-slider-dropdown').slider('enable');
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
      // Update dropdown button source type text
      function set_advanced_search_dropwdown_source_type_text() {
        var source_type = ($( "#edit-advanced-biblio-publication-type option:selected" ).val() != '') ? $( "#edit-advanced-biblio-publication-type option:selected" ).text() : 'All';
        $('.source-type-selected-filter').text(source_type);
      }
      // Set field values to default
      $('#edit-reset--2').click(function() {
        $('#edit-advanced-biblio-publication-type').val('').change();
        $('#edit-advanced-search-fieldset .form-text, field-selected-filter').val('');
        $('#edit-advanced-search-publication-year-range').prop('checked',true);
        $('.source-type-selected-filter').text('All');
        $('.field-selected-filter').text('');
        $('.year-selected-filter').text(', ' + publication_start_year + ' - ' + publication_end_year);
        $('#edit-condition-option').val('all');
        $('.form-item-advanced-biblio-publication-type .holder').text($("#edit-advanced-biblio-publication-type option:selected").text());
        $('.form-item-condition-option .holder').text($("#edit-condition-option option:selected").text());
        set_default_date_slider()
        return false;
      });
      $('#edit-reset').click(function() {
        $('#edit-biblio-publication-type').val('').change();
        $('#edit-biblio-authors, #edit-biblio-publisher, #edit-biblio-place-published, #edit-field-zotero-tags').val('');
        $('#edit-biblio-publication-type-wrapper .holder').text($("#edit-biblio-publication-type option:selected").text());
        $('#edit-biblio-authors-wrapper .holder').text($("#edit-biblio-authors option:selected").text());
        $('#edit-biblio-publisher-wrapper .holder').text($("#edit-biblio-publisher option:selected").text());
        $('#edit-biblio-place-published-wrapper .holder').text($("#edit-biblio-place-published option:selected").text());
        $('#edit-field-zotero-tags-wrapper .holder').text($("#edit-field-zotero-tags option:selected").text());
        set_default_date_slider();
        return false;
      });
      // Update dropdown button field text
      function set_advanced_search_dropwdown_filter_field_text() {
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
      function set_advanced_search_dropwdown_year_text() {
        if ($('input[name=advanced_search_publication_year]:checked').val() != 'range') {
          var publish_year = ', ' + $('input[name=advanced_search_publication_year]:checked').val();
           $('#date-range-slider-dropdown').slider('disable');
           $('#date-range-slider-dropdown .start-year, #date-range-slider-dropdown .end-year').fadeOut();
        }
        else {
          var publish_year = ', ' + default_publication_start_year + ' - ' + default_publication_end_year;
          $('#date-range-slider-dropdown .start-year, #date-range-slider-dropdown .end-year').fadeIn();
          $('#date-range-slider-dropdown').slider('enable');
        }
        $('.year-selected-filter').text(publish_year);
      }
      // Set default values for date sliders
      function set_default_date_slider() {
        $('#date-range-slider-dropdown').slider('enable');
        $('#date-range-slider-dropdown, #date-range-slider').slider({min: default_publication_start_year, max: default_publication_end_year, values: [default_publication_start_year, default_publication_end_year]});
        $('#date-range-slider-dropdown .start-year-inner, #date-range-slider .start-year-inner').text(default_publication_start_year);
        $('#date-range-slider-dropdown .end-year-inner, #date-range-slider .end-year-inner').text(default_publication_end_year);
        $('#date-range-slider-dropdown .start-year, #date-range-slider-dropdown .end-year, #date-range-slider .start-year, #date-range-slider .end-year').fadeIn();
        $('#edit-advanced-search-start-year, #edit-biblio-year').val(default_publication_start_year);
        $('#edit-advanced-search-end-year, #edit-biblio-year-1').val(default_publication_end_year);
        $('#edit-advanced-search-publication-year-range').prop('checked', true);
      }
    }
  };
})(jQuery);
