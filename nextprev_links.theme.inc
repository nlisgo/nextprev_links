<?php

/**
 * @file
 *
 * Contains the theme callbacks for our module
 */

/**
 * Theme callback for 'nextprev_links_pager'
 */
function theme_nextprev_links_pager($variables) {
  $interval = 1;
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  global $pager_page_array, $pager_total;

  if ($pager_page_array[$element] > 0) {
    // Add rel="prev".
    $page_new = pager_load_array($pager_page_array[$element] - $interval, $element, $pager_page_array);
    $head_link = _nextprev_links_prep_rel_link($page_new, $element, $parameters, 'prev');
    drupal_add_html_head($head_link, 'nextprev_links:prev:' . $head_link['#attributes']['href']);
  }

  if ($pager_page_array[$element] < ($pager_total[$element] - 1)) {
    // Add rel="next".
    $page_new = pager_load_array($pager_page_array[$element] + $interval, $element, $pager_page_array);
    $head_link = _nextprev_links_prep_rel_link($page_new, $element, $parameters, 'next');
    drupal_add_html_head($head_link, 'nextprev_links:next:' . $head_link['#attributes']['href']);
  }

  return theme('pager', $variables);
}

function _nextprev_links_prep_rel_link($page_new, $element, $parameters = array(), $rel = 'next') {
  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  return array(
    '#tag' => 'link',
    '#attributes' => array(
      'rel' => $rel,
      'href' => url(
        $_GET['q'],
        array(
          'query' => $query,
          'absolute' => TRUE,
        )
      ),
    ),
  );
}
