/**
 * @file
 * Custom javascript functionalities for CSC custom views module.
 */
(function ($) {
  $(document).ready(function () {    
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
    function update_sort_field(sort_type, sort_value) {
      $('#edit-sort-by').find('option[value="' + sort_type + '"]').attr('selected',true);
      $('#edit-sort-order').find('option[value="' + sort_value + '"]').attr('selected',true);
    }
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
    // Returns query string value.
    function get_query_string_val(variable) {
    var query = window.location.search.substring(1);
    var vars = query.split('&');
      for (var i=0; i < vars.length; i++) {
        var pair = vars[i].split('=');
        if(pair[0] == variable){return pair[1];}
      }
      return(false);
    }
    // Collections block
    $('#block-csc-views-custom-taxonomy-block .content .item-list a, #block-csc-views-custom-taxonomy-breadcrumb .content .item-list a').removeClass('active');
    $('#block-csc-views-custom-taxonomy-block .content .item-list .item-list, #block-csc-views-custom-taxonomy-breadcrumb .content .item-list .item-list').hide();
    $('#block-csc-views-custom-taxonomy-block .content .item-list .has-children, #block-csc-views-custom-taxonomy-breadcrumb .content .item-list .has-children').after('<a href="#" class="expand-btn">[+]</a>');
    $('#block-csc-views-custom-taxonomy-block a.expand-btn, #block-csc-views-custom-taxonomy-breadcrumb a.expand-btn').click(function(e) {
      e.stopPropagation();
      e.preventDefault();
      $(this).next('div.item-list').toggle();
      ($(this).next('div.item-list').is(':visible')) ? $(this).addClass('expanded') : $(this).removeClass('expanded');
    });
    // Add custom classes on div containers when results are returned
    if($('.view-biblio-search-api-dev .view-content').length || $('.view-biblio-search-api-dev .view-empty').length) {
      $('.view-biblio-search-api-dev .view-content').addClass('result-content-left');
      $('.view-biblio-search-api-dev .view-filters').addClass('filter-content-right');
      $('.view-biblio-search-api-dev .view-empty').addClass('result-content-left');
      $('.views-exposed-widget').show();
    }
    else {
      $('.view-biblio-search-api-dev .views-exposed-widget').hide();
      $('.views-widget-filter-search_api_views_fulltext, .views-submit-button').show();
    }
    // Breadcrumb child links
    $('#collection-library').click(function(e) {
      e.stopPropagation();
      e.preventDefault();
      $('.breadcrumb-child-container').hide();
      $('.library-dropdown').toggle();
    });
    $('a.breadcrumb-dropdown-cta').click(function(e) {
      e.stopPropagation();
      e.preventDefault();
      $('.library-dropdown').hide();
      $('.breadcrumb-child-container').not($(this).next('.breadcrumb-child-container')).hide();
      $(this).next('.breadcrumb-child-container').toggle();
    });
    $('.breadcrumb-child-sub-top a').after('<a href="#" class="expand-btn expanded">[ - ]</a>');
    $('.breadcrumb-child-sub-top a.expand-btn').click(function(e) {
      e.stopPropagation();
      e.preventDefault();
      $(this).parent().next('div.breadcrumb-child').toggle();
      ($(this).parent().next('div.breadcrumb-child').is(':visible')) ? $(this).addClass('expanded') : $(this).removeClass('expanded');
    });
    $('body').click(function() {
      if ($('div.breadcrumb-child-container').is(':visible')) $('div.breadcrumb-child-container').hide();
      if ($('div.library-dropdown').is(':visible')) $('div.library-dropdown').hide();
    });
    // Advanced search dropdown
    advanced_search_dropwdown_text_source_type();
    advanced_search_dropwdown_text_year();
    advanced_search_dropwdown_text_field();
    $('#edit-biblio-publication-type--2').keyup(function() {
      advanced_search_dropwdown_text_source_type();
    });
    $('.advanced-search-cta-container').click(function(e) {
      e.stopPropagation();
      e.preventDefault();
      $('.advanced-search-container').toggle();
    });
    $('.form-item-advanced-search-publication-year input[type="radio"]').change(function() {
      if ($('input[name=advanced_search_publication_year]:checked').val() != 'range') {
        $('#edit-biblio-year').val($(this).val());
        $('#edit-biblio-year-1').val($(this).val());
        $('#edit-advanced-search-start-year').prop('readonly', true);
        $('#edit-advanced-search-end-year').prop('readonly', true);
      }
      else {
        $('#edit-advanced-search-start-year').prop('readonly', false);
        $('#edit-advanced-search-end-year').prop('readonly', false);
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
    $('#edit-biblio-year').keyup(function() {
      $('#edit-advanced-search-start-year').prop('readonly', false);
      $('#edit-advanced-search-start-year').val($('#edit-biblio-year').val());
      $('input[name=advanced_search_publication_year]:checked').val('range');
      $('#edit-advanced-search-publication-year-range').prop('checked',true);
      advanced_search_dropwdown_text_year();
    });
    $('#edit-biblio-year-1').keyup(function() {
      $('#edit-advanced-search-end-year').prop('readonly', false);
      $('#edit-advanced-search-end-year').val($('#edit-biblio-year-1').val());
      $('#edit-advanced-search-publication-year-range').prop('checked',true);
      advanced_search_dropwdown_text_year();
    });
    $('#edit-advanced-biblio-publication-type').change(function() {
      $('#edit-biblio-publication-type').val($(this).val());
      advanced_search_dropwdown_text_source_type()
    });
    $('#edit-biblio-publication-type').change(function() {
      $('#edit-advanced-biblio-publication-type').val($(this).val());
      advanced_search_dropwdown_text_source_type()
    });
    // Set dropdown feild values to default
    $('#edit-reset--2').click(function() {
      $('#edit-advanced-biblio-publication-type, #edit-advanced-search-fieldset .form-text, field-selected-filter').val('');
      $('#edit-advanced-search-publication-year-range').prop('checked', true );
      $('#edit-advanced-search-start-year').val('1942');
      $('#edit-advanced-search-end-year').val(current_year);
      $('.source-type-selected-filter').text('All, ');
      $('.year-selected-filter').text('1942 - ' + current_year);
      $('#edit-condition-option').val('all');
      return false;
    });    
    // Update dropdown button source type text
    function advanced_search_dropwdown_text_source_type() {
      var source_type = ($( "#edit-advanced-biblio-publication-type option:selected" ).text() != 'Select') ? $( "#edit-advanced-biblio-publication-type option:selected" ).text() : 'All';
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
      }
      else {
        var publish_year = ', ' + $('#edit-advanced-search-start-year').val() + ' - ' + $('#edit-advanced-search-end-year').val();
      }
      $('.year-selected-filter').text(publish_year);
    }
  });
})(jQuery);