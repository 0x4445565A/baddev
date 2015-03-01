<?php
/**
 * Globals
 */
$user = NULL;
$hooks = array();
$connection = NULL;
$title = '';
$scripts = '';
$css = '';
$header = '';
$body = '';
$footer = '';
$navigation = array(
  'Home' => array(
    'base' => '/',
    'query' => array(
      'p' => 'index',
    ),
  ),
  'Login' => array(
    'base' => '/',
    'query' => array(
      'p' => 'login',
    ),
  ),
  'Register' => array(
    'base' => '/',
    'query' => array(
      'p' => 'register',
    ),
  ),
);

function common_attach_scripts($s = array()) {
  global $scripts;
  foreach ($s as $type => $script) {
    if ($type == 'inline') {
      $scripts .= '<script>' . $script  . '</script>';
    }
    else {
      $scripts .= '<script src="' . $script . '"></script>';
    }
  }
}

function common_attach_css($c = array()) {
  global $css;
  foreach ($c as $type => $style) {
    if ($type == 'inline') {
      $css .= '<style>' . $style  . '</style>';
    }
    else {
      $css .= '<link href="' . $style  . '" rel="stylesheet" />';
    }
  }
}

function common_attach_includes() {
  global $hooks;
  $includes = scandir('./includes');
  foreach ($includes as $file) {
    if (!preg_match("/\.inc$/", $file)) { continue; }
    include_once('./includes/' . $file);
    $hooks[] = str_replace('.inc', '', $file);
  }
}

function common_bootstrap() {
  global $hooks;
  common_attach_includes();
  foreach ($hooks as $hook) {
    if (function_exists($hook . '_bootstrap')) {
      $func = $hook . '_bootstrap';
      $func();
    }
  }
}
