<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Common\Collection;

/**
 * Rozhrani pro otazku s vyberem z moznosti
 * @author kadleto2
 */
interface ChoiceQuestion extends Question {

	/**
	 * Prida moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option $option
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion
	 */
	public function addOption(Option $option);

	/**
	 * Odebere moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option $option
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion
	 */
	public function removeOption(Option $option);

	/**
	 * Vrati pole moznosti
	 * @return array[\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option]
	 */
	public function getOptions();
	
	/**
	 * Najde moznost dle id
	 * @param mixed $id
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\ItemDoesNotExistException
	 */
	public function getOption($id);

	/**
	 * Zjisti, zda otazka ma danou moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option $option
	 * @return boolean
	 */
	public function hasOption(Option $option);

}
