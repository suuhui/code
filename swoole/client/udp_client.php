<?php
    $client = new swoole_client(SWOOLE_SOCK_UDP);

    if(!$client->connect('127.0.0.1', 9502))
        die('UDP connect failed');
    
    if(!$client->send('hello woeld'))
        die('UDP send failed');
    
    $res = $client->recv();

    var_dump($res);

    $client->close();