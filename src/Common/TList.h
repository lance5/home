#pragma once

template<typename DataType>
class TList
{
public:
	class INode
	{
		friend TList<DataType>;
		INode* m_pLast;
		INode* m_pNext;
	public:
		INode() : m_pLast( nullptr ), m_pNext( nullptr ) {}
		virtual ~INode()
		{
			Remove();
		}

		void Remove()
		{
			// 有一方为空，表示为list头尾节点，不然就是链表出现问题  
			if ( !m_pLast || !m_pNext )
				return;
			m_pLast->m_pNext = m_pNext;
			m_pNext->m_pLast = m_pLast;
			m_pNext = nullptr;
			m_pLast = nullptr;
		}

		DataType* GetLast()
		{
			return static_cast<DataType*>( m_pLast->m_pLast == nullptr ? nullptr : m_pLast );
		}

		DataType* GetNext()
		{
			return static_cast<DataType*>( m_pNext->m_pNext == nullptr ? nullptr : m_pNext );
		}

		bool IsList()
		{
			return m_pLast != nullptr || m_pNext != nullptr;
		}
	};

	TList()
	{
		m_First.m_pNext = &m_End;
		m_End.m_pLast = &m_First;
	}

	~TList()
	{
		if ( IsEmpty() )
			return;
		Log << "~TList Not Empty : " << this << std::endl;
	}

	DataType* GetFirst()
	{
		return static_cast<DataType*>( m_First.m_pNext == &m_End ? nullptr : m_First.m_pNext );
	}

	DataType* GetEnd()
	{
		return static_cast<DataType*>( m_End.m_pLast == &m_First ? nullptr : m_End.m_pLast );
	}

	bool IsEmpty()
	{ 
		return  m_First.m_pNext == &m_End && m_End.m_pLast == &m_First; 
	}

	void InsertToBack( INode& node, INode& Pos )
	{
		Assert( !node.IsList() );
		node.m_pLast = &Pos;
		node.m_pNext = Pos.m_pNext;
		node.m_pLast->m_pNext = &node;
		node.m_pNext->m_pLast = &node;
	}

	void Insert( INode& INode )
	{
		InsertToBack( INode, *m_End.m_pLast );
	}
private:
	INode m_First;
	INode m_End;
};