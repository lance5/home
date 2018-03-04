#pragma once

template<typename DataType>
class TList
{
public:
	class CNode
	{
		friend TList<DataType>;
		CNode* m_pLast;
		CNode* m_pNext;
	public:
		CNode() : m_pLast( nullptr ), m_pNext( nullptr ) {}
		~CNode()
		{
			Remove();
		}

		void Remove()
		{
			if ( !m_pLast && !m_pNext )
				return;
			m_pLast->m_pNext = m_pNext;
			m_pNext->m_pLast = m_pLast;
			m_pNext = nullptr;
			m_pLast = nullptr;
		}

		DataType* GetLast()
		{
			return m_pLast->m_pLast == nullptr ? nullptr : m_pLast;
		}

		DataType* GetNext()
		{
			return m_pNext->m_pNext == nullptr ? nullptr : m_pNext;
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
		return static_cast<DataType*>( m_First.m_pNext );
	}

	DataType* GetEnd()
	{
		return static_cast<DataType*>( m_End.m_pLast );
	}

	bool IsEmpty()
	{ 
		return  m_First.m_pNext == &m_End && m_End.m_pLast == &m_First; 
	}

	void InsertToBack( CNode& Node, CNode& Pos )
	{
		Assert( !Node.IsList() );
		Node.m_pLast = &Pos;
		Node.m_pNext = Pos.m_pNext;
		Node.m_pLast->m_pNext = &Node;
		Node.m_pNext->m_pLast = &Node;
	}

	void Insert( CNode& Node )
	{
		InsertToBack( Node, *m_End.m_pLast );
	}
private:
	CNode m_First;
	CNode m_End;
};