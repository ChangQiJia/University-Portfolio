#include "stdafx.h"
#include "Assn2.h"
 
//-------------------------------------------------------------------------------------
Assn2::Assn2(void)
{
}
//-------------------------------------------------------------------------------------
Assn2::~Assn2(void)
{
	if(mPhysicsEngine)
		delete mPhysicsEngine;
}

bool Assn2::setup(void)
{
	mPhysicsEngine = new PhysicsEngine();
	mPhysicsEngine->initPhysics();

	mBoxCount = 0;

	BaseApplication::setup();

	mTrayMgr->hideCursor();

	return true;
};

//-------------------------------------------------------------------------------------
void Assn2::createScene(void)
{
	weaponType = 1; 
	counter = 0; 
	shot = false; 
	impact = false; 
	timeSmoke = false; 

	mCamera->setPosition(Ogre::Vector3(0, 0, 0));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	
	Ogre::SceneNode* particle = mSceneMgr->getRootSceneNode () -> createChildSceneNode ("Particle");

	Ogre::SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("camNode", Ogre::Vector3 (0,50,100));
	camNode->attachObject (mCamera);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));
 
    // create the light
    Ogre::Light *light = mSceneMgr->createLight("Light1");
    light->setType(Ogre::Light::LT_POINT);
    light->setPosition(Ogre::Vector3(250, 250, 250));
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue::White);

	// Create the ground object shape
	btBoxShape* groundShape = new btBoxShape(btVector3(150.0f, 0.01f, 150.0f));
	btBoxShape* topShape = new btBoxShape(btVector3(150.0f, 0.01f, 150.0f));
	btBoxShape* leftShape = new btBoxShape(btVector3(150.0f, 0.01f, 150.0f));
	btBoxShape* rightShape = new btBoxShape(btVector3(150.0f, 0.01f, 150.0f));
	btBoxShape* backShape = new btBoxShape(btVector3(150.0f, 0.01f, 150.0f));
	btBoxShape* frontShape = new btBoxShape(btVector3(150.0f, 0.01f, 150.0f));

	// Set the object's transformation
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, 0, 0));

	btTransform topTransform;
	topTransform.setIdentity();
	topTransform.setOrigin(btVector3(0, 300, 0));

	btTransform leftTransform;
	leftTransform.setIdentity();
	leftTransform.setOrigin(btVector3(-150, 150, 0));
	leftTransform.setRotation (btQuaternion(btScalar(0), btScalar (1.5708), btScalar (0)));
	leftTransform.setRotation (btQuaternion(btScalar(0), btScalar (0), btScalar (1.5708)));

	btTransform rightTransform;
	rightTransform.setIdentity();
	rightTransform.setOrigin(btVector3(150, 150, 0));
	rightTransform.setRotation (btQuaternion(btScalar(0), btScalar (1.5708), btScalar (0)));
	rightTransform.setRotation (btQuaternion(btScalar(0), btScalar (0), btScalar (1.5708)));

	btTransform backTransform;
	backTransform.setIdentity();
	backTransform.setOrigin(btVector3(0, 150, -150));
	backTransform.setRotation (btQuaternion(btScalar(0), btScalar (1.5708), btScalar (0)));
	
	btTransform frontTransform;
	frontTransform.setIdentity();
	frontTransform.setOrigin(btVector3(0, 150, 150));
	frontTransform.setRotation (btQuaternion(btScalar(0), btScalar (1.5708), btScalar (0)));

	Ogre::Entity* cube = mSceneMgr->createEntity("Ground", "cube.mesh");
	Ogre::SceneNode* groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	groundNode->attachObject(cube);
	groundNode->scale(1, 0.25, 1);
	groundNode->translate(0, 0, 0);

	Ogre::Entity* topCube = mSceneMgr->createEntity("top", "cube.mesh");
	Ogre::SceneNode* topNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	topNode->attachObject(topCube);
	topNode->scale(1, 0.25, 1);
	topNode->translate(0, 0, 0);

	Ogre::Entity* leftCube = mSceneMgr->createEntity("left", "cube.mesh");
	Ogre::SceneNode* leftNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	leftNode->attachObject(leftCube);
	leftNode->scale(1, 0.25, 1);
	leftNode->translate(0, 0, 0);

	Ogre::Entity* rightCube = mSceneMgr->createEntity("right", "cube.mesh");
	Ogre::SceneNode* rightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	rightNode->attachObject(rightCube);
	rightNode->scale(1, 0.25, 1);
	rightNode->translate(0, 0, 0);

	Ogre::Entity* backCube = mSceneMgr->createEntity("back", "cube.mesh");
	Ogre::SceneNode* backNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	backNode->attachObject(backCube);
	backNode->scale(1, 0.25, 1);
	backNode->translate(0, 0, 0);

	Ogre::Entity* frontCube = mSceneMgr->createEntity("front", "cube.mesh");
	Ogre::SceneNode* frontNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	frontNode->attachObject(frontCube);
	frontNode->scale(1, 0.25, 1);
	frontNode->translate(0, 0, 0);

	// Create the rigid body
	mPhysicsEngine->createRigidBody(0.0f, groundTransform, groundShape, groundNode);
	mPhysicsEngine->createRigidBody(0.0f, topTransform, topShape, topNode);
	mPhysicsEngine->createRigidBody(0.0f, leftTransform, leftShape, leftNode);
	mPhysicsEngine->createRigidBody(0.0f, rightTransform, rightShape, rightNode);
	mPhysicsEngine->createRigidBody(0.0f, backTransform, backShape, backNode);
	mPhysicsEngine->createRigidBody(0.0f, frontTransform, frontShape, frontNode);

	leftNode -> setVisible(false); 
	rightNode -> setVisible (false); 
	groundNode -> setVisible(false);
	topNode -> setVisible (false); 
	backNode -> setVisible (false); 
	frontNode -> setVisible (false); 

	// Use a place to represent the ground
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 
		300, 300, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/GrassFloor");
	entGround->setCastShadows(false);

	Ogre::Entity* entTop = mSceneMgr->createEntity ("TopEntity", "ground"); 
	topNode->attachObject (entTop); 
	entTop ->setMaterialName ("Examples/CloudySky"); 
	entTop->setCastShadows(false); 
	topNode->pitch (Ogre::Degree(180)); 
	topNode->translate (Ogre::Vector3 (0,300,0)); 

	Ogre::Entity* entLeft = mSceneMgr->createEntity ("LeftEntity", "ground"); 
	leftNode->attachObject (entLeft); 
	entLeft ->setMaterialName ("Examples/Rockwall"); 
	entLeft->setCastShadows(false); 
	leftNode->roll (Ogre::Degree (-90)); 
	leftNode->yaw (Ogre::Degree (90)); 
	leftNode->translate (Ogre::Vector3 (-150,150,0)); 

	Ogre::Entity* entRight = mSceneMgr->createEntity ("RightEntity", "ground"); 
	rightNode->attachObject (entRight); 
	entRight ->setMaterialName ("Examples/Rockwall"); 
	entRight->setCastShadows(false); 
	rightNode->roll (Ogre::Degree (90)); 
	rightNode->yaw (Ogre::Degree (90)); 
	rightNode->translate (Ogre::Vector3 (150,150,0)); 

	Ogre::Entity* entBack = mSceneMgr->createEntity ("BackEntity", "ground"); 
	backNode->attachObject (entBack); 
	entBack ->setMaterialName ("Examples/Rockwall"); 
	entBack->setCastShadows(false); 
	backNode->pitch (Ogre::Degree (90)); 
	backNode->translate (Ogre::Vector3 (0,150,-150)); 

	Ogre::Entity* entFront = mSceneMgr->createEntity ("FrontEntity", "ground"); 
	frontNode->attachObject (entFront); 
	entFront ->setMaterialName ("Examples/Rockwall"); 
	entFront->setCastShadows(false); 
	frontNode->pitch (Ogre::Degree (270)); 
	frontNode->translate (Ogre::Vector3 (0,150,150)); 

	for (int j = 1; j <= 3 ;j++)
	{
		for (int i = 1; i <= 5 ; i++) 
			{

				std::ostringstream oss;
				oss << mBoxCount;
				std::string entityName = "Box" + oss.str();
				// Increment box count
				mBoxCount++;
			
				Ogre::Entity* box = mSceneMgr->createEntity(entityName, "cube.mesh");
				box->setMaterialName ("myMaterial/TexturedBoxMaterial"); 
				Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
				node->attachObject(box);
				// Scale it to appropriate size
				node->scale(0.1, 0.1, 0.1);

				// Create a collision shape
				// Note that the size should match the size of the object that will be displayed
				btCollisionShape* collisionShape = new btBoxShape(btVector3 (5,5,5));
				btTransform startingTrans;
				startingTrans.setIdentity();
				startingTrans.setOrigin(btVector3 (10*j,10*i,-100));

				// Create the rigid body
				btRigidBody* rigidBody = mPhysicsEngine->createRigidBody(1.0f, startingTrans, collisionShape, node);	
				rigidBody -> setFriction (0.9); 
			}
	}
		Ogre::Entity* barrel = mSceneMgr->createEntity("Barrel", "barrel.mesh");
		barrel->setMaterialName ("RustyBarrel"); 
		Ogre::SceneNode* barrelNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		barrelNode->attachObject(barrel);
		
		// Scale it to appropriate size
		barrelNode->scale(4, 4, 4);
		
		// Create a collision shape
		// Note that the size should match the size of the object that will be displayed
		btCollisionShape* collisionShape = new btCylinderShape(btVector3 (12,12,12));
		btTransform Trans;
		Trans.setIdentity();
		Trans.setOrigin(btVector3 (-50,30,-100));
		
		// Create the rigid body
		btRigidBody* rigidBody = mPhysicsEngine->createRigidBody(5.0f, Trans, collisionShape, barrelNode);
		rigidBody -> setFriction (0.9); 

		Ogre::OverlayManager* overlayManager = Ogre::OverlayManager::getSingletonPtr();

		overlay = overlayManager->create("Overlay");

		Ogre::Image image;
		image.load("Crosshair.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		Ogre::TextureManager::getSingleton().loadImage("LogoTexture", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, image, Ogre::TEX_TYPE_2D, 0, 1.0f); 
		image.freeMemory();

		Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().create("ImageMaterial", "General"); 
		materialPtr->getTechnique(0)->getPass(0)->createTextureUnitState("LogoTexture");
		materialPtr->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
		Ogre:: OverlayContainer* crosshairImageContainer = static_cast<Ogre::OverlayContainer*>(overlayManager->createOverlayElement("Panel", "DisplayImage1"));
		crosshairImageContainer->setMaterialName("ImageMaterial");
		crosshairImageContainer->setMetricsMode(Ogre::GMM_PIXELS);
		crosshairImageContainer->setDimensions (76,76); 
		crosshairImageContainer->setPosition((mWindow->getWidth()/2 - 38 ),(mWindow->getHeight()/2 - 38));

		overlay->add2D(crosshairImageContainer);
		overlay->show();
		

}

