<?php
$serv = new swoole_server("127.0.0.1", 9501);

$serv->set([
    'worker_num' => 4,
    'max_request' => 10000,
]);

$serv->on('connect', function($serv, $fd, $reactor_id) {
    echo "Client: {$reactor_id} - {$fd} - connent." . PHP_EOL;
});

$serv->on('receive', function($serv, $fd, $reactor_id, $data) {
    $serv->send($fd, "Server: {$reactor_id} - {$fd}" . $data);
});

$serv->on('close', function($serv, $fd) {
    echo 'Client: close.' . PHP_EOL;
});

$serv->start();
