#include <camera.h>
#include <math.h>


void update_camera_matrix(Camera* camera) {
	mat4 translate = {
		1,0,0,-camera->position.x,
		0,1,0,-camera->position.y,
		0,0,1,-camera->position.z,
		0,0,0,                  1
	};

	float sx = sin(camera->rotation.x);
	float cx = cos(camera->rotation.x);

	mat4 rotation_x = {
		1, 0,  0,0,
		0,cx,-sx,0,
		0,sx, cx,0,
		0, 0,  0,1
	};

	float sy = sin(camera->rotation.y);
	float cy = cos(camera->rotation.y);

	mat4 rotation_y = {
		cy,0,-sy,0,
		 0,1,  0,0,
		sy,0, cy,0,
		 0,0,  0,1
	};

	camera->rot_matrix = mul4m(rotation_x, rotation_y);
	camera->matrix = mul4m(camera->rot_matrix, translate);
}
