#version 330 core
in vec4 outColor;
in vec2 outTexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	vec2 outTexCoord1 = vec2( 1 * outTexCoord.x, outTexCoord.y );
    color = mix(texture(ourTexture1, outTexCoord1), texture(ourTexture2, outTexCoord1), 0.2);
}