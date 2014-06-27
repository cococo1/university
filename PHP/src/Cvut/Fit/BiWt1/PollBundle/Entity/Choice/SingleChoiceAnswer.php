<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

use Cvut\Fit\BiWt1\PollBundle\Entity\Answer;

/**
 * Rozhrani pro odpoved na otazku s vyberem z moznosti. Jako
 * odpoved vybrana prave jedna vybrana moznost.
 * @author jirkovoj
 */
interface SingleChoiceAnswer extends ChoiceAnswer {

	/**
	 * Resi nemoznost dale specializovat rozhrani pomoci type hinting
	 * @var string
	 */
	const COMPATIBLE_QUESTION = '\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceQuestion';

	/**
	 * Nastaveni odpovedi
	 * @param Option $answer
	 * @return SingleChoiceAnswer
	 */
	public function setAnswer(Option $answer);
}
