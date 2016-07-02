#include "json_object.h"

JsonObject::JsonObject( MapJEntity attributes )
	: JsonEntity( JsonEntity::OBJECT ),
	  attributes_( attributes ){}

const MapJEntity& JsonObject::attributes() const {
    return attributes_;
}

const JsonEntity& JsonObject::operator[]( std::string key ){
    return *( attributes_[key] );
}