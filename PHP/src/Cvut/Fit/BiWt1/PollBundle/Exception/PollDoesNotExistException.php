<?php
namespace Cvut\Fit\BiWt1\PollBundle\Exception;

class PollDoesNotExistException extends \Exception
{
    public function __construct($message = "", $code = 0) 
    {
        parent::__construct($message, $code);
    }

    public function __toString() {
        return __CLASS__ . ": [{$this->code}]: {$this->message}\n";
    }
}
?>