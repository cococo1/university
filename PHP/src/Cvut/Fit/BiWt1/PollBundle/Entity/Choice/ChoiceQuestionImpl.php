<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

use Cvut\Fit\BiWt1\PollBundle\Entity\QuestionImpl;
use Cvut\Fit\BiWt1\PollBundle\Common\Collection;

abstract class ChoiceQuestionImpl extends QuestionImpl implements ChoiceQuestion 
{
	protected $options; //Collection of options of answers... simply said -  answers.

	public function __construct()
	{
		parent::__construct();
		$this->options = new Collection;
	}

		/**
	 * Prida moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option $option
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion
	 */
	public function addOption(Option $option)
	{
		$this->options->addItem($option);
		$option->addQuestion($this);
		return $this;
	}

	/**
	 * Odebere moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option $option
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion
	 */
	public function removeOption(Option $option)
	{
		$this->options->removeItem($option);
		return $this;
	}

	/**
	 * Vrati pole moznosti
	 * @return array[\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option]
	 */
	public function getOptions()
	{
		return $this->options->getItems();
	}
	
	/**
	 * Najde moznost dle id
	 * @param mixed $id
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\ItemDoesNotExistException
	 */
	public function getOption($id)
	{
		return $this->options->getItem($id);
	}

	/**
	 * Zjisti, zda otazka ma danou moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option $option
	 * @return boolean
	 */
	public function hasOption(Option $option)
	{
		return $this->options->hasItem($option);
	}

}
?>