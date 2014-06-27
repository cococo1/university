<?php
// src/Surveys/SurveysBundle/Controller/PageController.php
//TODO: notify that title & description were saved.





namespace Cvut\Fit\BiWt1\PollBundle\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\Controller;
// Import new namespaces
use Cvut\Fit\BiWt1\PollBundle\Entity\Enquiry;

use Cvut\Fit\BiWt1\PollBundle\Form\QuestionEnquiryType;

use Cvut\Fit\BiWt1\PollBundle\Form\EnquiryType;

use Cvut\Fit\BiWt1\PollBundle\Form\SurveyType;
use Cvut\Fit\BiWt1\PollBundle\Form\TakeSurveyType;
use Cvut\Fit\BiWt1\PollBundle\Form\QuestionType;

use Cvut\Fit\BiWt1\PollBundle\Form\TextQuestionType;
use Cvut\Fit\BiWt1\PollBundle\Form\ChoiceQuestionType;
use Cvut\Fit\BiWt1\PollBundle\Entity\ChoiceQuestionEnquiry;


use Cvut\Fit\BiWt1\PollBundle\Service\LocalPollService;
use Cvut\Fit\BiWt1\PollBundle\Service\ServiceImpl\LocalObjectFactory;

use Symfony\Component\HttpFoundation\Request;

use Cvut\Fit\BiWt1\PollBundle\Entity\DataEntity;


class PageController extends Controller
{
    protected $localObjectFactory;

    protected $localPollService;

    protected $poll;

    // protected $localQuestionService;

    public function __construct()
    {


    }

    public function loadPollFromSession($session)
    {
        if (! $session->has('poll'))
        {
            $this->poll = $this->localPollService->create();
            $this->serializeEverything($session);
            // $this->writeAllToDatabase();
            if ($this->poll) $session->set('poll', serialize($this->poll)); 

        }
        else
        {
            $this->poll = unserialize($session->get('poll'));
            // $this->writeAllToDatabase();

        }
    }

    public function removeUnsavedData($session)
    {

        // $session->remove('poll');
        // // $session->remove('localPollService');
        // // $session->remove('localObjectFactory');

        // $this->loadSurveysFromSession($session);
        // if ($this->localPollService)
        // {
        //     if ($this->poll) $this->localPollService->delete($this->poll);

        //     $polls = $this->localPollService->getPolls()->getItems();
        //     // var_dump($polls);
        //     if ($polls)
        //         foreach ( $polls as $poll)
        //         {
        //             // var_dump($)
        //             if (! $poll->getTitle()) $this->localPollService->delete($poll);
        //         }
        //     // $session->set('localPollService', serialize($this->localPollService));

        // }


        // // $this->serializeEverything($session);

    }

    public function loadAllFromDatabase()
    {
        $session = $this->get('session');
        if ($session->has('poll')) $session->remove('poll');
        if ($session->has('localPollService')) $session->remove('localPollService');
        if ($session->has('localObjectFactory')) $session->remove('localObjectFactory');

        $data = $this->getDoctrine()->getRepository('PollBundle:DataEntity')->find('4'); //this is my dataEntity...

        if (!$data) 
        {
        throw $this->createNotFoundException('No product found for id 4');
        }       
         // var_dump($data);


        $this->localObjectFactory = $data->getLocalObjectFactory();
        $this->localPollService = $data->getLocalPollService();
        if (! $this->localObjectFactory) $this->localObjectFactory = new LocalObjectFactory();
        if (! $this->localPollService) $this->localPollService = new LocalPollService($this->localObjectFactory);
        // if (! $this->poll) $this->poll = $this->localPollService->create();

        $session = $this->get('session');
        $this->serializeEverything($session);

        // $this->getDoctrine()->getManager()->flush();
        // var_dump($data);

        // var_dump($this->localObjectFactory);
        // echo "aaaaaaaaaa";
        // var_dump($this->localPollService);


        // $this->localObjectFactory = $this->localPollService-
    }

    public function writeAllToDatabase()
    {
        $em = $this->getDoctrine()->getManager();
        $data = $em->getRepository('PollBundle:DataEntity')->find('4');

        if (!$data) 
        {
        throw $this->createNotFoundException('No product found for id 4');
        }
        $data->setLocalObjectFactory($this->localObjectFactory);
        // $this->localPollService->update($this->poll);
        $data->setLocalPollService($this->localPollService);
        // $em->persist($data);
        // var_dump($data);

        // var_dump($this->localPollService);

        $em->flush();
    }

