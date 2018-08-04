<?php
$process = new swoole_process(function (swoole_process $pro) {
	$pro->exec('/usr/bin/php', [__DIR__ . '/../server/http_server.php']);
}, false);

$pid = $process->start();
echo $pid . PHP_EOL;

swoole_process::wait();
