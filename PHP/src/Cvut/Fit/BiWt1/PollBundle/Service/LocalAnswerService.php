<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory;
use \Cvut\Fit\BiWt1\PollBundle\Exception\AnswerDoesNotExistException;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Respondent;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Answer;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextQuestionImpl;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceQuestionImpl;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceQuestionImpl;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceAnswerImpl;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceAnswerImpl;
use \Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextAnswerImpl;






class LocalAnswerService implements AnswerService 
{
	protected $poll; // implements Poll interface
	protected $objectFactory; // implements ObjectFactory interface
	/** @var array[] */
	protected $answers; //options

	public function __construct(Poll $poll, ObjectFactory $factory)
	{
		$this->objectFactory = $factory;//new LocalObjectFactory;
		$this->poll = $poll;//$objectFactory.createPoll();
		$this->answers = array();
	}
		/**
	 * Vrati anketu, pro kterou je sluzba platna
	 * @return Poll
	 */
	public function getPoll()
	{
		return $this->poll;
	}

	/**
	 * Vytvori odpoved podle typu otazky
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Question $question
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Respondent $respondent
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 */
	public function create(Question $question, Respondent $respondent)
	{
		// $type = ObjectFactory::TEXT_ANSWER;
		// echo get_class($question);
		if ($question instanceof TextQuestionImpl) $type = ObjectFactory::TEXT_ANSWER; 
		elseif ($question instanceof SingleChoiceQuestionImpl) $type = ObjectFactory::SINGLE_CHOICE_ANSWER;
		elseif ($question instanceof MultipleChoiceQuestionImpl)  $type = ObjectFactory::MULTIPLE_CHOICE_ANSWER; 
		$newAnswer = $this->objectFactory->createAnswer($type);
		$newAnswer->setQuestion($question);
		$newAnswer->setRespondent($respondent);

		$this->answers[$newAnswer->getId()] = $newAnswer;
		// var_dump($this->answers);
		return $newAnswer;
	}

	/**
	 * Najde odpoved podle jejiho id
	 * @param number $id
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\AnswerDoesNotExistException
	 */
	public function find($id)
	{
		// var_dump($this->answers);
		if (isset($this->answers[$id])) //we have such an answer
			return $this->answers[$id];
		throw new AnswerDoesNotExistException();
	}

	/**
	 * nastavi hodnotu odpovedi (text, moznost) nebo prida moznost (pro MultipleChoiceAnswer)
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 * @param mixed - string | \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 */
	public function setAnswer(Answer $answer, $value)
	{
		echo get_class($answer);
		if ($answer instanceof MultipleChoiceAnswerImpl) $answer->addAnswerOption($value);
		else $answer->setAnswer($value); //TextAnswerImpl or SingleChoiceAnswerImpl

	}
}
?>