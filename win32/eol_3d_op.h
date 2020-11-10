#ifndef __EOL_3D_OP__
#define __EOL_3D_OP__
/*
 *    Copyright 2012 - 2013 Engineer of Lies
 *    This file is part of the Engine of Lies game engine library
 *
 *    The Engine of Lies (EOL) is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    EOL is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with the EOL game engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gfc_types.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "simple_logger.h"

 /**
  * @purpose Common operations dealing with 3D math (and some 2D).
  */

typedef struct
{
	Vector3D position;
	Vector3D scale;
	Vector3D rotation;
	Vector3D color;
	float alpha;
}eolOrientation;

typedef struct
{
	Vector3D t1;
	Vector3D t2;
	Vector3D t3;
}eolTriangle3D;

typedef struct
{
	Vector3D t1;
	Vector3D t2;
	Vector3D t3;
}eolTriangle2D;

typedef struct
{
	Vector3D t1;
	Vector3D t2;
	Vector3D t3;
	Vector3D t4;
}eolQuad3D;

typedef struct
{
	Vector3D t1;
	Vector3D t2;
	Vector3D t3;
	Vector3D t4;
}eolQuad2D;

eolTriangle3D eol_triangle_3d(
	Vector3D t1,
	Vector3D t2,
	Vector3D t3
);

void eol_triangle_3d_set(
	eolTriangle3D *tri,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3
);

eolTriangle2D eol_triangle_2d(
	Vector2D t1,
	Vector2D t2,
	Vector2D t3
);

void eol_triangle_2d_set(
	eolTriangle2D *tri,
	Vector2D t1,
	Vector2D t2,
	Vector2D t3
);


eolQuad3D eol_quad_3d(
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D t4
);

void eol_quad_3d_set(
	eolQuad3D *quad,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D t4
);

eolQuad2D eol_quad_2d(
	Vector2D t1,
	Vector2D t2,
	Vector2D t3,
	Vector2D t4
);

void eol_quad_2d_set(
	eolQuad2D *quad,
	Vector2D t1,
	Vector2D t2,
	Vector2D t3,
	Vector2D t4
);

/*edge operations*/

/**
 * @brief test if a ray intersects an edge in 2d space
 * @param start the starting point of the ray
 * @param v the vecctor of the ray
 * @param e1 one end point of the edge
 * @param e2 one end point of the edge
 * @param contact output optional.  if provided this will be set with the point
 *                of intersection
 *                if ray and edge are not parallel, this will still be set to
 *                the intersection point if the lines were infinite
 * @return eolTrue if the ray intersects the edge, eolFalse otherwise
 *
 */
Bool eol_2d_op_ray_cross_edge(
	Vector2D start,
	Vector2D v,
	Vector2D e1,
	Vector2D e2,
	Vector3D *contact);

float eol_2d_edge_length(Vector2D e1, Vector2D e2);

/*transformations*/

void eol_3d_op_transform_quad_by_ori(eolQuad3D *out, eolQuad3D in, eolOrientation ori);
void eol_3d_op_transform_quad(eolQuad3D *out, eolQuad3D in, Vector3D translation, Vector3D rotation, Vector3D scale);

void eol_3d_op_transform_quad_inverse_by_ori(eolQuad3D *out, eolQuad3D in, eolOrientation ori);
void eol_3d_op_transform_quad_inverse(eolQuad3D *out, eolQuad3D in, Vector3D translation, Vector3D rotation, Vector3D scale);

/**
 * @brief apply a rotation, scale and translation to a vector
 * @param out output vector no-op if NULL
 * @param in input vector to be transformed
 * @param translation where to move the vector
 * @param rotation angles to rotate the vector
 * @param scale scale to apply to the vector
 */
void eol_3d_op_transform_vec3d(Vector3D *out, Vector3D in, Vector3D translation, Vector3D rotation, Vector3D scale);
void eol_3d_op_transform_vec3d_by_ori(Vector3D *out, Vector3D in, eolOrientation ori);

/**
 * @brief un-apply a rotation, scale and translation to a vector
 * @param out output vector no-op if NULL
 * @param in input vector to be transformed
 * @param translation where to move the vector
 * @param rotation angles to rotate the vector
 * @param scale scale to apply to the vector
 */
void eol_3d_op_transform_vec3d_inverse(Vector3D *out, Vector3D in, Vector3D translation, Vector3D rotation, Vector3D scale);
void eol_3d_op_transform_vec3d_inverse_by_ori(Vector3D *out, Vector3D in, eolOrientation ori);

/**
 * @brief apply a translation to a vector
 * @param out output vector no-op if NULL
 * @param in input vector to be transformed
 * @param translation where to move the vector
 */
void eol_3d_op_translate(Vector3D *out, Vector3D in, Vector3D translation);

/**
 * @brief apply a scale to a vector
 * @param out output vector no-op if NULL
 * @param in input vector to be transformed
 * @param scale scale to apply to the vector
 */
void eol_3d_op_scale(Vector3D *out, Vector3D in, Vector3D scale);

