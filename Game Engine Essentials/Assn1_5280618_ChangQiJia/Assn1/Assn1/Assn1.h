/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __Assn1_h_
#define __Assn1_h_

#include "BaseApplication.h"

class Assn1 : public BaseApplication
{
public:
    Assn1(void);
    virtual ~Assn1(void);

protected:
    virtual void createScene(void);
	virtual void createCamera(void); 
	virtual void createViewports (void); 
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	Ogre::Camera* thirdCamera;
	Ogre::SceneNode* robotNode;
	int counter; 
	Ogre::Overlay* overlay;
	Ogre::Viewport* vp;
	
	int height; 
	int width; 

	Ogre::Real mRotate; 
	Ogre::Real mMove; 
	Ogre::Vector3 transVector; 

	//Ogre::OverlayContainer* crosshairImageContainer;
};

#endif // #ifndef __TutorialApplication_h_
