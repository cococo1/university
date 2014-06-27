<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service;

use Cvut\Fit\BiWt1\PollBundle\Entity\Poll;
use Cvut\Fit\BiWt1\PollBundle\Entity\Respondent;

/**
 * Obsluha anket
 * 
 * @author kadleto2
 */
interface PollService {
	
	/**
	 * Nalezne anketu podle id 
	 * @param number $id
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\PollDoesNotExistException 
	 */
	public function find($id);
	
	/**
	 * Vytvori novou anketu
	 * @param string $title nazev ankety (nemusi byt unikatni, dokonce muze byt prazdny)
	 * @param string $description doplnujici popis (muze byt prazdny)
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 */
	public function create($title = null, $description = null);
	
	/**
	 * Smaze anketu
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\PollDoesNotExistException
	 */
	public function delete(Poll $poll);
	
	/**
	 * Upravi anketu, resp. ji po uprave ulozi
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 * @throws \Cvut\Fit\BiWt1\PollBundle\Exception\PollDoesNotExistException
	 */
	public function update(Poll $poll);
	
	/**
	 * Najde vsechny sdilene moznosti pres "kontejner" - v tomto pripade
	 * v teto ankete, ale nikoliv v ni zarazenych skupinach otazek
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll 
	 * @return Collection
	 */
	public function findSharedOptions(Poll $poll);
	
	/**
	 * Vytvori sluzbu pro praci s otazkami konkretni ankety
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 */
	public function getQuestionService(Poll $poll);
	
	/**
	 * Vytvori sluzbu pro praci s odpovedmi konkretni ankety
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 */
	public function getAnswerService(Poll $poll);
	
	/**
	 * Vytvtori sluzbu pro praci se skupinami otazek
	 * @param \Cvut\Fit\BiWt1\PollBundle\Entity\Poll $poll
	 * @return \LogicException pokud neni sluzba implementovana
	 */
	public function getGroupService(Poll $poll);

}