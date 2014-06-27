<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

class UnsharedOptionImpl extends OptionImpl implements UnsharedOption
{
	public function __construct()
	{
		parent::__construct();
		$this->exclusive = true;
	}
}
?>