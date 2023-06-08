#include <engine.h>
#include <shaders.h>
#include <object.h>
#include <camera.h>

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


GLFWwindow* current_window;
Camera* current_camera = NULL;

int render_program = 0;

int VBO;
int VAO;
int EBO;


void read_file(char*, char**, int*);


void init_engine(GLFWwindow* window) {
	change_window(window);
	update_resolution();
	reload_shaders();


	glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);


	unsigned int faces[] = {
		0,1,2,
		1,2,3,

		2,6,7,
		2,3,7,

		1,3,7,
		1,5,7,

		0,1,4,
		1,4,5,

		0,2,4,
		2,4,6,

		4,6,7,
		4,5,7,
	};


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glEnable(GL_DEPTH_TEST);
}


void change_window(GLFWwindow* window) {
	current_window = window;
	glfwMakeContextCurrent(window);
}


void update_resolution() {
	int w,h;
	glfwGetFramebufferSize(current_window, &w, &h);

	glViewport(0,0, w,h);
}


void reload_shaders() {
	char* vertex_source;
	char* fragment_source;

	read_file("render.vert", &vertex_source, NULL);
	read_file("render.frag", &fragment_source, NULL);

	int vertex_shader = create_shader(vertex_source, GL_VERTEX_SHADER);
	int fragment_shader = create_shader(fragment_source, GL_FRAGMENT_SHADER);

	render_program = create_program(2, (int[]){vertex_shader,fragment_shader});

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	free(vertex_source);
	free(fragment_source);
}


void set_current_camera(Camera* camera) {
	current_camera = camera;
}



void render_object(VObject object) {
	float vertices[8*3] = {
		-object.size*0.5,-object.size*0.5,-object.size*0.5,
		 object.size*0.5,-object.size*0.5,-object.size*0.5,
		-object.size*0.5, object.size*0.5,-object.size*0.5,
		 object.size*0.5, object.size*0.5,-object.size*0.5,
		-object.size*0.5,-object.size*0.5, object.size*0.5,
		 object.size*0.5,-object.size*0.5, object.size*0.5,
		-object.size*0.5, object.size*0.5, object.size*0.5,
		 object.size*0.5, object.size*0.5, object.size*0.5,
	};

	glUseProgram(render_program);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 8*3*4, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glUniformMatrix4fv(1, 1, GL_FALSE, &current_camera->projection);
	glUniformMatrix4fv(2, 1, GL_FALSE, &current_camera->matrix);


	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, object.texture);

	glUniform3fv(10, 1, &current_camera->position);
	glUniform3fv(11, 1, &object.position);
	glUniform1iv(13, 1, &object.size);


	glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0);

	glUseProgram(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_3D, 0);
}



void read_file(char* filename, char** buffer, int* size) {
	int f = open(filename, O_RDONLY);

	if (f == -1) {
		perror("open");
		exit(errno);
	}

	struct stat st;
	fstat(f, &st);

	if (size != NULL)
		*size = st.st_size+1;

	*buffer = calloc(st.st_size+1,1);

	read(f, *buffer, st.st_size);

	close(f);
}
