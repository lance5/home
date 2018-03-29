#pragma once

#include "CommonHelpType.h"

class IUnKnown
{
public:
	virtual uint32	GetRef()	= 0;
	virtual void	AddRef()	= 0;
	virtual void	Release()	= 0;
};

#define DEFAULT_OPERATOR( ClassName ) \
	private:	\
		uint32 m_nRef;	\
	public:	\
		ClassName() : m_nRef( 1 ) {} \
		uint32	GetRef() const { return m_nRef; }	\
		void	AddRef() { ++m_nRef; }	\
		void	Release() { if( --m_nRef == 0 ) delete this; } \
	private:

#define DEFAULT_METHOD( ClassName ) \
	private:	\
		uint32 m_nRef;	\
	public:	\
		uint32	GetRef() const { return m_nRef; }	\
		void	AddRef() { ++m_nRef; }	\
		void	Release() { if( --m_nRef == 0 ) delete this; } \
	private:
	