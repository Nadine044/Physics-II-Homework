#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"

#ifdef _RELEASE
#pragma comment (lib, "Box2D/libx86/Release/Box2D.lib")
#endif // RELEAS

#ifdef _DEBUG
#pragma comment (lib, "Box2D/libx86/Debug/Box2D.lib")
#endif // DEBUG


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

	b2Vec2 gravity(0.0f, 0.3f);
	world = new b2World(gravity);


	// TODO 4: Create a a big static circle as "ground"

	b2BodyDef ground;
	ground.position.Set(PIXELS_TO_METERS(500), PIXELS_TO_METERS(400));

	b2Body* groundBody = world->CreateBody(&ground);

	b2CircleShape groundBox;
	groundBox.m_radius = PIXELS_TO_METERS(300);

	groundBody->CreateFixture(&groundBox, 1.0f);

	//---------------------
	b2BodyDef floor;
	b2Body* floorBody = nullptr;
	b2PolygonShape floorShape;

	floor.type = b2_staticBody;
	floor.position.Set(PIXELS_TO_METERS(0), PIXELS_TO_METERS(SCREEN_HEIGHT));

	floorBody = world->CreateBody(&floor);
	
	floorShape.SetAsBox(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(100));
	
	floorBody->CreateFixture(&floorShape, 1.0f);

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

		circle.position.Set(PIXELS_TO_METERS(App->input->GetMouseX()), PIXELS_TO_METERS(App->input->GetMouseY()));

		b2Body* c = world->CreateBody(&circle);

		b2CircleShape circleBox;
		circleBox.m_radius = PIXELS_TO_METERS(rand()%100);
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

				/*case b2Shape::e_polygon:
				{
					b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
					int32 count = shape->GetVertexCount();
					b2Vec2 prev = b->GetWorldPoint(shape->GetVertex(0));
					b2Vec2 v;

					for (int32 i = 0; i < count; i++)
					{
						v = b->GetWorldPoint(shape->GetVertex(i));

						if (i > 0)
						{
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 255, 255);
							prev = v;
						}
					}

					v = b->GetWorldPoint(shape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 255, 255);
				}**/

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
