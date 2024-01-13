#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Gun.h"
#include "ParticleSystem.h"
#include "SolidRigidSystem.h"

#include <iostream>

std::string display_text = "Elf Hunt: final project by Andrea Vega";

std::string info_text = "";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;


ParticleSystem* particleSystem = nullptr;

bool canShoot = true;
float shootingTime = 0.2f;
float auxShootTime = 0.0f;
bool renderIntro = true;
bool renderUI = false;
bool renderRetry = false;
bool rifleSelected = true;
int score = 0;
gameState _state = INTRO;

void intro() {
	renderIntro = true;
	_state = INTRO;
}

void startGame() {
	renderRetry = false;
	renderIntro = false;
	renderUI = true;
	particleSystem->startGame();
}

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, 0.0f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	particleSystem = new ParticleSystem(gScene, gPhysics);

	intro();
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);

	//solidRigidSystem->update(t);

	//particle->integrate(t);
	//gun->integrate(t);
	if (canShoot == false) {
		auxShootTime += t;
		if (auxShootTime >= shootingTime) {
			auxShootTime = 0;
			canShoot = true;
		}
	}

	particleSystem->update(t);
	_state = particleSystem->getGameState();
	if (_state == RETRY) {
		renderUI = false;
		renderRetry = true;
	}
	score = particleSystem->getScore();
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	//delete particle;
	delete particleSystem;

	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	//delete solidRigidSystem;

	//delete gun;
}

void mouseInput(int button, int state, int x, int y)
{
	if (canShoot && button == 0) {
		
		particleSystem->shoot({ (GetCamera()->getMousePos().x / 5), (GetCamera()->getMousePos().y / 5), -1 }, { 0,0,0 });
		canShoot = false;
		if (_state == INTRO) startGame();
		else if (_state == RETRY) startGame();
	}
	PX_UNUSED(state);
	PX_UNUSED(button);
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 9:
	{
		particleSystem->changeWeapon();
		rifleSelected = !rifleSelected;
		break;
	}
	//case 'B': break;
	//case ' ':	break;
	//case ' ':
	//{
	//	//gun->shoot(bullet, GetCamera()->getTransform().p, GetCamera()->getDir());
	//	particleSystem->generateFirework();
	//	break;
	//}
	//case 'C':
	//{
	//	//gun->shoot(cannonBall, GetCamera()->getTransform().p, GetCamera()->getDir());
	//	break;
	//}
	//case 'P':
	//{
	//	//gun->shoot(laser, GetCamera()->getTransform().p, GetCamera()->getDir());
	//	break;
	//}
	case 'E':
	{
		//particleSystem->generateExplosion();
		//solidRigidSystem->generateExplosion();
		break;
	}
	//case 'K':
	//{
	//	int i = 2;
	//	particleSystem->changeSpringConstant(i);
	//	particleSystem->changeAnchoredSpringConstant(i);
	//	particleSystem->changeElasticBandConstant(i);
	//	break;
	//}
	//case 'L':
	//{
	//	int i = -2;
	//	particleSystem->changeSpringConstant(i);
	//	particleSystem->changeAnchoredSpringConstant(i);
	//	particleSystem->changeElasticBandConstant(i);
	//	break;
	//}
	//case 'F':
	//{
	//	particleSystem->addForceToSpring();
	//	particleSystem->addForceToAnchoredSpring();
	//	particleSystem->addForceToElasticBand();
	//	particleSystem->addMassToBuoyancy();
	//	break;
	//}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}