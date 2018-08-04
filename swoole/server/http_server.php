<?php

    $http = new swoole_http_server('127.0.0.1', 8080);

    $http->set([
        'enable_static_handler' => true,
        'document_root' => '/home/code/swoole/resource',
    ]);
    $http->on('request', function($rq, $rp) {
        $rp->cookie('username', 'djfkjdjk', time()+60);
        $rp->end('<h1>hello swoole' . rand(0, 9999) . '</h1>' . print_r($rq->get, true));
    });

    $success = $http->start();
    if($success)
        echo 'http server start success' . PHP_EOL;
    else
        echo 'http server start failed' . PHP_EOL;