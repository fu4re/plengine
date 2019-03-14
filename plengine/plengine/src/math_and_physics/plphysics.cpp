#include "plphysics.h"
Space * space;

void InitializePhysics(Space * s)
{
	max_parts_in_destroy = 10;
	space = s;
}
Space * GetSpace()
{
	return space;
}
void PutObject(int n, Object * object)
{
	space->Objects[n] = *object;
}

void UpdatePhysics()
{
	for (int i = 0; i < (int)space->Objects.size(); i++)
	{
		if (space->Objects[i].Params.UseGravity)
			space->Objects[i].Params.Acceleration = ApplyGravity(&space->Objects[i], &space->Plane, space->Objects[i].Params.Acceleration);
		for (int j = 0; j < (int)space->Objects.size(); j++)
		{
			if (i == j) continue;
			if (OBJECTS_COLLISION(space->Objects[i].Colider, space->Objects[j].Colider))
			{
				space->Objects[i].Params.Acceleration = space->Objects[i].Params.Acceleration + space->Objects[i].Params.Acceleration * space->Objects[j].Params.Strong * (1 - space->Objects[i].Params.Drag);
				space->Objects[i].Center += space->Objects[i].Params.Acceleration.Position;
				if (space->Objects[i].Params.Brakeable)
				{	
					std::vector<Object> vs = DestroyObject(&space->Objects[i], max_parts_in_destroy);
					space->Objects.erase(space->Objects.begin() + i);
					for (int f = 0; f < (int)vs.size(); f++)
						space->Objects.push_back(vs[f]);
				}
			}
		}
	}
}

#include <thread>

void __loop(bool condition, Time sleep, update Update)
{
	while (condition)
	{
		UpdatePhysics();
		Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	}
}

void Loop(bool condition, Time sleep, update Update)
{
	std::thread t = std::thread(__loop, condition, sleep, Update);
	t.detach();
}
