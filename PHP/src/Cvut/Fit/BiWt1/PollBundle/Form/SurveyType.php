<?php
// src/Cvut/Fit/BiWt1/PollBundle/Form/SurveyType.php

namespace Cvut\Fit\BiWt1\PollBundle\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;

class SurveyType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        // echo $options['data']->getTitle() ; 
        $builder->add('title', 'text', array( 'data' => isset($options['data']) ?  $options['data']->getTitle() : ''  ));
        $builder->add('description', 'textarea', array( 'data' => isset($options['data']) ?  $options['data']->getDescription() : ''  ));
        // $arrayOfQuestions = $options['data'];
        // foreach ($arrayOfQuestions as $question)
        // {
        // 	$builder->add($question->getId(), 'textarea', array( 'data' => $question->getQuestion()  ));
        // }
                // $builder->add('question', 'textarea', array( 'data' => isset($options['data']) ?  $options['data']->getQuestion() : ''  ));


    }

    public function getName()
    {
        return 'survey';
    }
}