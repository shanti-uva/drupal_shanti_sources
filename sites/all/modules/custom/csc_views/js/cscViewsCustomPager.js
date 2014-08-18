/**
 * @file
 * Custom javascript functionalities for CSC custom views custom pager.
 */
(function ($) {
Drupal.behaviors.cscViewsCustomPager = {
  attach: function (context, settings) {
    // Restrict input to numbers only
    $('#pager-input').keypress(function(key) {
      if (key.charCode < 48 || key.charCode > 57) return false;
    });
    // Auto submit pager value after 2 sec delay
    var timer;
    $('#pager-input').on('keyup', function() {
      var pager_path = window.location.href;
      var new_pager = ($(this).val() <= parseInt($('#max-page-input').val())) ? '&page=' + ($('#pager-input').val() - 1) : '&page=' + ($('#max-page-input').val() - 1);
      if ($.get_query_string_val('page')) {
        var old_page_path = $.get_query_string_val('page');
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
  }
};
})(jQuery);
