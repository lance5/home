#pragma once

template< typename DataType >
class TMatrix4
{
public:
	union
	{
		DataType	_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44;
		DataType value[4][4];
	};
	TMatrix4() {}
	~TMatrix4() {}

	DataType* operator[]( uint32 n ) { return value[n]; }
	const DataType* operator[]( uint32 n ) const { return value[n]; }
};

typedef TMatrix4<float> CMatrix4f;