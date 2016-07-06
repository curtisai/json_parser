#ifndef JSON_ENTITY
#define JSON_ENTITY




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

	JsonEntity& operator[]( const std::string key ) const;
	  // subscript operator for JsonObject
	  // return the element from the object with the given key

	virtual const JsonEntity& operator[]( int i ) const;
	  // subscript operator for JsonObject
	  // return the element from the array at index i

	// member functions

	virtual int const                                    asInt() const;
	  // return the value of the entity as an integer

	virtual std::string const                            asString() const;
	  // return the value of the entity as an string

	virtual double const                                 asDouble() const;
	  // return the value of the entity as an double

	virtual bool const                                   asBool() const;
	  // return the value of the entity as an boolean

	virtual const std::vector<JsonEntity*>&              asArray() const;
	  // return the value of the entity as an object

	virtual const std::map<std::string, JsonEntity*>&    asObject() const;

	virtual bool const                                   isInt() const;
	  // return true if type is int

	virtual bool const                                   isString() const;
	  // return true if type is std::string

	virtual bool const                                   isDouble() const;
	  // return true if type is double

	virtual bool const                                   isBool() const;
	  // return true if type is boolean

	virtual bool const                                   isArray() const;
	  // return true if type is array

	bool const                                   isObject() const;
};

std::ostream& operator<<( std::ostream& str, const JsonEntity* entity );


#endif