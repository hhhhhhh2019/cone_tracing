#ifndef ENGINE_H
#define ENGINE_H


#include <GLFW/glfw3.h>

#include <object.h>
#include <camera.h>


void init_engine(GLFWwindow*);
void change_window(GLFWwindow*);
void update_resolution();

void reload_shaders();

void set_current_camera(Camera*);
void render_object(VObject);


#endif // ENGINE_H
