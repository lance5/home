#version 330 core
struct Material 
{
	sampler2D	diffuse;
	sampler2D	specular;
	sampler2D	emission;
	float		shininess;
};

struct LightColor
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	float constant;
	float linear;
	float quadratic;
};

struct ParallelLight
{
	vec3 direction;
};

struct Spotlight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
};

uniform Material material;
uniform LightColor lightColor;
uniform ParallelLight paralleLight;
uniform PointLight pointLight;
uniform Spotlight spotLight;

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
	vec3 norm = normalize( vOutNormal );

	vec3 lightVector = pointLight.position - vOutFragPos;
	float distance = length( lightVector );
	float attenuation = 1.0 / ( pointLight.constant + pointLight.linear * distance + 
		pointLight.quadratic * ( distance * distance ) );
	//vec3 lightDir = normalize( lightVector );

	//vec3 lightDir = normalize( -paralleLight.direction );

	vec3 lightDir = normalize( spotLight.position - vOutFragPos );
	float theta = dot( lightDir, normalize( -spotLight.direction ) );
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp( ( theta - spotLight.outerCutOff ) / epsilon, 0.0, 1.0 );
	
	float diff = max( dot( norm, lightDir ), 0.0 );
	vec3 diffuse = lightColor.diffuse * diff * TexDiffuse;
	
	vec3 viewDir = normalize( viewPos - vOutFragPos );
	vec3 reflectDir = reflect( -lightDir, norm );
	float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), material.shininess );
	vec3 specular = lightColor.specular * spec *  TexSpecular;
	
	vec3 ambient = lightColor.ambient * TexDiffuse;
	diffuse *= intensity;
	specular *= intensity;

	vec3 result = ambient + diffuse + specular;
	result *= attenuation;

	FragColor = vec4( result, 1.0 );
}