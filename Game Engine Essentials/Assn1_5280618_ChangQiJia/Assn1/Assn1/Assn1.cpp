/*
-----------------------------------------------------------------------------
Filename:    Assn1.cpp
-----------------------------------------------------------------------------
*/
#include "Assn1.h"

//160417 
//Done orbit, fullscreen, switch camera
//1 , 2 and half of 3 (left moving robot and camera follow) ,4 and half of 5 (left crosshair) 
//F1 for camera toggle, F11 for Full screen, F for toggle ogre logo and fps 


//-------------------------------------------------------------------------------------
Assn1::Assn1(void)
{
		counter = 0;
	
}
//-------------------------------------------------------------------------------------

Assn1::~Assn1(void)
{
}
//-------------------------------------------------------------------------------------

void Assn1::createScene(void)
{
    mSceneMgr -> setAmbientLight (Ogre:: ColourValue (0.5,0.5,0.5)); 
	mSceneMgr -> setShadowTechnique (Ogre::SHADOWTYPE_STENCIL_ADDITIVE); 

	Ogre:: Light* pointLight = mSceneMgr->createLight ("pointLight") ; 
	pointLight -> setType (Ogre::Light::LT_POINT); 
	pointLight -> setPosition (Ogre::Vector3 (370,370,370)); 

	pointLight -> setDiffuseColour (1.0,1.0,1.0);
	pointLight -> setSpecularColour (1.0,1.0,1.0); 

	Ogre::Entity* entRobot = mSceneMgr -> createEntity ("Robot", "robot.mesh"); 
	entRobot -> setCastShadows (true);  
	robotNode = mSceneMgr -> getRootSceneNode () -> createChildSceneNode ("robotNode", Ogre::Vector3 (0,0,0));
	robotNode->attachObject (entRobot); 
	Ogre::SceneNode* cameraNode = robotNode -> createChildSceneNode ("cameraNode", mSceneMgr->getSceneNode("robotNode")->getPosition() + Ogre::Vector3 (0,100,0)); 
	cameraNode->attachObject (mCamera);
	mCamera->detachFromParent();

	Ogre::Entity* entBarrel = mSceneMgr -> createEntity ("Barrel", "Barrel.mesh"); 
	entBarrel -> setCastShadows (true);  
	Ogre::SceneNode* BarrelNode = mSceneMgr -> getRootSceneNode () -> createChildSceneNode ("barrelNode", Ogre::Vector3 (-300,45,200));
	BarrelNode->attachObject (entBarrel);
	BarrelNode->setScale(7,15,7); 

	Ogre::Entity* entAthene = mSceneMgr -> createEntity ("Athene", "athene.mesh"); 
	entAthene -> setCastShadows (true);  
	entAthene-> setMaterialName ("atheneNormalMap.png"); 
	Ogre::SceneNode* atheneNode = mSceneMgr -> getRootSceneNode () -> createChildSceneNode ("atheneNode", Ogre::Vector3 (0,82,-200));
	atheneNode->attachObject (entAthene); 

	Ogre::Entity* entWood = mSceneMgr -> createEntity ("Wood", "WoodPallet.mesh"); 
	entWood -> setCastShadows (true);  
	Ogre::SceneNode* woodNode = mSceneMgr -> getRootSceneNode () -> createChildSceneNode ("woodNode", Ogre::Vector3 (100,5,100));
	woodNode->attachObject (entWood); 
	woodNode -> setScale (10,10,10);

	Ogre::Entity* entPenguin = mSceneMgr -> createEntity ("Penguin", "penguin.mesh"); 
	entPenguin -> setCastShadows (true);  
	Ogre::SceneNode* penguinNode = mSceneMgr -> getRootSceneNode () -> createChildSceneNode ("penguinNode", Ogre::Vector3 (175, 25, 300));
	penguinNode->attachObject (entPenguin);

	mCameraMan->setStyle (OgreBites::CS_ORBIT); 
	mCamera->setAutoTracking (true, robotNode, Ogre::Vector3(0,0,500)); 
	mCameraMan->setYawPitchDist(Ogre::Degree(20), Ogre::Degree(40), 500); 
	mCameraMan->setStyle (OgreBites::CS_FREELOOK); 
	
	Ogre::Plane plane (Ogre::Vector3:: UNIT_Y, 0); 
	Ogre::MeshManager:: getSingleton().createPlane ("ground", Ogre::ResourceGroupManager:: DEFAULT_RESOURCE_GROUP_NAME, plane,750,750,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z); 
	
	Ogre::SceneNode* roomNode = mSceneMgr -> getRootSceneNode() -> createChildSceneNode ("roomNode", Ogre::Vector3 (0,0,0)); 
	
	Ogre::Entity* entGround = mSceneMgr -> createEntity ("GroundEntity", "ground");
	entGround -> setMaterialName ("Examples/GrassFloor"); 
	entGround -> setCastShadows (false); 

	roomNode->attachObject (entGround); 

	Ogre::Entity* entLeft = mSceneMgr -> createEntity ("LeftEntity", "ground"); 
	Ogre::SceneNode* leftNode = roomNode -> createChildSceneNode ("leftNode", Ogre::Vector3 (0,0,0)); 
	entLeft -> setMaterialName ("Examples/Rockwall"); 
	entLeft -> setCastShadows (false); 
	leftNode -> attachObject (entLeft); 
	leftNode ->roll (Ogre::Degree(-90)); 
	leftNode ->yaw (Ogre::Degree(90)); 
	leftNode ->translate (Ogre::Vector3 (-375,375,0)); 


	Ogre::Entity* entRight = mSceneMgr -> createEntity ("RightEntity", "ground"); 
	Ogre::SceneNode* rightNode = roomNode -> createChildSceneNode ("rightNode", Ogre::Vector3 (0,0,0)); 
	rightNode -> attachObject (entRight); 
	rightNode ->roll (Ogre::Degree(90)); 
	rightNode ->yaw (Ogre::Degree(90)); 
	entRight -> setMaterialName ("Examples/Rockwall"); 
	entRight -> setCastShadows (false); 
	rightNode ->translate (Ogre::Vector3 (375,375,0)); 

	Ogre::Entity* entBack = mSceneMgr -> createEntity ("BackEntity", "ground"); 
	Ogre::SceneNode* backNode = roomNode -> createChildSceneNode ("backNode", Ogre::Vector3 (0,0,0)); 
	backNode -> attachObject (entBack); 
	backNode ->pitch (Ogre::Degree(-90)); 
	entBack -> setMaterialName ("Examples/Rockwall"); 
	entBack -> setCastShadows (false); 
	backNode ->translate (Ogre::Vector3 (0,375,375));

	Ogre::Entity* entFront = mSceneMgr -> createEntity ("FrontEntity", "ground"); 
	Ogre::SceneNode* frontNode = roomNode -> createChildSceneNode ("frontNode", Ogre::Vector3 (0,0,0)); 
	frontNode -> attachObject (entFront); 
	frontNode ->pitch (Ogre::Degree(90)); 
	entFront -> setMaterialName ("Examples/Rockwall"); 
	entFront -> setCastShadows (false); 
	frontNode ->translate (Ogre::Vector3 (0,375,-375));

	Ogre::Entity* entTop = mSceneMgr -> createEntity ("TopEntity", "ground"); 
	Ogre::SceneNode* topNode = roomNode -> createChildSceneNode ("topNode", Ogre::Vector3 (0,0,0)); 
	topNode -> attachObject (entTop); 
	topNode ->roll (Ogre::Degree(180)); 
	entTop -> setMaterialName ("Examples/WaterStream"); 
	entTop -> setCastShadows (false); 
	topNode ->translate (Ogre::Vector3 (0,750,0));

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

	height = mWindow -> getHeight(); 
	width = mWindow -> getWidth(); 

	mWindow -> setFullscreen(true, width, height); 
	mWindow -> setFullscreen(false, width, height);
	mWindow -> setFullscreen(true, width, height); 
	mWindow -> setFullscreen(false, width, height);
}