void Assn2::createFrameListener(void)
{
	BaseApplication::createFrameListener();
 
	// set the rotation and move speed
	mRotate = 0.13;
	mMove = 250;
 
	mDirection = Ogre::Vector3::ZERO;
}



bool Assn2:: frameRenderingQueued (const Ogre:: FrameEvent& evt) 
{
	static Ogre::Real sToggle = 0.0; 

	if(mWindow->isClosed())
        return false;
 
	if(mShutDown)
		return false;

	mCamera->moveRelative(mDirection * mMove * evt.timeSinceLastFrame/1000);

	mTrayMgr->frameRenderingQueued(evt);

	if (!mTrayMgr->isDialogVisible())
	{
		mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
		if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
		{
			mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
			mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
			mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
			mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
			mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
			mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
			mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
		}
	}

	// Update physics simulation
	mPhysicsEngine->update(evt.timeSinceLastFrame);

	bool ret = BaseApplication::frameRenderingQueued(evt);

	transVector = Ogre::Vector3::ZERO; 

	Ogre::Vector3 pos = mSceneMgr->getSceneNode("camNode") -> getPosition () ; 

	if (mKeyboard->isKeyDown(OIS::KC_W)) // Forward
    {
       if (pos.z > -140) 
			transVector.z -= (mMove/3);
    }
    if (mKeyboard->isKeyDown(OIS::KC_S)) // Backward
    {
		if (pos.z < 140) 
			transVector.z += (mMove/3);
    }
    if (mKeyboard->isKeyDown(OIS::KC_A)) // Left - yaw or strafe
    {
		if (pos.x > -140) 
			transVector.x -= (mMove/3); 
    }
    if (mKeyboard->isKeyDown(OIS::KC_D)) // Right - yaw or strafe
    {
		if (pos.x < 140) 
			transVector.x += (mMove/3); 
    }
 
    mSceneMgr->getSceneNode("camNode")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	if (impact) 
	{
		btCollisionObject* tempObj = mPhysicsEngine -> checkForCollision (grenades[0]);  
		
		if (tempObj != NULL) 
		{

			btVector3 point = grenades[0] -> getCenterOfMassPosition (); 

			 mPhysicsEngine -> explosion (point); 
			 mPhysicsEngine -> destroyRigidBody (grenades[0]); 
			 grenades[0] = NULL; 
			 impact = false; 
			 mSceneMgr -> getRootSceneNode () -> removeAndDestroyChild ("Impact");

		}
	}

	if (smoke) 
	{
		btCollisionObject* tempObj = mPhysicsEngine -> checkForCollision (grenades[1]);  
		
		if (tempObj != NULL) 
		{

			btVector3 point = grenades[1] -> getCenterOfMassPosition (); 

			mSceneMgr -> getSceneNode ("Particle") -> createChild ("tempSmoke"); 

			 //mPhysicsEngine -> explosion (point); 
			particleSystem = mSceneMgr -> createParticleSystem ("Smokes", "Examples/Smoke"); 
			mSceneMgr -> getSceneNode ("tempSmoke") -> translate (convert(point)); 
			mSceneMgr -> getSceneNode ("tempSmoke") -> attachObject (particleSystem); 
			mPhysicsEngine -> destroyRigidBody (grenades[1]); 
			grenades[1] = NULL; 
			smoke = false; 
			timeSmoke = true; 
			mSceneMgr -> getRootSceneNode () -> removeAndDestroyChild ("Smoke");
			
			sToggle = 5; 
		}

	}
	
	if (sToggle < 0.0f)
	{
		 mSceneMgr -> destroyParticleSystem ("Smokes"); 
		 mSceneMgr -> getSceneNode ("Particle") -> removeAndDestroyChild ("tempSmoke");
		 timeSmoke = false; 
		 sToggle = 0.0; 
	}
	if (timeSmoke)
		sToggle -= evt.timeSinceLastFrame; 

    if(!processUnbufferedInput(evt)) return false;
 
    return ret;
}
 
