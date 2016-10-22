#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	bool CreateMap();
	void CreateBouncers();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> bouncers;

	PhysBody* lose_ball = nullptr;

	//Sensors
	PhysBody* Lose_sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* PinballMap;
	SDL_Texture* PinballMap_2nd_Layer;

	uint bonus_fx;
	p2Point<int> ray;

	bool ray_on;

	bool Game_Over = false;
};