    public function indexAction()
    {
        $session = $this->get('session');
        $this->loadObjectsFromSession($session);
        
        // $this->loadAllFromDatabase();
        $session->remove('poll');
        // $this->writeAllToDatabase();

        // var_dump($this->localPollService);
        // $data = new DataEntity();
        // $localObjectFactory = new LocalObjectFactory();
        // $localPollService = new LocalPollService($localObjectFactory);
        // $data->setLocalObjectFactory($localObjectFactory);
        // $data->setLocalPollService($localPollService);
        // $em = $this->getDoctrine()->getManager();
        // $em->persist($data);
        // $em->flush();
        // echo $data->getId(); //1; 








        // $this->loadObjectsFromSession($session);
        //                var_dump($this->poll);
        //                 // echo "asdasdasd";
        //                 var_dump($this->localPollService);


        // $session->remove('localQuestionService');
        

        // $session->remove('localPollService');
        // $session->remove('localObjectFactory');

        return $this->render('PollBundle:Page:index.html.twig');
    }

    public function aboutAction()
    {
        // $session = $this->get('session');
        // $this->removeUnsavedData($session);
        return $this->render('PollBundle:Page:about.html.twig');
    }

    public function contactAction()
    {
        // $session = $this->get('session');
        // $this->removeUnsavedData($session);

        $enquiry = new Enquiry();
        $form = $this->createForm(new EnquiryType(), $enquiry);

        $request = $this->getRequest();
        if ($request->getMethod() == 'POST') {
            $form->bindRequest($request);

            if ($form->isValid()) {
                // Perform some action, such as sending an email

                    $this->get('session')->setFlash('surveys-notice', 'Your contact enquiry was successfully sent. Thank you!');

                    // Redirect - This is important to prevent users re-posting
                // the form if they refresh the page
                return $this->redirect($this->generateUrl('PollBundle_contact'));
            }
        }

        return $this->render('PollBundle:Page:contact.html.twig', array('form' => $form->createView()));
    }

    public function questionAction()
    {
      /*  $session = $this->get('session');
        $this->removeUnsavedData($session);

        $questionType = new QuestionType();
        $form = $this->createForm(new QuestionEnquiryType(), $questionType);

        $request = $this->getRequest();
        if ($request->getMethod() == 'POST') {
            $form->bindRequest($request);

           // if ($form->isValid()) {
                // Perform some action, such as sending an email

                    $this->get('session')->setFlash('question-notice', $questionType->getTypeOfQuestion());
                    $this->get('session')->set('questionType',$questionType->getTypeOfQuestion());

                    // Redirect - This is important to prevent users re-posting
                // the form if they refresh the page
                return $this->redirect($this->generateUrl('PollBundle_question'));
            //}
        }

        // $templateContent = $this->get('twig')->loadTemplate('PollBundle:Page:question.html.twig');

        // return  $templateContent->renderBlock("body", array('form'=> $form->createView()));
        return  $this->render('PollBundle:Page:question.html.twig', array('form' => $form->createView()));  
        */
    }

    private function loadObjectsFromSession($session)
    {
        if (! $session->has('localObjectFactory'))
        {
            $this->loadAllFromDatabase();
            return;
            //$this->localObjectFactory = new LocalObjectFactory();
            // $session->set('localObjectFactory', serialize($this->localObjectFactory));
        }
        else
        {
            $this->localObjectFactory = unserialize($session->get('localObjectFactory'));
        }

        if (! $session->has('localPollService'))
        {
            $this->loadAllFromDatabase();
            return;
            // $this->localPollService = new LocalPollService($this->localObjectFactory);
            // $session->set('localPollService', serialize($this->localPollService));
        }
        else
        {
            $this->localPollService = unserialize($session->get('localPollService'));
        }

        // if (! $session->has('poll'))
        // {
        //     $this->poll = $this->localPollService->create();
        //     // $this->localPollService->update($this->poll);
        // // $this->localPollService->update($this->poll);

        //     // var_dump($this->localPollService->getPolls()->getItems);
        //     // echo "has this poll";
        //      // $session->set('poll', serialize($this->poll));
        // }
        // else
        // {
        //     $this->poll = unserialize($session->get('poll'));
        // }

        // if (! $session->has('localQuestionService'))
        // {
        //     $this->localQuestionService = $this->localObjectFactory->createQuestionService($this->poll);
        //      // $session->set('localQuestionService', serialize($this->localQuestionService));
        // }
        // else
        // {
        //     $this->localQuestionService = unserialize($session->get('localQuestionService'));
        // }
        // $this->serializeEverything($session);
        // $session->remove('localObjectFactory');
    }