// OIS::KeyListener
bool Assn2::keyPressed( const OIS::KeyEvent &arg )
{
	Ogre:: Vector3 pos = mCamera -> getPosition(); 

    switch (arg.key)
	{
		case OIS::KC_ESCAPE: 
			mShutDown = true;
			break;

		default:
			break;
	}

	return true;
}
 
bool Assn2::keyReleased( const OIS::KeyEvent &arg )
{

	Ogre::String newVal; 

	switch (arg.key)
	{
		case OIS::KC_UP:
		case OIS::KC_W:
			mDirection.z = 0;
			transVector.x = 0; 
			break;
 
		case OIS::KC_DOWN:
		case OIS::KC_S:
			mDirection.z = 0;
			transVector.x = 0; 
			break;
 
		case OIS::KC_LEFT:
		case OIS::KC_A:
			mDirection.x = 0;
			transVector.z = 0; 
			break;
 
		case OIS::KC_RIGHT:
		case OIS::KC_D:
			mDirection.x = 0;
			transVector.z = 0; 
			break;
 
		case OIS::KC_PGDOWN:
		case OIS::KC_E:
			mDirection.y = 0;
			break;
 
		case OIS::KC_PGUP:
		case OIS::KC_Q:
			mDirection.y = 0;
			break;

		case OIS::KC_1:
			weaponType = 1; 
			newVal = "Ball Shooting Machine"; 
			mDebugPanel->setParamValue(0, newVal);
			break ; 
		
		case OIS::KC_2:
			weaponType = 2; 
			newVal = "Hand Gun"; 
			mDebugPanel->setParamValue(0, newVal);
			break ; 
		
		case OIS::KC_3:
			weaponType = 3; 
			newVal = "Machine Gun"; 
			mDebugPanel->setParamValue(0, newVal);
			break ; 
		
		case OIS::KC_4:
			weaponType = 4; 
			newVal = "Shotgun"; 
			mDebugPanel->setParamValue(0, newVal);
			break ; 
		
		case OIS::KC_5:
			weaponType = 5; 
			newVal = "Sniper"; 
			mDebugPanel->setParamValue(0, newVal);
			break ; 

		case OIS::KC_6:
			weaponType = 6; 
			newVal = "Impact Grenade"; 
			mDebugPanel->setParamValue(0, newVal);
			break ; 

		case OIS::KC_7:
			weaponType = 7; 
			newVal = "Smoke Grenade"; 
			mDebugPanel->setParamValue(0, newVal);
			break ; 

 
		default:
			break;
	}


	return true;
}


