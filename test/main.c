#include <GLFW/glfw3.h>

#include <stdio.h>
#include <errno.h>
#include <math.h>

#include <engine.h>


float camera_speed = 1.;
float camera_rot_speed = 0.01;


float last_time;
float delta = 0;

char first_mouse = 1;


int width = 720;
int height = 720;

GLFWwindow* window;

VObject obj1;
Camera camera1 = {(vec3f){0,0,-2}, (vec3f){0,0,0}};

vec3f camera_vel = {0,0,0};


void window_size_callback(GLFWwindow*,int,int);
void key_callback(GLFWwindow*, int, int, int, int);
void cursor_position_callback(GLFWwindow*, double, double);

void update();
void render();


int main() {
	if (!glfwInit()) {
		printf("GLFW init failed!\n");
		return errno;
	}

	camera1.projection = perspective(3.14159 * 0.5, (float)width/(float)height, 0.001, 1000);

	window = glfwCreateWindow(width, height, "Engine", NULL, NULL);
	glfwSetCursorPos(window, 1000,1000);
	glfwSetFramebufferSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursor_position_callback);


	init_engine(window);
	set_current_camera(&camera1);


	load_object_from_file(&obj1, "object.mdl");


	while (!glfwWindowShouldClose(window)) {
		float current_time = glfwGetTime();
		delta = current_time - last_time;
		last_time = current_time;

		update();
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();

		glfwSetCursorPos(window, 1000,1000);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}


void window_size_callback(GLFWwindow*, int w, int h) {
	width  = w;
	height = h;

	update_resolution();

	camera1.projection = perspective(3.14159 * 0.5, (float)width/(float)height, 0.001, 1000);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_W)
			camera_vel.z = 1;
		if (key == GLFW_KEY_S)
			camera_vel.z = -1;
		if (key == GLFW_KEY_A)
			camera_vel.x = -1;
		if (key == GLFW_KEY_D)
			camera_vel.x = 1;
		if (key == GLFW_KEY_Q)
			camera_vel.y = 1;
		if (key == GLFW_KEY_E)
			camera_vel.y = -1;
	}

	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W)
			camera_vel.z = 0;
		if (key == GLFW_KEY_S)
			camera_vel.z = 0;
		if (key == GLFW_KEY_A)
			camera_vel.x = 0;
		if (key == GLFW_KEY_D)
			camera_vel.x = 0;
		if (key == GLFW_KEY_Q)
			camera_vel.y = 0;
		if (key == GLFW_KEY_E)
			camera_vel.y = 0;
	}
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	if (first_mouse == 0) {
		camera1.rotation.x -= (ypos - 1000) * camera_rot_speed;
		camera1.rotation.y += (xpos - 1000) * camera_rot_speed;
	}

	first_mouse = 0;
}


void update() {
	update_camera_matrix(&camera1);


	float sx = sin(-camera1.rotation.x);
	float cx = cos(-camera1.rotation.x);

	mat3 rotation_x = {
		1, 0,  0,
		0,cx,-sx,
		0,sx, cx,
	};

	float sy = sin(-camera1.rotation.y);
	float cy = cos(-camera1.rotation.y);

	mat3 rotation_y = {
		cy,0,-sy,
		 0,1,  0,
		sy,0, cy,
	};


	if (delta != 0)
		camera1.position = sum3f(camera1.position, mul3fs(mul3fm(mul3fm(camera_vel, rotation_x), rotation_y), camera_speed * delta));
}


void render() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render_object(obj1);
}
