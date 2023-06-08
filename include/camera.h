#ifndef CAMERA_H
#define CAMERA_H


#include <vector.h>


typedef struct Camera {
	vec3f position;
	vec3f rotation;
	mat4 projection;
	mat4 rot_matrix;
	mat4 matrix;
} Camera;

void update_camera_matrix(Camera*);


#endif // CAMERA_H
