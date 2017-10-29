#include "stdafx.h"

int main2( int argc, char* argv[] )
{
	float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f,
	};

	GLuint VAO, CubeVAO;
	GLuint VBO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );

	glGenBuffers( 1, &VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 3, GL_FLOAT, false, 3 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

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

	vec3 lightPos(1.2f, 1.0f, -2.0f);

	MainWhileStart
		glm::mat4 matView = g_MainCamera.GetViewMatrix();
		glm::mat4 matProjection = g_MainCamera.GetProjection((float)g_nWindowHeight, (float)g_nWindowWidth);

		glBindVertexArray(VAO);

		lightingShader.Use();
		lightingShader.SetValue("view", matView);
		lightingShader.SetValue("projection", matProjection);
		lightingShader.SetValue( "objectColor", vec3(1.0f, 0.5f, 0.31f));
		lightingShader.SetValue( "lightColor", vec3(1.0f, 1.0f, 1.0f));
		mat4 matLightModel( 1 );
		lightingShader.SetValue( "model", matLightModel );
		glDrawArrays( GL_TRIANGLES, 0, 36 );

		lampShader.Use();
		lampShader.SetValue("view", matView);
		lampShader.SetValue("projection", matProjection);
		mat4 matLampModel( 1 );
		matLampModel = translate( matLampModel, lightPos );
		matLampModel = scale(matLampModel, vec3(0.2f));
		lampShader.SetValue("model", matLampModel);
		glDrawArrays( GL_TRIANGLES, 0, 36 );
	MainWhileEnd
	return 0;
}