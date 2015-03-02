<?php
function mysql_bootstrap() {
  mysql_database_connect();
}

function mysql_database_connect() {
  global $mysql;
  global $connection;
  $connection = new mysqli($mysql['server'], $mysql['user'], $mysql['password'], $mysql['database']);
  if ($connection->connect_errno) {
    echo "Failed to connect to MySQL: (" . $connection->connect_errno . ") " . $connection->error;
  }
}

function mysql_database_query($sql) {
  global $connection;
  return $connection->query($sql);
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
