<?php
$str = file_get_contents('mime-mixed-related-alternative.eml');

preg_match_all('/((?<=(Content-Type: multipart\/mixed; boundary="))(.*)?(?=(")))|((?<=(Content-Type: multipart\/related; boundary="))(.*)?(?=(")))|((?<=(Content-Type: multipart\/alternative; boundary="))(.*)?(?=(")))/', $str, $boundary);

echo "<pre>";
print_r($boundary);

die();
?>
