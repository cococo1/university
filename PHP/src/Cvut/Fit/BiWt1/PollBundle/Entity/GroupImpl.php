<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity;

use Cvut\Fit\BiWt1\PollBundle\Common\Collection;

class GroupImpl extends PollItemImpl implements Group 
{
	protected $questions; //Collection
	protected $title; //string
	protected $description; //string

	public function __construct()
	{
		parent::__construct();
		$this->questions = new Collection();
		$this->title = "";
		$this->description = "";
	}

	/**
	 * Prida otazku
	 * @param Question $question
	 * @return Group
	 */
	public function addQuestion(Question $question)
	{
		$this->questions->addItem($question);
		return $this;
	}

	/**
	 * Odebere otazku
	 * @param Question $question
	 * @return Group
	 */
	public function removeQuestion(Question $question)
	{
		$this->questions->removeItem($question);
		return $this;
	}

	/**
	 * Vrati pole otazek
	 * @return array[Question]
	 */
	public function getQuestions()
	{
		return $this->questions;
	}

	/**
	 * Nalezne otazku podle id
	 * @param mixed $id
	 * @return Question
	 * @throws ItemDoesNotExistException
	 */
	public function getQuestion($id)
	{
		return $this->questions->getItem($id);
	}

	/**
	 * Overi, ze otazka je ve skupine
	 * @param Question $question
	 * @return boolean
	 */
	public function hasQuestion(Question $question)
	{
		return $this->questions->hasItem($question);
	}

	/**
	 * Vrati nazev skupiny
	 * @return string
	 */
	public function getTitle()
	{
		return $this->title;
	}

	/**
	 * Nastavi nazev skupiny
	 * @param string $title
	 * @return Group
	 */
	public function setTitle($title)
	{
		$this->title = $title;
		return $this;
	}

	/**
	 * Vrati popis skupiny
	 * @return string
	 */
	public function getDescription()
	{
		return $this->description;
	}
	
	/**
	 * Nastavi popis skupiny
	 * @param string $description
	 * @return Group
	 */
	public function setDescription($description)
	{
		$this->description = $description;
		return $this;
	}
}
?>