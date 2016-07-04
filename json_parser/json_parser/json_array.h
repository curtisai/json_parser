#ifndef JSON_ARRAY
#define JSON_ARRAY


#include <vector>

#include "json_entity.h"

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

std::ostream& operator<<( std::ostream& str, const JsonArray j_array );

#endif