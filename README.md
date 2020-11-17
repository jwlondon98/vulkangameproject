# Vulkan Midterm Project
By: Jordan London

## Unique Deliverables

* On screen clicks for shooting

* World to interact with

* 5 different entities to interact with

* On rails camera sequence

* Variety of weapon pickups

## Common Deliverables

* Rendering Through Vulkan

*   Functioning Entity System

*   Basic Collision Detection

*   Basic User Controls

*   A contained game world

## How To Play
The game is similar to Beat Saber in that the player is on a track and has to hit incoming cubes, although in this case the player has a gun in order to shoot the cubes. The player has an overall score that updates depending on if the player destroys enemies and targets.

There are 3 different lanes: left, center, and right. Pressing the number keys (1, 2, and 3 respectively) changes the gun's lane.

### Entity Cubes
1. Target Cube (YELLOW) - Shooting this gives 100 points
2. Basic Enemy Cube (RED) - Shooting this gives 25 points.
3. Advanced Enemy Cube (RED) - This entity shoots at the player. Shooting this enemy gives 50 points. If an enemy bullet hits the player, 20 points are subtracted.
4. Weapon Drop (PURPLE) - Shoot this to get a new weapon.
5. Hostage (GREEN) - The player must change to the lane of the hostage and hold space until the hostage reaches the player in order to save the hostage (60 points).

### Weapon Types
1. Pistol - Left click to shoot
2. Machine Gun - Hold left click to shoot without having to reclick
3. Shotgun - Shoots down all 3 lanes on click. When player has shotgun, hostages can be saved without changing lanes.

### BUGS
There are few game-breaking bugs that are inconsistent. I have unfortunately not been able to fix them yet:
1. The game fails to get a free descriptor set at times. Unsure of how to fix this. Error stating cannot allocate any more descriptor sets prints out.
2. gf3d_vgraphics_render_end has a bug where vkQueueSubmit returns an unsuccessful result. Printed Error: "failed to submit draw command buffer!"
