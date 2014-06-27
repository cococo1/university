<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Common\Collection;
use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory;
use \Cvut\Fit\BiWt1\PollBundle\Exception\PollDoesNotExistException;
use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\PollImpl;
use Cvut\Fit\BiWt1\PollBundle\Exception\ItemDoesNotExistException;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestionImpl;



class LocalPollService implements PollService 
{
	protected $objectFactory; //implements ObjectFactory interface
	protected $polls; //Collection class
	protected $questionServices; //array of question services

	public function __construct(ObjectFactory $objectFactory)
	{
		$this->objectFactory = $objectFactory;//new LocalObjectFactory;
		$this->polls = new Collection();
		$this->questionServices = array();
		// $this->questionService = $this->objectFactory->createQuestionService()
	}

	//returns a collection of polls
	public function getPolls()
	{
		return $this->polls;
	}
	/**
	 * Nalezne anketu podle id 
	 * @param number $id
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\PollDoesNotExistException 
	 */
	public function find($id)
	{
		// echo "find poll";
		try
		{
			return $this->polls->getItem($id);
		}
		catch (ItemDoesNotExistException $e)
		{
			// echo "cought exception at find";
			throw new PollDoesNotExistException();
			
		}
	}
	
	/**
	 * Vytvori novou anketu
	 * @param string $title nazev ankety (nemusi byt unikatni, dokonce muze byt prazdny)
	 * @param string $description doplnujici popis (muze byt prazdny)
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 */
	public function create($title = null, $description = null)
	{
		$poll = new PollImpl;
		$poll->setTitle($title);
		$poll->setDescription($description);
		$this->polls->addItem($poll);

		return $poll;
	}
	
	/**
	 * Smaze anketu
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\PollDoesNotExistException
	 */
	public function delete(Poll $poll)
	{
		try
		{
			$this->polls->removeItem($poll,true);
		}
		catch (ItemDoesNotExistException $e)
		{
			// echo "hohoho";
			throw new PollDoesNotExistException();
		}
		return $poll;

	}
	
	/**
	 * Upravi anketu, resp. ji po uprave ulozi
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\PollDoesNotExistException
	 */
	public function update(Poll $poll)
	{
		// $this->delete($poll);
		$this->polls->addItem($poll);
		return $poll;
	}
	
	/**
	 * Najde vsechny sdilene moznosti pres "kontejner" - v tomto pripade
	 * v teto ankete, ale nikoliv v ni zarazenych skupinach otazek
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll 
	 * @return Collection
	 */
	public function findSharedOptions(Poll $poll)
	{
		$sharedOptions = new Collection;

		foreach ($this->questionServices as $qs)
		{
			$aPoll = $qs->getPoll();
			if ($aPoll == $poll) {  $allQuestions = $qs->getAllQuestions(); break; }
		}
		// var_dump($allOptions);
		foreach ($allQuestions as $question)
		{
			if ($question instanceof ChoiceQuestionImpl)
			{
				// echo "choice";
				$options = $question->getOptions();
				foreach ($options as $option)
				{
					if (! $option->getExclusive())	$sharedOptions->addItem($option);
				}		
			}
		}

		//  // $questionService->

		// $pollItems = $poll->getItems(); // these are questions
		// // echo get_class($pollItems);
		// // var_dump($pollItems);
		// //???????????????
		// foreach ($pollItems as $item)
		//  {
		//  	echo "polls";
		// 	if ($item instanceof ChoiceQuestionImpl)
		// 	{
		// 		echo "choice";
		// 		$options = $item->getOptions();
		// 		foreach ($options as $option)
		// 		{
		// 			if (! $option->getExclusive())	$sharedOptions->addItem($option);
		// 		}
		// 	}
		// }

		return $sharedOptions;

	}
	
	/**
	 * Vytvori sluzbu pro praci s otazkami konkretni ankety
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 */
	public function getQuestionService(Poll $poll)
	{
		$qs = $this->objectFactory->createQuestionService($poll);
		$this->questionServices[count($this->questionServices)] = $qs;
		return $qs;
	}
	
	/**
	 * Vytvori sluzbu pro praci s odpovedmi konkretni ankety
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 */
	public function getAnswerService(Poll $poll)
	{
		return $this->objectFactory->createAnswerService($poll);
	}
	
	/**
	 * Vytvtori sluzbu pro praci se skupinami otazek
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \LogicException pokud neni sluzba implementovana
	 */
	public function getGroupService(Poll $poll)
	{
		try
		{
			return $this->objectFactory->createGroupService($poll);
		}
		catch (Exception $e)
		{
			throw new \LogicException(" pokud neni sluzba implementovana");
		}
	}
}
?>