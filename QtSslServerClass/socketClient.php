<?php
// echo base64_encode("demo@breakermind.com");
echo base64_encode("pass");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

$ctx = stream_context_create();
stream_context_set_option($ctx, 'ssl', 'verify_peer', false);
stream_context_set_option($ctx, 'ssl', 'verify_peer_name', false);
try{
    echo $socket = stream_socket_client('ssl://qflash.pl:3333', $err, $errstr, 60, STREAM_CLIENT_CONNECT, $ctx);
    if (!$socket) {
        print "Failed to connect $err $errstr\n";
        return;
    }else{
        // Http
        // fwrite($socket, "GET / HTTP/1.0\r\nHost: www.example.com\r\nAccept: */*\r\n\r\n");
        // Smtp
        echo fread($socket,8192);
        echo fwrite($socket, "EHLO localhost \n");
        echo fread($socket,8192);

        echo fwrite($socket, "MAIL FROM:hello@email.com \n");
        echo fread($socket,8192);

        echo fwrite($socket, "RCPT TO:hello@email.to \n");
        echo fread($socket,8192);

        echo fwrite($socket, "DATA\n");
        echo fread($socket,8192);

        echo fwrite($socket, "Date: ".time()."\r\nTo:hello@email.to\r\nFrom:hello@email.com\r\nSubject:Hello from php\r\n.\r\n");
        echo fread($socket,8192);

        echo fwrite($socket, "QUIT \n");
        echo fread($socket,8192);
        fclose($socket);
    }
}catch(Exception $e){
    echo $e;
}
die();
?>

<?php
/*
// get file
$filename = "bg.jpg";
$handle = fopen($filename, "rb");
$contents = fread($handle, filesize($filename));
fclose($handle);
*/
?>

<?php
/*
$socket = stream_socket_client("ssl://127.0.0.1:8888", $errno, $errstr);
if ($socket) {
        // fwrite($socket, "\n");
    echo fread($socket,8192);
}else{
        echo "Could not connect to server";
}


$ctx = stream_context_create();

stream_context_set_option($ctx, 'ssl', 'passphrase', 'password12345');
stream_context_set_option($ctx, 'ssl', 'local_cert', '/home/user/certificate.pem');
stream_context_set_option($ctx, 'ssl', 'cafile', '/home/user/ca_bundle.crt');
stream_context_set_option($ctx, 'ssl', 'verify_peer', false);
stream_context_set_option($ctx, 'ssl', 'verify_depth', '3');
stream_context_set_option($ctx, 'ssl', 'allow_self_signed', true);

//stream_context_set_option($ctx, 'ssl', 'cafile', '/home/user/qflash.crt');
//stream_context_set_option($ctx, 'ssl', 'cafile', '/home/user/certificate.pem');
//stream_context_set_option($ctx, 'ssl', 'CN_match', 'qflash.pl');
//stream_context_set_option($ctx, 'ssl', 'ciphers', 'HIGH:!SSLv2:!SSLv3');
//stream_context_set_option($ctx, 'ssl', 'disable_compression', true);


$ctx = stream_context_create(
    array('ssl'=>array(
        'local_cert'=> '/home/user/certificate.crt',
        'passphrase' => 'password12345',
        'cafile' => '/home/user/ca_bundle.crt',
        'allow_self_signed' => 'true',
        'verify_peer' => 'false'
    ))
);
$fp = stream_socket_client('ssl://qflash.pl:8888', $err, $errstr, 60, STREAM_CLIENT_CONNECT, $ctx);
if (!$fp) {
    print "Failed to connect $err $errstr\n";
    return;
}

$host = '127.0.0.1';
$port = 8888;
$timeout = 30;
$cert = '/home/user/certificate.pem'; // Path to certificate
$context = stream_context_create(
    array('ssl'=>array('local_cert'=> $cert))
);
if ($socket = stream_socket_client(
        'ssl://'.$host.':'.$port,
        $errno,
        $errstr,
        30,
        STREAM_CLIENT_CONNECT,
        $context)
) {
    // fwrite($socket, "\n");
    echo fread($socket,8192);
    fclose($socket);
} else {
   echo "ERROR: $errno - $errstr\n";
}
*/
?>
