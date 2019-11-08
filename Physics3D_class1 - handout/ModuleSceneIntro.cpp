#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// TODO 2: Place the camera one unit up in Y and one unit to the right
	// experiment with different camera placements, then use LookAt()
	// to make it look at the center

	vec3 newCamPos(1, 1, 0);

	App->camera->Move(newCamPos);
	App->camera->LookAt(vec3(0, 0, 0));

	/*App->camera->LookAt(vec3(0, 0, 0));
		App->camera->Position.y = App->camera->Position.y - 0.05;*/

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// TODO 1: Create a Plane primitive. This uses the plane formula
	// so you have to express the normal of the plane to create 
	// a plane centered around 0,0. Make that it draw the axis for reference

	Plane floor(0.f, 1.f, 0.f, 1.f);
	floor.axis = true;
	floor.Render();

	// TODO 6: Draw a sphere of 0.5f radius around the center
	// Draw somewhere else a cube and a cylinder in wireframe

	Sphere sphere(0.5f);

	Cube cube(0.5f, 0.5f, 0.5f);
	cube.SetPos(1.f, 1.f, 2.f);
	cube.wire = true;

	Cylinder cylinder(0.5f, 2.f);
	cylinder.SetPos(-1.f, 1.f, 2.f);
	cylinder.wire = true;

	sphere.Render();
	cube.Render();
	cylinder.Render();

	return UPDATE_CONTINUE;
}

