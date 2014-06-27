<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceQuestionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\OptionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Exception\IncompatibleClassException;






class SingleChoiceAnswerImpl extends ChoiceAnswerImpl implements SingleChoiceAnswer 
{
	protected $answer; //Option

	public function __construct()
	{
		parent::__construct();
		$this->question = new SingleChoiceQuestionImpl;
		$this->answer = null;
	}
	/**
	 * Nastaveni odpovedi
	 * @param Option $answer
	 * @return SingleChoiceAnswer
	 */
	public function setAnswer(Option $answer)
	{
		if ($this->question->hasOption($answer))
		{	
			$this->answer = $answer;
			$this->question->addAnswer($this);
			$answer->addAnswer($this);
		}
		return $this;
	}

	/**
	 * @return Option|Options
	 */
	public function getAnswer()
	{
		return $this->answer;
	}

		/**
	 * Metoda resi na zaklade konstanty potomka compatibleClass
	 * kontrolu, zda je predany datovy typ spravny (nejen Question,
	 * ale konkretni Question napr. TextQuestion).
	 * @param Question $question
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 * @throws \LogicException pokud trida/rozhrani, se kterou je odpoved kompatibilni, neexistuje
	 * @throws IncompatibleClassException otazka neni kompatibilni s touto odpovedi
	 */
	public function setQuestion(Question $question)
	{
		if (!$question)
			throw new \LogicException("Question cannot be empty!");
		if ($question instanceof SingleChoiceQuestionImpl)
		{
			$this->question = $question;
		}
		else { throw new IncompatibleClassException(); }
		
		return $this;
	}
}
?>