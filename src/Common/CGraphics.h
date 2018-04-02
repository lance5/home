#pragma once

class CRenderModel;
class CMatrix;
class CShader;
class CFrameBuffer;

enum
{
	eShaderType_Sprite,
	eShaderType_Count,
};

class CGraphics
{
	CShader*		m_aryShader[eShaderType_Count];
	CFrameBuffer*	m_pCurFrameBuffer;

public:
	CGraphics();
	~CGraphics();

	void			InitShader();
	void			SetFrameBuffer( CFrameBuffer* pBuffer ) { m_pCurFrameBuffer = pBuffer; }
	void			RenderObject( uint32 nShaderID, const CRenderModel& model, const CMatrix& mat );
	
	template<class ClassName>
	ClassName*		CreateResource();
};
