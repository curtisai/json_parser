#include "json_object.h"

JsonObject::JsonObject( MapJEntity attributes )
	: JsonEntity( JsonEntity::OBJECT ),
	  attributes_( attributes ){}

MapJEntity& JsonObject::attributes() {
    return attributes_;
}

const JsonEntity& JsonObject::operator[]( std::string key ){
    return *( attributes_[key] );
}

std::ostream& operator<<( std::ostream& str, const JsonObject j_obj ){
	str << " { ";
	for ( auto iter = j_obj.attributes_.begin(); iter != j_obj.attributes_.end(); ++iter ) {
		str << ( *iter ).first << " : " << ( *iter ).second << '\n';
	}
	return str << " } ";
}