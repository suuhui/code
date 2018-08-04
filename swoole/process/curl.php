<?php
$urls = array(
	'http://www/baidu.co1',
	'http://www/baidu.co2',
	'http://www/baidu.co3',
	'http://www/baidu.co4',
	'http://www/baidu.co5',
	'http://www/baidu.co6',
	'http://www/baidu.co7',
);

$workers = [];


for($i = 0; $i < 7; $i++) {
	$pro = new swoole_process(function(swoole_process $process) use ($urls, $i){
		$data = curlData($urls[$i]);
		echo $data;
	}, true);

	$pid = $pro->start();
	$workers[$pid] = $pro;
}
$s = microtime(true);
foreach($workers as $worker) {
	$cont = $worker->read();
	echo $cont;
}
$e = microtime(true);
echo $e - $s . PHP_EOL;


function curlData($url)
{
	sleep(2);
	echo $url . ' success' . PHP_EOL;
}
