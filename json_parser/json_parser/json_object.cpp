#include "json_object.h"

JsonObject::JsonObject( MapJEntity attributes )
	: JsonEntity( JsonEntity::OBJECT ),
	  attributes_( attributes ){}

const MapJEntity& JsonObject::attributes() const {
    return attributes_;
}

const JsonEntity& JsonObject::operator[]( const std::string& key ) const{
    return *( attributes_.at(key) );
}

std::ostream& operator<<( std::ostream& str, const JsonObject j_obj ){
	str << " { ";
	for ( auto iter = j_obj.attributes_.begin(); iter != j_obj.attributes_.end(); ++iter ) {
		str << ( *iter ).first << " : " << ( *iter ).second << '\n';
	}
	return str << " } ";
}