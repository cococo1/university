<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity;

use Cvut\Fit\BiWt1\PollBundle\Common\Identified;

/**
 * Rozhrani pro odpoved na otazku - spolecna cast
 * @author jirkovoj
 */
interface Answer extends Identified {
	
	/**
	 * Vrati respondenta
	 * @return Respondent
	 */
	public function getRespondent();

	/**
	 * Nastavi respondenta
	 * @param Respondent $respondent
	 */
	public function setRespondent(Respondent $respondent);

	/**
	 * Vrati otazku, ke ktere se tato odpoved vztahuje
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Question
	 */
	public function getQuestion();

	/**
	 * Metoda resi na zaklade konstanty potomka compatibleClass
	 * kontrolu, zda je predany datovy typ spravny (nejen Question,
	 * ale konkretni Question napr. TextQuestion).
	 * @param Question $question
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Answer
	 * @throws \LogicException pokud trida/rozhrani, se kterou je odpoved kompatibilni, neexistuje
	 * @throws IncompatibleClassException otazka neni kompatibilni s touto odpovedi
	 */
	public function setQuestion(Question $question);

}
