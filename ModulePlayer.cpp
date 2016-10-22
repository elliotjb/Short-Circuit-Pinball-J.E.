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
	}
	else
	{
		pivot_force_left->body->ApplyForceToCenter(b2Vec2(0.0f, 100.0f), true);
	}

	/*int x, y;
	lever_left->GetPosition(x, y);
	App->renderer->Blit(lever_left_Tex, x -10, y -5, NULL, 1.0f, lever_left->GetRotation());
	int x_, y_;
	lever_Right->GetPosition(x_, y_);
	App->renderer->Blit(lever_right_Tex, 335 - x_, 570 - y_, NULL, 1.0f, lever_Right->GetRotation());*/

	return UPDATE_CONTINUE;
}


bool ModulePlayer::CreateLevers()
{

	//Lever Left
	pivot_left = App->physics->CreateCircle(205, 586, 10, false);
	//lever_left = App->physics->CreateRectangle(210, 586, 70, 10, true);
	pivot_force_left = App->physics->CreateCircle(280, 586, 5, true);

	//Lever Right
	pivot_Right = App->physics->CreateCircle(410, 586, 10, false);
	//lever_Right = App->physics->CreateRectangle(410, 586, 70, 10, true);
	pivot_force_Right = App->physics->CreateCircle(340, 586, 5, true);

	int Chain_lever_left[16] = {
		272, 620,
		278, 619,
		281, 613,
		280, 607,
		210, 576,
		201, 577,
		195, 586,
		200, 596
	};


	int Chain_lever_right[16] = {
		420, 582,
		414, 576,
		406, 576,
		336, 605,
		333, 610,
		334, 615,
		339, 620,
		416, 597
	};

	lever_left = App->physics->CreatePolygon(0, 0, Chain_lever_left, 16, 0, true);
	lever_Right = App->physics->CreatePolygon(0, 0, Chain_lever_right, 16, 0, true);


	return true;
}