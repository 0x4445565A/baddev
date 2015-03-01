<?php
error_reporting(E_ALL);
include_once('common.inc');
common_bootstrap();
$title = $title == '' ? "#AKHax presents BaDDeV" : $title;
?>
<html>
  <head>
    <title><?php print $title; ?></title>
    <?php print $scripts; ?>
    <?php print $css; ?>
  </head>
  <body>
    <div class="container">
    <?php print $header; ?>
    <?php print $body; ?>
    </div>
    <?php print $footer; ?>
  </body>
</html>

