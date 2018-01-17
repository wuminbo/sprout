#ifndef __SPROUT_MATH__H__
#define __SPROUT_MATH__H__
#include "SdlDraw.h"

#define MAX_OBJ_VERTICES 1000
#define MAX_RENDER_LIST_POLYS 1000
#define PI 3.141592654
#define DEG_TO_RAD(angle) ((angle)*PI/180.0)
typedef struct POINT_4D_TYPE
{
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float M[4]; 
	};
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
	float M[4][4];
} MAT_4X4, *MAT_4X4_PTR;

typedef struct OBJ_4D_TYPE
{
	int state;
	int attr;

	POINT_4D wold_pos;
	POLYF_4D obj[MAX_OBJ_VERTICES];

} OBJ_4D, *OBJ_4D_PTR;

typedef struct RENDER_4D_LIST_TYPE
{
	int state;
	int attr;

	int poly_num;

	POLYF_4D poly_data[MAX_RENDER_LIST_POLYS];
	POLYF_4D_PTR poly_ptr[MAX_RENDER_LIST_POLYS];
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

	POINT_4D pos;

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


const MAT_4X4 IMAT_4X4 = { 1,0,0,0,
						   0,1,0,0,
						   0,0,1,0,
						   0,0,0,1,};


void clearRenderList(RENDER_4D_LIST *render_list);

void insertPoly4dToRenderList1(RENDER_4D_LIST *render_list, POLYF_4D poly);

void buildXYZRotationMat4X4(float theta_x, float theta_y,float theta_z, MAT_4X4_PTR rot_mat);

void transformRenderList(RENDER_4D_LIST_PTR render_list, MAT_4X4_PTR mat);

void TransModelToWorldCoor(RENDER_4D_LIST_PTR render_list, POINT_4D_PTR pos);

void buildCame4DMatrixEuler(CAM_4D_PTR cam);

void worldToCameraRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam);

void cameraToPerspectiveRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam);

void perspectiveToScreenRenderList(RENDER_4D_LIST_PTR render_list, CAM_4D_PTR cam);

void fillFrameBuff(RENDER_4D_LIST_PTR render_list, Uint8 *frameData);

void identityMat4X4(MAT_4X4_PTR mat);

void initMat4X4(MAT_4X4_PTR mat, float m00, float m01, float m02, float m03,
								 float m10, float m11, float m12, float m13,
								 float m20, float m21, float m22, float m23,
								 float m30, float m31, float m32, float m33);

void mulMat4X4(MAT_4X4_PTR m1, MAT_4X4_PTR m2, MAT_4X4_PTR m);

void mat4X4MulVerctor4D(VECTOR_4D *vector, MAT_4X4 *mat, VECTOR_4D *dis_vt);

inline void vector4dCopy(VECTOR_4D *dis_v, VECTOR_4D *src_v)
{
	dis_v->x = src_v->x; dis_v->y = src_v->y; 
	dis_v->z = src_v->z; dis_v->w = src_v->w;
}

inline void vector3dCopy(VECTOR_3D *dis_v, VECTOR_3D *src_v)
{
	dis_v->x = src_v->x; dis_v->y = src_v->y; 
	dis_v->z = src_v->z;
}


inline void vector4dAdd(VECTOR_4D *dis_v, VECTOR_4D *va, VECTOR_4D *vb)
{
	dis_v->x = va->x + vb->x; dis_v->y = va->y + vb->y; 
	dis_v->z = va->z + vb->z; dis_v->w = va->w + vb->w;
}

inline void vectorInitXYZ(VECTOR_3D *v, float x, float y, float z)
{
	v->x = x; v->y = y; v->z = z;
}
inline void vector4dInitXYZ(VECTOR_4D *v, float x, float y, float z)
{
	v->x = x; v->y = y; 
	v->z = z; v->w = 1.0;
}
inline void vectorZero(VECTOR_4D *v)
{
	v->x = v->y = v->z = 0;
}

void initPlane3d(PLANE_3D_PTR plane, POINT_3D_PTR pt, VECTOR_3D_PTR normal);

void vector3dNormalize(VECTOR_3D_PTR v);

void initCamera(CAM_4D *cam, 
				POINT_4D *pos, 
				VECTOR_4D *dir, 
				POINT_4D *tar, 
				float near_clip_z,
				float far_clip_z, 
				float fov, 
				float view_port_width, 
				float view_port_height);


void drawPixel(int x, int y, int color, int lpitch, int *frameData);

void drawLine(int x0, int y0, int x1, int y1,int color, int lpitch, Uint8 *frameData);
#endif
