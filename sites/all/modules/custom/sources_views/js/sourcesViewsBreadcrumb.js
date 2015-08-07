var globalElement;
(function ($) {
  //Display the correct dropdown when user clicks a breadcrumb
  Drupal.behaviors.sourcesViewsDisplayBreadcrumbDropdowns = {
    attach: function (context, settings) {
      $('ol.breadcrumb a').click(function(e) {
        e.preventDefault();
        e.stopPropagation();

        var term_id = $(this).attr('term_id');
        var clicked_dropdown_is_visible = sourcesDropDownIsVisible(term_id);
        sourcesHideAllDropDowns();

        if (!clicked_dropdown_is_visible) {
          sourcesDisplayBreadCrumbDropDown(term_id);
        }
      });
    }
  };
  //make sure the pointer cursor is displayed on hover if breadcrumb has a dropdown
  Drupal.behaviors.sourcesViewsSetBreadcumbCursor = {
    attach: function (context, settings) {
      $('ol.breadcrumb a').each(function(key, element) {
        var term_id = $(this).attr('term_id');
        var dropdownElement = sourcesGetDropdownElement(term_id);
        if (dropdownElement) {
          $(this).css({cursor: 'pointer'});  
        }
      });
    }
  }


})(jQuery);

$ = jQuery;

  function sourcesHideAllDropDowns() {
    $('.breadcrumb-dropdown').css({opacity: 0, 'pointer-events': 'none'}).hide();
  }

  function sourcesDisplayBreadCrumbDropDown(term_id) {
    var breadcrumbElement = sourcesGetBreadcrumbElement(term_id);
    var dropdownElement   = sourcesGetDropdownElement(term_id);

    sourcesCenterFirstElementWithSecondHorizontally(dropdownElement, breadcrumbElement);
    sourcesPositionFirstElementBelowSecondPlusOffset(dropdownElement, breadcrumbElement, 5);
    $(dropdownElement).css({opacity: 1, 'pointer-events': 'all'}).show();
    globalElement = dropdownElement;
  }

  function sourcesDropDownIsVisible(term_id) {
    var dropdownElement = sourcesGetDropdownElement(term_id);
    var el = $(dropdownElement).get()[0];
    return $(dropdownElement).is(':visible');

  }

  function sourcesGetDropdownElement(term_id) {
    var dropdownElement = $('.breadcrumb-dropdown[term_id="' + term_id + '"]');
    if (dropdownElement.length) {
      return dropdownElement;
    }
  }

  function sourcesGetBreadcrumbElement(term_id) {
    var breadcrumbElement = $('ol.breadcrumb a[term_id="' + term_id + '"]');
    if (breadcrumbElement.length) {
      return breadcrumbElement;
    }
  }

  function sourcesPositionFirstElementBelowSecondPlusOffset(firstElement, secondElement, offsetPixels) {
    var top = $(secondElement).offset().top + offsetPixels;
    $(firstElement).offset({top: top + 'px'});
  }

  /*
   *  Align the horizontal center of two elements, moving the first to align with the second
   */
  function sourcesCenterFirstElementWithSecondHorizontally(firstElement, secondElement) {
    var secondElementCenter = sourcesFindElementHorizontalCenter(secondElement);
    sourcesSetElementHorizontalCenter(firstElement, secondElementCenter);
  }

  function sourcesFindElementHorizontalCenter(element) {
    element = $(element);
    var width = $(element).width();
    var position = $(element).offset();
    var center = (width / 2) + position.left;
    return center;
  }

  function sourcesFindElementBottom(element) {
    element = $(element);
    var position = $(element).offset();
    var height = $(element).height();
    var bottom = (height / 2) + position.top;
    return bottom;
  }

  function sourcesSetElementHorizontalCenter(element, centerPosition) {
    var width = $(element).width();
    var leftEdgePosition = centerPosition - (width / 2);
    leftEdgePosition = leftEdgePosition > 0 ? leftEdgePosition : 0;
    $(element).offset({left: leftEdgePosition});
  }

