
#include "json_entity.h"
#include "json_array.h"
#include "json_object.h"
#include "json_primitive.h"


JsonEntity::JsonEntity( EntityType type )
: type_( type ) {}

JsonEntity::EntityType JsonEntity::type() const {
	return type_;
}

std::string JsonEntity::typeStr() const {
	switch ( type_ ) {
	case STRING:
		return "STRING";
		
	case INTEGER:
		return "INTEGER";

	case BOOLEAN:
		return "BOOLEAN";

	case DOUBLE:
		return "DOUBLE";

	case OBJECT:
		return "OBJECT";

	case ARRAY:
		return "ARRAY";

	default:
		return "ERROR";
	}
}


JsonEntity& JsonEntity::operator[]( const std::string key ) const {
	if ( isObject() ) {
		return *dynamic_cast<const JsonObject* const>( this )->attributes().at(key);
	}
	throw "Entity is not an object";
}

const JsonEntity& JsonEntity::operator[]( int index ) const {
	if ( isArray() ) {
		return *dynamic_cast<const JsonArray* const>( this )->array()[index];
			
	}
	throw "Entity is not an array";
}

int const JsonEntity::asInt() const {
	if ( isInt() ) {
		return dynamic_cast<const JsonInt  *const>(this)->value();
	}
	throw "Entity is not an int";
}

std::string const JsonEntity::asString() const {
	if ( isString() ) {
		return dynamic_cast<const JsonString* const>( this )->value();
	}
	throw "Entity is not a string";
}

double const JsonEntity::asDouble() const {
	if ( isDouble() ) {
		return dynamic_cast<const JsonDouble* const>( this )->value();
	}
	throw "Entity is not a string";
}

bool const JsonEntity::asBool() const {
	if ( isBool() ) {
		return dynamic_cast<const JsonBool* const>( this )->value();
	}
	throw "Entity is not a boolean";
}

const std::vector<JsonEntity*>& JsonEntity::asArray() const {
	if ( isArray() ) {
		return dynamic_cast<const JsonArray* const>( this )->array();
	}
	throw "Entity is not an array";
}

const std::map<std::string, JsonEntity*>& JsonEntity::asObject() const {
	if ( isObject() ) {
		return dynamic_cast<const JsonObject* const>( this )->attributes();//( ( JsonObject* ) this )->attributes();
	}
	throw "Entity is not an object";
}

bool const JsonEntity::isInt() const {
	return type_ == INTEGER;
}

bool const JsonEntity::isString() const {
	return type_ == STRING;
}

bool const JsonEntity::isDouble() const {
	return type_ == DOUBLE;
}

bool const JsonEntity::isBool() const {
	return type_ == BOOLEAN;
}

bool const JsonEntity::isArray() const {
	return type_ == ARRAY;
}

bool const JsonEntity::isObject() const {
	return type_ == OBJECT;
}

std::ostream& operator<<( std::ostream& str, const JsonEntity* entity ) {

	switch ( entity->type() ) {
	case JsonEntity::OBJECT:
		return str << *((JsonObject*)entity);
		

	case JsonEntity::ARRAY:
		return str << *((JsonArray*)entity);

	case JsonEntity::INTEGER:
		return str << entity->asInt();

	case JsonEntity::STRING:
		return str << "\"" << entity->asString() << "\"";

	case JsonEntity::BOOLEAN:
		return str << entity->asString();

	default:
		return str << "{ UNKNOWN ENTITY }";
	}
}