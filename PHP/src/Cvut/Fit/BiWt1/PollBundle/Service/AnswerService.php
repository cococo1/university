<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Entity\Answer;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOption;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion;
use Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextQuestion;
use Cvut\Fit\BiWt1\PollBundle\Entity\Respondent;

/**
 * Obsluha anketnich polozek konkretni ankety
 *
 * @author kadleto2
 */
interface AnswerService {

	/**
	 * Vrati anketu, pro kterou je sluzba platna
	 * @return Poll
	 */
	public function getPoll();

	/**
	 * Vytvori odpoved podle typu otazky
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Question $question
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Respondent $respondent
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 */
	public function create(Question $question, Respondent $respondent);

	/**
	 * Najde odpoved podle jejiho id
	 * @param number $id
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\AnswerDoesNotExistException
	 */
	public function find($id);

	/**
	 * nastavi hodnotu odpovedi (text, moznost) nebo prida moznost (pro MultipleChoiceAnswer)
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 * @param mixed - string | \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 */
	public function setAnswer(Answer $answer, $value);
}