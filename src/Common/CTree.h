#pragma once

#define MAXCHILD 2

struct STreeData
{
	int Num = 0;
};

class CTree
{
	typedef bool( *FuncTreeSort )(STreeData, STreeData);


	class CTreeNode
	{
	private:
		STreeData* pData;
		CTreeNode* pParent;
		CTreeNode* pChild[MAXCHILD];
	public:

	};
private:
	FuncTreeSort m_pFuncSort;
	CTreeNode* m_pRootNode;
	unsigned int m_nDepth;
public:
	CTree( FuncTreeSort pFunc );
	~CTree();

	bool empty() const { return m_pRootNode ? true : false; }
	unsigned int depth() { return m_nDepth; }
	CTreeNode* GetRoot() { return m_pRootNode; }

};