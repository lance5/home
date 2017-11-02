#version 330 core
struct Material 
{
	sampler2D	diffuse;
	sampler2D	specular;
	sampler2D	emission;
	float		shininess;
};

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
vec3 CalcDirLight( DirLight light, vec3 vNormal, vec3 vViewDir, float shininess, vec3 TexDiffuse, vec3 TexSpecular )
{
	vec3 lightDir = normalize( -light.direction );
	float diff = max( dot( vNormal, lightDir ), 0.0 );
	vec3 reflectDir = reflect( -lightDir, vNormal );
	float spec = pow( max( dot( vViewDir, reflectDir ), 0.0 ), shininess );
	vec3 ambient = light.ambient * TexDiffuse;
	vec3 diffuse = light.diffuse * diff * TexDiffuse;
	vec3 specular = light.specular * spec * TexSpecular;
	return ambient + diffuse + specular;
}

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
vec3 CalcPointLight( PointLight light, vec3 vNormal, vec3 vFragPos, vec3 vViewDir, float shininess, vec3 TexDiffuse, vec3 TexSpecular )
{
	vec3 lightDir = normalize( light.position - vFragPos );
	float diff = max( dot( vNormal, lightDir ), 0.0 );
	vec3 reflectDir = reflect( -lightDir, vNormal );
	float spec = pow( max( dot( vViewDir, reflectDir ), 0.0 ), shininess );
	float distance = length( light.position - vFragPos );
	float attenuation = 1.0 / (light.constant + light.linear * distance + 
		light.quadratic * ( distance * distance ) );

	vec3 ambient = light.ambient * TexDiffuse;
	vec3 diffuse = light.diffuse * diff * TexDiffuse;
	vec3 specular = light.specular * spec * TexSpecular;

	return ( ambient + diffuse + specular ) * attenuation;
}

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
vec3 CalcSpotLight( SpotLight light, vec3 vNormal, vec3 vFragPos, vec3 vViewDir, float shininess, vec3 TexDiffuse, vec3 TexSpecular )
{
	vec3 lightDir = normalize( light.position - vFragPos );
	float theta = dot( lightDir, normalize( -light.direction ) );
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp( ( theta - light.outerCutOff ) / epsilon, 0.0, 1.0 );

	vec3 reflectDir = reflect( -lightDir, vNormal );
	float spec = pow( max( dot( vViewDir, reflectDir ), 0.0 ), shininess );
	float diff = max( dot( vNormal, lightDir ), 0.0 );

	vec3 ambient = light.ambient * TexDiffuse;
	vec3 diffuse = light.diffuse * diff * TexDiffuse;
	vec3 specular = light.specular * spec * TexSpecular;

	diffuse *= intensity;
	specular *= intensity;

	return  ambient + diffuse + specular;
}

uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform Material material;
out vec4 FragColor;
uniform vec3 viewPos;
in vec3 vOutNormal;
in vec3 vOutFragPos;
in vec2 vOutTexCoords;

void main()
{
	vec3 TexDiffuse = texture( material.diffuse, vOutTexCoords ).rgb;
	vec3 TexSpecular = texture( material.specular, vOutTexCoords ).rgb;
	vec3 TexEmission = texture( material.emission, vOutTexCoords ).rgb;
	vec3 vNormal = normalize( vOutNormal );
	vec3 vViewDir = normalize( viewPos - vOutFragPos );

	vec3 result = CalcDirLight( dirLight, vNormal, vViewDir, material.shininess, TexDiffuse, TexSpecular );
	
	for( int i = 0; i < NR_POINT_LIGHTS; ++i )
		result += CalcPointLight( pointLights[i], vNormal, vOutFragPos, vViewDir, material.shininess, TexDiffuse, TexSpecular );

	result += CalcSpotLight( spotLight, vNormal, vOutFragPos, vViewDir, material.shininess, TexDiffuse, TexSpecular );

	FragColor = vec4( result, 1.0 );
}