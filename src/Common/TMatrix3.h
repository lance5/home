#pragma once

template< typename DataType >
class TMatrix3
{
public:
	union
	{
		DataType	_11, _12, _13, 
			_21, _22, _23, 
			_31, _32, _33;
		DataType value[3][3];
	};
	TMatrix3() {}
	~TMatrix3() {}

	DataType* operator[]( uint32 n ) { return value[n]; }
	const DataType* operator[]( uint32 n ) const { return value[n]; }
};

typedef TMatrix3<float> CMatrix3f;