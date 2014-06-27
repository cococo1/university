<?php
namespace Cvut\Fit\BiWt1\PollBundle\Exception;

class ItemDoesNotExistException extends \Exception
{
    public function __construct($message = "", $code = 0) 
    {
        parent::__construct($message, $code);
    }

    // custom string representation of object
    public function __toString() {
        return __CLASS__ . ": [{$this->code}]: {$this->message}\n";
    }
	
}
?>