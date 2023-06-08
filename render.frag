#version 460 core


in vec3 vertex_pos;

out vec4 color;
layout (depth_greater) out float gl_FragDepth;

layout (location = 10) uniform vec3 camera_pos;
layout (location = 11) uniform vec3 global_pos;
layout (location = 12) uniform sampler3D voxels;
layout (location = 13) uniform int size;


#define TSQRT2 2.828427
#define SQRT2 1.414213
#define ISQRT2 0.707106

float VOXEL_SIZE = 1./float(size);


bool isInsideCube(const vec3 p, float e) { return abs(p.x) < e && abs(p.y) < e && abs(p.z) < e; }


float get_dist(vec3 ro, vec3 rd) {
	float dist = 0;
	vec4 acc = vec4(0);

	while (dist < 2. && acc.a < 1) {
		vec3 p = ro + rd * dist;
		p = p * 0.5 + 0.5;

		vec4 v = textureLod(voxels, p, 0);

		acc += v;

		dist += VOXEL_SIZE;
	}

	return dist;
}


vec4 get_diffuse(vec3 ro, vec3 rd, float spread) {
	vec4 acc = vec4(0);
	float dist = 0.1953125;

	while(dist < SQRT2 && acc.a < 1){
		vec3 p = ro + rd * dist;
		p = p * 0.5 + 0.5;
		float l = 1 + spread * dist / VOXEL_SIZE;
		float level = log2(l);
		float ll = (level + 1) * (level + 1);
		vec4 voxel = textureLod(voxels, p, level);
		acc += 0.075 * ll * voxel * pow(1 - voxel.a, 2);
		dist += ll * VOXEL_SIZE * 2;
	}

	return pow(acc * 2.0, vec4(1.5));
}


vec4 get_specular(vec3 ro, vec3 rd) {
	vec4 acc = vec4(0);
	float dist = 0;

	while (dist < 2 && acc.a < 1.) {
		vec3 p = ro + rd * dist;
		p = p * 0.5 + 0.5;
		float level = 0.01 * log2(1 + dist / VOXEL_SIZE);
		vec4 v = textureLod(voxels, p, 0);
		float f = 1. - acc.a;
		acc.rgb += v.rgb * v.a * f;
		acc.a += v.a * f;
		dist += VOXEL_SIZE * (1.0f + 0.125f * level);
	}

	return acc;
}


vec4 get_shadow(vec3 ro, vec3 rd, float shadow_dist) {
	float acc = 0;
	float dist = VOXEL_SIZE * 3;

	while (dist <= shadow_dist) {
		vec3 p = ro + rd * dist;
		p = p * 0.5 + 0.5;

		float l = dist;

		float v1 = textureLod(voxels, p, 1 + 0.75 * l).a;

		acc += (1 - acc) * v1;

		dist += 0.9 * VOXEL_SIZE * (1 + 0.05 * l);
	}

	return vec4(1 - acc);
}


void main() {
	vec3 rd = normalize(global_pos + vertex_pos - camera_pos);
	vec3 ro = camera_pos - global_pos + rd * max(0, length(camera_pos) - 1.1);

	vec4 diffuse = get_diffuse(camera_pos,rd, 0.01);
	vec4 specular = get_specular(ro,rd);

	float dist = get_dist(ro,rd);

	vec4 shadow = get_shadow(ro+rd*dist, vec3(0,1,0), 2);

	gl_FragDepth = dist * 0.01;

	color = specular;// + diffuse * 0.5;
	//color *= shadow;

	color = pow(color, vec4(1./2.2));
}
