#ifndef VECTOR_H
#define VECTOR_H



typedef union {
	struct {float x,y;};
	float data[2];
} vec2f;

#define vec2f(vx,vy,vz) (vec2f){.x=vx,.y=vy}


typedef union {
	struct {float x,y,z;};
	float data[3];
} vec3f;

#define vec3f(vx,vy,vz) (vec3f){.x=vx,.y=vy,.z=vz}


typedef union {
	struct {float x,y,z,w;};
	float data[4];
} vec4f;

#define vec4f(vx,vy,vz,vw) (vec4f){.x=vx,.y=vy,.z=vz,.w=vw}


typedef struct {
	float a,b, c,d;
} mat2;

typedef struct {
	float a,b,c, d,e,f, g,h,i;
} mat3;

typedef struct {
	float a,b,c,d, e,f,g,h, i,j,k,l, m,n,o,p;
} mat4;


vec2f sum2f(vec2f, vec2f);
vec2f sub2f(vec2f, vec2f);
vec2f mul2f(vec2f, vec2f);
vec2f div2f(vec2f, vec2f);

vec2f mul2fs(vec2f, float);

vec2f mul2fm(vec2f, mat2);

float length2(vec2f);
vec2f normalize2(vec2f);


vec3f sum3f(vec3f, vec3f);
vec3f sub3f(vec3f, vec3f);
vec3f mul3f(vec3f, vec3f);
vec3f div3f(vec3f, vec3f);

vec3f mul3fs(vec3f, float);

vec3f mul3fm(vec3f, mat3);

float length3(vec3f);
vec3f normalize3(vec3f);


vec4f sum4f(vec4f, vec4f);
vec4f sub4f(vec4f, vec4f);
vec4f mul4f(vec4f, vec4f);
vec4f div4f(vec4f, vec4f);

vec4f mul4fs(vec4f, float);

vec4f mul4fm(vec4f, mat4);

float length4(vec4f);
vec4f normalize4(vec4f);


mat2 mul2m(mat2, mat2);
mat3 mul3m(mat3, mat3);
mat4 mul4m(mat4, mat4);


mat4 perspective(float fov, float asp, float near, float far);
mat4 ortho(float size, float asp, float near, float far);


#endif // VECTOR_H
