#ifndef VOBJECT_H
#define VOBJECT_H


#include <vector.h>


typedef struct VObject {
	int size;
	vec3f position;

	int texture;
	float* data;
} VObject;


void load_object_from_file(VObject*, char*);


#endif // VOBJECT_H
