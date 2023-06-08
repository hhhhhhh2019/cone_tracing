#include <vector.h>
#include <math.h>


vec2f sum2f(vec2f a, vec2f b) {
	return (vec2f){a.x+b.x, a.y+b.y};
}

vec2f sub2f(vec2f a, vec2f b) {
	return (vec2f){a.x-b.x, a.y-b.y};
}

vec2f mul2f(vec2f a, vec2f b) {
	return (vec2f){a.x*b.x, a.y*b.y};
}

vec2f div2f(vec2f a, vec2f b) {
	return (vec2f){a.x/b.x, a.y/b.y};
}

vec2f mul2fs(vec2f a, float b) {
	return (vec2f){a.x*b, a.y*b};
}


vec3f sum3f(vec3f a, vec3f b) {
	return (vec3f){a.x+b.x, a.y+b.y, a.z+b.z};
}

vec3f sub3f(vec3f a, vec3f b) {
	return (vec3f){a.x-b.x, a.y-b.y, a.z-b.z};
}

vec3f mul3f(vec3f a, vec3f b) {
	return (vec3f){a.x*b.x, a.y*b.y, a.z*b.z};
}

vec3f div3f(vec3f a, vec3f b) {
	return (vec3f){a.x/b.x, a.y/b.y, a.z/b.z};
}

vec3f mul3fs(vec3f a, float b) {
	return (vec3f){a.x*b, a.y*b, a.z*b};
}

vec3f mul3fm(vec3f a, mat3 b) {
	return (vec3f){
		a.x * b.a + a.y * b.b + a.z * b.c,
		a.x * b.d + a.y * b.e + a.z * b.f,
		a.x * b.g + a.y * b.h + a.z * b.i
	};
}


vec4f sum4f(vec4f a, vec4f b) {
	return (vec4f){a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w};
}

vec4f sub4f(vec4f a, vec4f b) {
	return (vec4f){a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w};
}

vec4f mul4f(vec4f a, vec4f b) {
	return (vec4f){a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w};
}

vec4f div4f(vec4f a, vec4f b) {
	return (vec4f){a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w};
}

vec4f mul4fs(vec4f a, float b) {
	return (vec4f){a.x*b, a.y*b, a.z*b, a.w*b};
}

vec4f mul4fm(vec4f a, mat4 b) {
	return (vec4f){
		a.x * b.a + a.y * b.b + a.z * b.c + a.w * b.d,
		a.x * b.e + a.y * b.f + a.z * b.g + a.w * b.h,
		a.x * b.i + a.y * b.j + a.z * b.k + a.w * b.l,
		a.x * b.m + a.y * b.n + a.z * b.o + a.w * b.p,
	};
}


mat2 mul2m(mat2 a, mat2 b) {
	return (mat2){
		a.a * b.a + a.b * b.c,
		a.a * b.b + a.b * b.d,

		a.c * b.a + a.d * b.c,
		a.c * b.b + a.d * b.d,
	};
}


mat3 mul3m(mat3 a, mat3 b) {
	return (mat3){
		a.a * b.a + a.b * b.d + a.c * b.g,
		a.a * b.b + a.b * b.e + a.c * b.h,
		a.a * b.c + a.b * b.f + a.c * b.i,

		a.d * b.a + a.e * b.d + a.f * b.g,
		a.d * b.b + a.e * b.e + a.f * b.h,
		a.d * b.c + a.e * b.f + a.f * b.i,

		a.g * b.a + a.h * b.d + a.i * b.g,
		a.g * b.b + a.h * b.e + a.i * b.h,
		a.g * b.c + a.h * b.f + a.i * b.i,
	};
}


mat4 mul4m(mat4 a, mat4 b) {
	return (mat4){
		a.a * b.a + a.b * b.e + a.c * b.i + a.d * b.m,
		a.a * b.b + a.b * b.f + a.c * b.j + a.d * b.n,
		a.a * b.c + a.b * b.g + a.c * b.k + a.d * b.o,
		a.a * b.d + a.b * b.h + a.c * b.l + a.d * b.p,

		a.e * b.a + a.f * b.e + a.g * b.i + a.h * b.m,
		a.e * b.b + a.f * b.f + a.g * b.j + a.h * b.n,
		a.e * b.c + a.f * b.g + a.g * b.k + a.h * b.o,
		a.e * b.d + a.f * b.h + a.g * b.l + a.h * b.p,

		a.i * b.a + a.j * b.e + a.k * b.i + a.l * b.m,
		a.i * b.b + a.j * b.f + a.k * b.j + a.l * b.n,
		a.i * b.c + a.j * b.g + a.k * b.k + a.l * b.o,
		a.i * b.d + a.j * b.h + a.k * b.l + a.l * b.p,

		a.m * b.a + a.n * b.e + a.o * b.i + a.p * b.m,
		a.m * b.b + a.n * b.f + a.o * b.j + a.p * b.n,
		a.m * b.c + a.n * b.g + a.o * b.k + a.p * b.o,
		a.m * b.d + a.n * b.h + a.o * b.l + a.p * b.p,
	};
}


mat4 perspective(float fov, float asp, float n, float f) {
	return (mat4){
		1./tan(fov/2)/asp,             0,              0, 0,
		                0, 1./tan(fov/2),              0, 0,
		                0,             0,              0, 0,
		                0,             0,              1, 0
	};
}


mat4 ortho(float size, float asp, float n, float f) {
	return (mat4){
		1./size/asp,      0,              0, 0,
		         0, 1./size,              0, 0,
		         0,       0,              1, 0,
		         0,       0,              0, 1
	};
}
