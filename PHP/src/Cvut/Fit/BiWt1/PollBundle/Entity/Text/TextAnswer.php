<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Text;

use Cvut\Fit\BiWt1\PollBundle\Entity\Answer;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;

/**
 * Rozhrani pro textovou odpoved
 * @author kadleto2
 */
interface TextAnswer extends Answer {
	
	/**
	 * Resi nemoznost dale specializovat rozhrani pomoci type hinting
	 * @var string
	 */
	const COMPATIBLE_QUESTION = '\Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextQuestion';

	/**
	 * Vrati textovou odpoved 
	 * @return string
	 */
	public function getAnswer();

	/**
	 * Nastavi textovou odpoved
	 * @param string $anwser
	 * @return TextAnswer
	 */
	public function setAnswer($anwser);

}
