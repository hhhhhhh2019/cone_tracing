#include <stdio.h>

#include <GL/gl.h>


int create_shader(char* source, int type) {
	int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[2048];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 2048, NULL, infoLog);
		printf("error: shader compilation failed:\n%s\n", infoLog);
	}

	return shader;
}


int create_program(int count, int shaders[]) {
	unsigned int prog = glCreateProgram();
	for (int i = 0; i < count; i++)
		glAttachShader(prog, shaders[i]);
	glLinkProgram(prog);

	int success;
	char infoLog[2048];
	glGetProgramiv(prog, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(prog, 2048, NULL, infoLog);
		printf("error: program linking failed:\n%s\n", infoLog);
	}

	return prog;
}