    public function loadSurveysFromSession($session)
    {
        // if (! $session->has('localObjectFactory'))
        // {
        //     $this->localObjectFactory = new LocalObjectFactory();
        //     // $session->set('localObjectFactory', serialize($this->localObjectFactory));
        // }
        // else
        // {
        //     $this->localObjectFactory = unserialize($session->get('localObjectFactory'));
        // }

        // if (! $session->has('localPollService'))
        // {
        //     $this->localPollService = new LocalPollService($this->localObjectFactory);
        //     // $session->set('localPollService', serialize($this->localPollService));
        // }
        // else
        // {
        //     $this->localPollService = unserialize($session->get('localPollService'));
        // }

        
        // // $this->serializeEverything($session);
        // // $session->remove('localObjectFactory');
    }

    public function serializeEverything($session)
    {
        if ($this->localObjectFactory) $session->set('localObjectFactory', serialize($this->localObjectFactory));
        // $this->localPollService->update($this->poll);

        if ($this->localPollService) $session->set('localPollService', serialize($this->localPollService));
        if ($this->poll) $session->set('poll', serialize($this->poll)); 
        // $session->set('localQuestionService', serialize($this->localQuestionService));
    }

    public function createSurveyAction()
    {
        // $this->loadAllFromDatabase();
        $session = $this->get('session');
        // $this->loadPollFromSession($session);

        $this->loadObjectsFromSession($session);
        $this->loadPollFromSession($session);

        // var_dump($this->poll);
        
        // if (! strcmp($action, "createTextQuestion"))
        // {
        //     $question = $this->localQuestionService->create("", LocalObjectFactory::TEXT_QUESTION);
        // }
        // elseif (! strcmp($action, "createChoiceQuestion"))
        // {
        //     echo "create choice question";
        // }
        // elseif (! strcmp($action, "render"))
        // {

        // }
        // elseif (! strcmp($action, "post"))
        // {
            $form = $this->createForm(new SurveyType(), $this->poll, array('data' => $this->poll));
            // $this->serializeEverything($session);


            $request = $this->getRequest();
            if ($request->getMethod() == 'POST') 
            {
                $form->bindRequest($request);
                if ($this->poll) $session->set('poll', serialize($this->poll)); 

                 // $this->serializeEverything($this->get('session'));


                if (isset($_POST['saveTitle']))
                {
                    if ($this->poll) $this->localPollService->update($this->poll);
                    // $this->writeAllToDatabase();
                    if ($this->poll) $session->set('poll', serialize($this->poll)); 

                    // $this->serializeEverything($session);

                }
                else
                    {

                    // echo $poll->getDescription();


                    if ($form->isValid())
                    {
                        // Perform some action, such as sending an email

                        $session->setFlash('surveys-notice', 'Your survey was created.');
                                                // $session->remove('localObjectFactory');
                        // $this->poll->setTitle($title);
                        // $this->poll->setDescription($description);
                        $this->localPollService->update($this->poll);
                        $this->writeAllToDatabase();
                        if ($session->has('poll')) $session->remove('poll');
                        // if ($session->has('localPollService')) $session->remove('localPollService');
                        // if ($session->has('localObjectFactory')) $session->remove('localObjectFactory');
                        // $this->loadAllFromDatabase();
                        // if ($this->poll) $session->set('poll', serialize($this->poll)); 


                // echo $this->poll->getId();

                        // $this->serializeEverything($session);
                        // echo "aaaaa";
                        // echo "asdaa";




                        // $session->remove('localQuestionService');
                        // $session->remove('poll');
                        // $session->remove('localPollService');



                            // Redirect - This is important to prevent users re-posting
                        // the form if they refresh the page
                        return $this->redirect($this->generateUrl('PollBundle_homepage'));
                    }
                }
            }
        // }



        // var_dump($this->poll);
        $createdQuestions = $this->poll->getItems();// $this->localQuestionService->getAllQuestions();

         // $response = $this->render('PollBundle:Page:createSurvey.html.twig', array('form' => $form->createView()));

        $response = $this->render('PollBundle:Page:createSurvey.html.twig', 
            array('form' => $form->createView(), 
                'createdQuestions' => $createdQuestions)); 
                //,'questionService' => $this->localQuestionService)



        return $response;
    }


