<?php

function theme_bootstrap() {
  common_attach_css(array('file' => '/css/bootstrap.min.css'));
  theme_page();
}

function theme_page() {
  if (isset($_GET['p'])) {
    $page = preg_replace('/[^\da-z]/i', '_', $_GET['p']);
    $func = 'theme_page_' . $page;
    if (!function_exists($func)) {
      theme_page_404();
      return;
    }
    $func();    
  }
  else {
    theme_page_index();
  }
}

function theme_page_i_dont_understand() {
  global $body;
  $body = 'hi mer';
}

function theme_page_index() {
  global $body;
  $body .= 'BAH';
}

function theme_page_404() {
  global $body;
  $body = '<h1>404</h1>
           <p><b>' . $_GET['p'] . '</b> not found!</p>';
}

function theme_page_login() {
  global $body;
  if (isset($_POST['username'], $_POST['password'])) {
    print_r($_POST);
  }
  $body .= '<form action="?p=login" method="POST">
            <input type="text" name="username" placeholder="Username">
            <input type="password" name="password" placeholder="Password">
            <input type="submit">
            </form>';
}

