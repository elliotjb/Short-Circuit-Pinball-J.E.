#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
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

	lever_left_Tex = App->textures->Load("pinball/LeftLever.png");

	pivot_left = App->physics->CreateCircle(205, 586, 10, false);
	lever_left = App->physics->CreateRectangle(210, 586, 70, 10, true);
	pivot_force_left = App->physics->CreateCircle(280, 586, 5, true);

	lever_right_Tex = App->textures->Load("pinball/RightLever.png");

	pivot_Right = App->physics->CreateCircle(410, 586, 10, false);
	lever_Right = App->physics->CreateRectangle(410, 586, 70, 10, true);
	pivot_force_Right = App->physics->CreateCircle(340, 586, 5, true);

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
	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		pivot_force_Right->body->ApplyForceToCenter(b2Vec2(0.0f, -200.0f), true);
	}
	else
	{
		pivot_force_Right->body->ApplyForceToCenter(b2Vec2(0.0f, 100.0f), true);
	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		pivot_force_left->body->ApplyForceToCenter(b2Vec2(0.0f, -200.0f), true);
	}
	else
	{
		pivot_force_left->body->ApplyForceToCenter(b2Vec2(0.0f, 100.0f), true);
	}

	int x, y;
	lever_left->GetPosition(x, y);
	App->renderer->Blit(lever_left_Tex, x -10, y -5, NULL, 1.0f, lever_left->GetRotation());
	int x_, y_;
	lever_Right->GetPosition(x, y);
	App->renderer->Blit(lever_right_Tex, x -10, y -5, NULL, 1.0f, lever_Right->GetRotation());

	return UPDATE_CONTINUE;
}

