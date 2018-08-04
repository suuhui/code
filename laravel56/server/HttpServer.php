<?php
class HttpServer
{
    const HOST = '0.0.0.0';
    const PORT = 8080;

    private $http;

    public function __construct()
    {
        $this->init();
    }

    public function serverStart()
    {
        $this->http->start();
    }

    private function init()
    {
        $this->http = new swoole_http_server(self::HOST, self::PORT);
        $this->http->set([
            'enable_static_handler' => true,
            'document_root' => '/home/code/laravel56/',
            'worker_num' => 5,
        ]);

        $this->http->on('workerStart', [$this, 'onWorkerStart']);
        $this->http->on('request', [$this, 'onRequest']);
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

        $pathinfo = pathinfo($_SERVER['REQUEST_URI']);
        $extension = isset($pathinfo['extension']) ? $pathinfo['extension'] : '';
        switch ($extension) {
            case 'css':
                $rp->header('Content-Type', 'text/css');
                break;
            case 'js':
                $rp->header('Content-Type', 'application/javascript');
                break;
            default:
                break;
        }
        $rp->end($res);
    }
}
$server = new HttpServer;
$server->serverStart();
