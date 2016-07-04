template<typename T>
std::ostream& operator<<( std::ostream& str, const JsonPrimitive<T>* prim ) {
	return str << prim->value();
}

template<>
std::ostream& operator<<( std::ostream& str, const JsonPrimitive<std::string>* prim ) {
	return str << "\"" << prim->value() << "\"";
}

template<typename T>
JsonPrimitive<T>::JsonPrimitive( T value )
	: JsonEntity( JsonEntity::UNKNOWN ),
	value_( value ){}

template<>
JsonPrimitive<int>::JsonPrimitive( int value )
	: JsonEntity( JsonEntity::INTEGER ),
	value_( value ){}

template<>
JsonPrimitive<std::string>::JsonPrimitive( std::string value ) // const string&
	: JsonEntity( JsonEntity::STRING ),
	value_( value ){}

template<>
JsonPrimitive<double>::JsonPrimitive( double value )
	: JsonEntity( JsonEntity::DOUBLE ),
	value_( value ){}

template<>
JsonPrimitive<bool>::JsonPrimitive( bool value )
	: JsonEntity( JsonEntity::BOOLEAN ),
	value_( value ){}


// accessor
template<typename T>
const T JsonPrimitive<T>::value() const {
	return value_;
}