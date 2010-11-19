<?php
// $Id: var_export.drush.inc

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function var_export_drush_help($section) {
  switch ($section) {
    case 'drush:variable-export':
      return dt("Export variables for your site");
  }
}


/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * @return
 *   An associative array describing your command(s).
 */
function var_export_drush_command() {
  $items['variable-export'] = array(
    'description' => 'Get a list of some or all site variables and values.',
    'arguments' => array(
      'name' => 'A string to filter the variables by.  Only variables beginning with the string will be listed.',
    ),
    'examples' => array(
      'drush vexport' => 'List all variables and values.',
      'drush vexport user' => 'List all variables beginning with the string "user".',
    ),
    'aliases' => array('vexport'),
  );

  return $items;
}

/**
 * Command callback.
 * List your site's variables.
 */
function drush_variable_export() {
  global $conf;
  $keys = array_keys($conf);
  if ($args = func_get_args()) {
    $keys = preg_grep("/{$args[0]}/", $keys);
  }
  foreach ($keys as $name) {
    drush_print('features[variable][] = "' . $name  .'"');
  }
}