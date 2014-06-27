<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Choice;

class SharedOptionImpl extends OptionImpl implements SharedOption
{
	public function __construct()
	{
		parent::__construct();
		$this->exclusive = false;
	}
}
?>