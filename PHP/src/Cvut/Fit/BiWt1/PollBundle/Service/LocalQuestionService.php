<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory;
use \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOption;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option;
use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\UnsharedOptionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOptionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\OptionImpl;





class LocalQuestionService implements QuestionService 
{
	protected $poll; //implements Poll interface;
	protected $objectFactory; // implements ObjectFactory interface;
	/** @var array[] */
	protected $questions;
	// protected $options; //ale options


	public function __construct(Poll $poll, ObjectFactory $factory)
	{
		$this->objectFactory = $factory;//new LocalObjectFactory;
		$this->poll = $poll; //$objectFactory.createPoll();
		$this->questions = array();
		// $this->options = array();
	}

	public function getAllQuestions()
	{
		// var_dump($this->options);
		return $this->questions;
	}
	/**
	 * Vrati anketu, pro kterou je sluzba platna
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 */
	public function getPoll()
	{
				// var_dump($poll);

		return $this->poll;
	}
	
	/**
	 * Najde otazku dle id
	 * @param number $id
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Question
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException
	 */
	public function find($id)
	{
		if (isset($this->questions[$id])) //we have such a question
			return $this->questions[$id];
		throw new QuestionDoesNotExistException();
	}
	
	/**
	 * Vytvori novou otazku s textem dle argumentu
	 * @param string $question text otazky
	 * @param number $type typ otazky - konstanta @see \Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Question
	 */
	public function create($question, $type = ObjectFactory::TEXT_QUESTION)
	{
		// echo $type;
		$newQuestion = $this->objectFactory->createQuestion($type);
		// if ($type == ObjectFactory::SINGLE_CHOICE_QUESTION) echo "single";
		// echo $question;
		$newQuestion->setQuestion($question);
		$this->questions[$newQuestion->getId()] = $newQuestion;
		return $newQuestion;
	}
	
	/**
	 * Smaze otazku
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Question $question
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException
	 */
	public function delete(Question $question)
	{
		if (! isset( $this->questions[$question->getId()] ) )
		{
			throw new QuestionDoesNotExistException();
		}
		unset( $this->questions[$question->getId()] );
	}
	
	/**
	 * Aktualizuje otazku
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Question $question
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException
	 */
	public function update(Question $question)
	{
		 //$this->delete($question);
		 $this->questions[$question->getId()] = $question;//this will throw an exception if it does not exist in our array
	}
	
	/**
	 * Prida do otazky typu choice moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion $question otazka
	 * @param string $option text moznosti
	 * @param string $shared ma byt moznost sdilena mezi otazkami
	 * @param string $exclusive pokud ma byt sdilena, lze ji ve vsech otazkach vybrat vicekrat nebo jen jednou
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException pokud otazka neexistuje v ankete
	 * @return Option;
	 */
	public function addOption(ChoiceQuestion $question, $option, $shared = false, $exclusive = false)
	{
		if ($shared)
		{
			$newOption = $this->objectFactory->createOption(LocalObjectFactory::SHARED_OPTION);
			$newOption->setOption($option);
			$newOption->setExcusive($exclusive);
			$question->setOption($newOption);
		}
		else
		{
			$newOption = $this->objectFactory->createOption(LocalObjectFactory::UNSHARED_OPTION);
			// echo get_class($newOption);
			// var_dump(method_exists($newOption, 'setExclusive'));
			// var_dump($newOption);
			$newOption->setOption($option);
			$newOption->setExclusive($exclusive);
			$question->addOption($newOption);
		}



		
		$question->addOption($newOption);
		$this->update($question);//this will throw an exception if it does not exist in our array
		return $newOption;
	}
	
	/**
	 * Prida existujici sdilenou moznost do jine otazky, nez pro tu, kde vznikla.
	 * Moznost pri opakovanem pridani zustava v otazce pouze jednou.
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion $question otazka
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOption $option moznost
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException pokud otazka neexistuje v ankete
	 */
	public function addSharedOption(ChoiceQuestion $question, SharedOption $option)
	{
		$question->addOption($option);
		$this->update($question);//this will throw an exception if it does not exist in our array
	}
	
	/**
	 * Odebere moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion $question
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option $option
	 * @throws FIXME pokud otazka neexistuje v ankete
	 * @throws FIXME pokud moznost v otazce neexistuje
	 */
	public function removeOption(ChoiceQuestion $question, Option $option)
	{
		try
		{
			$question->removeOption($option);
		}
		catch (Exception $e)
		{
			throw new Exception("FIXME pokud moznost v otazce neexistuje", 1);
		}

		$this->update($question);

	}

}
?>