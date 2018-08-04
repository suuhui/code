<?php
class wsServer
{
    const HOST = '0.0.0.0';
    const PORT = '9501';

    private $server;
    public function __construct()
    {
        $this->server = new swoole_websocket_server(self::HOST, self::PORT);
        $this->server->set(array(
            'worker_num' => 2,
            'task_worker_num' => 4
        ));
        $this->server->on('open', [$this, 'onOpen']);
        $this->server->on('message', [$this, 'onMessage']);
        $this->server->on('task', [$this, 'onTask']);
        $this->server->on('finish', [$this, 'onFinish']);
        $this->server->on('close', [$this, 'onClose']);
    }

    /**
     * listen websocket establish event
     * @param  swoole_websocket_server $server
     * @param  $reqest
     * @return null
     */
    public function onOpen(swoole_websocket_server $server, $request)
    {
        echo 'server: handshake success with fd' . $request->fd . PHP_EOL;

        if($request->fd == 1) {
            swoole_timer_tick(2000, function($timer_id) {
                echo '2s: timer id : ' . $timer_id . PHP_EOL;
            });
        }
    }

    /**
     * @param  swoole_websocket_server
     * @param  [type]
     * @return [type]
     */
    public function onMessage(swoole_websocket_server $server, $frame)
    {
        echo 'receiver from ' . $frame->fd . ':' . $frame->data . ',opcode:' . $frame->opcode . ',fin:' . $frame->finish . PHP_EOL;

        var_dump($frame);
        $data = array(
            'task' => 1,
            'fd' => $frame->fd,
        );
        swoole_timer_after(5000, function() use ($server, $frame) {
            echo '5s after ' . PHP_EOL;
            $server->push($frame->fd, 'after 5s server push');
        });
        $server->task($data);
        $server->push($frame->fd, 'server push: i am 007,please callback');
    }

    /**
     * @param  swoole_server
     * @param  int
     * @param  int
     * @param  array
     * @return string
     */
    public function onTask(swoole_server $serv, int $taskId, int $workerId, $data)
    {
        print_r($data);
        sleep(4);

        return 'task run';
    }

    /**
     * @param  swoole_server
     * @param  int
     * @param  string
     * @return void
     */
    public function onFinish(swoole_server $serv, int $taskId, string $data)
    {
        echo "taskId: {$taskId}" . PHP_EOL;
        echo "finish data success:" . $data . PHP_EOL;
    }

    /**
     * @param  swoole_websocket_server
     * @param  [type]
     * @return [type]
     */
    public function onClose(swoole_websocket_server $server, $fd)
    {
        echo 'client ' . $fd . ' closed' . PHP_EOL;
    }

    public function start()
    {
        $this->server->start();
    }

    public function getServer()
    {
        return $this->server;
    }
}

$ws = new wsServer;
$ws->start();
