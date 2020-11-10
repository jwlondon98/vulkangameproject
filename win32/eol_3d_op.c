#include "eol_3d_op.h"

/*
 * *** triangle basics ***
 */

eolTriangle3D eol_triangle_3d(
	Vector3D t1,
	Vector3D t2,
	Vector3D t3
)
{
	eolTriangle3D tri;
	vector3d_copy(tri.t1, t1);
	vector3d_copy(tri.t2, t2);
	vector3d_copy(tri.t3, t3);
	return tri;
}

void eol_triangle_3d_set(
	eolTriangle3D *tri,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3
)
{
	if (!tri)return;
	vector3d_copy(tri->t1, t1);
	vector3d_copy(tri->t2, t2);
	vector3d_copy(tri->t3, t3);
}


eolTriangle2D eol_triangle_2d(
	Vector2D t1,
	Vector2D t2,
	Vector2D t3
)
{
	eolTriangle2D tri;
	vector2d_copy(tri.t1, t1);
	vector2d_copy(tri.t2, t2);
	vector2d_copy(tri.t3, t3);
	return tri;
}

void eol_triangle_2d_set(
	eolTriangle2D *tri,
	Vector2D t1,
	Vector2D t2,
	Vector2D t3
)
{
	if (!tri)return;
	vector2d_copy(tri->t1, t1);
	vector2d_copy(tri->t2, t2);
	vector2d_copy(tri->t3, t3);
}

eolQuad3D eol_quad_3d(
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D t4
)
{
	eolQuad3D quad;
	vector3d_copy(quad.t1, t1);
	vector3d_copy(quad.t2, t2);
	vector3d_copy(quad.t3, t3);
	vector3d_copy(quad.t4, t4);
	return quad;
}

void eol_quad_3d_set(
	eolQuad3D *quad,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D t4
)
{
	if (!quad)return;
	vector3d_copy(quad->t1, t1);
	vector3d_copy(quad->t2, t2);
	vector3d_copy(quad->t3, t3);
	vector3d_copy(quad->t4, t4);
}


eolQuad2D eol_quad_2d(
	Vector2D t1,
	Vector2D t2,
	Vector2D t3,
	Vector2D t4
)
{
	eolQuad2D quad;
	vector2d_copy(quad.t1, t1);
	vector2d_copy(quad.t2, t2);
	vector2d_copy(quad.t3, t3);
	vector2d_copy(quad.t4, t4);
	return quad;
}

void eol_quad_2d_set(
	eolQuad2D *quad,
	Vector2D t1,
	Vector2D t2,
	Vector2D t3,
	Vector2D t4
)
{
	if (!quad)return;
	vector2d_copy(quad->t1, t1);
	vector2d_copy(quad->t2, t2);
	vector2d_copy(quad->t3, t3);
	vector2d_copy(quad->t4, t4);
}

/*
 * *** edge operations ***
 */

float eol_2d_edge_length(Vector2D e1, Vector2D e2)
{
	return vector2d_magnitude(vector2d(e1.x - e2.x, e1.y - e2.y));
}

float eol_3d_edge_length(Vector3D e1, Vector3D e2)
{
	return vector3d_magnitude(vector3d(e1.x - e2.x, e1.y - e2.y, e1.z - e2.z));
}


Bool eol_2d_op_ray_cross_edge(
	Vector2D start,
	Vector2D v,
	Vector2D e1,
	Vector2D e2,
	Vector3D *contact)
{
	float testx, testy;
	float endx, endy;
	float Ua, Ub, Uden;

	endx = start.x + v.x;
	endy = start.y + v.y;

	Uden = ((e2.y - e1.y)*(endx - start.x)) - ((e2.x - e1.x)*(endy - start.y));
	if (Uden == 0)
	{
		return false;/*parallel, can't hit*/
	}

	Ua = (((e2.x - e1.x)*(start.y - e1.y)) - ((e2.y - e1.y)*(start.x - e1.x))) / Uden;
	Ub = (((endx - start.x)*(start.y - e1.y)) - ((endy - start.y)*(start.x - e1.x))) / Uden;

	testx = start.x + (Ua * (endx - start.x));
	testy = start.y + (Ua * (endy - start.y));

	if (contact != NULL)
	{
		contact->x = testx;
		contact->y = testy;
	}

	if ((Ua >= 0) && (Ua <= 1) && (Ub >= 0) && (Ub <= 1))
	{
		return true;
	}
	return false;
}

/*
 * *** transformation operations
 */

void eol_3d_op_transform_quad_by_ori(eolQuad3D *out, eolQuad3D in, eolOrientation ori)
{
	eol_3d_op_transform_quad(out, in, ori.position, ori.rotation, ori.scale);
}

