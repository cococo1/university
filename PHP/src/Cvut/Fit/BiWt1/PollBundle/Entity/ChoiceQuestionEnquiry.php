<?php
// src/Blogger/BlogBundle/Entity/ChoiceQuestionEnquiry.php

namespace  Cvut\Fit\BiWt1\PollBundle\Entity;

use Symfony\Component\Validator\Mapping\ClassMetadata;
use Symfony\Component\Validator\Constraints\NotBlank;



class ChoiceQuestionEnquiry
{
    protected $question; //string

    protected $options; //string

    public function setQuestion($question)
    {
        $this->question = $question;
    }

    public function getQuestion()
    {
        return $this->question;
    }

    public function setOptions($options)
    {
        $this->options = $options;
    }

    public function getOptions()
    {
        return $this->options;
    }



    public static function loadValidatorMetadata(ClassMetadata $metadata)
    {
        $metadata->addPropertyConstraint('question', new NotBlank());
        $metadata->addPropertyConstraint('options', new NotBlank());


    }
}