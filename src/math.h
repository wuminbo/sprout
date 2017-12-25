#ifndef __MATH__H__
#define __MATH__H__

#define MAX_OBJ_VERTICES 1000
#define MAX_RENDER_LIST_POLYS = 1000
typedef struct POINT_4D_TYPE
{
	int state;
	int attr;

	int x, y, z, w;
} POINT_4D, *POINT_4D_PTR, VECTOR_4D, *VECTOR_4D_PTR;

typedef struct POINT_3D_TYPE
{
	int state;
	int attr;

	int x, y, z;
} POINT_3D, *POINT_3D_PTR, VECTOR_3D, *VECTOR_3D_PTR;

typedef struct POLYF_4D_TYPE
{
	int state;
	int attr;
	
	int color;

	POINT_4D vlist[3];
	POINT_4D tvlist[3];
} POLYF_4D, *POLYF_4D_PTR;

typedef struct MAT_4X4_TYPE
{
	float mat[4][4];
} MAT_4X4, *MAT_4X4_PTR;

typedef struct OBJ_4D_TYPE
{
	int state;
	int attr;

	POINT_4D wold_pos;
	POLYF_4D[MAX_OBJ_VERTICES];

} OBJ_4D, *OBJ_4D_PTR;

typedef struct RENDER_4D_LIST_TYPE
{
	int state;
	int attr;

	int poly_num;

	POLYF_4D poly_list[MAX_RENDER_LIST_POLYS];
	POLYF_4D_PTR poly_ptr_list[MAX_RENDER_LIST_POLYS];
} RENDER_4D_LIST, *RENDER_4D_LIST_PTR;

typedef struct PLANE_3D_TYPE
{
	POINT_3D p;
	VECTOR_3D n;
} PLANE_3D, *PLANE_3D_PTR;

typedef struct CAM_4D_TYPE
{
	int state;
	int attr;

	POLYF_4D pos;

	VECTOR_4D dir;

	VECTOR_4D u;
	VECTOR_4D v;
	VECTOR_4D n;

	VECTOR_4D target;

	float view_dist;

	float fov;

	float near_clip_z;
	float far_clip_z;

	PLANE_3D r_clip_plane;
	PLANE_3D l_clip_plane;
	PLANE_3D t_clip_plane;
	PLANE_3D b_clip_plane;

	float view_plane_width;
	float view_plane_height;	

	float view_port_width;
	float view_port_height;
	float view_port_center_x;
	float view_port_center_y;

	float aspect_ratio;

	MAT_4X4 cam_mat;
	MAT_4X4 per_mat;
	MAT_4X4 scr_mat;
} CAM_4D, *CAM_4D_PTR;


void clearRenderList(RENDER_4D_LIST *render_list);

void insertPoly4dToRenderList(RENDER_4D_LIST *render_list, POLYF_4D poly);

void buildXYZRotationMat4X4(float theta_x, float theta_y,float theta_z, MAT_4X4_PTR rot_mat);

void transformRenderList(RENDER_4D_LIST_PTR render_list, MAT_4X4_PTR mat);

void TransModelToWorldCoor(RENDER_4D_LIST_PTR, render_list, POINT_4D_PTR pos);

void buildCame4DMatrixEuler(CAM_4D_PTR cam);

void worldToCameraRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam);

void cameraToPerspectiveRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam);

void perspectiveToScreenRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam);


#endif