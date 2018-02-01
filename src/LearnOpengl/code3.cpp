#include "stdafx.h"
#include <Common/CResourceModel.h>

int main3( int argc, char* argv[] )
{
	CResourceModel ResModel;
	CFileManage::Inst().Load( "nanosuit/nanosuit.obj", ResModel );

	GLuint VAO, CubeVAO;
	GLuint VBO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );

	glGenBuffers( 1, &VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)( 3 * sizeof( float ) ) );
	glEnableVertexAttribArray( 1 );

	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)( 6 * sizeof( float ) ) );
	glEnableVertexAttribArray( 2 );

	glGenVertexArrays( 1, &CubeVAO );
	glBindVertexArray( CubeVAO );

	glBindBuffer( GL_ARRAY_BUFFER, CubeVAO );

	glVertexAttribPointer( 0, 3, GL_FLOAT, false, 8 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, nDiffuseMap );
	glActiveTexture( GL_TEXTURE1 );
	glBindTexture( GL_TEXTURE_2D, nSpecularMap );
	glActiveTexture( GL_TEXTURE2 );
	glBindTexture( GL_TEXTURE_2D, nEmissionMap );

	const char* szLightPath[eShader_Count] = 
	{
		"colos.vs",
		"colos.fs",
		nullptr,
	};
	CShader lightingShader(szLightPath);

	const char* szLampPath[eShader_Count] =
	{
		"colos.vs",
		"lamp.fs",
		nullptr,
	};
	CShader lampShader(szLampPath);

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	glm::vec3 pointLightPositions[] = {
		glm::vec3( 0.7f,  0.2f,  2.0f),
		glm::vec3( 2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3( 0.0f,  0.0f, -3.0f)
	};
	vec3 ambient( 0.1f );
	vec3 diffuse( 0.5f );
	vec3 specular( 1.0f, 1.0f, 1.0f );
	MainWhileStart
		glm::mat4 matView = g_MainCamera.GetViewMatrix();
	glm::mat4 matProjection = g_MainCamera.GetProjection((float)g_nWindowWidth, (float)g_nWindowHeight);

	lightingShader.Use();
	lightingShader.SetValue("view", matView);
	lightingShader.SetValue("projection", matProjection);
	lightingShader.SetValue( "viewPos", g_MainCamera.GetPosition() );

	lightingShader.SetValue( "material.diffuse", 0 );
	lightingShader.SetValue( "material.specular", 1 );
	lightingShader.SetValue( "material.emission", 2 );
	lightingShader.SetValue( "material.shininess", 32.0f );

	lightingShader.SetValue( "dirLight.direction", vec3( -0.2f, -1.0f, -0.3f ) );
	lightingShader.SetValue( "dirLight.ambient", ambient );
	lightingShader.SetValue( "dirLight.diffuse", diffuse );
	lightingShader.SetValue( "dirLight.specular", specular );

	lightingShader.SetValue( "pointLights[0].position", pointLightPositions[0] );
	lightingShader.SetValue( "pointLights[0].constant", 1.0f );
	lightingShader.SetValue( "pointLights[0].linear", 0.09f );
	lightingShader.SetValue( "pointLights[0].quadratic", 0.032f );
	lightingShader.SetValue( "pointLights[0].ambient", ambient );
	lightingShader.SetValue( "pointLights[0].diffuse", diffuse );
	lightingShader.SetValue( "pointLights[0].specular", specular );

	lightingShader.SetValue( "pointLights[1].position", pointLightPositions[1] );
	lightingShader.SetValue( "pointLights[1].constant", 1.0f );
	lightingShader.SetValue( "pointLights[1].linear", 0.09f );
	lightingShader.SetValue( "pointLights[1].quadratic", 0.032f );
	lightingShader.SetValue( "pointLights[1].ambient", ambient );
	lightingShader.SetValue( "pointLights[1].diffuse", diffuse );
	lightingShader.SetValue( "pointLights[1].specular", specular );

	lightingShader.SetValue( "pointLights[2].position", pointLightPositions[2] );
	lightingShader.SetValue( "pointLights[2].constant", 1.0f );
	lightingShader.SetValue( "pointLights[2].linear", 0.09f );
	lightingShader.SetValue( "pointLights[2].quadratic", 0.032f );
	lightingShader.SetValue( "pointLights[2].ambient", ambient );
	lightingShader.SetValue( "pointLights[2].diffuse", diffuse );
	lightingShader.SetValue( "pointLights[2].specular", specular );

	lightingShader.SetValue( "pointLights[3].position", pointLightPositions[3] );
	lightingShader.SetValue( "pointLights[3].constant", 1.0f );
	lightingShader.SetValue( "pointLights[3].linear", 0.09f );
	lightingShader.SetValue( "pointLights[3].quadratic", 0.032f );
	lightingShader.SetValue( "pointLights[3].ambient", ambient );
	lightingShader.SetValue( "pointLights[3].diffuse", diffuse );
	lightingShader.SetValue( "pointLights[3].specular", specular );

	lightingShader.SetValue( "spotLight.position", g_MainCamera.GetPosition() );
	lightingShader.SetValue( "spotLight.direction", g_MainCamera.GetFront() );
	lightingShader.SetValue( "spotLight.cutOff", cos(radians(12.5f)));
	lightingShader.SetValue( "spotLight.outerCutOff", cos(radians(17.5f )));
	lightingShader.SetValue( "spotLight.ambient", ambient );
	lightingShader.SetValue( "spotLight.diffuse", diffuse );
	lightingShader.SetValue( "spotLight.specular", specular );

	for (int i = 0; i < 10; ++i)
	{
		mat4 model(1);
		model = translate( model, cubePositions[i] );
		float angle = 20.0f * i;
		model = rotate( model, radians( angle ), vec3( 1.0f, 0.3f, 0.5f ) );
		lightingShader.SetValue("model", model);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	for (int i = 0; i < 4; ++i)
	{
		lampShader.Use();
		lampShader.SetValue("view", matView);
		lampShader.SetValue("projection", matProjection);
		mat4 matLampModel( 1 );
		matLampModel = translate( matLampModel, pointLightPositions[i] );
		matLampModel = scale(matLampModel, vec3(0.2f));
		lampShader.SetValue("model", matLampModel);
		glBindVertexArray( CubeVAO );
		glDrawArrays( GL_TRIANGLES, 0, 36 );
	}

	MainWhileEnd
		return 0;
}