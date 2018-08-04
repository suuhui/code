<?php
$client = new swoole_client(SWOOLE_SOCK_TCP);
if(!$client->connect('127.0.0.1', 9501)) {
    echo 'connect fail';
    exit();
}

fwrite(STDOUT, 'enter message:');
$msg = trim(fgets(STDIN));

if(!$client->send($msg))
    die('send message fail');

$response = $client->recv();

if(!$response)
die('recv faile');

echo $response . PHP_EOL;

$client->close();