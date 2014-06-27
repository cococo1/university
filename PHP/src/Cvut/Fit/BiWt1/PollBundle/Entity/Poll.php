<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity;

use Cvut\Fit\BiWt1\PollBundle\Common\Collection;
use Cvut\Fit\BiWt1\PollBundle\Common\Identified;

/**
 * Entita Anketa
 * @author jirkovoj
 */
interface Poll extends Identified {

	/**
	 * Prida otazku ci skupinu otazek, pokud uz existuje
	 * @param Cvut\Fit\BiWt1\PollBundle\Entity\PollItem $item
	 * @return Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 */
	public function addItem(PollItem $item);

	/**
	 * Odebere otazku ci skupinu otazek
	 * @param Cvut\Fit\BiWt1\PollBundle\Entity\PollItem $item
	 * @return Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 */
	public function removeItem(PollItem $item);

	/**
	 * Vrati vsechny polozky ankety jako pole
	 * @return array[PollItem]
	 */
	public function getItems();

	/**
	 * Najde polozku ankety podle id
	 * @param mixed $id
	 * @return Cvut\Fit\BiWt1\PollBundle\Entity\PollItem
	 * @throws ItemDoesNotExistException pokud polozka neexistuje
	 */
	public function getItem($id);

	/**
	 * Overi, ze polozka existuje
	 * @param Cvut\Fit\BiWt1\PollBundle\Entity\PollItem $item
	 * @return boolean
	 */
	public function hasItem(PollItem $item);

	/**
	 * Vrati nazev ankety
	 * @return string
	 */
	public function getTitle();

	/**
	 * Nastavi nazev ankety
	 * @param string $title
	 * @return Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 */
	public function setTitle($title);

	/**
	 * Vrati popisek ankety
	 * @return string
	 */
	public function getDescription();

	/**
	 * Nastavi popisek ankety
	 * @param string $description
	 * @return Cvut\Fit\BiWt1\PollBundle\Entity\Poll
	 */
	public function setDescription($description);

}
