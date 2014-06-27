<?php
namespace Cvut\Fit\BiWt1\PollBundle\Common;

/**
 * Unikatne identifikovatelny objekt
 *
 * @author kadleto2
 */
abstract class IdentifiedClass implements Identified {

	/** @var string $id */
	protected $id;

	/**
	 * Zajistuje prirazeni unikatniho id pri vytvoreni objektu
	 */
	public function __construct() {
		$this->id = uniqid();
	}

	/**
	 * (non-PHPdoc)
	 * @see \Cvut\Fit\BiWt1\PollBundle\Common\Identified::getId()
	 */
	public function getId() {
		return $this->id;
	}

}
