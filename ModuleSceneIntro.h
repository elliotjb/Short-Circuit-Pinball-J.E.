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
	void CreateSensors();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> bouncers;
	p2List<PhysBody*> sensors;

	PhysBody* lose_ball = nullptr;

	//Sensors
	PhysBody* Lose_sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* PinballMap;
	SDL_Texture* PinballMap_2nd_Layer;

	//Audio Fx
	uint orange_button;
	uint right_triangle;
	uint left_triangle;
	uint led_activation;
	uint diana;
	uint turbine;
	uint red_panel;
	uint blue_led_reactivation;
	uint all_led_activation;

	p2Point<int> ray;

	bool ray_on;

	bool Game_Over = false;
	bool rLed_activated = false;
	bool lLed_activated = false;
	bool cLed_activated = false;

};

