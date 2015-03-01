<?php

function theme_bootstrap() {
  common_attach_css(array(
    'boot' => '/css/bootstrap.min.css',
    'main' => '/css/main.css',
  ));
  theme_page();
}

function theme_page() {
  theme_header();
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


function theme_build_nav_link($nav, $text) {
  $link = '<li class="' . (isset($_GET['p']) && $_GET['p'] == $nav['query']['p'] ? 'active' : '')  .'">';
  $url = $nav['base'];
  reset($nav['query']);
  $first = key($nav['query']);
  foreach ($nav['query'] as $query => $data) {
    $url .= ($query === $first ? '?' : '&') . $query . '=' . $data;
  }
  $link .= '<a href="' . $url  . '">' . $text  . '</a>';
  $link .= '</li>';
  return $link;
}

function theme_header() {
  global $header;
  global $navigation;
  $header .= '
    <nav class="navbar navbar-inverse">
    <div class="contianer-fluid"> 
    <div class="collapse navbar-collapse" id="nav">
      <ul class="nav navbar-nav">';
      foreach ($navigation as $text => $nav) {
        $header .= theme_build_nav_link($nav, $text);
      }
    $header .= '</ul>
    </div>
    </div>
    </nav>
  ';
}

function theme_page_i_dont_understand() {
  global $body;
  $body = 'hi mer';
}

function theme_page_index() {
  global $body;
  $body .= '<h2>Welcome to BaDDeV</h2>
            <p>BaDDev is a sandboxed website designed to teach developers about common exploits; how they work and how to fix them.</p>
            <p>Developers should never place this website on a server OR network you care about.  It is extremly dangerous and <b>very</b> vulnerable.</p>
            <p><b>NOTE:</b> Exploitation of this server is allowed under the condition that the users do not deface files (Attacking profiles and dynamic pages in the form of XSS <b>is</b> allowed).</p>
            <p>Also, please do not use real email address or real passwords on this site.  Consider ever single piece of data on this site to be logged by either the site or an attacker.</p>

';
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
    $body .= '<div class="alert alert-danger" role="alert">
     <b>Incorrect username or password</b> Please check your input and try again.
   </div>';
  }
  $body .= '<form action="?p=login" method="POST" class="form-signin">
            <h2 class="form-signin-heading">Please sign in</h2>           
            <input type="text" name="username" class="form-control" placeholder="Username">
            <br>
            <input type="password" name="password" class="form-control" placeholder="Password">
            <br>
            <input type="submit" class="btn btn-success btn-block">
            </form>';
}

function theme_page_list() {
  global $body;
  $query = mysql_database_query("SELECT uid, mail, bio FROM users;");
  $results = mysql_database_get_results($query);
  $body .= '<table class="table">';
  $body .= '<thead><tr>
              <th>User Mail</th>
              <th>User Bio</th>
            </tr></thead><tbody>';
  foreach ($results as $result) {
    $body .= '<tr class="uid-' . $result['uid'] . '">
                <td>' . $result['mail']  . '</td>
                <td>' . $result['bio']  . '</td>
              </tr>';
  }
  $body .= '</tbody></table>';
}
