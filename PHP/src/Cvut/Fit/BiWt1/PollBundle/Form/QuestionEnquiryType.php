<?php
// src/Cvut/Fit/BiWt1/PollBundle/Form/EnquiryType.php

namespace Cvut\Fit\BiWt1\PollBundle\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;

class QuestionEnquiryType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder->add('typeOfQuestion', 'choice', array('choices'   => array('m' => 'Multiple choice', 's' => 'Single choice', 't' => 'Text question'),
         'required'  => true, 'expanded' => true, )); //'multiple' => false,

    }

    public function getName()
    {
        return 'questionType';
    }
}