<?php

namespace App\Http\Controllers;

use App\Http\Controllers\Controller;
use App\Mail\MailClient;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Mail;

class MailController extends Controller
{
    public $toAddress = '';
    public $username = '';
    public $sendData = [];

    /**
     * init mail config
     * @param string $to
     * @param string $username [description]
     * @param array $data [description]
     */
    public function __construct($to, $username, $data)
    {
        $this->toAddress = $to;
        $this->username = $username;
        $this->data = $data;
    }

    public function sendVerifyCodeEmail()
    {

    }

    public function send()
    {
        $toAddress = 'suhui527238294@163.com';
        $username = 'live';
        $code = '23423423';
        Mail::to($toAddress, 'live')
            ->send(new MailClient(['code' => $code], 'email.verifinedCode'));
    }
}
