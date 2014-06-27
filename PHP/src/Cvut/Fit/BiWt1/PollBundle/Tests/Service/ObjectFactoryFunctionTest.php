<?php
namespace Cvut\Fit\BiWt1\PollBundle\Tests\Service;

use Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory;
use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory;

/**
 * 
 * @author kadleto2
 */
class ObjectFactoryTest extends \PHPUnit_Framework_TestCase {
	
	/** @var ObjectFactory */
	protected $factory;
	
	protected function setUp() {
		$this->factory = new LocalObjectFactory();
	}
	
	/**
	 * Overi, ze vytvorena instance je typu Poll
	 */
	public function testCreatePoll() {
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Poll", 
			$this->factory->createPoll(),
			'Vytvorena anketa neimplementuje rozhrani Poll'
		);
	}
	
	/**
	 * Overi, ze vytvorene instance jsou typu TextQuestion, SingleChoiceQuestion a MultipleChoiceQuestion
	 */
	public function testCreateQuestion() {
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextQuestion",
				$this->factory->createQuestion(ObjectFactory::TEXT_QUESTION),
				'Vytvorena textova otazka neimplementuje rozhrani TextQuestion'
			);
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceQuestion",
				$this->factory->createQuestion(ObjectFactory::SINGLE_CHOICE_QUESTION),
				'Vytvorena vyberova otazka neimplementuje rozhrani SingleChoiceQuestion'
			);
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceQuestion",
				$this->factory->createQuestion(ObjectFactory::MULTIPLE_CHOICE_QUESTION),
				'Vytvorena vyberova otazka neimplementuje rozhrani MultipleChoiceQuestion'
			);
	}
	
	/**
	 * Overi, ze vytvorene instance jsou typy SharedOption nebo UnsharedOption
	 */
	public function testCreateOption() {
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOption",
				$this->factory->createOption(ObjectFactory::SHARED_OPTION),
				'Vytvorena sdilena moznost neimplementuje rozhrani SharedOption'
			);
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\UnsharedOption",
				$this->factory->createOption(ObjectFactory::UNSHARED_OPTION),
				'Vytvorena nesdilena moznost neimplementuje rozhrani UnsharedOption'
			);
	}
	
	/**
	 * Overi, ze vytvorene instance jsou typu TextAnswer, SingleChoiceAnswer a MultipleChoiceAnswer
	 */
	public function testCreateAnswer() {
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextAnswer",
				$this->factory->createAnswer(ObjectFactory::TEXT_ANSWER),
				'Vytvorena textova odpoved neimplementuje rozhrani TextAnswer'
			);
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceAnswer",
				$this->factory->createAnswer(ObjectFactory::SINGLE_CHOICE_ANSWER),
				'Vytvorena vyberova odpoved neimplementuje rozhrani SingleChoiceAnswer'
			);
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceAnswer",
				$this->factory->createAnswer(ObjectFactory::MULTIPLE_CHOICE_ANSWER),
				'Vytvorena vyberova odpoved neimplementuje rozhrani MultipleChoiceAnswer'
			);
	}
	
	/**
	 * Overi, ze vytvorena instance je typu PollService
	 */
	public function testCreatePollService() {
		$this->assertInstanceOf("\Cvut\Fit\BiWt1\PollBundle\Service\PollService", 
				$this->factory->createPollService(),
				'Vytvorena sluzba pro ankety neimplementuje rozhrani PollService'
			);
	}

}