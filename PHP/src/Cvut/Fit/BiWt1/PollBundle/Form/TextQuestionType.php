<?php
// src/Cvut/Fit/BiWt1/PollBundle/Form/TextQuestionType.php

namespace Cvut\Fit\BiWt1\PollBundle\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;

class TextQuestionType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder->add('question', 'textarea', array( 'data' => isset($options['data']) ?  $options['data']->getQuestion() : ''  ));

    }

    public function getName()
    {
        return 'textQuestion';
    }
}