/**
 * @brief rotate the vector about the z axis
 * @param out output vector no-op if NULL
 * @param in input vector to be transformed
 * @param angle the amount to rotate
 */
void eol_3d_op_rotate_about_z(Vector3D *out, Vector3D in, float angle);

/**
 * @brief rotate the vector about the y axis
 * @param out output vector no-op if NULL
 * @param in input vector to be transformed
 * @param angle the amount to rotate
 */
void eol_3d_op_rotate_about_y(Vector3D *out, Vector3D in, float angle);

/**
 * @brief rotate the vector about the x axis
 * @param out output vector no-op if NULL
 * @param in input vector to be transformed
 * @param angle the amount to rotate
 */
void eol_3d_op_rotate_about_x(Vector3D *out, Vector3D in, float angle);

/**
 * @brief apply a rotation to a vector
 * @param out output vector no-op if NULL
 * @param in input vector to be transformed
 * @param rotation angles to rotate the vector
 */
void eol_3d_op_rotate(Vector3D *out, Vector3D in, Vector3D rotation);


/*ray casting*/

/**
 * @brief get the normal described by the triangle defined by the 3 points passed
 * @param t1 one triangle vertex
 * @param t2 one triangle vertex
 * @param t3 one triangle vertex
 * @param normal output normal vector for the triangle
 */
void eol_3d_op_get_triangle_normal(
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D *normal);

/**
 * @brief given a triangle's 3 points, calculate the normal and distance from the origin
 * @param t1 one triangle vertex
 * @param t2 one triangle vertex
 * @param t3 one triangle vertex
 * @param normal output normal vector for the triangle
 * @param D output distance of the plane from origin
 */
void eol_3d_op_get_triangle_plane(
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D *normal,
	float *D);

/**
 * @brief calculate the contact point of the rar with the provided plane
 * @param start starting point of the ray
 * @param dir ray vector
 * @param normal the normal describing the plane
 * @param D the distance of the plane from origin
 * @param contact output optional the point where the ray would intersect the plane
 * @return 0 ray is perpendicular to the plane, it will never intersect
 *         < 0 ray is pointing away from the plane  Contact point is still set where the ray would have passed through
 *         > 0 to 1 ray intersects plane contact point is the intersection point
 *         > 1 ray does not intersect, but it would if it were longer by this factor
 */
float eol_3d_op_ray_in_plane(
	Vector3D start,
	Vector3D dir,
	Vector3D normal,
	Vector3D D,
	Vector3D *contact);

/**
 * @brief given a triangle and a ray, determine if they intersect
 * @param start starting point of ray
 * @param dir vector of the ray
 * @param t1 one triangle vertex
 * @param t2 one triangle vertex
 * @param t3 one triangle vertex
 * @param contact output optional the point where the ray would intersect the triangle
 * @return eolTrue if the ray intersects the triangle, eolFalse otherwise.
 *         contact is not set if there is not intersection
 */
Bool eol_3d_op_ray_in_triangle(
	Vector3D start,
	Vector3D dir,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D *contact);

/**
 * @brief given a triangle and a ray, determine if they intersect
 * @param start starting point of ray
 * @param dir vector of the ray
 * @param tri the triangle to test
 * @param contact output optional the point where the ray would intersect the triangle
 * @return eolTrue if the ray intersects the triangle, eolFalse otherwise.
 *         contact is not set if there is not intersection
 */
Bool eol_3d_op_ray_in_triangle3d(
	Vector3D start,
	Vector3D dir,
	eolTriangle3D tri,
	Vector3D *contact);


/**
 * @brief given a point on the same plane of the triangle, determine if it is
 * inside the triangle or outside
 * @param point the point to test
 * @param t1 one triangle vertex
 * @param t2 one triangle vertex
 * @param t3 one triangle vertex
 * @param normal optional if this is provided, normal calculation can be skipped
 */
Bool eol_3d_op_point_in_triangle(
	Vector3D point,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D *normal);

/**
 * @brief given a quad and a ray, determine if they intersect
 * @param start starting point of ray
 * @param dir vector of the ray
 * @param t1 one quad vertex
 * @param t2 one quad vertex
 * @param t3 one quad vertex
 * @param t4 one quad vertex
 * @param contact output optional the point where the ray would intersect the quad
 * @return eolTrue if the ray intersects the quad, eolFalse otherwise.
 *         contact is not set if there is not intersection
 */
Bool eol_3d_op_ray_in_quad(
	Vector3D start,
	Vector3D dir,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D t4,
	Vector3D *contact);

/**
 * @brief given a quad and a ray, determine if they intersect
 * @param start starting point of ray
 * @param dir vector of the ray
 * @param quad the quad to test
 * @param contact output optional the point where the ray would intersect the quad
 * @return eolTrue if the ray intersects the quad, eolFalse otherwise.
 *         contact is not set if there is not intersection
 */
Bool eol_3d_op_ray_in_quad3d(
	Vector3D start,
	Vector3D dir,
	eolQuad3D quad,
	Vector3D *contact);

/**
 * @brief print the quad data to the out text
 */
void eol_3d_op_print_quad3d(eolQuad3D quad);

#endif
