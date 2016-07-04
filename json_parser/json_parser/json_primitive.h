#ifndef JSON_PRIMITIVE
#define JSON_PRIMITIVE


#include "json_entity.h"
#include <exception>
#include <string>


template<typename T>
class JsonPrimitive : public JsonEntity {
  private:
	
	T                      value_;
	    // primitive value stored

  public:
	// constructors
	JsonPrimitive( T value );

	// accessors
	const T                 value() const;

};



template<typename T>
std::ostream& operator<<( std::ostream& str, const JsonPrimitive<T>* prim );

template<>
std::ostream& operator<<( std::ostream& str, const JsonPrimitive<std::string>* prim );

typedef JsonPrimitive<std::string>       JsonString;
typedef JsonPrimitive<int>               JsonInt;
typedef JsonPrimitive<double>            JsonDouble;
typedef JsonPrimitive<bool>              JsonBool;

#include "json_primitive.tpp"
#endif
