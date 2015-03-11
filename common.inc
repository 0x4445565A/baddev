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
  'Users' => array(
    'base' => '/',
    'query' => array(
      'p' => 'list',
    ),
  ),
  'Search' => array(
    'base' => '/',
    'query' => array(
      'p' => 'search',
    ),
  ),
  'Calendar' => array(
    'base' => '/',
    'query' => array(
      'p' => 'cal', 
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
  'Theme Red' => array(
    'base' => '/',
    'query' => array(
      'p' => isset($_GET['p']) ? $_GET['p'] : 'index',
      'theme' => 'red.css',
    ),
  ),
  'Theme Black' => array(
    'base' => '/',
    'query' => array(
      'p' => isset($_GET['p']) ? $_GET['p'] : 'index',
      'theme' => 'black.css',
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
  global $navigation;
  $session_id = session_id();
  if (empty($session_id)) session_start();
  common_attach_includes();
  if (isset($_SESSION['uid'])) {
    unset($navigation['Login'], $navigation['Register']);
    $navigation['Edit Profile'] = array(
      'base' => '/',
      'query' => array(
        'p' => 'user-edit',
      ),
    );
    $navigation['Logout'] = array(
      'base' => '/',
      'query' => array(
        'p' => 'logout',
      ),
    );
  }
  common_hook('bootstrap');
  common_hook('alter');
}

function common_hook($func) {
  global $hooks;
  foreach ($hooks as $hook) {
    $hook = $hook . '_' . $func;
    if (function_exists($hook)) {
      $hook();
    }
  }
}

function common_login_user($uid) {
  $_SESSION['uid'] = $uid;
}
