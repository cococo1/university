<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\PollItem;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option;
use Cvut\Fit\BiWt1\PollBundle\Entity\Answer;

/**
 * Rozhrani objektove tovarny, ktera centralizuje mapovani mezi jednotlivymi
 * rozhranimi a jejich implementacemi.
 * 
 * Implementace tohoto rozhrani ma povinny nazev!!!
 * \Cvut\Fit\BiWt1\PollBudle\Service\ServiceImpl\LocalObjectFactory
 *
 * @author kadleto2
 */
interface ObjectFactory {

	const TEXT_QUESTION = 1;
	const SINGLE_CHOICE_QUESTION = 2;
	const MULTIPLE_CHOICE_QUESTION = 3;

	const SHARED_OPTION = true;
	const UNSHARED_OPTION = false;

	const TEXT_ANSWER = 1;
	const SINGLE_CHOICE_ANSWER = 2;
	const MULTIPLE_CHOICE_ANSWER = 3;

	const QUESTION_GROUP = 4;

	/**
	 * Vytvori novou anketu
	 * @return Poll
	 */
	public function createPoll();

	/**
	 * Vytvori novou skupinu otazek
	 * @return Group
	 */
	public function createGroup();

	/**
	 * Vytvori otazku pozadovaneho typu. Viz konstanty TEXT_QUESTION,
	 * SINGLE_CHOICE_QUESTION, MULTIPLE_CHOICE_QUESTION
	 * @param number $type
	 * @return Question
	 */
	public function createQuestion($type = self::TEXT_QUESTION);

	/**
	 * Vytvori novou moznost pozadovaneho typu. Viz konstanty SHARED_OPTION
	 * a UNSHARED_OPTION
	 * @param number $type
	 * @return Option
	 */
	public function createOption($type = self::UNSHARED_OPTION);

	/**
	 * Vytvori odpoved pozadovaneho typu. Viz konstanty TEXT_ANSWER,
	 * SINGLE_CHOICE_ANSWER, MULTIPLE_CHOICE_ANSWER
	 * @param number $type
	 * @return Question
	 */
	public function createAnswer($type = self::TEXT_ANSWER);

	/**
	 * Vytvori sluzbu pro spravu anket
	 * @return \Cvut\Fit\BiWt1\PollBundle\Service\PollService
	 */
	public function createPollService();

	/**
	 * Vytvori sluzbu pro spravu anketnich otazek v ramci jedne ankety
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \Cvut\Fit\BiWt1\PollBundle\Service\QuestionService
	 */
	public function createQuestionService(Poll $poll);

	/**
	 * Vytvori sluzbu pro spravu odpovedi na anketni otazky
	 * v ramci zvolene ankety
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \Cvut\Fit\BiWt1\PollBundle\Service\AnswerService
	 */
	public function createAnswerService(Poll $poll);

	/**
	 * Vytvori sluzbu pro spravu anketnich polozek v ramci jedne ankety
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \Cvut\Fit\BiWt1\PollBundle\Service\GroupService
	 * @throws \LogicException pokud neni sluzba implementovana
	 */
	public function createGroupService(Poll $poll);

}