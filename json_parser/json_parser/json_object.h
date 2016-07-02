#pragma once
#include <string>
#include <map>
#include "json_entity.h"

typedef std::map<std::string, JsonEntity*>  MapJEntity;

class JsonObject : public JsonEntity {
  private:
	  MapJEntity            attributes_;
	    // map of pointer to JsonEntity

  public:
	  // constructor
	  JsonObject( MapJEntity attributes );

	  // accessor
	  const MapJEntity&      attributes() const;

	  // operator
	  const JsonEntity&      operator[]( std::string key );
};

std::ostream& operator<<( std::ostream& str, const JsonObject j_obj ){
	return str << "{ OBJ }";
}