void Assn2::shootBall(const btVector3& position, const btQuaternion& orientation, const btVector3& linearVelocity)
{
	// Create unique name
	std::ostringstream oss;
	oss << mBoxCount;
	std::string entityName = "Ball" + oss.str();
	// Increment box count
	mBoxCount++;
		
	// Create cube mesh with unique name
	Ogre::Entity* ball = mSceneMgr->createEntity(entityName, "sphere.mesh");
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ball);
	// Scale it to appropriate size
	node->scale(0.02, 0.02, 0.02);

	// Create a collision shape
	// Note that the size should match the size of the object that will be displayed
	btCollisionShape* collisionShape = new btSphereShape(btScalar (2));

	// The object's starting transformation
	btTransform startingTrans;
	startingTrans.setIdentity();
	startingTrans.setOrigin(position);
	startingTrans.setRotation(orientation);

	// Create the rigid body
	btRigidBody* rigidBody = mPhysicsEngine->createRigidBody(1.0f, startingTrans, collisionShape, node);

	// Give the rigid body an initial velocity
	rigidBody->setLinearVelocity(linearVelocity);
}

void Assn2::shootImpact(const btVector3& position, const btQuaternion& orientation, const btVector3& linearVelocity)
{
	// Create cube mesh with unique name
	std::ostringstream oss;
	oss << mBoxCount;
	std::string entityName = "Nade" + oss.str();
	// Increment box count
	mBoxCount++;

	Ogre::Entity* nade = mSceneMgr->createEntity(entityName, "sphere.mesh");
	nade->setMaterialName ("Examples/SphereMappedRustySteel"); 
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Impact");
	node->attachObject(nade);
	// Scale it to appropiate size
	node->scale(0.05, 0.05, 0.05);

	// Create a collision shape
	// Note that the size should match the size of the object that will be displayed
	btCollisionShape* collisionShape = new btSphereShape(btScalar (5));

	// The object's starting transformation
	btTransform startingTrans;
	startingTrans.setIdentity();
	startingTrans.setOrigin(position);
	startingTrans.setRotation(orientation);

	// Create the rigid body
	btRigidBody* rigidBody = mPhysicsEngine->createRigidBody(1.0f, startingTrans, collisionShape, node);

	// Give the rigid body an initial velocity
	rigidBody->setLinearVelocity(linearVelocity);

	grenades [0] = rigidBody; 

	impact = true; 

	
}

