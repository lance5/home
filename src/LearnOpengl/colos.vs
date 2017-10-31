#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vOutNormal;
out vec3 vOutFragPos;

void main()
{
	gl_Position = projection * view * model * vec4( vPos, 1.0 );
	vOutFragPos = vec3( model * vec4( vPos, 1.0 ) );
	vOutNormal = mat3( transpose( inverse( model ) ) ) * vNormal;
}