void eol_3d_op_transform_quad(eolQuad3D *out, eolQuad3D in, Vector3D translation, Vector3D rotation, Vector3D scale)
{
	if (!out)return;
	eol_3d_op_transform_vec3d(&out->t1, in.t1, translation, rotation, scale);
	eol_3d_op_transform_vec3d(&out->t2, in.t2, translation, rotation, scale);
	eol_3d_op_transform_vec3d(&out->t3, in.t3, translation, rotation, scale);
	eol_3d_op_transform_vec3d(&out->t4, in.t4, translation, rotation, scale);
}

void eol_3d_op_transform_quad_inverse_by_ori(eolQuad3D *out, eolQuad3D in, eolOrientation ori)
{
	eol_3d_op_transform_quad_inverse(out, in, ori.position, ori.rotation, ori.scale);
}

void eol_3d_op_transform_quad_inverse(eolQuad3D *out, eolQuad3D in, Vector3D translation, Vector3D rotation, Vector3D scale)
{
	if (!out)return;
	eol_3d_op_transform_vec3d_inverse(&out->t1, in.t1, translation, rotation, scale);
	eol_3d_op_transform_vec3d_inverse(&out->t2, in.t2, translation, rotation, scale);
	eol_3d_op_transform_vec3d_inverse(&out->t3, in.t3, translation, rotation, scale);
	eol_3d_op_transform_vec3d_inverse(&out->t4, in.t4, translation, rotation, scale);
}


void eol_3d_op_rotate(Vector3D *out, Vector3D in, Vector3D rotation)
{
	if (!out)return;
	eol_3d_op_rotate_about_z(out, in, rotation.z);
	eol_3d_op_rotate_about_y(out, *out, rotation.y);
	eol_3d_op_rotate_about_x(out, *out, rotation.x);
}

void eol_3d_op_rotate_inverse(Vector3D *out, Vector3D in, Vector3D rotation)
{
	Vector3D locRot;
	if (!out)return;
	vector3d_negate(locRot, rotation);
	eol_3d_op_rotate_about_x(out, in, locRot.x);
	eol_3d_op_rotate_about_y(out, *out, locRot.y);
	eol_3d_op_rotate_about_z(out, *out, locRot.z);
}

void eol_3d_op_rotate_about_x(Vector3D *out, Vector3D in, float angle)
{
	/*Matrix4 m;
	if (!out)return;
	angle *= GFC_DEGTORAD;
	m_eol_mat4(
		m,
		1, 0, 0, 0,
		0, cos(angle), sin(angle), 0,
		0, -sin(angle), cos(angle), 0,
		0, 0, 0, 1);
	gfc_matrix_multiply(
		out,
		m,
		in
	);*/
}

void eol_3d_op_rotate_about_y(Vector3D *out, Vector3D in, float angle)
{
	/*Matrix4 m;
	if (!out)return;
	angle *= GFC_DEGTORAD;
	m_eol_mat4(
		m,
		cos(angle), 0, -sin(angle), 0,
		0, 1, 0, 0,
		sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1);
	eol_mat4_mult_vert(
		out,
		m,
		in
	);*/
}

void eol_3d_op_rotate_about_z(Vector3D *out, Vector3D in, float angle)
{
	//Matrix4 m;
	//if (!out)return;
	//angle *= GFC_DEGTORAD;
	//m_eol_mat4(
	//	m,
	//	cos(angle), sin(angle), 0, 0,
	//	-sin(angle), cos(angle), 0, 0,
	//	0, 0, 1, 0,
	//	0, 0, 0, 1);
	//eol_mat4_mult_vert(
	//	out,
	//	m,
	//	in
	//);
}

void eol_3d_op_scale(Vector3D *out, Vector3D in, Vector3D scale)
{
	/*Matrix4 m;
	if (!out)return;
	matrix(
		m,
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1);
	eol_mat4_mult_vert(
		out,
		m,
		in
	);*/
}

void eol_3d_op_scale_inverse(Vector3D *out, Vector3D in, Vector3D scale)
{
	//Matrix4 m;
	//Vector3D lScale = { 1,1,1 };
	//if (!out)return;
	//if (scale.x != 0)lScale.x = 1 / scale.x;
	//if (scale.y != 0)lScale.y = 1 / scale.y;
	//if (scale.z != 0)lScale.z = 1 / scale.z;
	//m_eol_mat4(
	//	m,
	//	lScale.x, 0, 0, 0,
	//	0, lScale.y, 0, 0,
	//	0, 0, lScale.z, 0,
	//	0, 0, 0, 1);
	//eol_mat4_mult_vert(
	//	out,
	//	m,
	//	in
	//);
}


