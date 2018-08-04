<?php

/**
 * table test
 */
$table = new swoole_table(1024);

$table->column('id', swoole_table::TYPE_INT, 4);
$table->column('name', swoole_table::TYPE_STRING, 64);
$table->create();

$table->set('grey', ['id'=>2, 'name'=>'test']);
$table->incr('grey', 'id', 5);

$table->set('gray', ['id'=>3, 'name'=>'ttttt']);

foreach($table as $t) {
	print_r($t);
}

// print_r($table->get('grey'));
