#ifndef JSON_OBJECT
#define JSON_OBJECT

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
	  const JsonEntity&      operator[]( const std::string& key ) const;

	  friend std::ostream& operator<<( std::ostream& str, const JsonObject j_obj );
};



#endif