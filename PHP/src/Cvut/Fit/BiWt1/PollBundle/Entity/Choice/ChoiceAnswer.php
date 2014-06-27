<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

use Cvut\Fit\BiWt1\PollBundle\Entity\Answer;

/**
 * Rozhrani pro odpoved na otazku s vyberem z moznosti
 * @author jirkovoj
 */
interface ChoiceAnswer extends Answer {

	/**
	 * @return Option|Options
	 */
	public function getAnswer();

}
