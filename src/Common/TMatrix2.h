#pragma once

template< typename DataType >
class TMatrix2
{
public:
	union
	{
		DataType	_11, _12,
			_21, _22;
		DataType value[2][2];
	};
	TMatrix2() {}
	~TMatrix2() {}

	DataType* operator[]( uint32 n ) { return value[n]; }
	const DataType* operator[]( uint32 n ) const { return value[n]; }
};

typedef TMatrix2<float> CMatrix2f;