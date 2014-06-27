<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

use Cvut\Fit\BiWt1\PollBundle\Entity\AnswerImpl;

abstract class ChoiceAnswerImpl extends AnswerImpl implements ChoiceAnswer 
{

	public function __construct()
	{
		parent::__construct();
	}
	
}
?>