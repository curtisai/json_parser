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