void Assn2::shootSmoke(const btVector3& position, const btQuaternion& orientation, const btVector3& linearVelocity)
{
	std::ostringstream oss;
	oss << mBoxCount;
	std::string entityName = "Smoke" + oss.str();
	// Increment box count
	mBoxCount++;

	// Create cube mesh with unique name
	Ogre::Entity* nade = mSceneMgr->createEntity(entityName, "sphere.mesh");
	nade->setMaterialName ("Examples/Chrome"); 
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Smoke");
	node->attachObject(nade);
	// Scale it to appropiate size
	node->scale(0.05, 0.05, 0.05);

	// Create a collision shape
	// Note that the size should match the size of the object that will be displayed
	btCollisionShape* collisionShape = new btSphereShape(btScalar (5));

	// The object's starting transformation
	btTransform startingTrans;
	startingTrans.setIdentity();
	startingTrans.setOrigin(position);
	startingTrans.setRotation(orientation);

	// Create the rigid body
	btRigidBody* rigidBody = mPhysicsEngine->createRigidBody(1.0f, startingTrans, collisionShape, node);

	// Give the rigid body an initial velocity
	rigidBody->setLinearVelocity(linearVelocity);

	grenades [1] = rigidBody; 

	smoke = true;
}


void Assn2::shootPistol(const btVector3& position,const btVector3& toPosition, const btVector3& linearVelocity)
{
	srand (time(NULL)); 
	int random;
	int direction; 

	random = rand() % 5;

	btVector3 impulse = linearVelocity; 
	impulse *= 0.5f;

	btVector3 newPos = position; 
	
	btScalar newX = newPos.getX(); 
	btScalar newY = newPos.getY(); 
	btScalar newZ = newPos.getZ(); 

	random = rand() % 5;
	direction = rand()%2; 
	if (direction == 0)
		newX += random; 
	else
		newX -= random; 

	random = rand() % 5;
	direction = rand()%2; 
	
	if (direction == 0)
		newY += random; 
	else
		newY -= random; 

	random = rand() % 5;
	direction = rand()%2; 
	if (direction == 0)
		newZ += random; 
	else
		newZ -= random;  

	newPos.setValue (newX, newY, newZ); 


	mPhysicsEngine -> shootRay (newPos, toPosition, impulse); 


}

