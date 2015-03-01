<?php
function mysql_bootstrap() {
  mysql_database_connect();
}

function mysql_database_connect() {
  global $mysql;
  global $connection;
  $connection = mysqli_connect($mysql['server'], $mysql['user'], $mysql['password']);

  if (!$connection) {
    die('connection failed: ' . mysqli_connect_error());
  }
  mysqli_select_db($connection, $mysql['database']);
}

function mysql_database_query($sql) {
  global $connection;
  return mysqli_query($connection, $sql);
}

function mysql_database_get_results($query) {
  $return = array();
  if (mysqli_num_rows($query) > 0) {
    while ($row = mysqli_fetch_assoc($query)) {
      $return[] = $row;
    }
  }
  return $return;
}
