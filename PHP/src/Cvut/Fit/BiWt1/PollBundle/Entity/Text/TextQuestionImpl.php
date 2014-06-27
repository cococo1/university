<?php
namespace Cvut\Fit\BiWt1\PollBundle\Entity\Text;

use Cvut\Fit\BiWt1\PollBundle\Entity\QuestionImpl;

/**
 * Implementace otazky s textovou odpovedi
 * @author kadleto2
 */
class TextQuestionImpl extends QuestionImpl implements TextQuestion
{
	public function __construct()
	{
		parent::__construct();
	}

}