#pragma once

template<typename DataType>
class TRect
{
	DataType	m_top;
	DataType	m_bottom;
	DataType	m_left;
	DataType	m_right;

public:
	TRect() : m_top( DataType() ), m_bottom( DataType() ), 
		m_left( DataType() ), m_right( DataType() ){}
	TRect( DataType top, DataType bottom, DataType left, DataType right )
		: m_top( top ), m_bottom( bottom ), 
		m_left( left ), m_right( right ){}
	~TRect() {}
};

typedef TRect<float> CFRect;