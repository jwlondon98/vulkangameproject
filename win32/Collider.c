#include "Collider.h"

Collider* CreateCollider()
{
	Collider* collider;
	collider = malloc(sizeof(Collider));
	atexit(FreeCollider);
	return collider;
}

void FreeCollider(Collider* collider)
{
	if (!collider) return;

	memset(collider, 0, sizeof(Collider));
}

void UpdateCollider(Collider *c, Vector3D newCenter)
{
	// set new center
	c->center = newCenter;

	// set the minimum bounds
	c->min = vector3d(newCenter.x - c->extents.x, newCenter.y - c->extents.y, newCenter.z - c->extents.z);
	
	// set the maximum bounds
	c->max = vector3d(newCenter.x + c->extents.x, newCenter.y + c->extents.y, newCenter.z + c->extents.z);
}

int DetectCollision(Collider *collider1, Collider *collider2)
{
	if (collider1 == NULL || collider2 == NULL)
		return;

	//slog("Collider1 X: %f Collider2 X: %f", collider1->min.x, collider2->min.x);
	/*if ((collider1->min.x <= collider2->max.x && collider1->max.x >= collider2->min.x) &&
		(collider1->min.y <= collider2->max.y && collider1->max.y >= collider2->min.y) &&
		(collider1->min.z <= collider2->max.z && collider1->max.z >= collider2->min.z))
	*/
	if (collider1->min.y <= collider2->max.y &&
		collider1->max.x >= collider2->min.x)
	{
		slog("collision detected");
		return 1;
	}
	else
		return 0;
}