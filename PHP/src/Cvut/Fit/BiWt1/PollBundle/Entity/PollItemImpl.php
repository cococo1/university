<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity;

use Cvut\Fit\BiWt1\PollBundle\Common\IdentifiedClass;


/**
 * Implementace entity polozka ankety
 * @author kadleto2
 */
abstract class PollItemImpl extends IdentifiedClass implements PollItem {

	/** @var number */
	protected $type;

	/** @var Poll $poll */
	protected $poll;

	// public function __construct()
	// {
	// 	parent::__construct();
	// }

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\PollItem::getType()
	 */
	public function getType() {
		$this->type;	
	}

	/** 
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\PollItem::getPoll()
	 */
	public function getPoll() {
		return $this->poll;
	}

	/** 
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\PollItem::setPoll()
	 */
	public function setPoll(Poll $poll) {
		if (!$poll) {
			throw new \LogicException("Poll cannot be empty!");
		}
		if($this->poll)
			$this->poll->removeItem($this);
		$this->poll = $poll;
		$this->poll->addItem($this);
		return $this;
	}

}
