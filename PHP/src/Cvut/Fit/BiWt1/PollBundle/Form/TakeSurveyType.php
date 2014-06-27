<?php
// src/Cvut/Fit/BiWt1/PollBundle/Form/TakeSurveyType.php

namespace Cvut\Fit\BiWt1\PollBundle\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;

class TakeSurveyType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {

        $survey = NULL;
        if (isset($options['data'])) $survey = $options['data'];

        $builder->add('title', 'text', array( 'data' => isset($options['data']) ?  $options['data']->getTitle() : ''  ));
        $builder->add('description', 'textarea', array( 'data' => isset($options['data']) ?  $options['data']->getDescription() : ''  ));
        
        // $builder->add('items', 'collection', array('type' => new QuestionType()));

        // $arrayOfQuestions = $options['data'];
        // foreach ($arrayOfQuestions as $question)
        // {
        // 	$builder->add($question->getId(), 'textarea', array( 'data' => $question->getQuestion()  ));
        // }
                // $builder->add('question', 'textarea', array( 'data' => isset($options['data']) ?  $options['data']->getQuestion() : ''  ));


    }

    // public function setDefaultOptions(OptionsResolverInterface $resolver)
    // {
    //     $resolver->setDefaults(array(
    //         'data_class' => 'Cvut\Fit\BiWt1\PollBundle\Entity\PollImpl',
    //     ));
    // }


    public function getName()
    {
        return 'takeSurvey';
    }
}