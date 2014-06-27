<?php
// src/Cvut/Fit/BiWt1/PollBundle/Form/EnquiryType.php

namespace Cvut\Fit\BiWt1\PollBundle\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;

class EnquiryType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder->add('name');
        $builder->add('email', 'email');
        $builder->add('subject');
        $builder->add('body', 'textarea');

    }

    public function getName()
    {
        return 'contact';
    }
}