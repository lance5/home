#include <iostream>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;

struct ShaderInfo
{
	GLenum		nType;
	const char*	szName;
};

GLint LoadShaders( const ShaderInfo aryInfo[] )
{
	GLuint		aryShader[12];
	int			nLength = 0;

	for( int i = 0; true; ++i )
	{
		const ShaderInfo& info = aryInfo[i];
		if( info.nType == GL_NONE || info.szName == NULL )
			break;

		GLuint nShader = glCreateShader( info.nType );
		glShaderSource( nShader, 1, &info.szName, NULL );
		glCompileShader( nShader );
		GLint nError = GL_TRUE;
		glGetShaderiv( nShader, GL_COMPILE_STATUS, &nError );
		if( nError != GL_TRUE )
		{
			char szBuffer[2048];
			GLsizei nLength = 0;
			glGetShaderInfoLog( nShader, 2048, &nLength, szBuffer );
			fprintf( stderr, szBuffer );
			fprintf( stderr, "\n" );
			break;
		}

		aryShader[nLength++] = nShader;
	}

	GLuint nProgram = glCreateProgram();
	for( int i = 0; i < nLength; ++i )
		glAttachShader( nProgram, aryShader[i] );
	glLinkProgram( nProgram );

	GLint nError = GL_TRUE;
	glGetProgramiv( nProgram, GL_LINK_STATUS, &nError );
	if( nError != GL_TRUE )
	{
		char szBuffer[2048];
		GLsizei nLength = 0;
		glGetProgramInfoLog( nProgram, 2048, &nLength, szBuffer );
		fprintf( stderr, szBuffer );
		fprintf( stderr, "\n" );
		return 0;
	}

	for( int i = 0; i < nLength; ++i )
		glDeleteShader( aryShader[i] );

	return nProgram;
}

void			Displayer();
void			framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow*		InitWindow();
void			InitOpenGL();

