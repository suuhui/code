<?php

namespace App\Mail;

use Illuminate\Bus\Queueable;
use Illuminate\Mail\Mailable;
use Illuminate\Queue\SerializesModels;
use Illuminate\Contracts\Queue\ShouldQueue;

class MailClient extends Mailable
{
    use Queueable, SerializesModels;

    /**
     * Which view to use
     * @var string
     */
    public $view;

    /**
     * Data
     * @var array
     */
    public $data;

    /**
     * Create a new message instance.
     *
     * @return void
     */
    public function __construct($data, $view)
    {
        $this->data = $data;
        $this->view = $view;
    }

    /**
     * Build the message.
     *
     * @return $this
     */
    public function build()
    {
        $mailFrom = config('mail.from');
        return $this->from($mailFrom['address'])
                    ->view($this->view);
    }
}
