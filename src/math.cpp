#include<math.h>

void clearRenderList(RENDER_4D_LIST *render_list)
{
	render_list->poly_num = 0;
}

void insertPoly4dToRenderList(RENDER_4D_LIST *render_list, POLYF_4D *poly)
{
	int polys_num = render_list->poly_num;

	render_list->poly_ptr[polys_num] = &render_list->poly_data[polys_num];

	memcpy((void *)&render_list->poly_data[polys_num], (void *)poly);

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
	
}

void TransModelToWorldCoor(RENDER_4D_LIST_PTR, render_list, POINT_4D_PTR pos)
{
	
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
