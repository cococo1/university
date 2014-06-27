<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity;

use Cvut\Fit\BiWt1\PollBundle\Common\Collection;

use Symfony\Component\Validator\Mapping\ClassMetadata;
use Symfony\Component\Validator\Constraints\NotBlank;

abstract class QuestionImpl extends PollItemImpl implements Question
{
	protected $question; //string
	protected $answers; //Collection

	public function __construct()
	{
		parent::__construct();
		$this->answers = new Collection;
		$this->question = "";
	}


	public function getType()
	{
		if (! strcmp(get_class($this), "Cvut\Fit\BiWt1\PollBundle\Entity\Text\TextQuestionImpl"))
		{
			return "textQuestion";
		}
		elseif (! strcmp(get_class($this), "Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SingleChoiceQuestionImpl"))
		{
			return "singleChoiceQuestion";
		}
		elseif (! strcmp(get_class($this), "Cvut\Fit\BiWt1\PollBundle\Entity\Choice\MultipleChoiceQuestionImpl"))
		{
			return "multipleChoiceQuestion";
		}
	}
/**
	 * Vrati text otazky
	 * @return string
	 */
	public function getQuestion()
	{
		return $this->question;
	}

	/**
	 * Nastavi text otazky
	 * @param string $question
	 * @return Question
	 */
	public function setQuestion($question)
	{
		$this->question = $question;
		return $this;
	}

	/**
	 * Prida odpoved na otazku
	 * @param Answer $answer
	 * @return Question
	 */
	public function addAnswer(Answer $answer)
	{
		$this->answers->addItem($answer);
		return $this;

	}

	/**
	 * Smaze odpoved na otazku
	 * @param Answer $answer
	 * @return Question
	 */
	public function removeAnswer(Answer $answer)
	{
		$this->answers->removeItem($answer);
		return $this;
	}

	/**
	 * Vrati pole instanci Answer
	 * @return array[Answer]
	 */
	public function getAnswers()
	{
		return $this->answers;
	}

	/**
	 * Nalezne odpoved podle id
	 * @param string $id
	 * @return Question
	 * @throws ItemDoesNotExistException
	 */
	public function getAnswer($id)
	{
		return $this->answers->getItem($id);
	}

	/**
	 * Overi, ze mezi odpovedmi je i odpoved
	 * @param Answer $answer
	 * @return boolean
	 */
	public function hasAnswer(Answer $answer)
	{
		return $this->answers->hasItem($answer);

	}


	public static function loadValidatorMetadata(ClassMetadata $metadata)
    {
        $metadata->addPropertyConstraint('question', new NotBlank());
    }

}
?>