    public function takeSurveyAction($id)
    {
        // $this->loadAllFromDatabase();
        $session = $this->get('session');
        $this->loadObjectsFromSession($session);
        // $this->removeUnsavedData($session);

        $response = NULL;
        $survey = NULL;
        $createdQuestions = NULL;

        // $this->loadSurveysFromSession($session);
        $survey = $this->localPollService->find($id);
        // var_dump($survey);
        $createdQuestions = $survey->getItems();

        // $form = $this->createForm(new TakeSurveyType(), $survey, array('data' => $survey));
        $request = $this->getRequest();

        if ($request->getMethod() == 'POST') 
        {
            $allRight = TRUE;
            foreach ($createdQuestions as $q)
            {
                // var_dump($q);
                if (  !isset( $_POST[$q->getId()] )  )
                {
                    $allRight = FALSE;
                    // if ($this->poll) $this->localPollService->update($this->poll);
                    // $this->serializeEverything($session);
                }
                else
                {
                    $answer = NULL;
                    // $question = $survey->getItem($id);
                    if (! strcmp($q->getType(), "textQuestion"))
                    {
                        $answer = $this->localObjectFactory->createAnswer(LocalObjectFactory::TEXT_ANSWER);
                        $answer->setAnswer($_POST[$q->getId()]);
                    }
                    elseif (! strcmp($q->getType(), "singleChoiceQuestion"))
                    {
                        $answer = $this->localObjectFactory->createAnswer(LocalObjectFactory::SINGLE_CHOICE_ANSWER);
                        $answer->setQuestion($q);

                        // $option = $this->localObjectFactory->createOption();
                        $option = $q->getOption($_POST[$q->getId()]);
                        $answer->setAnswer($option);
                    }
                    else
                    {
                        foreach ($_POST[$q->getId()] as $answeredOptionId)
                        {
                            $answer = $this->localObjectFactory->createAnswer(LocalObjectFactory::MULTIPLE_CHOICE_ANSWER);
                            $answer->setQuestion($q);
                            // $option = $q->getOption()
                            // $option = $this->localObjectFactory->createOption();
                            // $option->setOption($_POST[$q->getId()]);
                            // var_dump($q->getOptions());
                            // echo "asdasda";
                            // var_dump($answer->getAnswer());
                            $option = $q->getOption($answeredOptionId);
                            $answer->addAnswerOption($option);                        }

                    }
                    $q->addAnswer($answer);


                    $survey->addItem($q);

                }
            }


            if ($allRight)
            {
                $session->setFlash('surveys-notice', 'Thank you for taking this survey!');
                // echo '<pre>'.var_dump($survey).'</pre>';
                $this->localPollService->update($survey);
                $this->writeAllToDatabase();

                // $this->serializeEverything($session);
                $response = $this->redirect($this->generateUrl('PollBundle_homepage'));
                // $response =$this->render('PollBundle:Page:takeSurvey.html.twig', array( 'survey' => $survey, 'createdQuestions' => $createdQuestions ));




            }
            else
            {
                $session->setFlash('surveys-notice', 'Please, answer all question then submit the survey.');
                $response =$this->render('PollBundle:Page:takeSurvey.html.twig', array( 'survey' => $survey, 'createdQuestions' => $createdQuestions ));

            }



            return $response; 

        } 


        $response = $this->render('PollBundle:Page:takeSurvey.html.twig', array( 'survey' => $survey, 'createdQuestions' => $createdQuestions ));

        return $response;
    }





