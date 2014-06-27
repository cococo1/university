<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\Question;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOption;
use Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion;

/**
 * Obsluha anketnich polozek konkretni ankety
 * 
 * @author kadleto2
 */
interface QuestionService {
	
	/**
	 * Vrati anketu, pro kterou je sluzba platna
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 */
	public function getPoll();
	
	/**
	 * Najde otazku dle id
	 * @param number $id
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Question
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException
	 */
	public function find($id);
	
	/**
	 * Vytvori novou otazku s textem dle argumentu
	 * @param string $question text otazky
	 * @param number $type typ otazky - konstanta @see \Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Question
	 */
	public function create($question, $type = ObjectFactory::TEXT_QUESTION);
	
	/**
	 * Smaze otazku
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Question $question
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException
	 */
	public function delete(Question $question);
	
	/**
	 * Aktualizuje otazku
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Question $question
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException
	 */
	public function update(Question $question);
	
	/**
	 * Prida do otazky typu choice moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion $question otazka
	 * @param string $option text moznosti
	 * @param string $shared ma byt moznost sdilena mezi otazkami
	 * @param string $exclusive pokud ma byt sdilena, lze ji ve vsech otazkach vybrat vicekrat nebo jen jednou
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException pokud otazka neexistuje v ankete
	 */
	public function addOption(ChoiceQuestion $question, $option, $shared = false, $exclusive = false);
	
	/**
	 * Prida existujici sdilenou moznost do jine otazky, nez pro tu, kde vznikla.
	 * Moznost pri opakovanem pridani zustava v otazce pouze jednou.
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion $question otazka
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\SharedOption $option moznost
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\QuestionDoesNotExistException pokud otazka neexistuje v ankete
	 */
	public function addSharedOption(ChoiceQuestion $question, SharedOption $option);
	
	/**
	 * Odebere moznost
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\ChoiceQuestion $question
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Choice\Option $option
	 * @throws FIXME pokud otazka neexistuje v ankete
	 * @throws FIXME pokud moznost v otazce neexistuje
	 */
	public function removeOption(ChoiceQuestion $question, Option $option);

}