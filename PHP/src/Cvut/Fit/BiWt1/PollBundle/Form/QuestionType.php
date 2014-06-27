<?php
// src/Cvut/Fit/BiWt1/PollBundle/Form/QuestionType.php

namespace Cvut\Fit\BiWt1\PollBundle\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;

class QuestionType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder->add('name');
        // echo $options['data']->getTitle() ; 
        // $question = NULL;
        // if (isset($options['data']))
        // {
        //     $question = $options['data'];

        //     $builder->add('question', 'text', array( 'data' => isset($options['data']) ?  $options['data']->getQuestion() : ''  ));

        //     $options = NULL;
        //     if (strcmp($question->getType(), "textQuestion")) 
        //         foreach ($question->getOptions() as $option)
        //         {
        //             $options[$option->getId()] = $option->getOption();
        //         }
        //     if (! strcmp($question->getType(), "singleChoiceQuestion")) $builder->add('answer', 'choice', array('choices' => $options));
        //     if (! strcmp($question->getType(), "multipleChoiceQuestion")) $builder->add('answerOption', 'checkbox', array('choices' => $options));  

            // $builder->add('description', 'textarea', array( 'data' => isset($options['data']) ?  $options['data']->getDescription() : ''  ));
            // $arrayOfQuestions = $options['data'];
            // foreach ($arrayOfQuestions as $question)
            // {
            // 	$builder->add($question->getId(), 'textarea', array( 'data' => $question->getQuestion()  ));
            // }
                    // $builder->add('question', 'textarea', array( 'data' => isset($options['data']) ?  $options['data']->getQuestion() : ''  ));
        }


    }

    // public function setDefaultOptions(OptionsResolverInterface $resolver)
    // {
    //     $resolver->setDefaults(array(
    //         'data_class' => 'Cvut\Fit\BiWt1\PollBundle\Entity\Question',
    //     ));
    // }

    public function getName()
    {
        return 'question';
    }
}