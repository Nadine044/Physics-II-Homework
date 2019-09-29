#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"

#pragma comment (lib, "Box2D/libx86/Debug/Box2D.lib")
#pragma comment (lib, "Box2D/libx86/Release/Box2D.lib")

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// TODO 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it

	b2Vec2 gravity(0.0f, -9.8f);
	world = new b2World(gravity);


	// TODO 4: Create a a big static circle as "ground"

	b2BodyDef ground;
	ground.position.Set(10, 7.5);

	b2Body* groundBody = world->CreateBody(&ground);

	b2CircleShape groundBox;
	groundBox.m_radius = 4;

	groundBody->CreateFixture(&groundBox, 1.0f);

	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)

	float32 timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	for(int32 i = 0 ; i < 60 ; ++i)
	{
		world->Step(timeStep, velocityIterations, positionIterations);
	}

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

 	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		b2BodyDef circle;
		circle.type = b2_dynamicBody;

		int mouse_x = App->input->GetMouseX();
		int mouse_y = App->input->GetMouseY();

		circle.position.Set(10, 0);

		b2Body* c = world->CreateBody(&circle);

		b2CircleShape circleBox;
		circleBox.m_radius = 1;
		b2FixtureDef fixture;
		fixture.shape = &circleBox;
		fixture.density = 1.0f;

		c->CreateFixture(&circleBox, 1.0f);
	}
		

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}