    public function textQuestionAction($id)
    {
        $session = $this->getRequest()->getSession();
        $this->loadObjectsFromSession($session);
        // $this->loadAllFromDatabase();
        $this->loadPollFromSession($session);

        // $this->loadObjectsFromSession($session);



        // if (! $session->has('localQuestionService'))
        // {
        //     $this->localQuestionService = $this->localObjectFactory->createQuestionService($this->poll);
        //      $session->set('localQuestionService', serialize($this->localQuestionService));
        // }
        // else
        // {
        //     $this->localQuestionService = unserialize($session->get('localQuestionService'));
        // }

        $question = NULL;
        if (! strcmp( $id, "0") ) 
        {
            $question = $this->localObjectFactory->createQuestion(LocalObjectFactory::TEXT_QUESTION); //localQuestionService...
            $this->poll->addItem($question);


        }
        else
        {
            // $question = $this->localQuestionService->find($id);

            $question = $this->poll->getItem($id);
            // $this->localQuestionService->delete($question);
            // $session->set('localQuestionService', serialize($this->localQuestionService));
        }
        $form = $this->createForm(new TextQuestionType(), $question, array ('data' => $question ));



        $request = $this->getRequest();
        if ($request->getMethod() == 'POST') {
            $form->bindRequest($request);
            // echo $poll->getDescription();


            if ($form->isValid()) {
                // Perform some action, such as sending an email

                    $this->get('session')->setFlash('surveys-notice', 'Your question was created.');
                    // echo $question->getQuestion();
                    // $textOfQuestion = $question->getQuestion();
                    // $this->localQuestionService->update($question);
                    // $this->poll->removeItem($question);
                    $this->poll->addItem($question);
                    // $question = $this->localQuestionService->create($textOfQuestion, LocalObjectFactory::TEXT_QUESTION);

                    $this->serializeEverything($session);
                    // $this->writeAllToDatabase();
                    if ($this->poll) $session->set('poll', serialize($this->poll)); 




                    // Redirect - This is important to prevent users re-posting
                // the form if they refresh the page
                // $request1 = new Request();
                // $request1->setMethod('GET');
                return $this->redirect($this->generateUrl('PollBundle_createSurvey'));//$this->generateUrl('PollBundle_createSurvey'));
            }
        }




        return $this->render('PollBundle:Page:textQuestion.html.twig' , array('form' => $form->createView()));
    }

    
    public function deleteQuestionAction($id)
    {
        $session = $this->getRequest()->getSession();
        $this->loadObjectsFromSession($session);
        // $this->loadAllFromDatabase();
        $this->loadPollFromSession($session);


        // echo $id;
        // $question = $this->localQuestionService->find($id);
        // $this->localQuestionService->delete($question);
        $question = $this->poll->getItem($id);
        $this->poll->removeItem($question);
        $this->serializeEverything($session);
        // $this->writeAllToDatabase();
        if ($this->poll) $session->set('poll', serialize($this->poll)); 
        // $session->set('localQuestionService', serialize($this->localQuestionService));

                // $request1 = new Request();
                // $request1->setMethod('GET');
                return $this->redirect($this->generateUrl('PollBundle_createSurvey'));//$this->createSurveyAction($request1);
    }


    public function modifyQuestionAction($id)
    {
        $session = $this->getRequest()->getSession();
        // $this->loadAllFromDatabase();
        
        $this->loadObjectsFromSession($session);
        $this->loadPollFromSession($session);

        // $question = $this->localQuestionService->find($id);
        $question = $this->poll->getItem($id);
        // echo $question->getType();
        if (! strcmp($question->getType(), "textQuestion"))
        {
            return $this->redirect($this->generateUrl('PollBundle_textQuestion', array('id' => $id )));
        }
        elseif (! strcmp($question->getType(), "singleChoiceQuestion"))
        {
            return $this->redirect($this->generateUrl('PollBundle_choiceQuestion', array('id' => $id, 'type' => "single" )));
        }
        elseif (! strcmp($question->getType(), "multipleChoiceQuestion"))
        {
            return $this->redirect($this->generateUrl('PollBundle_choiceQuestion', array('id' => $id, 'type' => "multiple" )));
        }


        // echo $id;
        // $question = $this->localQuestionService->find($id);
        // $questionText = $question->getQuestion();
        // //$this->localQuestionService->delete($question);
        // $session->set('localQuestionService', serialize($this->localQuestionService));

                // $request1 = new Request();
                // $request1->setMethod('GET');
        // return $this->redirect($this->generateUrl('PollBundle_textQuestion', array('id' => $id )));

    }




