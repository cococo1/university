<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Text;

use Cvut\Fit\BiWt1\PollBundle\Entity\AnswerImpl;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextQuestionImpl;
use Cvut\Fit\BiWt1\PollBundle\Exception\IncompatibleClassException;



/**
 * Implementace textove odpovedi
 * @author kadleto2
 */
class TextAnswerImpl extends AnswerImpl implements TextAnswer 
{
	protected $answer; //string

	public function __construct()
	{
		parent::__construct();
		$this->question = new TextQuestionImpl;
	}

	/**
	 * @return string
	 */
	public function getAnswer()
	 {
		return $this->answer;
	}

	/**
	 *
	 * @param string $anwser
	 * @return TextAnswer
	 */
	public function setAnswer($anwser) 
	{
		$this->answer = $anwser;
		return $this;
	}

		/**
	 * Metoda resi na zaklade konstanty potomka compatibleClass
	 * kontrolu, zda je predany datovy typ spravny (nejen Question,
	 * ale konkretni Question napr. TextQuestion).
	 * @param Question $question
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 * @throws \LogicException pokud trida/rozhrani, se kterou je odpoved kompatibilni, neexistuje
	 * @throws IncompatibleClassException otazka neni kompatibilni s touto odpovedi
	 */
	public function setQuestion(Question $question)
	{
		if (!$question)
		{
			throw new \LogicException("Question cannot be empty!");
		}
		if ($question instanceof TextQuestionImpl)
		{
			$this->question = $question;
			$question->addAnswer($this);
		}
		else throw new IncompatibleClassException();
		
		return $this;
	}
}
