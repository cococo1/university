<?php
// src/Blogger/BlogBundle/Entity/Enquiry.php

namespace  Cvut\Fit\BiWt1\PollBundle\Entity;

use Symfony\Component\Validator\Mapping\ClassMetadata;
use Symfony\Component\Validator\Constraints\NotBlank;
use Symfony\Component\Validator\Constraints\Email;
use Symfony\Component\Validator\Constraints\MinLength;
use Symfony\Component\Validator\Constraints\MaxLength;

class Enquiry
{
    protected $name;

    protected $email;

    protected $subject;

    protected $body;

    protected $typeOfQuestion;

    public function getName()
    {
        return $this->name;
    }

    public function setName($name)
    {
        $this->name = $name;
    }

    public function getEmail()
    {
        return $this->email;
    }

    public function setEmail($email)
    {
        $this->email = $email;
    }

    public function getSubject()
    {
        return $this->subject;
    }

    public function setSubject($subject)
    {
        $this->subject = $subject;
    }

    public function getBody()
    {
        return $this->body;
    }

        public function setBody($body)
    {
        $this->body = $body;
    }

    public function getTypeOfQuestion()
    {
        return $this->typeOfQuestion;
    }

    public function setTypeOfQuestion($typeOfQuestion)
    {
        $this->typeOfQuestion = $typeOfQuestion;
    }

    public static function loadValidatorMetadata(ClassMetadata $metadata)
    {
        $metadata->addPropertyConstraint('name', new NotBlank());

        $metadata->addPropertyConstraint('email', new Email());

        $metadata->addPropertyConstraint('subject', new NotBlank());
        $metadata->addPropertyConstraint('subject', new MaxLength(50));

        // $metadata->addPropertyConstraint('body', new MinLength(50));
    }
}