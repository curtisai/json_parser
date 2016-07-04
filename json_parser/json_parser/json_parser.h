#ifndef JSON_PARSER
#define JSON_PARSER


#include "token.h"
#include "token_primitive.h"
#include "json_array.h"
#include "json_object.h"
#include "json_object.h"
#include "json_primitive.h"


class JsonParser {
  private:

	static std::string             json_;

	static int                     index_;

	// member functions

	static Token*                  token();
	    // analyze the json string and return the next token

	static Token*                  parseNull();
	    // parse a null token

	static Token*                  parseBool();
	    // parse a bool token

	static Token*                  parseNumber();
	    // parse an integer, or a double token

	static Token*                  parseString();



	static JsonArray*              createArray();
	    // create a JsonArray object from the json string

	static JsonObject*             createObject();

	static JsonInt*                createInt( Token* t );
	    // create a JsonPrimitive of int from the given token

	static JsonBool*               createBool( Token* t );

	static JsonDouble*             createDouble( Token* t );

	static JsonString*             createString( Token* t );

  public:

	static JsonEntity*             fromString( const std::string& json );
};

#endif