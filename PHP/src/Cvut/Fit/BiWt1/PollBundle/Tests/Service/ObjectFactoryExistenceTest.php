<?php
namespace Cvut\Fit\BiWt1\PollBundle\Tests\Service;

use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory;

/**
 * Overi existenci pozadovane factory tridy pro instanciaci trid
 * @author kadleto2
 */
class ObjectFactoryExistenceTest extends \PHPUnit_Framework_TestCase {
	
	public function testObjectService() {
		$this->assertTrue(class_exists("\Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory"),'Trida LocalObjectFactory neexistuje');
		$this->assertTrue(is_subclass_of(
				"\Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory",
				"\Cvut\Fit\BiWt1\PollBundle\Service\ObjectFactory"),'Trida LocalObjectFactory neimplementuje rozhrani ObjectFactory');
	}
		
	
}
