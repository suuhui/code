<?php
class WsServer
{
    private const HOST = '0.0.0.0';
    private const PORT = 9501;

    private $ws;

    public function __construct()
    {
        $this->init();
    }

    public function serverStart()
    {
        $this->ws->start();
    }

    private function init()
    {
        $this->ws = new swoole_websocket_server(self::HOST, self::PORT);
        $this->ws->set([
            'task_worder_num' => 4,
            'worker_num' => 2,
        ]);

        $this->ws->on('workerStart', [$this, 'onWorkerStart']);
        $this->ws->on('request', [$this, 'onRequest']);
        $this->ws->on('open', [$this, 'onOpen']);
        $this->ws->on('message', [$this, 'onMessage']);
        $this->ws->on('task', [$this, 'onTask']);
        $this->ws->on('finish', [$this, 'onFinish']);
        $this->ws->on('close', [$this, 'onClose']);
    }

    public function onWorkerStart($serv, $worderId)
    {
        define('LARAVEL_START', microtime(true));
        require __DIR__ . '/../vendor/autoload.php';
    }

    public function onRequest($rq, $rp)
    {
        if(isset($rq->server)) {
            foreach($rq->server as $k => $s) {
                $_SERVER[strtoupper($k)] = $s;
            }
        }
        if(isset($rq->get)) {
            foreach($rq->get as $k => $s) {
                $_GET[strtoupper($k)] = $s;
            }
        }
        if(isset($rq->post)) {
            foreach($rq->post as $k => $s) {
                $_POST[strtoupper($k)] = $s;
            }
        }
        if(isset($rq->header)) {
            foreach($rq->header as $k => $s) {
                $_SERVER[strtoupper($k)] = $s;
            }
        }
        ob_start();
        $app = new Illuminate\Foundation\Application(
            realpath(__DIR__.'/../')
        );

        $app->singleton(
            Illuminate\Contracts\Http\Kernel::class,
            App\Http\Kernel::class
        );

        $app->singleton(
            Illuminate\Contracts\Console\Kernel::class,
            App\Console\Kernel::class
        );

        $app->singleton(
            Illuminate\Contracts\Debug\ExceptionHandler::class,
            App\Exceptions\Handler::class
        );

        $kernel = $app->make(Illuminate\Contracts\Http\Kernel::class);

        $response = $kernel->handle(
            $request = Illuminate\Http\Request::capture()
        );

        $response->send();

        $kernel->terminate($request, $response);

        $res = ob_get_contents();
        ob_end_clean();

        $rp->end($res);
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

        // $data = array(
        //     'task' => 1,
        //     'fd' => $frame->fd,
        // );
        // swoole_timer_after(5000, function() use ($server, $frame) {
        //     echo '5s after ' . PHP_EOL;
        //     $server->push($frame->fd, 'after 5s server push');
        // });
        // $server->task($data);
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
     * @param  int $fd
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
$server = new WsServer;
$server->serverStart();
