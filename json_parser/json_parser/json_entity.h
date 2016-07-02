#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class JsonEntity{
  public:
	
	enum EntityType{
		// Primitive Type
		STRING,
		INTEGER,
		BOOLEAN,
		DOUBLE,

		// Object
		OBJECT,

		// Array
		ARRAY,

		// In case of error
		UNKNOWN
	};

  private:

	EntityType         type_;
	  // Json entity type

  public:

	// constructor
	JsonEntity( EntityType type );
	  

	// accessors
	EntityType         type() const;
	  // return the type of the entity

	std::string        typeStr() const;
	  // return the type as string

	// operators

	const JsonEntity& operator[]( std::string& key ) const;
	  // subscript operator for JsonObject
	  // return the element from the object with the given key

	const JsonEntity& operator[]( int i ) const;
	  // subscript operator for JsonObject
	  // return the element from the array at index i

	// member functions

	int const                                    asInt() const;
	  // return the value of the entity as an integer

	std::string const                            asString() const;
	  // return the value of the entity as an string

	double const                                 asDouble() const;
	  // return the value of the entity as an double

	bool const                                   asBool() const;
	  // return the value of the entity as an boolean

	const std::vector<JsonEntity*>&              asArray() const;
	  // return the value of the entity as an object

	const std::map<std::string, JsonEntity*>&    asObject() const;

	bool const                                   isInt() const;
	  // return true if type is int

	bool const                                   isString() const;
	  // return true if type is std::string

	bool const                                   isDouble() const;
	  // return true if type is double

	bool const                                   isBool() const;
	  // return true if type is boolean

	bool const                                   isArray() const;
	  // return true if type is array

	bool const                                   isObject() const;
};

std::ostream& operator<<( std::ostream& str, const JsonEntity* entity ) {
	
	switch ( entity->type() ) {
	    case JsonEntity::OBJECT:
			return str << "obj";

		case JsonEntity::ARRAY:
			return str << "array";

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