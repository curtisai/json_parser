#include "json_array.h"


JsonArray::JsonArray( ArrayJEntity array )
	: JsonEntity( JsonEntity::ARRAY ),
	  array_( array ){}

const ArrayJEntity& JsonArray::array() const {
    return array_;
}

const JsonEntity& JsonArray::operator[]( int index ){
    return *( array_[index] );
}

std::ostream& operator<<( std::ostream& str, const JsonArray j_array ){
	str << " [ ";
	for ( auto iter = j_array.array_.begin(); iter != j_array.array_.end(); ++iter ) {
		str << ( *iter ) << " ";
	}
	return str << " ] ";
}