int main()
{
	GLFWwindow* pWindow = InitWindow();
	if( !pWindow )
		return 0;
	InitOpenGL();

	while(!glfwWindowShouldClose( pWindow ) )
	{
		glfwSwapBuffers( pWindow );
		glfwPollEvents(); 
		Displayer();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* InitWindow()
{
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	GLFWwindow* pWindow = glfwCreateWindow( 800, 600, "LearnOpenGL", nullptr, nullptr );
	if (pWindow == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent( pWindow );

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}

	glViewport( 0, 0, 800, 800 );
	glfwSetFramebufferSizeCallback( pWindow, framebuffer_size_callback );
	return pWindow;
}

size_t TypeSize( GLenum type )
{
	size_t size;

#define CASE( Enum, Count, Type ) \
case Enum: size = Count * sizeof( Type ); break

	switch( type )
	{
		CASE( GL_FLOAT,					1,	GLfloat );
		CASE( GL_FLOAT_VEC2,			2,	GLfloat );
		CASE( GL_FLOAT_VEC3,			3,	GLfloat );
		CASE( GL_FLOAT_VEC4,			4,	GLfloat );
		CASE( GL_INT,					1,	GLint );
		CASE( GL_INT_VEC2,				2,	GLint );
		CASE( GL_INT_VEC3,				3,	GLint );
		CASE( GL_INT_VEC4,				4,	GLint );
		CASE( GL_UNSIGNED_INT,			1,	GLuint );
		CASE( GL_UNSIGNED_INT_VEC2,		2,	GLuint );
		CASE( GL_UNSIGNED_INT_VEC3,		3,	GLuint );
		CASE( GL_UNSIGNED_INT_VEC4,		4,	GLuint );
		CASE( GL_BOOL,					1,	GLboolean );
		CASE( GL_BOOL_VEC2,				2,	GLboolean );
		CASE( GL_BOOL_VEC3,				3,	GLboolean );
		CASE( GL_BOOL_VEC4,				4,	GLboolean );
		CASE( GL_FLOAT_MAT2,			4,	GLfloat );
		CASE( GL_FLOAT_MAT2x3,			6,	GLfloat );
		CASE( GL_FLOAT_MAT2x4,			8,	GLfloat );
		CASE( GL_FLOAT_MAT3,			9,	GLfloat );
		CASE( GL_FLOAT_MAT3x2,			6,	GLfloat );
		CASE( GL_FLOAT_MAT3x4,			12,	GLfloat );
		CASE( GL_FLOAT_MAT4,			16,	GLfloat );
		CASE( GL_FLOAT_MAT4x2,			8,	GLfloat );
		CASE( GL_FLOAT_MAT4x3,			12,	GLfloat );
#undef CASE

	default:
		fprintf( stderr, "Unknown type: 0x%x\n", type );
		exit( EXIT_FAILURE );
		break;
	}
	return size;
}

const char* vShader = 
"#version 330 core\n"
"uniform Uniforms {"
"	vec3	translation;"
"	float	scale;"
"	vec4	rotation;"
"	bool	enabled;"
"};"
"in vec2 vPos;"
"in vec3 vColor;"
"out vec4 fColor;"
"void main()"
"{"
"	vec3 pos = vec3( vPos, 0.0 );"
"	float angle = radians( rotation[0] );"
"	vec3 axis = normalize( rotation.yzw );"
"	mat3 I = mat3( 1.0 );"
"	mat3 S = mat3( 0, -axis.z, axis.y,"
"					axis.z, 0, -axis.x,"
"					-axis.y, axis.x, 0 );"
"	mat3 uuT = outerProduct( axis, axis );"
"	mat3 rot = uuT + cos( angle ) * ( I - uuT )"
"					+ sin( angle ) * S;"
"	pos *= scale;"
"	pos *= rot;"
"	pos += translation;"
"	fColor = vec4( scale, scale, scale, 1 );"
"	gl_Position = vec4( pos, 1 );"
"}";

const char* fShader = 
"#version 330 core\n"
"uniform Uniforms {"
"	vec3	translation;"
"	float	scale;"
"	vec4	rotation;"
"	bool	enabled;"
"};"
"in vec4 fColor;"
"out vec4 color;"
"void main()"
"{"
"	color = fColor;"
"}";

void InitOpenGL()
{
	glClearColor( 1, 0, 0, 1 );
	ShaderInfo shaders[] = 
	{
		{ GL_VERTEX_SHADER, vShader },
		{ GL_FRAGMENT_SHADER, fShader },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders( shaders );
	glUseProgram( program );

	GLuint	uBoIndex;
	GLint	uBoSize;
	GLuint	uBo;
	GLchar*	pBuffer;

	uBoIndex = glGetUniformBlockIndex( program, "Uniforms" );
	if( uBoIndex == GL_INVALID_INDEX )
	{
		fprintf( stderr, "Invalid Index.\n" );
		exit( EXIT_FAILURE );
		return;
	}
	glGetActiveUniformBlockiv( program, uBoIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uBoSize );
	pBuffer = (GLchar*)malloc( uBoSize );

	if( pBuffer == NULL )
	{
		fprintf( stderr, "Unable to allocate buffer\n" );
		exit( EXIT_FAILURE );
		return;
	}
	
	enum
	{
		Translation,
		Scale,
		Rotation,
		Enabled,
		NumUniforms
	};

	GLfloat translation[] = { 0.1, 0.1, 0.0 };
	GLfloat	scale = 0.5f;
	GLfloat rotation[] = { 90, 0.0, 0.0, 1.0 };
	GLboolean enabled = GL_TRUE;

	const char* names[NumUniforms] = 
	{
		"translation",
		"scale",
		"rotation", 
		"enabled"
	};

	GLuint	indices[NumUniforms];
	GLint	size[NumUniforms];
	GLint	offset[NumUniforms];
	GLint	type[NumUniforms];

	glGetUniformIndices( program, NumUniforms, names, indices );
	glGetActiveUniformsiv( program, NumUniforms, indices, GL_UNIFORM_OFFSET, offset );
	glGetActiveUniformsiv( program, NumUniforms, indices, GL_UNIFORM_SIZE, size );
	glGetActiveUniformsiv( program, NumUniforms, indices, GL_UNIFORM_TYPE, type );

	memcpy( pBuffer + offset[Translation], &translation, size[Translation] * TypeSize( type[Translation] ) );
	memcpy( pBuffer + offset[Scale], &scale, size[Scale] * TypeSize( type[Scale] ) );
	memcpy( pBuffer + offset[Rotation], &rotation, size[Rotation] * TypeSize( type[Rotation] ) );
	memcpy( pBuffer + offset[Enabled], &enabled, size[Enabled] * TypeSize( type[Enabled] ) );

	glGenBuffers( 1, &uBo );
	glBindBuffer( GL_UNIFORM_BUFFER, uBo );
	glBufferData( GL_UNIFORM_BUFFER, uBoSize, pBuffer, GL_STATIC_DRAW );
	glBindBufferBase( GL_UNIFORM_BUFFER, uBoIndex, uBo );
}

void Displayer()
{
	
}
