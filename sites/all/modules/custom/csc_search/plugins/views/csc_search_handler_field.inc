<?csc_search

/**
 * A handler to provide a field that is constructed by the administrator using PHP.
 *
 * @ingroup views_field_handlers
 */
class csc_search_handler_field extends views_handler_field {
  const CLICK_SORT_DISABLED = 0;
  const CLICK_SORT_NUMERIC = 1;
  const CLICK_SORT_ALPHA = 2;
  const CLICK_SORT_ALPHA_CASE = 3;
  const CLICK_SORT_NAT = 4;
  const CLICK_SORT_NAT_CASE = 5;
  const CLICK_SORT_PHP = 6;

  protected $csc_search_static_variable = NULL;

  /**
   * Implements views_object#option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['use_csc_search_setup'] = array('default' => FALSE);
    $options['csc_search_setup'] = array('default' => '');
    $options['csc_search_value'] = array('default' => '');
    $options['csc_search_output'] = array('default' => '');
    $options['use_csc_search_click_sortable'] = array('default' => self::CLICK_SORT_DISABLED);
    $options['csc_search_click_sortable'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Implements views_handler#options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form += views_csc_search_form_element($this,
      array('use_csc_search_setup', t('Use setup code'), t('If checked, you can provide PHP code to be run once right before execution of the view. This may be useful to define functions to be re-used in the value and/or output code.')),
      array('csc_search_setup', t('Setup code'), t('Code to run right before execution of the view.'), FALSE),
      array('$view', '$handler', '$static')
    );
    $form += views_csc_search_form_element($this,
      FALSE,
      array('csc_search_value', t('Value code'), t('Code to construct the value of this field.'), FALSE),
      array('$view', '$handler', '$static', '$row', '$data')
    );
    $form += views_csc_search_form_element($this,
      array('use_csc_search_click_sortable', t('Enable click sort'), t('If checked, you can use PHP code to enable click sort on the field.')),
      array('csc_search_click_sortable', t('Click sort code'), t('The comparison code must return an integer less than, equal to, or greater than zero if the first row should respectively appear before, stay where it was compared to, or appear after the second row.'), FALSE),
      array(
        '$view', '$handler', '$static',
        '$row1' => t('Data of row.'),
        '$row2' => t('Data of row to compare against.'),
      )
    );
    $form['use_csc_search_click_sortable']['#type'] = 'select';
    $form['use_csc_search_click_sortable']['#options'] = array(
      self::CLICK_SORT_DISABLED => t('No'),
      self::CLICK_SORT_NUMERIC => t('Sort numerically'),
      self::CLICK_SORT_ALPHA => t('Sort alphabetically'),
      self::CLICK_SORT_ALPHA_CASE => t('Sort alphabetically (case insensitive)'),
      self::CLICK_SORT_NAT => t('Sort using a "natural order" algorithm'),
      self::CLICK_SORT_NAT_CASE => t('Sort using a "natural order" algorithm (case insensitive)'),
      self::CLICK_SORT_PHP => t('Sort using custom PHP code'),
    );
    $form['use_csc_search_click_sortable']['#default_value'] = $this->options['use_csc_search_click_sortable'];
    $form['csc_search_click_sortable']['#states'] = array(
      'visible' => array(
        ':input[name="options[use_csc_search_click_sortable]"]' => array('value' => (string)self::CLICK_SORT_PHP),
      ),
    );
    $form += views_csc_search_form_element($this,
      FALSE,
      array('csc_search_output', t('Output code'), t('Code to construct the output of this field.'), TRUE),
      array('$view', '$handler', '$static', '$row', '$data', '$value' => t('Value of this field.'))
    );
  }

  /**
   * Implements views_handler_field#query().
   *
   * @see views_csc_search_views_pre_execute()
   */
  function query() {
    // Provide an field alias but don't actually alter the query.
    $this->field_alias = 'views_csc_search_' . $this->position;
    // Inform views_csc_search_views_pre_execute() to seize control over the query.
    $this->view->views_csc_search = TRUE;
  }

  /**
   * Implements views_handler_field#click_sortable().
   */
  function click_sortable() {
    return $this->options['use_csc_search_click_sortable'] != self::CLICK_SORT_DISABLED;
  }

  /**
   * Implements views_handler_field#click_sort().
   *
   * @see self::csc_search_post_execute()
   */
  function click_sort($order) {
    $this->csc_search_click_sort_order = $order;
  }

  /**
   *
   * @see views_csc_search_views_pre_execute()
   * @see self::csc_search_post_execute()
   */
  function csc_search_pre_execute() {
    // Ecexute static PHP code.
    if (!empty($this->options['csc_search_setup'])) {
      $function = create_function('$view, $handler, &$static', $this->options['csc_search_setup'] . ';');
      ob_start();
      $function($this->view, $this, $this->csc_search_static_variable);
      ob_end_clean();
    }
  }

  /**
   *
   * @see views_csc_search_views_post_execute()
   */
  function csc_search_post_execute() {
  }

  /**
   * Helper function; usort callback for numeric sort.
   */
  function csc_search_click_sort_numeric($a, $b) {
    return $a - $b;
  }

  /**
   * Implements views_handler_field#render().
   */
  function render($values) {
    $value = 'It WORKS!';
    return $value;
  }
}
