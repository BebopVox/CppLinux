<?php

// Get app id
$app = (int)$_GET['app'];

// Get key value
// $key = htmlentities(quoted_printable_decode($_GET['key'],ENT_QUOTES,'UTF-8'));
$key = htmlentities($_GET['key'],ENT_QUOTES,'UTF-8');

// if key valid and app = 1
if($key == "ID-999" && $app == 1){
  return 1;
}else{
  return 0;
}

?>
