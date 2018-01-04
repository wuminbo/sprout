#include<math.h>

void clearRenderList(RENDER_4D_LIST *render_list)
{
	render_list->poly_num = 0;
}

void insertPoly4dToRenderList(RENDER_4D_LIST *render_list, POLYF_4D *poly)
{
	int poly_num = render_list->poly_num;

	render_list->poly_ptr[poly_num] = &render_list->poly_data[poly_num];

	memcpy((void *)&render_list->poly_data[poly_num], (void *)poly);

	render_list->poly_num++;
}

void buildXYZRotationMat4X4(float theta_x, float theta_y,float theta_z, MAT_4X4_PTR rot_mat)
{
	MAT_4X4 mx, my, mz, mtmp;

	float sin_theta = 0, cos_theta = 0;
	identityMat4X4(rot_mat);

	cos_theta = cos(theta_x);
	sin_theta = sin(theta_x);

	initMat4X4(&mx, 1,			0,		   0, 0,
					0,  cos_theta, sin_theta, 0,
					0, -sin_theta, cos_theta, 0,
					0,			0,		   0, 1);

	cos_theta = cos(theta_y);
	sin_theta = sin(theta_y);

	initMat4X4(&my, cos_theta, 0, -sin_theta, 0,
					0,		   1, 		   0, 0,
					sin_theta, 0,  cos_theta, 0,
					0,		   0,		   0, 1);

	cos_theta = cos(theta_z);
	sin_theta = sin(theta_z);

	initMat4X4(&mz, cos_theta, sin_theta, 0, 0,
				   -sin_theta, cos_theta, 0, 0,
				   	0, 			       0, 1, 0,
				   	0, 				   0, 0, 1);

	mulMat4X4(&mx, &my, &mtmp);
	mulMat4X4(&mtmp, &mz, rot_mat);

}

void transformRenderList(RENDER_4D_LIST_PTR render_list, MAT_4X4_PTR mat)
{
	for (int index = 0; index < render_list->poly_num; index++)
	{
		POLYF_4D_PTR poly = render_list->poly_ptr[index];

		for (int vertex = 0; vertex < 3; vertex++)
		{
			POINT_4D res_point;

			mat4X4MulVerctor4D(&poly->vlist[vertex], mat, &res_point);

			vector4dCopy(&poly->vlist[vertex], &res_point);
		}
	}
}

void TransModelToWorldCoor(RENDER_4D_LIST_PTR render_list, POINT_4D_PTR pos)
{
	for (int index = 0; index < render_list->poly_num; index++)
	{
		POLYF_4D_PTR poly_ptr = render_list->poly_ptr[index];

		for (int k = 0; k < 3; k++)
		{
			vector4dAdd(&poly_ptr->tvlist[k], wold_pos, &poly_ptr->tvlist[k]);
		}
	} 
}

void buildCame4DMatrixEuler(CAM_4D_PTR cam)
{
	
}

void worldToCameraRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam)
{
	
}

void cameraToPerspectiveRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam)
{
	
}

void perspectiveToScreenRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam)
{
	
}

void fillFrameBuff(RENDER_4D_LIST_PTR render_list, Uint8 *frameData)
{

}

void identityMat4X4(MAT_4X4_PTR mat)
{
	memcpy((void *)m, (void *)&IMAT_4X4, sizeof(MAT_4X4));
}
void initMat4X4(MAT_4X4_PTR mat, float m00, float m01, float m02, float m03,
								 float m10, float m11, float m12, float m13,
								 float m20, float m21, float m22, float m23,
								 float m30, float m31, float m32, float m33)
{
	mat->M[0][0] = m00;mat->M[0][1] = m01;mat->M[0][2] = m02;mat->M[0][3] = m03;
	mat->M[1][0] = m10;mat->M[1][1] = m11;mat->M[1][2] = m12;mat->M[1][3] = m13;
	mat->M[2][0] = m20;mat->M[2][1] = m21;mat->M[2][2] = m22;mat->M[2][3] = m23;
	mat->M[3][0] = m30;mat->M[3][1] = m31;mat->M[3][2] = m32;mat->M[3][3] = m33;
}