void eol_3d_op_translate(Vector3D *out, Vector3D in, Vector3D translation)
{
	if (!out)return;
	out->x = in.x + translation.x;
	out->y = in.y + translation.y;
	out->z = in.z + translation.z;
}

void eol_3d_op_transform_vec3d_by_ori(Vector3D *out, Vector3D in, eolOrientation ori)
{
	eol_3d_op_transform_vec3d(out, in, ori.position, ori.rotation, ori.scale);
}

void eol_3d_op_transform_vec3d(Vector3D *out, Vector3D in, Vector3D translation, Vector3D rotation, Vector3D scale)
{
	if (!out)return;
	eol_3d_op_scale(out, in, scale);
	eol_3d_op_rotate(out, *out, rotation);
	eol_3d_op_translate(out, *out, translation);
}

void eol_3d_op_transform_vec3d_inverse_by_ori(Vector3D *out, Vector3D in, eolOrientation ori)
{
	eol_3d_op_transform_vec3d_inverse(out, in, ori.position, ori.rotation, ori.scale);
}

void eol_3d_op_transform_vec3d_inverse(Vector3D *out, Vector3D in, Vector3D translation, Vector3D rotation, Vector3D scale)
{
	Vector3D move;
	if (!out)return;
	vector3d_negate(move, translation);
	eol_3d_op_translate(out, in, move);
	eol_3d_op_rotate_inverse(out, *out, rotation);
	eol_3d_op_scale_inverse(out, *out, scale);
}

/*
 * *** triangle ops ***
 */
void eol_3d_op_get_triangle_normal(Vector3D t1, Vector3D t2, Vector3D t3, Vector3D *normal)
{
	if (normal)
	{
		normal->x = (t1.y * (t2.z - t3.z)) + (t2.y * (t3.z - t1.z)) + (t3.y * (t1.z - t2.z));
		normal->y = (t1.z * (t2.x - t3.x)) + (t2.z * (t3.x - t1.x)) + (t3.z * (t1.x - t2.x));
		normal->z = (t1.x * (t2.y - t3.y)) + (t2.x * (t3.y - t1.y)) + (t3.x * (t1.y - t2.y));
		vector3d_normalize(normal);
	}
}

void eol_3d_op_get_triangle_plane(Vector3D t1, Vector3D t2, Vector3D t3, Vector3D *normal, float *D)
{
	eol_3d_op_get_triangle_normal(t1, t2, t3, normal);
	if (D)
	{
		*D = -((t1.x *(t2.y * t3.z - t3.y * t2.z)) +
			(t2.x *(t3.y * t1.z - t1.y * t3.z)) +
			(t3.x *(t1.y * t2.z - t2.y * t1.z)));
	}
}

float eol_3d_op_ray_in_plane(
	Vector3D start,
	Vector3D dir,
	Vector3D normal,
	float D,
	Vector3D *contact)
{
	float denom, t;
	denom = ((normal.x * dir.x) + (normal.y * dir.y) + (normal.z * dir.z));
	if (denom == 0)return 0;
	t = -(((normal.x * start.x) + (normal.y * start.y) + (normal.z * start.z) + D) / denom);
	if ((t > 0) && (t <= 1))
	{
		if (contact)
		{
			contact->x = start.x + (dir.x * t);
			contact->y = start.y + (dir.y * t);
			contact->z = start.z + (dir.z * t);
		}
		return 1;
	}
	if (contact)
	{
		contact->x = start.x + (dir.x * t);
		contact->y = start.y + (dir.y * t);
		contact->z = start.z + (dir.z * t);
	}
	return -1;
}

