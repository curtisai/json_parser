template<typename T>
inline
std::ostream& operator<<( std::ostream& str, const JsonPrimitive<T>* prim ) {
	return str << prim->value();
}

template<>
inline
std::ostream& operator<<( std::ostream& str, const JsonPrimitive<std::string>* prim ) {
	return str << "\"" << prim->value() << "\"";
}

template<typename T>
inline
JsonPrimitive<T>::JsonPrimitive( T value )
	: JsonEntity( JsonEntity::UNKNOWN ),
	value_( value ){}

template<>
inline
JsonPrimitive<int>::JsonPrimitive( int value )
	: JsonEntity( JsonEntity::INTEGER ),
	value_( value ){}

template<>
inline
JsonPrimitive<std::string>::JsonPrimitive( std::string value ) // const string&
	: JsonEntity( JsonEntity::STRING ),
	value_( value ){}

template<>
inline
JsonPrimitive<double>::JsonPrimitive( double value )
	: JsonEntity( JsonEntity::DOUBLE ),
	value_( value ){}

template<>
inline
JsonPrimitive<bool>::JsonPrimitive( bool value )
	: JsonEntity( JsonEntity::BOOLEAN ),
	value_( value ){}


// accessor
template<typename T>
inline
const T JsonPrimitive<T>::value() const {
	return value_;
}