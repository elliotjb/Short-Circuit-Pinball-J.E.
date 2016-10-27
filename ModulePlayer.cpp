#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleWindow.h"
#include "ModuleAudio.h"
#include "p2Point.h"
#include "math.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	lever_left_Tex = lever_right_Tex = NULL;
	Lives = 5;
	Extra_Balls = 0;
	Score = 0;
}

ModulePlayer::~ModulePlayer()
{}


// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	CreateLevers();
	lever_left_Tex = App->textures->Load("pinball/LeftLever.png");
	lever_right_Tex = App->textures->Load("pinball/RightLever.png");
	lever_fx = App->audio->LoadFx("pinball/Audio/Fx/Flipers.wav");
	lever_UP_Tex = App->textures->Load("pinball/UpLever.png");

	//Create Joints
	Joint_lever_left = App->physics->CreateJoint(Joint_lever_left, lever_left, pivot_left, false, 205, 575, 0, 0, true, 0, 40);
	Joint_force_left = App->physics->CreateJoint(Joint_force_left, lever_left, pivot_force_left, false, 270, 599, 0, 0, false, 0, 0);
	Joint_lever_right = App->physics->CreateJoint(Joint_lever_right, lever_Right, pivot_Right, false, 410, 575, 0, 0, true, -40, 0);
	Joint_force_right = App->physics->CreateJoint(Joint_force_right, lever_Right, pivot_force_Right, false, 340, 599, 0, 0, false, 0, 0);
	Joint_lever_UP = App->physics->CreateJoint(Joint_lever_UP, lever_UP_left, pivot_UP_left, false, 187, 144, 0, 0, true, 0, 62);
	Joint_force_UP = App->physics->CreateJoint(Joint_force_UP, lever_UP_left, pivot_UP_force_left, false, 187, 170, 0, 0, false, 0, 0);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
    App->textures->Unload(lever_left_Tex);
	App->textures->Unload(lever_right_Tex);
	App->textures->Unload(lever_UP_Tex);
	
	return true;
}



// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		active_right = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		active_left = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		pivot_force_Right->body->ApplyForceToCenter(b2Vec2(0.0f, -200.0f), true);
	}

	else
	{
		pivot_force_Right->body->ApplyForceToCenter(b2Vec2(0.0f, 100.0f), true);
	}

	if (active_left == true)
	{
		App->audio->PlayFx(lever_fx);
		active_left = false;
	}

	if (active_right == true)
	{
		App->audio->PlayFx(lever_fx);
		active_right = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		pivot_force_left->body->ApplyForceToCenter(b2Vec2(0.0f, -200.0f), true);
		pivot_UP_force_left->body->ApplyForceToCenter(b2Vec2(50.0f, 0.0f), true);
	}
	else
	{
		pivot_force_left->body->ApplyForceToCenter(b2Vec2(0.0f, 100.0f), true);
		pivot_UP_force_left->body->ApplyForceToCenter(b2Vec2(-10.0f, 0.0f), true);
	}

	//Draw Imatge of lever left
	App->renderer->Blit(lever_left_Tex, 190, 560, NULL, 1.0f, lever_left->GetRotation(), 10, 13);
	//Draw Imatge of lever right
	App->renderer->Blit(lever_right_Tex, 335, 560, NULL, 1.0f, lever_Right->GetRotation(), 78, 12);
	//Draw Imatge of lever UP
	App->renderer->Blit(lever_UP_Tex, 182, 132, NULL, 1.0f, lever_UP_left->GetRotation(), 8, 9);

	if (App->scene_intro->isEnter)
	{
		sprintf_s(title, "Score: %06d - Lives: %02d - Last Score: %06d   EXTRA BALL IN: %i s", Score, Lives, Last_score,40 - (App->scene_intro->actualtime - App->scene_intro->Blue_Button)/1000);
	}
	else
	{
		sprintf_s(title, "Score: %06d - Lives: %02d - Last Score: %06d", Score, Lives, Last_score);
	}
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}


