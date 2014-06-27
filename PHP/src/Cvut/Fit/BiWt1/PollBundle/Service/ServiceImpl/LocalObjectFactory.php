<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl;

use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\PollItem;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Entity\Answer;
use Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory;
use Cvut\Fit\BiWt1\PollBundle\Entity\PollImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\PollItemImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextQuestionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceQuestionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceAnswerImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceQuestionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceAnswerImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\UnsharedOptionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOptionImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextAnswerImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\GroupImpl;
use Cvut\Fit\BiWt1\PollBundle\Service\LocalPollService;
use Cvut\Fit\BiWt1\PollBundle\Service\LocalQuestionService;
use Cvut\Fit\BiWt1\PollBundle\Service\LocalAnswerService;
use Cvut\Fit\BiWt1\PollBundle\Service\LocalGroupService;



/**
 * Interface pro vytvareni objektu
 *
 * @author kadleto2
 */
class LocalObjectFactory implements ObjectFactory {

	/**
	 * Vytvori novou anketu
	 * @return Poll
	 */
	public function createPoll() {
		return new PollImpl();
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory::createGroup()
	 */
	public function createGroup() {
		return new GroupImpl();
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory::createQuestion()
	 */
	public function createQuestion($type = self::TEXT_QUESTION) {
		switch ($type) {
			case self::TEXT_QUESTION:
				return new TextQuestionImpl();
			case self::SINGLE_CHOICE_QUESTION:
				return new SingleChoiceQuestionImpl();
			case self::MULTIPLE_CHOICE_QUESTION:
				return new MultipleChoiceQuestionImpl();
			default:
				throw new \LogicException("Unsupported question type $type.");
		}
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory::createOption()
	 */
	public function createOption($type = self::UNSHARED_OPTION) {
		switch ($type) {
			case self::UNSHARED_OPTION:
				return new UnsharedOptionImpl();
			case self::SHARED_OPTION:
				return new SharedOptionImpl();
			default:
				throw new \LogicException("Unsupported option type $type.");
		}
	}

	/**
	 * Vytvori odpoved pozadovaneho typu. Viz konstanty TEXT_ANSWER,
	 * SINGLE_CHOICE_ANSWER, MULTIPLE_CHOICE_ANSWER
	 * @param number $type
	 * @return Question
	 */
	public function createAnswer($type = self::TEXT_ANSWER) {
		switch ($type) {
			case self::TEXT_ANSWER:
				return new TextAnswerImpl();
			case self::SINGLE_CHOICE_ANSWER:
				return new SingleChoiceAnswerImpl();
			case self::MULTIPLE_CHOICE_ANSWER:
				return new MultipleChoiceAnswerImpl();
			default:
				throw new \LogicException("Unsupported answer type $type.");
		}
	}

	public function createPollService() {
		return new LocalPollService($this);
	}

	/**
	 * @see \Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory::createQuestionService()
	 */
	public function createQuestionService(Poll $poll) {
		return new LocalQuestionService($poll, $this);
	}

	/**
	 * @see \Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory::createAnswerService()
	 */
	public function createAnswerService(Poll $poll) {
		return new LocalAnswerService($poll, $this);

	}

	/**
	 * @see \Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory::createGroupService()
	 */
	public function createGroupService(Poll $poll) {
		return new LocalGroupService($poll, $this);
	}

}