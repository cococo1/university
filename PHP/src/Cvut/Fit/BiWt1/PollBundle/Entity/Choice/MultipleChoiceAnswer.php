<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

use Cvut\Fit\BiWt1\PollBundle\Entity\Answer;
use Cvut\Fit\BiWt1\PollBundle\Common\Collection;
use Cvut\Fit\BiWt1\PollBundle\Exception\ItemDoesNotExistException;

/**
 * Rozhrani pro odpoved otazku s vyberem z moznosti,
 * odpovedi muze byt vice vybranych moznosti
 * @author kadleto2
 */
interface MultipleChoiceAnswer extends ChoiceAnswer {

	/**
	 * Resi nemoznost dale specializovat rozhrani pomoci type hinting
	 * @var string
	 */
	const COMPATIBLE_QUESTION = '\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceQuestion';

	/**
	 * prida zvolenou moznost do kolekce odpovedi
	 * @param Option $option
	 * @return MultipleChoiceAnswer
	 */
	public function addAnswerOption(Option $option);

	/**
	 * odebere zvolenou moznost z kolekce odpovedi
	 * @param Option $option
	 * @return ChoiceAnswer
	 */
	public function removeAnswerOption(Option $option);

	/**
	 * vrati pole zvolenych moznosti
	 * @return array[Option]
	 */
	public function getAnswer();

	/**
	 * vrati jednotlivou polozku z kolekce odpovedi
	 * @param mixed $id
	 * @return Option
	 * @throws ItemDoesNotExistException
	 */
	public function getAnswerOption($id);

	/**
	 * zjisti zda je moznost v kolekci odpovedi
	 * @param Option $option
	 * @return boolean
	 */
	public function hasAnswerOption(Option $option);

}
