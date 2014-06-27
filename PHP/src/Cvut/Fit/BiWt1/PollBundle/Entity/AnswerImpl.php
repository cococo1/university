<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity;

use Cvut\Fit\BiWt1\PollBundle\Common\IdentifiedClass;
use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\DummyRespondentImpl;

abstract class AnswerImpl extends IdentifiedClass implements Answer
{
	protected $respondent; //should implement Respondent interface;
	protected $question; //should implement Question interface. !!!!! each non-abstract class should initialize this!

	public function __construct() 
	{
		//vygeneruje se id z vzdaleneho rodice IdentifiedClass
		parent::__construct();
		$this->respondent = new DummyRespondentImpl;
	}


	public function getRespondent()
	{
		return $this->respondent;
	}


	public function setRespondent(Respondent $respondent)
	{
		if (!$respondent)
		 {
			throw new \LogicException("Respondent cannot be empty!");
		}
		$this->respondent = $respondent;
	}


	public function getQuestion()
	{
		return $this->question;
	}


}
?>