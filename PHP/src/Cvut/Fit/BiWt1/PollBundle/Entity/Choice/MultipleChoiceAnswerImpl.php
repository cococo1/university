<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;


use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceAnswer;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceQuestionImpl;
use Cvut\Fit\BiWt1\PollBundle\Common\Collection;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;


class MultipleChoiceAnswerImpl extends ChoiceAnswerImpl implements MultipleChoiceAnswer
{
	protected $answers; //Collection // ???? Should we use a collection? there is no arrow.

	public function __construct()
	{
		parent::__construct();
		$this->answers = new Collection;
		$this->question = new MultipleChoiceQuestionImpl;
	}

	/**
	 * prida zvolenou moznost do kolekce odpovedi
	 * @param Option $option
	 * @return MultipleChoiceQuestion
	 */
	public function addAnswerOption(Option $option)
	{
		if ($this->question->hasOption($option))
		{
			$this->answers->addItem($option);
			$this->question->addAnswer($this);
			$option->addAnswer($this);
		}
		return $this;
	}

	/**
	 * odebere zvolenou moznost z kolekce odpovedi
	 * @param Option $option
	 * @return ChoiceAnswer//ChoiceQuestion
	 */
	public function removeAnswerOption(Option $option)
	{
		if ($this->answers->hasItem($option))
		{
			$this->answers->removeItem($option); //strict = false, so no exception thrown.
			$this->question->removeAnswer($this);
			$option->removeAnswer($this);
		}
		return $this;
	}

	/**
	 * vrati pole zvolenych moznosti
	 * @return array[Option]
	 */
	public function getAnswer()
	{
		return $this->answers;
	}

	/**
	 * vrati jednotlivou polozku z kolekce odpovedi
	 * @param mixed $id
	 * @return Option
	 * @throws ItemDoesNotExistException
	 */
	public function getAnswerOption($id)
	{
		return $this->answers->getItem($id);
	}

	/**
	 * zjisti zda je moznost v kolekci odpovedi
	 * @param Option $option
	 * @return boolean
	 */
	public function hasAnswerOption(Option $option)
	{
		return $this->answers->hasItem($option);
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
		 {
			throw new \LogicException("Question cannot be empty!");
		}
		if ($question instanceof MultipleChoiceQuestionImpl)
		{
			$this->question = $question;
		}
		else throw new IncompatibleClassException();
		
		return $this;
	}


}
?>