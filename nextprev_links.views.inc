<?php

/**
 * @file
 * 
 * Views plugin implementations for Next Prev Links.
 */

/**
 * Implements hook_views_plugins
 */
function nextprev_links_views_plugins() {
  return array(
    'pager' => array(
      'nextprev_links' => array(
        'title' => t('Paged output, full pager (with rel next and prev links)'),
        'short title' => t('Full (rel links)'),
        'help' => t('Paged output, full Drupal style (with rel next and prev links)'),
        'handler' => 'nextprev_links_pager',
        'help topic' => 'pager-nextprev',
        'uses options' => TRUE,
        'parent' => 'full',
      ),
    ),
  );
}

/**
 * The plugin to provide the Next Prev Links.
 *
 * @ingroup views_pager_plugins
 */
class nextprev_links_pager extends views_plugin_pager_full {

  /**
   * Overrides views_plugin_pager_full::render().
   *
   * Overrides the full pager renderer by changing the theme function
   * and leaving out variables that are not used in the mini pager.
   */
  function render($input) {
    $pager_theme = views_theme_functions('nextprev_links_pager', $this->view, $this->display);
    // The 0, 1, 3, 4 index are correct. See theme_pager documentation.
    $tags = array(
      0 => $this->options['tags']['first'],
      1 => $this->options['tags']['previous'],
      3 => $this->options['tags']['next'],
      4 => $this->options['tags']['last'],
    );
    $output = theme($pager_theme, array(
      'tags' => $tags,
      'element' => $this->get_pager_id(),
      'parameters' => $input,
      'quantity' => $this->options['quantity'],
    ));
    return $output;
  }
}
