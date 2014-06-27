<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

use Cvut\Fit\BiWt1\PollBundle\Common\IdentifiedClass;
use Cvut\Fit\BiWt1\PollBundle\Common\Collection;


abstract class OptionImpl extends IdentifiedClass implements Option 
{
	protected $option; //some string 
	protected $exclusive; // bool. Initialize it in non-abstract class 
	protected $questions; //Collection
	protected $answers; //Collection

	public function __construct()
	{
		parent::__construct();
		$this->questions = new Collection();
		$this->answers = new Collection();
		$this->option = "";
	}

	/**
	 * Vrati text moznosti
	 * @return string
	 */
	public function getOption()
	{
		return $this->option;
	}

	/**
	 * Nastavi text moznosti
	 * @param string $option
	 * @return Option
	 */
	public function setOption($option)
	{
		$this->option = $option;
		return $this;
	}

	/**
	 * Prida otazku, v pripade sdilene moznosti jich muze byt vice
	 * (druha strana vztahu otazka - moznost, ktery muze byt m:n)
	 * @param ChoiceQuestion $question
	 * @return Option
	 */
	public function addQuestion(ChoiceQuestion $question)
	{
		$this->questions->addItem($question);
		return $this;
	}

	/**
	 * Prida otazku, v pripade sdilene moznosti jich muze byt vice
	 * (druha strana vztahu otazka - moznost, ktery muze byt m:n)
	 * @param ChoiceQuestion $question
	 * @return Option
	 */
	public function removeQuestion(ChoiceQuestion $question)
	{
		$this->questions->removeItem($question);
		return $this;
	}

	/**
	 * Vrati pole otazek, ve kterych je moznost pouzita
	 * (druha strana vztahu otazka - moznost, ktery muze byt m:n)
	 * @return array[Option]
	 */
	public function getQuestions()
	{
		return $this->questions;
	}

	/**
	 * Najde otazku podle id mezi temi, do kterych moznost patri
	 * @param mixed $id
	 * @return ChoiceQuestion
	 * @throws ItemDoesNotExistException
	 */
	public function getQuestion($id)
	{
		return $this->questions->getItem($id);
	}

	/**
	 * Zjisti, zda je moznost pouzita v otazce 
	 * @param ChoiceQuestion $question
	 * @return boolean
	 */
	public function hasQuestion(ChoiceQuestion $question)
	{
		return $this->questions->hasItem($question);
	}

	/**
	 * Prida odpoved, ktera zvolila tuto moznost
	 * (pozor, v pripade sdilene moznosti jde o vztah m:n)
	 * @param MultipleChoiceAnswer $answer
	 * @return ChoiceQuestion
	 */
	public function addAnswer(ChoiceAnswer $answer)
	{
		$this->answers->addItem($answer);
		return $answer->getQuestion();

	}

	/**
	 * Odebere odpoved, ktera zvolila tuto moznost
	 * @param MultipleChoiceAnswer $answer
	 * @return ChoiceQuestion
	 */
	public function removeAnswer(ChoiceAnswer $answer)
	{
		$this->answers->removeItem($answer);
		return $answer->getQuestion();	}

	/**
	 * Vrati odpovedi, ktere zvolily tuto moznost
	 * @return array[Answer]
	 */
	public function getAnswers()
	{
		return $this->answers;
	}

	/**
	 * Najde odpoved, ktera zvolila tuto moznost podle id
	 * @param mixed $id
	 * @return Answer
	 * @throws ItemDoesNotExistException
	 */
	public function getAnswer($id)
	{
		return $this->answers->getItem($id);
	}

	/**
	 * Zjisti, jesli je odpoved mezi temi, co zvolily tuto moznost
	 * @param ChoiceAnswer $answer
	 * @return boolean
	 */
	public function hasAnswer(ChoiceAnswer $answer)
	{
		return $this->answers->hasItem($answer);
	}
	
	/**
	 * Zjisti, zda je moznost exkluzivni, tj. je sdilena, ale zvolit 
	 * ji lze pouze v jedne z otazek, kam je zarazena
	 * @return true pokud je moznost exkluzivni pro anketu / skupinu otazek
	 */
	public function getExclusive()
	{
		return $this->exclusive;
	}
	
	/**
	 * Nastavi priznak otazky, ze je exkluzivni.
	 * @param boolean $exclusive
	 * @return Option
	 */
	public function setExclusive($exclusive)
	{
		$this->exclusive = $exclusive;
		return $this;
	}

}
?>