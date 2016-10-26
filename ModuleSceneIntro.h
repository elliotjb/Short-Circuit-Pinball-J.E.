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
	void DrawLeds();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	p2List<PhysBody*> bouncers;
	p2List<PhysBody*> sensors;

	//Pointers to balls
	PhysBody* lose_ball = nullptr;
	PhysBody* save = nullptr;
	PhysBody* miniball = nullptr;

	//Sensors
	PhysBody* Lose_sensor;
	bool sensed;

	//Bal Drawing
	SDL_Texture* circle;
	SDL_Rect ball_rect[7];
	void DrawBall(const PhysBody* ball);

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
	uint led_reactivation;
	uint all_led_activation;

	p2Point<int> ray;

	bool ray_on;
	bool tree_on_raw = false;

	bool Game_Over = false;
	bool rLed_activated = false;
	bool lLed_activated = false;
	bool cLed_activated = false;

	bool Red_Panel1 = false;
	bool Red_Panel2 = false;
	bool Red_Panel3 = false;
	bool Red_Panel4 = false;

	//TEXTURES LEDS 
	SDL_Texture* Leds_tex;
	int now = GetTickCount();
	int now_3_row = GetTickCount();
	int Lives_save_now = GetTickCount();
	int actualtime_3_row;
	int actualtime;
	int Live_actualtime_save;
	bool Leds_intermittent = false;
	//Led Blue Botton
	uint Leds_Blue_Button = 0;
	//Led Arrows
	bool Leds_Arrow[4];
	//Led Turbine
	uint Leds_Turbine = 0;
	//Led Arrows
	bool B_UP_LED[3];
	//Led Arrows
	bool Leds_Reds[4];
	//Led Save Ball
	bool Save_Ball = false;



};