void mulMat4X4(MAT_4X4_PTR ma, MAT_4X4_PTR ma, MAT_4X4_PTR dis_m)
{
	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
		{
			float sum = 0;

			for (int index = 0; index < 4; index++)
			{
				sum += (ma->M[row][index] * mb->M[index][col]);
			}
			dis_m->M[row][rol] = sum;
		}
}

void mat4X4MulVerctor4D(VECTOR_4D *v, MAT_4X4 *mat, VECTOR_4D *dis_vt)
{
	for (int col = 0; col < 4; col++)
	{
		float sum = 0;

		for (int row = 0; row < 4; row++)
		{
			sum += (v->M[row] * mat->M[row][col]);
		}

		dis_vt->M[col] = sum;
	}
}


void vector3dNormalize(VECTOR_3D_PTR v)
{
	float len = sqrt(v->x*v->x + v->y*v->y + v->z*v->z);

	if(len <= 0) 
		return;

	float len_rev = 1/len;

	v->x *= len_rev;
	v->y *= len_rev;
	v->z *= len_rev;
}

void initPlane3d(PLANE_3D_PTR plane, POINT_3D_PTR pt, VECTOR_3D_PTR normal)
{
	vector3dCopy(&plane->p, pt);
	vector3dCopy(&plane->n, normal);	
}
void initCamera(CAM_4D *cam, 
				POINT_4D *pos, 
				VECTOR_4D *dir, 
				POINT_4D *tar, 
				float near_clip_z,
				float far_clip_z, 
				float fov, 
				float view_port_width, 
				float view_port_height)
{
	vector4dCopy(&cam->pos, pos);
	vector4dCopy(&cam->dir, dir);

	vectorInitXYZ(&cam->u, 1,0,0);
	vectorInitXYZ(&cam->v, 0,1,0);
	vectorInitXYZ(&cam->n, 0,0,1);

	vectorZero(&cam->target);

	cam->near_clip_z = near_clip_z;
	cam->far_clip_z = far_clip_z;

	cam->view_port_width = view_port_width;
	cam->view_port_height = view_port_height;

	cam->view_port_center_x = (view_port_width-1)/2;
	cam->view_port_center_y = (view_port_height-1)/2;

	cam->aspect_ratio = (float)view_port_width/(float)view_port_height;

	identityMat4X4(&cam->cam_mat);
	identityMat4X4(&cam->per_mat);
	identityMat4X4(&cam->scr_mat);

	cam->fov = fov;

	cam->view_plane_width = 2.0;
	cam->view_plane_height = 2.0/cam->aspect_ratio;

	float tan_fov_div2 = tan(DEG_TO_RAD(fov/2));

	cam->view_dist = (0.5)*(cam->view_plane_width) * tan_fov_div2;

	if(fov == 90.0)
	{
		POINT_3D org_pt;
		vectorInitXYZ(&org_pt, 0,0,0);

		VECTOR_3D vn;

		vectorInitXYZ(&vn, 1,0,-1);
		initPlane3d(&cam->r_clip_plane, &org_pt, &vn);
		vector3dNormalize(&cam->r_clip_plane->n);

		vectorInitXYZ(&vn, -1,0,-1);
		initPlane3d(&cam->l_clip_plane, &org_pt, &vn);
		vector3dNormalize(*cam->l_clip_plane->n);

		vectorInitXYZ(&vn, 0,1,-1);
		initPlane3d(&cam->t_clip_plane, &org_pt, &vn);
		vector3dNormalize(&cam->t_clip_plane->n);

		vectorInitXYZ(&vn, 0,-1,-1);
		initPlane3d(&cam->b_clip_plane, &org_pt, &vn);
		vector3dNormalize(&cam->b_clip_plane->n);
	}

}
