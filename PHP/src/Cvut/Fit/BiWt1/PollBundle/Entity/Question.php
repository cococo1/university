<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity;

/**
 * Entita otazka
 * @author kadleto2
 */
interface Question extends PollItem {

	/**
	 * Vrati text otazky
	 * @return string
	 */
	public function getQuestion();

	public function getType();

	/**
	 * Nastavi text otazky
	 * @param string $question
	 * @return Question
	 */
	public function setQuestion($question);

	/**
	 * Prida odpoved na otazku
	 * @param Answer $answer
	 * @return Question
	 */
	public function addAnswer(Answer $answer);

	/**
	 * Smaze odpoved na otazku
	 * @param Answer $answer
	 * @return Question
	 */
	public function removeAnswer(Answer $answer);

	/**
	 * Vrati pole instanci Answer
	 * @return array[Answer]
	 */
	public function getAnswers();

	/**
	 * Nalezne odpoved podle id
	 * @param string $id
	 * @return Question
	 * @throws ItemDoesNotExistException
	 */
	public function getAnswer($id);

	/**
	 * Overi, ze mezi odpovedmi je i odpoved
	 * @param Answer $answer
	 * @return boolean
	 */
	public function hasAnswer(Answer $answer);

}
