#include <object.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include <GL/gl.h>


void init_object(VObject* obj) {
	glGenTextures(1, &obj->texture);

	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, obj->texture);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//GL_NEAREST_MIPMAP_NEAREST GL_LINEAR_MIPMAP_LINEAR
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32F, obj->size,obj->size,obj->size, 0, GL_RGBA, GL_FLOAT, obj->data);
	glGenerateMipmap(GL_TEXTURE_3D);

	//glActiveTexture(0);
}


void load_object_from_file(VObject* obj, char* filename) {
	int f = open(filename, O_RDONLY);

	if (f == -1) {
		perror("open");
		exit(errno);
	}

	read(f, &obj->size, 4);
	obj->data = malloc(obj->size*obj->size*obj->size*4*4);
	read(f, obj->data, obj->size*obj->size*obj->size*4*4);

	close(f);

	init_object(obj);
}
