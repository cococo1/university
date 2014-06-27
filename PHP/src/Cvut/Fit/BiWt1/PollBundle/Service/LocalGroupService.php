<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory;
use Cvut\Fit\BiWt1\PollBundle\Entity\Group;
use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;


class LocalGroupService implements GroupService
{
	protected $poll; //implements Poll interface;
	protected $objectFactory; //implements ObjectFactory interface;
	/** @var array[] */
	protected $groups; 

	// protected $group;

	public function __construct(Poll $poll, ObjectFactory $factory)
	{
		$this->objectFactory = $factory;//new LocalObjectFactory; 
		$this->poll = $poll;//$objectFactory.createPoll();
		$this->groups = array();

	}
		/**
	 * Vrati anketu, pro kterou je sluzba platna
	 * @return Poll
	 */
	public function getPoll()
	{
		return $this->poll;
	}

	public function create($title, $description)
	{
		$group = $this->objectFactory.createGroup();
		$group->setTitle($title);
		$group->setDescription($description);
		$this->groups[$group->getId()] = $group;
		return $group;
	}

	public function delete(Group $group)
	{
		if (! isset( $this->groups[$group->getId()] ) )
		{
			throw new GroupDoesNotExistException();
		}
		unset( $this->groups[$group->getId()] );
	}

	public function addQuestion(Group $group,Question $question)
	{
		$group->addQuestion($question);
		delete($group);
		$this->groups[$group->getId()] = $group;
		return $group;
	}

	public function removeQuestion(Group $group,Question $question)
	{
		$group->removeQuestion($question);
		delete($group);
		$this->groups[$group->getId()] = $group;
		return $group;
	}

}
?>