void Assn1::createCamera(void)
{
	mCamera = mSceneMgr -> createCamera ("FreeCamera"); 

	mCamera->setPosition (Ogre::Vector3 (0,30,500)); 
	mCamera->lookAt (Ogre::Vector3 (0,0,0)); 
	mCamera->setNearClipDistance (5); 

	thirdCamera = mSceneMgr -> createCamera ("ThirdCamera"); 
	thirdCamera->setPosition (Ogre::Vector3 (200,200,0)); 
	thirdCamera->lookAt (Ogre::Vector3 (0,0,0)); 
	thirdCamera->setNearClipDistance (5); 

	
	mCameraMan = new OgreBites:: SdkCameraMan (mCamera); 

}
//-------------------------------------------------------------------------------------

void Assn1::createViewports(void)
{
	Ogre::Viewport* vp = mWindow -> addViewport (mCamera); 
	vp -> setBackgroundColour (Ogre:: ColourValue (0.2,0.2,0.2));

	mCamera -> setAspectRatio (Ogre:: Real (vp->getWidth())/ Ogre:: Real (vp->getHeight())); 

}

bool Assn1::keyPressed( const OIS::KeyEvent &arg )
{
	//Not mine
	if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up
 
	//Not mine
	if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
	{
		mTrayMgr->toggleAdvancedFrameStats();
	}

	//Not mine
	else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
	{
		if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
		{
			mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
			mDetailsPanel->show();
		}
		else
		{
			mTrayMgr->removeWidgetFromTray(mDetailsPanel);
			mDetailsPanel->hide();
		}
	}

	//Not mine
	else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
	{
		Ogre::String newVal;
		Ogre::TextureFilterOptions tfo;
		unsigned int aniso;
 
		switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
		{
		case 'B':
			newVal = "Trilinear";
			tfo = Ogre::TFO_TRILINEAR;
			aniso = 1;
			break;
		case 'T':
			newVal = "Anisotropic";
			tfo = Ogre::TFO_ANISOTROPIC;
			aniso = 8;
			break;
		case 'A':
			newVal = "None";
			tfo = Ogre::TFO_NONE;
			aniso = 1;
			break;
		default:
			newVal = "Bilinear";
			tfo = Ogre::TFO_BILINEAR;
			aniso = 1;
		}
 
		Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
		mDetailsPanel->setParamValue(9, newVal);
	}

	//Not mine
	else if(arg.key == OIS::KC_F5)   // refresh all textures
	{
		Ogre::TextureManager::getSingleton().reloadAll();
	}

	else if(arg.key == OIS::KC_Q)   // roll
	{
		if (mCameraMan->getStyle() == OgreBites::CS_FREELOOK)
			mCamera->roll (Ogre::Degree (-5)); 
	}

	else if(arg.key == OIS::KC_E)   // roll
	{
		if (mCameraMan->getStyle() == OgreBites::CS_FREELOOK)
			mCamera->roll (Ogre::Degree (5)); 
	}

	else if (arg.key == OIS::KC_F1) //toggle camera mode
	{
		Ogre::String newVal; 
		counter++; 

		if (counter == 1) 
		{
			mCameraMan->setStyle(OgreBites::CS_ORBIT);
			mCameraMan->setYawPitchDist(Ogre::Degree(20), Ogre::Degree(40), 500); 
			mCamera->lookAt(0,0,0);  
			newVal = "Orbit"; 
			
		}
		else if (counter == 2) 
		{
			mSceneMgr->getSceneNode("cameraNode") ->attachObject (mCamera); 
			mCamera -> setPosition (mSceneMgr->getSceneNode("robotNode")->getPosition() + Ogre::Vector3(-200,200,0));
			mCamera -> lookAt (mSceneMgr->getSceneNode("robotNode")->getPosition() + Ogre::Vector3 (0,100,0));  

			newVal = "Third Person"; 
		}
		else 
		{
			mCamera->detachFromParent(); 
			mCamera -> lookAt (mSceneMgr->getSceneNode("robotNode")->getPosition() + Ogre::Vector3 (0,100,0));  
			mCameraMan->setStyle(OgreBites::CS_FREELOOK);
			mCamera->setAutoTracking (false); 
			counter = 0; 
			newVal = "Free Camera"; 
		}

		mDebugPanel->setParamValue(1, newVal);
	}

	else if (arg.key == OIS::KC_F2)		// toggle logo
	{
		if (mTrayMgr->isLogoVisible())
			mTrayMgr->hideLogo(); 
		else
			mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);  
	}

	else if (arg.key == OIS::KC_F3)		// toggle debug panel
	{
		if (mDebugPanel->getTrayLocation() == OgreBites::TL_NONE)
		{
			mTrayMgr->moveWidgetToTray(mDebugPanel, OgreBites::TL_TOPLEFT, 0);
			mDebugPanel->show();
		}
		else
		{
			mTrayMgr->removeWidgetFromTray(mDebugPanel);
			mDebugPanel->hide();
		}
	}

	else if (arg.key == OIS::KC_R) // reset
	{
		mCamera->setPosition(Ogre::Vector3(0,200,200)); 

		mSceneMgr->getSceneNode("robotNode")->setPosition (Ogre:: Vector3 (0, 0, 0)) ;

	}

	else if (arg.key == OIS::KC_F11) // full screen
	{
		Ogre::String newVal; 
		
		height = mWindow -> getHeight(); 
		width = mWindow -> getWidth(); 


		if (!(mWindow -> isFullScreen()))
		{
			mWindow -> setFullscreen(true, width, height); 
			newVal = "Fullscreen"; 
		}

		else
		{		
			mWindow -> setFullscreen(false, width, height); 
			newVal = "Windowed"; 
		}

		mDebugPanel -> setParamValue (0, newVal);
	}

	//Not mine
	else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
	{
		mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
	}
	else if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}

	mCameraMan->injectKeyDown(arg);
	return true;
}

//Not mine
bool Assn1::keyReleased( const OIS::KeyEvent &arg )
{
	mCameraMan->injectKeyUp(arg);
	return true;
}
//Not mine
void Assn1::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);
 
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

bool Assn1::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	mRotate = 0.25; 
	mMove = 150; 
	transVector = Ogre::Vector3::ZERO; 

	if(mWindow->isClosed())
		return false;
 
	if(mShutDown)
		return false;
 
	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();
 
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

		if (mDebugPanel->isVisible())   // if details panel is visible, then update its contents
		{
			mDebugPanel->setParamValue(3, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
			mDebugPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
			mDebugPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));

			mDebugPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
			mDebugPanel->setParamValue(8, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
			mDebugPanel->setParamValue(9, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
		}
	}

	if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
        transVector.x += mMove;

    }
    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
        transVector.x -= mMove;
    }
    if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
    {
        mSceneMgr->getSceneNode("robotNode")->yaw(Ogre::Degree(mRotate * 5));
    }
    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
    {
        mSceneMgr->getSceneNode("robotNode")->yaw(Ogre::Degree(-mRotate * 5));
    }
 
    mSceneMgr->getSceneNode("robotNode")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

 
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
        Assn1 app;

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