bool ModulePlayer::CreateLevers()
{

	//Lever Left
	pivot_left = App->physics->CreateCircle(205, 575, 10, false,FLOOR_1, FLOOR_1);
	//lever_left = App->physics->CreateRectangle(210, 586, 70, 10, true);
	pivot_force_left = App->physics->CreateCircle(280, 575, 5, true, FLOOR_1, FLOOR_1);

	//Lever Right
	pivot_Right = App->physics->CreateCircle(410, 575, 10, false, FLOOR_1, FLOOR_1);
	//lever_Right = App->physics->CreateRectangle(410, 586, 70, 10, true);
	pivot_force_Right = App->physics->CreateCircle(340, 575, 5, true, FLOOR_1, FLOOR_1);

	//Lever UP Right
	pivot_UP_left = App->physics->CreateCircle(187, 144, 5, false, FLOOR_1, FLOOR_1);
	//lever_Right = App->physics->CreateRectangle(410, 586, 70, 10, true);
	pivot_UP_force_left = App->physics->CreateCircle(187, 155, 2, true, FLOOR_1, FLOOR_1);

	int Chain_lever_left[16] = {
		272, 609,
		278, 608,
		281, 602,
		280, 596,
		210, 565,
		201, 566,
		195, 575,
		200, 585
	};


	int Chain_lever_right[16] = {
		420, 571,
		414, 565,
		406, 565,
		336, 594,
		333, 599,
		334, 604,
		339, 609,
		416, 586
	};

	int Left_UP_Lever[16] = {
		183, 144,
		183, 172,
		185, 174,
		187, 174,
		189, 173,
		195, 143,
		191, 137,
		186, 137
	};

	lever_UP_left = App->physics->CreatePolygon(0, 0, Left_UP_Lever, 16, 0.5f, true, LEVER, false, FLOOR_1, FLOOR_1 | BALL_1);
	lever_left = App->physics->CreatePolygon(0, 0, Chain_lever_left, 16, 0.5f, true, LEVER, false, FLOOR_1, FLOOR_1 | BALL_1);
	lever_Right = App->physics->CreatePolygon(0, 0, Chain_lever_right, 16, 0.5f, true, LEVER, false, FLOOR_1, FLOOR_1 | BALL_1);


	return true;
}

void ModulePlayer::Restart_game()
{
	if (App->scene_intro->Check_Game_Over == true)
	{
		Lives = 5;
		Last_score = Score;
		Score = 0;
		App->scene_intro->circles.add(App->physics->CreateCircle(620, 600, 8, true, BALL_1, FLOOR_1 | BALL_1 | BALL_2));
	}
	App->scene_intro->Number_of_Ball = 1;
	for (int i = 0; i < 4; i++)
		App->scene_intro->Leds_Arrow[i] = false;
	for (int i = 0; i < 3; i++)
		App->scene_intro->B_UP_LED[i] = false;
	for (int i = 0; i < 4; i++)
		App->scene_intro->Leds_Reds[i] = false;
	App->scene_intro->Leds_Turbine = 0;
	App->scene_intro->Leds_Blue_Button = 0;

	App->scene_intro->Check_Game_Over = false;

	App->scene_intro->rLed_activated = false;
	App->scene_intro->lLed_activated = false;
	App->scene_intro->cLed_activated = false;

	for (int i = 0; i < 4; i++)
		App->scene_intro->Arrow_Panel[i] = false;

	App->scene_intro->deactivate_entrance = false;
	App->scene_intro->activate_entrance = false;
	App->scene_intro->activate_left = false;
	App->scene_intro->deactivate_left = false;
	App->scene_intro->activate_right = false;
	App->scene_intro->deactivate_right = false;
	App->scene_intro->activate_blackbox = false;
	App->scene_intro->deactivate_blackbox = false;
	App->scene_intro->tree_on_raw = false;

}
