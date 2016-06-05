<?php

/**
 * @file
 * Utility functions.
 */

/**
 * AJAX callback to populate current year.
 * 
 * @param string $pid
 *   PID of newspaper object
 * @param string $year
 *   Year requested
 */
function agile_newspaper_view_get_year() {
  module_load_include('inc', 'islandora_newspaper', 'includes/utilities');
  $year = intval(filter_input(INPUT_POST, 'year'));
  $pid = filter_input(INPUT_POST, 'pid');
  $object = islandora_object_load($pid);
  $issues = islandora_newspaper_get_issues($object);
  $grouped_issues = islandora_newspaper_group_issues($issues);
  $months = $grouped_issues[$year];
  $tabs[$year] = array(
    '#title' => $year,
    '#type' => 'fieldset',
  );
  foreach ($months as $month => $days) {
    $month_name = t("@date", array(
      "@date" => date("F", mktime(0, 0, 0, $month, 1, 2000)),
    ));
    $tabs[$year][$month] = array(
      '#title' => $month_name,
      '#type' => 'fieldset',
      '#attributes' => array(
        'class' => array('collapsible', 'month', 'collapsed'),
      ),
    );
    foreach ($days as $day => $issues) {
      foreach ($issues as $issue) {
        $tabs[$year][$month][$day][] = array(
          '#theme' => 'link',
          '#prefix' => '<div>',
          '#suffix' => '</div>',
          '#text' => t("@month @day, @year", array(
            '@year' => $year,
            '@month' => $month_name,
            '@day' => $day,
          )),
          '#path' => "islandora/object/{$issue['pid']}",
          '#options' => array(
            'attributes' => array(),
            'html' => FALSE,
          ),
        );
      }
    }
    ksort($tabs[$year][$month]);
  }
  ksort($tabs[$year]);
  agile_newspaper_view_add_images($tabs[$year]);
  echo drupal_render($tabs[$year]);
}

/**
 * Adds images to default issue output.
 *
 * @param array $years
 *  All represented years
 * @param array $input_array
 *   Existing rendered array
 */
function agile_newspaper_view_add_images(&$input_array) {
  $months = element_children($input_array);
  foreach ($months as $month) {
    $issues = element_children($input_array[$month]);
    foreach ($issues as $issue) {
      $path = $input_array[$month][$issue][0]['#path'];
      $input_array[$month][$issue][0]['#prefix'] = '<span class = "agile_issue_title">';
      $input_array[$month][$issue][0]['#suffix'] = '</span>';
      $img = agile_newspaper_view_make_element($path);

      $input_array[$month][$issue][] = array(
        '#theme' => 'link',
        '#prefix' => '<span class = "agile_issue_image">',
        '#suffix' => '</span>',
        '#text' => drupal_render($img),
        '#path' => $path,
        '#options' => array(
          'attributes' => array(),
          'html' => TRUE,
        ),
      );
    }
  }
}

/**
 * Makes image element
 *
 * @param string $path
 *   Path to islandora object
 * @return array
 *   Image element for render array
 */
function agile_newspaper_view_make_element($path) {
  return array(
    '#theme' => 'image',
    '#prefix' => '<span class = "agile_issue_image">',
    '#suffix' => '</span>',
    '#height' => '80px',
    '#path' => "/$path/datastream/TN/view",
    '#attributes' => array('class' => 'agile_newspaper_thumb', 'data' => "/$path/datastream/TN/view"),
    '#options' => array(
      'attributes' => array(),
      'html' => FALSE,
    ),
  );
}
