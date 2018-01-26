#ifndef __Assn2_h_
#define __Assn2_h_
 
#include "stdafx.h"
#include "BaseApplication.h"
#include "PhysicsEngine.h"

#include <fstream>
#include <string>

class Assn2 : public BaseApplication
{
public:
   Assn2(void);
    virtual ~Assn2(void);
 
protected:
	virtual bool setup();
    virtual void createScene(void);
	virtual void createFrameListener(void);
	void shootBall(const btVector3& position, const btQuaternion& orientation, const btVector3& linearVelocity);
	void shootImpact(const btVector3& position, const btQuaternion& orientation, const btVector3& linearVelocity);
	void shootSmoke(const btVector3& position, const btQuaternion& orientation, const btVector3& linearVelocity);
	void shootPistol(const btVector3& position,const btVector3& orientation,const btVector3& linearVelocity);
	void shootShotgun(const btVector3& position,const btVector3& orientation,const btVector3& linearVelocity);
	void shootMachine(const btVector3& position,const btVector3& orientation,const btVector3& linearVelocity);
	void shootSniper(const btVector3& position,const btVector3& orientation,const btVector3& linearVelocity);
	bool processUnbufferedInput(const Ogre::FrameEvent& evt);

	// Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    // OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
 
	Ogre::Real mRotate;          // The rotate constant
	Ogre::Real mMove;            // The movement constant
 
	Ogre::Vector3 mDirection;     // Value to move in the correct direction
 
	Ogre::Overlay* overlay;
	int weaponType; 
	int counter; 
	bool shot; 
	bool impact; 
	bool smoke; 
	bool timeSmoke; 
	Ogre::ParticleSystem* particleSystem;
	Ogre::Vector3 transVector; 

	btRigidBody* grenades [2];  

	// for physics
	PhysicsEngine*	mPhysicsEngine;

	int				mBoxCount;
};
 
#endif // #ifndef __DemoApp_h_