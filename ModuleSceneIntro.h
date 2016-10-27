#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "time.h"
#include "Box2D/Box2D/Box2D.h"

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
	void CreateElements();
	void CreateSensors();
	void DrawLeds();
	void DrawPanels();
	void CreateBall();
	void LaunchBall(PhysBody* ball);

	void Activate_Deactivate_Doors();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> pinball;
	p2List<PhysBody*> solids;
	p2List<PhysBody*> sensors;

	//Pointers to balls-----------
	PhysBody* lose_ball = nullptr;
	PhysBody* save = nullptr;
	PhysBody* miniball = nullptr;
	PhysBody* Sup_Button = nullptr;
	PhysBody* Ball_in_start = nullptr;

	//Sensors----------------------
	PhysBody* Lose_sensor;
	bool sensed;

	//Ball Texture------------------
	SDL_Texture* circle;
	SDL_Rect ball_rect[7];
	void DrawBall(const PhysBody* ball);

	//Map Textures
	SDL_Texture* PinballMap;
	SDL_Texture* PinballMap_2nd_Layer;

	//Audio Fx---------------------
	uint orange_button;
	uint right_triangle;
	uint left_triangle;
	uint led_activation;
	uint diana;
	uint turbine;
	uint red_panel;
	uint led_reactivation;
	uint all_led_activation;
	uint saved_ball;
	uint start;
	uint blue_button;
	uint ball_positioning;
	uint launch;

	p2Point<int> ray;

	bool ray_on;


	//BOOLS------------------------
	bool Check_Game_Over = false;
	bool rLed_activated = false;
	bool lLed_activated = false;
	bool cLed_activated = false;

	bool deactivate_entrance = false;
	bool activate_entrance = false;
	bool activate_left = false;
	bool deactivate_left = false;
	bool activate_right = false;
	bool deactivate_right = false;
	bool activate_blackbox = false;
	bool deactivate_blackbox = false;

	//TIME----------------------------
	int now = GetTickCount();
	int now_3_row = GetTickCount();
	int now_4_arrows = GetTickCount();
	int now_All_Reds = GetTickCount();
	int Lives_save_now = GetTickCount();
	int actualtime_3_row;
	int actualtime;
	int Live_actualtime_save;
	int Blue_Button = GetTickCount();
	int time_extra_ball = GetTickCount();
	int time_new_ball = GetTickCount();
	bool can_crate_new_ball = false;

	//ELEMENTS(LEDS, PANELS...) TEXTURES--------------------
	SDL_Texture* Texture;
	bool Leds_intermittent = false;
	//Led Blue Botton
	uint Leds_Blue_Button = 0;
	bool tree_on_raw = false;
	//Led Arrows
	bool Leds_Arrow[4];
	bool Arrow_Panel[4];
	bool arrows_actived = false;
	//Led Turbine
	uint Leds_Turbine = 0;
	//Led Arrows
	bool B_UP_LED[3];
	//Led Arrows
	bool Leds_Reds[4];
	bool all_reds = false;
	//Led Save Ball
	bool Save_Ball = false;
	bool last_seconds = false;

	//SPRITES RECTS
	SDL_Rect blue_button_led;
	SDL_Rect black_box_leds[5];
	SDL_Rect blue_led;
	SDL_Rect red_arrow;
	SDL_Rect red_leds[4];
	SDL_Rect save_ball;
	SDL_Rect Extra_ball;
	SDL_Rect ball_panel[5];
	SDL_Rect red_panel_rect;
	SDL_Rect ramp_cover;

	//Joint in blue button-------------------
	b2RevoluteJoint* Joint_Blue_button = NULL;
	bool isEnter = false;

	//Apply Froce---------------------------
	bool CanApplyForce = false;
	bool ifSave_force = false;
	bool CanCreate_ball = false;

	//Texture of center
	uint Number_of_Ball;

};

