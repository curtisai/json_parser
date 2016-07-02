#pragma once
#include "json_entity.h"
#include <vector>

typedef std::vector<JsonEntity*>    ArrayJEntity;

class JsonArray : public JsonEntity {
private:
	ArrayJEntity         array_;

public:

	
	JsonArray( ArrayJEntity array );

	// accessors
	const ArrayJEntity&     array() const;

	// operators
	const JsonEntity&       operator[]( int index );	
};

std::ostream& operator<<( std::ostream& str, const JsonArray j_array ){
    return str << j_array.array();
}