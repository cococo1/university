<?php

namespace Cvut\Fit\BiWt1\PollBundle\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * Cvut\Fit\BiWt1\PollBundle\Entity\DataEntity
 *
 * @ORM\Table()
 * @ORM\Entity
 */
class DataEntity
{
    /**
     * @var integer $id
     *
     * @ORM\Column(name="id", type="integer")
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="AUTO")
     */
    private $id;

    /**
     * @var \stdClass $localObjectFactory
     *
     * @ORM\Column(name="localObjectFactory", type="object")
     */
    private $localObjectFactory;

    /**
     * @var \stdClass $localPollService
     *
     * @ORM\Column(name="localPollService", type="object")
     */
    private $localPollService;


    /**
     * Get id
     *
     * @return integer 
     */
    public function getId()
    {
        return $this->id;
    }

    /**
     * Set localObjectFactory
     *
     * @param \stdClass $localObjectFactory
     * @return DataEntity
     */
    public function setLocalObjectFactory($localObjectFactory)
    {
        $this->localObjectFactory = $localObjectFactory;
    
        return $this;
    }

    /**
     * Get localObjectFactory
     *
     * @return \stdClass 
     */
    public function getLocalObjectFactory()
    {
        return $this->localObjectFactory;
    }

    /**
     * Set localPollService
     *
     * @param \stdClass $localPollService
     * @return DataEntity
     */
    public function setLocalPollService($localPollService)
    {
        $this->localPollService = $localPollService;
    
        return $this;
    }

    /**
     * Get localPollService
     *
     * @return \stdClass 
     */
    public function getLocalPollService()
    {
        return $this->localPollService;
    }
}
