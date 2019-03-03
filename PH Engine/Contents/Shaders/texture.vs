#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 vert;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 vertbonedata;
layout (location = 4) in vec4 boneweights;

#define MAX_BONES 100

uniform mat4 BoneTransforms[MAX_BONES];


out vec2 texcoord;
out vec3 norm;
out vec3 pos;
out vec4 vertbonedata2;
out vec4 boneweights2;

void main()
{
	texcoord = uv;

	mat4 newTransform = mat4(0);
	
	int newx = int(vertbonedata.x);
	int newy = int(vertbonedata.y);
	int newz = int(vertbonedata.z);
	int neww = int(vertbonedata.w);
	newTransform += BoneTransforms[newx] * boneweights.x;
	newTransform += BoneTransforms[newy] * boneweights.y;
	newTransform += BoneTransforms[newz] * boneweights.z;
	newTransform += BoneTransforms[neww] * boneweights.w;
	
	if(newTransform == mat4(0.0f)){
		newTransform = mat4(1.0f);
	}

	vec4 newVert =  newTransform * vec4(vert, 1.0f);
	vec4 viewSpace = view * model * newVert; //vec4(mix(vert, vec3(newVert), 0.5f), 1.0f);



	vec4 newnorm =   newTransform * vec4(normal, 0.0f);
	norm = vec3(view * model * newnorm);
	
	
	vertbonedata2 = vertbonedata;
	boneweights2 = boneweights;
	
	
	
	//norm = vec3();
	gl_Position = projection * viewSpace;

	pos = viewSpace.xyz;
}