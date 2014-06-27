<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity;

use Cvut\Fit\BiWt1\PollBundle\Common\Collection;
use Cvut\Fit\BiWt1\PollBundle\Common\IdentifiedClass;

use Symfony\Component\Validator\Mapping\ClassMetadata;
use Symfony\Component\Validator\Constraints\NotBlank;


/**
 * Implementace entity anketa
 * @author jirkovoj
 */
class PollImpl extends IdentifiedClass implements Poll {

	/** @var string */
	protected $title;

	/** @var string */
	protected $description;

	/** @var Collection */
	protected $items;

	public function __construct() {
		//vygeneruje se id z vzdaleneho rodice IdentifiedClass
		parent::__construct();
		$this->items = new Collection;
		$this->title = "";
		$this->description = "";
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::addItem()
	 */
	public function addItem(PollItem $item) {
		$this->items->addItem($item);
		return $this;
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::removeItem()
	 */
	public function removeItem(PollItem $item) {
		$this->items->removeItem($item);
		return $this;
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::getItems()
	 */
	public function getItems() {
		// $a  = array();
		// echo get_class($a);
		return $this->items->getItems();
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::getItem()
	 */
	public function getItem($id) {
		return $this->items->getItem($id);
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::hasItem()
	 */
	public function hasItem(PollItem $item) {
		return $this->items->hasItem($item);
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::getTitle()
	 */
	public function getTitle() {
		return $this->title;
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::setTitle()
	 */
	public function setTitle($title) {
		$this->title = $title;
		return $this;
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::getDescription()
	 */
	public function getDescription() {
		return $this->description;
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Entity\Poll::setDescription()
	 */
	public function setDescription($description) {
		$this->description = $description;
		return $this;
	}

	public static function loadValidatorMetadata(ClassMetadata $metadata)
    {
        $metadata->addPropertyConstraint('title', new NotBlank());
    }
}
