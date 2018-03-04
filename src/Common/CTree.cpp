#include "CTree.h"

CTree::CTree( FuncTreeSort pFunc )
	: m_pFuncSort( pFunc )
	, m_pRootNode( nullptr )
	, m_nDepth( 0 )
{

}

CTree::~CTree()
{
}