    public function choiceQuestionAction($type,$id)
    {
        $session = $this->getRequest()->getSession();
        // $this->loadAllFromDatabase();
        $this->loadObjectsFromSession($session);
        $this->loadPollFromSession($session);

        
        $enquiry = new ChoiceQuestionEnquiry();
        $question = NULL;
        if (! strcmp( $id, "0") ) 
        {
            if (! strcmp($type, "single"))
            {
                // $question = $this->localQuestionService->create("", LocalObjectFactory::SINGLE_CHOICE_QUESTION);
                $question = $this->localObjectFactory->createQuestion(LocalObjectFactory::SINGLE_CHOICE_QUESTION);
                $this->poll->addItem($question);
            }
            elseif (! strcmp($type, "multiple"))
            {
                // $question = $this->localQuestionService->create("", LocalObjectFactory::MULTIPLE_CHOICE_QUESTION);

                $question = $this->localObjectFactory->createQuestion(LocalObjectFactory::MULTIPLE_CHOICE_QUESTION);
                $this->poll->addItem($question);
            }


        }
        else
        {

            // $question = $this->localQuestionService->find($id); 
            $question = $this->poll->getItem($id);
            $enquiry->setQuestion($question->getQuestion());
            $options = $question->getOptions();
            $stringOptions = "";
            foreach ($options as $option)
            {   
                $stringOptions .=$option->getOption()."\n";
            }
            // echo $stringOptions;
            $enquiry->setOptions($stringOptions); 

            // ...      
            // $this->localQuestionService->delete($question);
            // $session->set('localQuestionService', serialize($this->localQuestionService));
        }
        $form = $this->createForm(new ChoiceQuestionType(), $enquiry, array ('data' => $enquiry ));



        $request = $this->getRequest();
        if ($request->getMethod() == 'POST') {
            $form->bindRequest($request);
            // echo $poll->getDescription();


            if ($form->isValid()) {
                // Perform some action, such as sending an email

                    $this->get('session')->setFlash('surveys-notice', 'Your question was created.');
                    // echo $question->getQuestion();
                    // $textOfQuestion = $question->getQuestion();
                    //...
                    if ($question->getOptions())
                        foreach ($question->getOptions() as $option)
                        {
                            $question->removeOption($option);
                        }

                    $question->setQuestion($enquiry->getQuestion());
                    $arrayOfOptions = preg_split("/\n/", preg_replace("/(^[\r\n]*|[\r\n]+)[\s\t]*[\r\n]+/", "\n", $enquiry->getOptions()));
                    //explode(" ", $enquiry->getOptions());
                    foreach ($arrayOfOptions as $optionString)
                    {
                        $option = $this->localObjectFactory->createOption();
                        $option->setOption($optionString);
                        $question->addOption($option);
                        // $this->localQuestionService->addOption($question, $option);
                    }
                    // $this->localQuestionService->update($question);
                    // $this->poll->removeItem($question);
                    $this->poll->addItem($question);
                    // $question = $this->localQuestionService->create($textOfQuestion, LocalObjectFactory::TEXT_QUESTION);

                    $this->serializeEverything($session);
                // $this->writeAllToDatabase();
                if ($this->poll) $session->set('poll', serialize($this->poll)); 



                    // Redirect - This is important to prevent users re-posting
                // the form if they refresh the page
                // $request1 = new Request();
                // $request1->setMethod('GET');
                return $this->redirect($this->generateUrl('PollBundle_createSurvey'));//$this->generateUrl('PollBundle_createSurvey'));
            }
        }
        $response = NULL;
        if (! strcmp($type, "single"))
        {
            $response = $this->render('PollBundle:Page:choiceQuestion.html.twig' , array('form' => $form->createView(), 'type' => "single"));
            // $question = $this->localQuestionService->create("", LocalObjectFactory::SINGLE_CHOICE_QUESTION);
        }
        elseif (! strcmp($type, "multiple"))
        {
            // $question = $this->localQuestionService->create("", LocalObjectFactory::MULTIPLE_CHOICE_QUESTION);
            $response = $this->render('PollBundle:Page:choiceQuestion.html.twig' , array('form' => $form->createView(), 'type' => "multiple"));

        }

        return $response;  
    }

public function  saveTitleAction($title)
{
    $session = $this->getRequest()->getSession();
    // $this->loadAllFromDatabase();
    
    $this->loadObjectsFromSession($session);
    $this->loadPollFromSession($session);

    $this->poll->setTitle($title);

    $this->serializeEverything($session);
    // $this->writeAllToDatabase();
    if ($this->poll) $session->set('poll', serialize($this->poll)); 


    return $this->redirect($this->generateUrl('PollBundle_createSurvey'));
}

public function  saveDescriptionAction($description)
{
    $session = $this->getRequest()->getSession();
    $this->loadObjectsFromSession($session);
    $this->loadPollFromSession($session);


    $this->poll->setDescription($description);

    $this->serializeEverything($session);
    if ($this->poll) $session->set('poll', serialize($this->poll)); 


    return $this->redirect($this->generateUrl('PollBundle_createSurvey'));

}
    
public function  listSurveysAction($display)
{
    $session = $this->getRequest()->getSession();

    // $this->removeUnsavedData($session);
    $this->loadAllFromDatabase();


    // $this->loadSurveysFromSession($session);

    // var_dump($this->localPollService);
    $surveys = $this->localPollService->getPolls()->getItems();

    // var_dump($surveys);
    // echo $this->poll->getTitle();

    $response = $this->render('PollBundle:Page:surveysList.html.twig' , array('surveys' => $surveys, 'display' => $display));

    return $response;

}

public function displaySurveyAction($id)
{
    $session = $this->getRequest()->getSession();
    // $this->loadAllFromDatabase();

            // $session = $this->get('session');
    // $this->removeUnsavedData($session);

    $this->loadObjectsFromSession($session);

    $this->poll = $this->localPollService->find($id);
    $this->serializeEverything($session);
    if ($this->poll) $session->set('poll', serialize($this->poll)); 
    // $this->writeAllToDatabase();


    // var_dump($this->poll);
    // $form = $this->createForm(new SurveyType(), $this->poll, array('data' => $this->poll));


    $createdQuestions = $this->poll->getItems();

         // $response = $this->render('PollBundle:Page:createSurvey.html.twig', array('form' => $form->createView()));

    $response = $this->render('PollBundle:Page:displaySurvey.html.twig', 
            array(
                'createdQuestions' => $createdQuestions,
                'survey' => $this->poll));



    return $response;


}

public function deleteSurveyAction($id)
{
    $session = $this->getRequest()->getSession();
    $this->loadObjectsFromSession($session);
    // $this->loadSurveysFromSession($session);
    // $this->loadAllFromDatabase();


    $this->localPollService->delete($this->localPollService->find($id));
    $this->writeAllToDatabase();

    // $session->set('localPollService', serialize($this->localPollService));
    $this->get('session')->setFlash('surveys-notice', 'Survey was deleted.');



    return $this->redirect($this->generateUrl('PollBundle_listSurveys', array('display' => "true" )));
}

public function seeAnswersAction($surveyId, $id)
{
    $session = $this->getRequest()->getSession();
    // $this->loadSurveysFromSession($session);
    // $this->loadAllFromDatabase();
    $this->loadObjectsFromSession($session);

    $survey = $this->localPollService->find($surveyId);
    $question = $survey->getItem($id);

    $answers = NULL;
    $answers = $question->getAnswers()->getItems();
    $textAnswers = NULL;
    // var_dump($answers);
    if ($answers)
        foreach ($answers as $answer)
        {
            $textAnswers[$answer->getId()] = $answer->getAnswer();
            // echo $answer->getAnswer();
        }
    // var_dump($answers);
    // $session->set('localPollService', serialize($this->localPollService));
    // $this->get('session')->setFlash('surveys-notice', 'Survey was deleted.');


    return $this->render('PollBundle:Page:seeAnswers.html.twig', array( 'survey' => $survey, 'question' => $question, 'answers' => $textAnswers ));

    // return $this->redirect($this->generateUrl('PollBundle_listSurveys', array('display' => "true" )));
}







}