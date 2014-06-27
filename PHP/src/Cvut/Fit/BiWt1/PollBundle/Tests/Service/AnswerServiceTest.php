<?php
namespace Cvut\Fit\BiWt1\PollBundle\Tests\Service;

use Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory;
use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory;
use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\DummyRespondentImpl;
use Cvut\Fit\BiWt1\PollBundle\Exception\AnswerDoesNotExistException;

/**
 *
 * @author jirkovoj
 */
class AnswerServiceTest extends \PHPUnit_Framework_TestCase {

	protected $objectFactory;

	protected $service;

	protected $textQuestion;
	protected $singleChoiceQuestion;
	protected $multipleChoiceQuestion;

	protected function setUp() {
		$this->objectFactory = new LocalObjectFactory();
		$application = $this->objectFactory->createPollService();
		$poll = $application->create("Prvni anketa", "Testovaci anketa");
		$qs = $application->getQuestionService($poll);

		$this->textQuestion = $qs->create('Textova otazka',ObjectFactory::TEXT_QUESTION);
		$this->singleChoiceQuestion = $qs->create('Vyberova otazka',ObjectFactory::SINGLE_CHOICE_QUESTION);
		$this->multipleChoiceQuestion = $qs->create('Multivyberova otazka',ObjectFactory::MULTIPLE_CHOICE_QUESTION);

		$o1 = $this->objectFactory->createOption(ObjectFactory::SHARED_OPTION);
		$o1->setOption('Moznost 1');
		$qs->addSharedOption($this->singleChoiceQuestion,$o1);
		$o2 = $qs->addOption($this->singleChoiceQuestion,'Moznost 2');

		$o1 = $this->objectFactory->createOption(ObjectFactory::SHARED_OPTION);
		$o1->setOption('Moznost 1');
		$qs->addSharedOption($this->multipleChoiceQuestion,$o1);
		$o2 = $qs->addOption($this->multipleChoiceQuestion,'Moznost 2');

		$this->service = $application->getAnswerService($poll);
	}

	public function testImplementation() {
		$this->assertInstanceOf(
			'\Cvut\Fit\BiWt1\PollBundle\Service\AnswerService',
			$this->service,
			'Trida neimplementuje rozhrani AnswerService'
		);
	}

	public function testGetPoll() {
		$this->assertInstanceOf(
			'\Cvut\Fit\BiWt1\PollBundle\Entity\Poll',
			$this->service->getPoll(),
			'Pripojena anketa neimplementuje rozhrani Poll'
		);
	}

	public function testCreateAnswer() {
		$a1 = $this->service->create($this->textQuestion,new DummyRespondentImpl());
		$a2 = $this->service->create($this->singleChoiceQuestion,new DummyRespondentImpl());
		$a3 = $this->service->create($this->multipleChoiceQuestion,new DummyRespondentImpl());

		$this->assertSame($this->service->find($a1->getId()), $a1,'Vlozena odpoved nebyla nasledne nalezena');
		$this->assertSame($this->service->find($a2->getId()), $a2,'Vlozena odpoved nebyla nasledne nalezena');
		$this->assertSame($this->service->find($a3->getId()), $a3,'Vlozena odpoved nebyla nasledne nalezena');
	}

	public function testSetAnswer() {
		$a1 = $this->service->create($this->textQuestion,new DummyRespondentImpl());
		$a2 = $this->service->create($this->singleChoiceQuestion,new DummyRespondentImpl());
		$a3 = $this->service->create($this->multipleChoiceQuestion,new DummyRespondentImpl());

		$this->service->setAnswer($a1,'Odpoved');
		$this->assertEquals('Odpoved',$a1->getAnswer(),'Nastaveny a ziskany text odpovedi nejsou shodne');

		$opts = $a2->getQuestion()->getOptions();
		if($opt = current($opts)) {
			$this->service->setAnswer($a2,$opt);
			$this->assertEquals($opt,$a2->getAnswer(),'Nastavena a ziskana moznost nejsou shodne');
		}

		$opts = $a3->getQuestion()->getOptions();
		if($opt = current($opts)) {
			$this->service->setAnswer($a3,$opt);
			$this->assertEquals($opt,$a3->getAnswerOption($opt->getId()),'Nastavena a ziskana moznost nejsou shodne');
		}
		if($opt = next($opts)) {
			$this->service->setAnswer($a3,$opt);
			$this->assertEquals($opt,$a3->getAnswerOption($opt->getId()),'Nastavena a ziskana moznost nejsou shodne');
		}
	}
}
