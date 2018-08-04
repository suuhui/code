<?php

$str = '';
for($i = 0; $i < 100000; $i++) {
	$str .= rand(0, 99);
	$str .= ($i % 40 == 0) ? PHP_EOL : '';
}

swoole_async_writefile('./log.log', $str, function($filename) {
	echo 'write success' . PHP_EOL;
}, FILE_APPEND);

echo 'start' . PHP_EOL;
