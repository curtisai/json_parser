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
	return str << j_array.array();
}