#include "stdafx.h"

int main2( int argc, char* argv[] )
{
	float vertices[] = {    
	// positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

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

	GLuint nDiffuseMap = loadTexture( "./../../res/container2.png" );	
	GLuint nSpecularMap = loadTexture( "./../../res/container2_specular.png" );
	GLuint nEmissionMap = loadTexture( "./../../res/matrix.jpg" );
	
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
	
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
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

		lightingShader.SetValue( "lightColor.ambient", vec3( 0.1f ) );
		lightingShader.SetValue( "lightColor.diffuse", vec3( 0.5f ) );
		lightingShader.SetValue( "lightColor.specular", vec3( 1.0f, 1.0f, 1.0f ) );

		//lightingShader.SetValue( "paralleLight.direction", vec3( -0.2f, -1.0f, -0.3f ) );
		
		lightingShader.SetValue( "pointLight.position", lightPos );
		lightingShader.SetValue( "pointLight.constant", 1.0f );
		lightingShader.SetValue( "pointLight.linear", 0.09f );
		lightingShader.SetValue( "pointLight.quadratic", 0.032f );
		
		lightingShader.SetValue( "spotLight.position", g_MainCamera.GetPosition() );
		lightingShader.SetValue( "spotLight.direction", g_MainCamera.GetFront() );
		lightingShader.SetValue( "spotLight.cutOff", cos( radians( 12.5f  ) ) );

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

		lampShader.Use();
		lampShader.SetValue("view", matView);
		lampShader.SetValue("projection", matProjection);
		mat4 matLampModel( 1 );
		matLampModel = translate( matLampModel, lightPos );
		matLampModel = scale(matLampModel, vec3(0.2f));
		lampShader.SetValue("model", matLampModel);
		glBindVertexArray( CubeVAO );
		glDrawArrays( GL_TRIANGLES, 0, 36 );
	MainWhileEnd
	return 0;
}