#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "p2Point.h"
#include "math.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	lever_left_Tex = lever_right_Tex = NULL;
	Lives = 3;
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

	App->physics->CreateRevolutionJoint();


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

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

	return UPDATE_CONTINUE;
}


bool ModulePlayer::CreateLevers()
{

	//Lever Left
	pivot_left = App->physics->CreateCircle(205, 575, 10, false);
	//lever_left = App->physics->CreateRectangle(210, 586, 70, 10, true);
	pivot_force_left = App->physics->CreateCircle(280, 575, 5, true);

	//Lever Right
	pivot_Right = App->physics->CreateCircle(410, 575, 10, false);
	//lever_Right = App->physics->CreateRectangle(410, 586, 70, 10, true);
	pivot_force_Right = App->physics->CreateCircle(340, 575, 5, true);

	//Lever UP Right
	pivot_UP_left = App->physics->CreateCircle(187, 144, 5, false);
	//lever_Right = App->physics->CreateRectangle(410, 586, 70, 10, true);
	pivot_UP_force_left = App->physics->CreateCircle(187, 155, 2, true);

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

	lever_UP_left = App->physics->CreatePolygon(0, 0, Left_UP_Lever, 16, 0, true, LEVER, false);
	lever_left = App->physics->CreatePolygon(0, 0, Chain_lever_left, 16, 0, true, LEVER, false);
	lever_Right = App->physics->CreatePolygon(0, 0, Chain_lever_right, 16, 0, true, LEVER, false);


	return true;
}