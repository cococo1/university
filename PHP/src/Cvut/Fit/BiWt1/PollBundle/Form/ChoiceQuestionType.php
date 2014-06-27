<?php
// src/Cvut/Fit/BiWt1/PollBundle/Form/ChoiceQuestionType.php

namespace Cvut\Fit\BiWt1\PollBundle\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;

class ChoiceQuestionType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder->add('question', 'textarea',  array( 'data' => isset($options['data']) ?  $options['data']->getQuestion() : ''  ));
        $builder->add('options', 'textarea',  array( 'data' => isset($options['data']) ?  $options['data']->getOptions() : ''  ));


    }

    public function getName()
    {
        return 'singleChoiceQuestion';
    }
}