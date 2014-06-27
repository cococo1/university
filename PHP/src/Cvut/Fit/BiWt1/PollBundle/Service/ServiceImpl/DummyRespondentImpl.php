<?php
namespace Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl;

use Cvut\Fit\BiWt1\PollBundle\Common\IdentifiedClass;
use Cvut\Fit\BiWt1\PollBundle\Entity\Respondent;

/**
 * Instantiable implementation of Respondent
 * FOR TESTING PURPOSES ONLY! 
 * @author jirkovoj
 */
final class DummyRespondentImpl extends IdentifiedClass implements Respondent {

	public function getImplementation() {
		return $this;
	}

}