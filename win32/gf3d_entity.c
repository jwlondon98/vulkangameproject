

#include "gf3d_entity.h"
#include "simple_logger.h"
#include "gfc_types.h"

typedef struct
{
	Entity		*entity_list;		/* List of entities */
	Uint32		*entity_count;		/* upper limit for concurrent active entities */

} EntityManager;

static EntityManager gf3d_entity = {0};

/* forward delcaration --  */
void gf3d_entity_free(Entity *entity);

/* destroy entity */
void gf3d_entity_close()
{
	int i;
	if (gf3d_entity.entity_list != NULL)
	{
		for (i = 0; i < gf3d_entity.entity_count; i++)
		{
			gf3d_entity_free(&gf3d_entity.entity_list[i]);
		}
		free(gf3d_entity.entity_list);
	}
	slog("Entity System Closed");
}

/* initializes internal structures for managing the entity system */
void gf3d_entity_init(Uint32 maxEntities)
{
	if (gf3d_entity.entity_list != NULL)
	{
		slog("WARNING: entity system already initialized");
		return;
	}

	gf3d_entity.entity_list = gfc_allocate_array(sizeof(Entity), maxEntities);
	if (!gf3d_entity.entity_list)
	{
		slog("failed to allocate entity list");
		return;
	}
	gf3d_entity.entity_count = maxEntities;
	atexit(gf3d_entity_close);
	slog("Entity System Initialized");
}

/* free entity */
void gf3d_entity_free(Entity *entity)
{
	if (!entity) return;
	gf3d_model_free(entity->model);
	memset(entity, 0, sizeof(Entity));
}

/* make new entity */
Entity *gf3d_entity_new()
{
	int i;
	for (i = 0; i < gf3d_entity.entity_count; i++)
	{
		if (gf3d_entity.entity_list[i]._inuse)
		{
			gf3d_entity.entity_list[i]._inuse = 1;
			return &gf3d_entity.entity_list[i];
		}
	}

	slog("Failed to provide new entity, no unused slots");
	return NULL;
}

/* draw entity */
void gf3d_entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
	/*if (!self) return;
	gf3d_model_draw(self->model, bufferFrame, commandBuffer, self->modelMartix);*/
}

void gf3d_entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
	int i;
	for (i = 0; i < gf3d_entity.entity_count; i++)
	{
		if (gf3d_entity.entity_list[i]._inuse) continue;
		//
	}
}