<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Entity\Group;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOption;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion;

/**
 * Rozhrani pro praci se skupinami otazek
 * (volitelna vlastnost)
 *
 * @author kadleto2
 */
interface GroupService {

	/**
	 * Vrati anketu, pro kterou je sluzba platna
	 * @return Poll
	 */
	public function getPoll();

	public function create($title, $description);

	public function addQuestion(Group $group,Question $question);

	public function removeQuestion(Group $group,Question $question);

}