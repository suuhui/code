<?php

/**
 * asyn read file
 */
swoole_async_readfile(__DIR__ . '/r.txt', function($fn, $cont) {
	echo 'filename: ' . $fn . ' : content:' . $cont . PHP_EOL;
});