void Assn2::shootShotgun(const btVector3& position,const btVector3& toPosition, const btVector3& linearVelocity)
{
	srand (time(NULL)); 
	int random;
	int direction; 

	random = rand() % 30;

	btVector3 impulse = linearVelocity; 
	impulse *= 2.0f;

	btVector3 newPos = position; 
	
	for (int i = 0; i < 5 ; i++) 
	{
		btScalar newX = newPos.getX(); 
		btScalar newY = newPos.getY(); 
		btScalar newZ = newPos.getZ(); 

		random = rand() % 5;
		direction = rand()%2; 
		if (direction == 0)
			newX += random; 
		else
			newX -= random; 

		random = rand() % 5;
		direction = rand()%2; 
	
		if (direction == 0)
			newY += random; 
		else
			newY -= random; 

		random = rand() % 5;
		direction = rand()%2; 
		if (direction == 0)
			newZ += random; 
		else
			newZ -= random;  

		newPos.setValue (newX, newY, newZ); 


		mPhysicsEngine -> shootRay (newPos, toPosition, impulse); 
	}
}

void Assn2::shootMachine(const btVector3& position,const btVector3& toPosition, const btVector3& linearVelocity)
{
	srand (time(NULL)); 
	int random;
	int direction; 

	random = rand() % 5;

	btVector3 impulse = linearVelocity; 
	impulse *= 0.5f;

	btVector3 newPos = position; 
	
	btScalar newX = newPos.getX(); 
	btScalar newY = newPos.getY(); 
	btScalar newZ = newPos.getZ(); 

	random = rand() % 5;
	direction = rand()%2; 
	if (direction == 0)
		newX += random; 
	else
		newX -= random; 

	random = rand() % 5;
	direction = rand()%2; 
	
	if (direction == 0)
		newY += random; 
	else
		newY -= random; 

	random = rand() % 5;
	direction = rand()%2; 
	if (direction == 0)
		newZ += random; 
	else
		newZ -= random;  

	newPos.setValue (newX, newY, newZ); 


	mPhysicsEngine -> shootRay (newPos, toPosition, impulse); 

}

void Assn2::shootSniper(const btVector3& position,const btVector3& toPosition, const btVector3& linearVelocity)
{
	srand (time(NULL)); 
	
	btVector3 impulse = linearVelocity; 
	impulse *= 4.0f;

	mPhysicsEngine -> shootRay (position, toPosition, impulse); 

}