Bool eol_3d_op_point_in_triangle(
	Vector3D point,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D *normal)
{
	Vector3D n;
	Vector2D rayTest = { 0,0 };
	int intersectCount = 0;
	if (!normal)
	{
		eol_3d_op_get_triangle_normal(t1, t2, t3, &n);
		normal = &n;
	}

	rayTest.y = eol_3d_edge_length(t1, t2) + eol_3d_edge_length(t2, t3) + eol_3d_edge_length(t3, t1);

	if (normal->x > (MAX(normal->y, normal->z)))
	{
		/*project triangle to yz plane*/
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.y, point.z),
			rayTest,
			vector2d(t1.y, t1.z),
			vector2d(t2.y, t2.z),
			NULL))
		{
			intersectCount++;
		}
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.y, point.z),
			rayTest,
			vector2d(t2.y, t2.z),
			vector2d(t3.y, t3.z),
			NULL))
		{
			intersectCount++;
		}
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.y, point.z),
			rayTest,
			vector2d(t3.y, t3.z),
			vector2d(t1.y, t1.z),
			NULL))
		{
			intersectCount++;
		}
	}
	else if (normal->y > (MAX(normal->x, normal->z)))
	{
		/*project triangle to xz plane*/
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.x, point.z),
			rayTest,
			vector2d(t1.x, t1.z),
			vector2d(t2.x, t2.z),
			NULL))
		{
			intersectCount++;
		}
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.x, point.z),
			rayTest,
			vector2d(t2.x, t2.z),
			vector2d(t3.x, t3.z),
			NULL))
		{
			intersectCount++;
		}
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.x, point.z),
			rayTest,
			vector2d(t3.x, t3.z),
			vector2d(t1.x, t1.z),
			NULL))
		{
			intersectCount++;
		}
	}
	else
	{
		/*project triangle to xy plane*/
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.x, point.y),
			rayTest,
			vector2d(t1.x, t1.y),
			vector2d(t2.x, t2.y),
			NULL))
		{
			intersectCount++;
		}
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.x, point.y),
			rayTest,
			vector2d(t2.x, t2.y),
			vector2d(t3.x, t3.y),
			NULL))
		{
			intersectCount++;
		}
		if (eol_2d_op_ray_cross_edge(
			vector2d(point.x, point.y),
			rayTest,
			vector2d(t3.x, t3.y),
			vector2d(t1.x, t1.y),
			NULL))
		{
			intersectCount++;
		}
	}
	if (intersectCount % 2)
	{
		return true;
	}
	return false;
}

Bool eol_3d_op_ray_in_triangle3d(
	Vector3D start,
	Vector3D dir,
	eolTriangle3D tri,
	Vector3D *contact)
{
	return eol_3d_op_ray_in_triangle(
		start,
		dir,
		tri.t1,
		tri.t2,
		tri.t3,
		contact);
}

Bool eol_3d_op_ray_in_triangle(
	Vector3D start,
	Vector3D dir,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D *contact)
{
	float t;
	Vector3D normal;
	float D;
	Vector3D intersectPoint;

	eol_3d_op_get_triangle_plane(t1, t2, t3, &normal, &D);
	t = eol_3d_op_ray_in_plane(
		start,
		dir,
		normal,
		D,
		&intersectPoint);
	if ((t <= 0) || (t > 1))
	{
		return false;
	}
	if (eol_3d_op_point_in_triangle(
		intersectPoint,
		t1,
		t2,
		t3,
		&normal))
	{
		if (contact)
		{
			vector3d_copy((*contact), intersectPoint);
		}
		return true;
	}
	return false;
}

Bool eol_3d_op_ray_in_quad3d(
	Vector3D start,
	Vector3D dir,
	eolQuad3D quad,
	Vector3D *contact)
{
	return eol_3d_op_ray_in_quad(
		start,
		dir,
		quad.t1,
		quad.t2,
		quad.t3,
		quad.t4,
		contact);
}

Bool eol_3d_op_ray_in_quad(
	Vector3D start,
	Vector3D dir,
	Vector3D t1,
	Vector3D t2,
	Vector3D t3,
	Vector3D t4,
	Vector3D *contact)
{
	float t;
	Vector3D normal;
	float D;
	Vector3D intersectPoint;

	eol_3d_op_get_triangle_plane(t1, t2, t3, &normal, &D);

	t = eol_3d_op_ray_in_plane(
		start,
		dir,
		normal,
		D,
		&intersectPoint);

	if ((t <= 0) || (t > 1))
	{
		return false;
	}
	if (eol_3d_op_point_in_triangle(
		intersectPoint,
		t1,
		t2,
		t3,
		&normal))
	{
		if (contact)
		{
			vector3d_copy((*contact), intersectPoint);
		}
		return true;
	}
	if (eol_3d_op_point_in_triangle(
		intersectPoint,
		t1,
		t3,
		t4,
		&normal))
	{
		if (contact)
		{
			vector3d_copy((*contact), intersectPoint);
		}
		return true;
	}
	return false;
}

void eol_3d_op_print_quad3d(eolQuad3D quad)
{
	//eolLine line1, line2, line3, line4;
	//eol_vec3d_print(line1, quad.t1);
	//eol_vec3d_print(line2, quad.t2);
	//eol_vec3d_print(line3, quad.t3);
	//eol_vec3d_print(line4, quad.t4);
	//slog("{%s,%s,%s,%s}", line1, line2, line3, line4);
}



/*eol@eof*/
