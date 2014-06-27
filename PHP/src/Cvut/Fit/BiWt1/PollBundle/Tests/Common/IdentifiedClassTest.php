<?php
namespace Cvut\Fit\BiWt1\PollBundle\Tests\Common;

use Cvut\Fit\BiWt1\PollBundle\Common\IdentifiedClass;

/**
 * 
 * @author kadleto2
 */
class IdentifiedClassTest extends \PHPUnit_Framework_TestCase {

	public function testInstantiation() {
		/** @var IdentifiedClass */
		$object = new IdentifiedClassImpl();
		$this->assertInstanceOf(
				'\Cvut\Fit\BiWt1\PollBundle\Common\Identified',
				$object,
				'Instance neimplementuje rozhrani Identified');
	}
	
	public function testUniqueIdentifiers() {
		$ids = array();
		for ($i = 0; $i < 1000; $i++) {
			$object = new IdentifiedClassImpl();
			if (!isset($ids[$object->getId()]))
				$ids[$object->getId()] = 1;
			else 
				$ids[$object->getId()] += 1;
		}
		$this->assertCount(1000, $ids, 'Nepodarilo se vytvorit 1000 unikatnich id');
	}
	
}
