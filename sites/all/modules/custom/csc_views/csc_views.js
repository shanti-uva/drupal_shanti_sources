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
    // Auto submit pager value after delay
    var timer;
    $('#pager-input').on('keyup', function() {
      var text_search = 'search_api_views_fulltext='+ $('#edit-search-api-views-fulltext').val();
      var sort_order = '&sort_order=' + $('#edit-sort-order').val();
      var sort_type = '&sort_by=' + $('#edit-sort-by').val();
      var filter_collection = '&field_zotero_collections=' + $('#edit-field-zotero-collections').val();
      var source_type = '&biblio_publication_type=' + $('#edit-biblio-publication-type').val();
      var authors = '&biblio_authors=' + $('#edit-biblio-authors').val();
      var publishers = '&biblio_publisher=' + $('#edit-biblio-publisher').val();
      var published_location = '&biblio_place_published=' + $('#edit-biblio-place-published').val();
      var publish_year = '&biblio_year=' + $('#edit-biblio-year').val() + '&biblio_year_1=' +  $('#edit-biblio-year-1').val();
      var zotero_tag = '&field_zotero_tags=' + $('#edit-field-zotero-tags').val();
      var pager = ($(this).val() <= parseInt($('#max-page-input').val())) ? '&page=' + ($('#pager-input').val() - 1) : '&page=' + ($('#max-page-input').val() - 1);   
      clearInterval(timer);
      timer = setTimeout(function() {
        window.location.replace(window.location.href.split('?')[0] + '?' + text_search + source_type + authors + publishers + published_location +
        publish_year + zotero_tag + sort_order + sort_type + filter_collection + pager);
      }, 2000);
    });
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
  });
})(jQuery);