bool Assn2::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
	static bool mMouseDown = false; 
	static bool rMouseDown = false; 
	static Ogre::Real mToggle = 0.0; 
	static Ogre::Real mTimer = 0.0; 
	Ogre::String charge; 

	bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);

	Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(0.5,0.5);

	// Get a point one unit from the mouse ray origin, in the direction of the ray
	Ogre::Vector3 destination = mouseRay.getPoint(1);
				
		// Calculate the direction for the linear velocity
	btVector3 linearVelocity(
		destination.x-mouseRay.getOrigin().x, 
		destination.y-mouseRay.getOrigin().y, 
		destination.z-mouseRay.getOrigin().z);
				
	linearVelocity.normalize();
		// Scale to appropriate velocity
				linearVelocity *= 30.0f;

	if (currMouse && (mToggle < 0.0f) && !mMouseDown) 
	{
				if (weaponType == 2) 
				{
					// Shoot pistol
					shootPistol (convert(mouseRay.getOrigin()), convert(mouseRay.getPoint(1000)), linearVelocity);
					mToggle = 0.5;
				}


				if (weaponType == 4) 
				{
					// Shoot Shotgun
					shootShotgun (convert(mouseRay.getOrigin()), convert(mouseRay.getPoint(1000)), linearVelocity);
					mToggle = 1.5;

				}

				if (weaponType == 5) 
				{
					///Shoot Sniper
					shootSniper (convert(mouseRay.getOrigin()), convert(mouseRay.getPoint(1000)), linearVelocity);
					mToggle = 3;
				}
	}

	else if (currMouse && (mToggle < 0.0f)) 
	{
			if (weaponType == 1 || weaponType == 6 || weaponType == 7)
				{
					mTimer += evt.timeSinceLastFrame;

					if (mTimer >= 0 && mTimer < 1) 
						charge = "0%"; 
					if (mTimer >= 1 && mTimer < 2) 
						charge = "20%"; 
					if (mTimer >= 2 && mTimer < 3) 
						charge = "40%"; 
					if (mTimer >= 3 && mTimer < 4) 
						charge = "60%"; 
					if (mTimer >= 4 && mTimer < 5) 
						charge = "80%"; 
					if (mTimer >= 5) 
						charge = "100%"; 
					shot = true; 

					mDebugPanel->setParamValue(1, charge);
				}

			if (weaponType == 3) 
				{
					shootMachine (convert(mouseRay.getOrigin()), convert(mouseRay.getPoint(1000)), linearVelocity);
					mToggle = 0.25;
				}
	}

	else if (!currMouse && shot) 
	{
		
			if (mTimer > 5)
			{
				mTimer = 5; 
			}

			mTimer += 1; 

			charge = "0%"; 
			mDebugPanel->setParamValue(1, charge);
			
			if (weaponType == 1)
			{
				shootBall(convert(mouseRay.getOrigin()), btQuaternion(0,0,0,1), linearVelocity*mTimer);		
				mToggle = 1;
			}
			
			if (weaponType == 6)
			{
				shootImpact(convert(mouseRay.getOrigin()), btQuaternion(0,0,0,1), linearVelocity*mTimer);
				mToggle = 3;
			}

			if (weaponType == 7)
			{
				shootSmoke(convert(mouseRay.getOrigin()), btQuaternion(0,0,0,1), linearVelocity*mTimer);
				mToggle = 6;
			}


			mTimer = 0; 
			shot = false; 

		

	}

	if (mMouse->getMouseState().buttonDown(OIS::MB_Right) && !rMouseDown)
	{
		if (weaponType == 5) 
		{
			if ( counter == 0)
			{
				Ogre::Radian r = mCamera-> getFOVy (); 
				Ogre::Radian newR (Ogre::Degree (25)); 

				mCamera -> setFOVy (newR); 
				counter ++ ; 
			}
			
			
			else if ( counter == 1) 
			{
				Ogre::Radian r = mCamera-> getFOVy (); 
				Ogre::Radian newR (Ogre::Degree (10)); 

				mCamera -> setFOVy (newR); 
				counter ++ ; 
			}

			else if ( counter == 2) 
			{
				Ogre::Radian r = mCamera-> getFOVy (); 
				Ogre::Radian newR (Ogre::Degree (40)); 

				mCamera -> setFOVy (newR); 
				counter = 0 ; 
			}
		}
	}

	mMouseDown = currMouse;
	rMouseDown = mMouse->getMouseState().buttonDown(OIS::MB_Right);
 
    mToggle -= evt.timeSinceLastFrame;

    return true;
}



 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Assn2 app;
 
        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif