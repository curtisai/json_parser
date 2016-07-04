
#include <exception>
#include "json_array.h"
#include "json_object.h"
#include "json_parser.h"

int               JsonParser::index_ = -1;
std::string       JsonParser::json_ = "";


Token* JsonParser::token() {
    
	++index_;

	if ( index_ >= json_.length() ) {
		return nullptr;
	}

	switch ( json_[index_] ) {
	// skip spaces and newlines
	case ' ':
	case '\r':
	case '\n':
		return token();
	
	// object
	case '{':
		return new Token( OPEN_BRACE );
	case '}':
		return new Token( CLOSE_BRACE );

	// punctuation inside object
	case ',':
		return new Token( COMMA );
	case ':':
		return new Token( COLON );

	// array
	case '[':
		return new Token( OPEN_BRACKET );
	case ']':
		return new Token( CLOSE_BRACKET );

	// string
	case '"':
	case '\'':
		return parseString();

	// bool
	case 't':
	case 'f':
		return parseBool();

	// null
	case 'n':
		return parseNull();

	// integer or double
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '-':
		return parseNumber();
	default:
		throw "UNknown Token ";
	}
}


Token* JsonParser::parseNull() {
	Token* token = nullptr;

	if ( json_.substr( index_, 4 ) == "null" ){
		token = new Token( NULLPTR );
		index_ += 4;
	}
	else{
	    throw "parsenull error";
	}
	return token;
}

Token* JsonParser::parseBool() {
	TokenBool* token = nullptr;
	if ( json_.substr( index_, 5 ) == "false" ){
	    token = new TokenBool( BOOLEAN, false );
		index_ += 4;
	}
	else if ( json_.substr( index_, 4 ) == "true" ){
		token = new TokenBool( BOOLEAN, true );
		index_ += 3;
	}
	else {
		throw "parsebool error";
	}
	return token;
}

Token* JsonParser::parseNumber() {
	const char    *numbers = "0123456789";
	int            start = index_++;
	std::size_t    i = json_.find_first_not_of( numbers, index_ );
	bool           isFloat = false;

	if ( json_[i] == '.' ) {
	    isFloat = true;
		i = json_.find_first_not_of( numbers, i + 1 );
	}

	std::string    nb = json_.substr( start, i - start );

	index_ = i - 1;

	if ( isFloat ) {
	    return new TokenDouble( DOUBLE, atof( nb.c_str() ) );
	}
	else {
		return new TokenInt( INTEGER, atoi( nb.c_str() ) );
	}
}

Token* JsonParser::parseString() {
	int      start = ++index_;

	while ( index_ < json_.size() 
		 && json_[index_] != '"'
		 && json_[index_] != '\'' ) {
	    index_++;
	}

	std::string s = json_.substr( start, index_ - start );

	return new TokenString( STRING, s );
}

JsonArray* JsonParser::createArray() {
	ArrayJEntity     array;
	Token            expect( NULLPTR );

	while ( true ) {
		Token*       t = token();
		if ( t == nullptr ) {
			throw "end of file";
		}


		// we check if the token is the one we expected
		if ( ( expect.type() != NULLPTR && t->type() != expect.type()
			&& t->type() != CLOSE_BRACKET ) 
			|| ( expect.type() != COMMA && t->type() == CLOSE_BRACKET ) ) {

			std::string err = "createArray: Invalid token \"";
			err += t->typeStr();
			err += "\" when expected \"";
			err += "\"";
			throw std::invalid_argument( err );
		}
		switch ( t->type() ) {
		case COMMA:
			expect.setType( NULLPTR );
			break;

		// possible values
		case STRING:
			array.push_back( createString( t ) );
			expect.setType( COMMA );
			break;

		case INTEGER:
			array.push_back( createInt( t ) );
			expect.setType( COMMA );
			break;

		case DOUBLE:
			array.push_back( createDouble( t ) );
			expect.setType( COMMA );
			break;

		case BOOLEAN:
			array.push_back( createBool( t ) );
			expect.setType( COMMA );
			break;

		case OPEN_BRACKET:
			array.push_back( createArray() );
			expect.setType( COMMA );
			break;

		case OPEN_BRACE:
			array.push_back( createObject() );
			expect.setType( COMMA );
			break;

		case CLOSE_BRACKET:
			return new JsonArray( array );

		// everything else is an error	
		default:
			std::string err = "createArray: Invalid token \"";
			err += t->type();
			err += "\"";
			throw std::invalid_argument( err );
		}
	}
}

JsonObject* JsonParser::createObject() {
	MapJEntity       object;
	Token            expect( STRING );


	// initialization of a new attribute
	std::string      key;
	JsonEntity*      value = nullptr;

	while ( true ) {
		Token*       t = token();

		// we check if the token is the one we expeted
		if ( ( expect.type() != NULLPTR && t->type() != expect.type() 
			&& t->type() != CLOSE_BRACE )
			|| ( expect.type() != COMMA && t->type() == CLOSE_BRACE ) ) {
			
			std::string err = "createArray: Invalid token \"";
			err += t->typeStr();
			err += "\" when expected \"";
			err += "\"";
			throw std::invalid_argument( err );
		}

		switch ( t->type() ) {
		case COLON:
			expect.setType( NULLPTR );
			break;

		case COMMA:
			object[key] = value;
			expect.setType( STRING );
			break;

		case STRING:
			// if we expect a string then it's an identifier
			if ( expect.type() == STRING ){
			    key = ( ( TokenString*) t )->value();
				expect.setType( COLON );
			}
			// if we didn't explicitly expected a STRING then, it's a value
			else {
				value = createString( t );
				expect.setType( COMMA );
			}
			break;

		case INTEGER:
			value = createInt( t );
			expect.setType( COMMA );
			break;

		case DOUBLE:
			value = createDouble( t );
			expect.setType( COMMA );
			break;

		case OPEN_BRACKET:
			value = createArray();
			expect.setType( COMMA );
			break;

		case OPEN_BRACE:
			value = createObject();
			expect.setType( COMMA );
			break;

		case CLOSE_BRACE:
			object[key] = value;
			return new JsonObject( object );

		default:
			std::string err = "createArray: Invalid token \"";
			err += t->typeStr();
			err += "\"";
			throw std::invalid_argument( err );
		}
	}
}

JsonInt* JsonParser::createInt( Token* token ) {
	TokenInt*     t = ( TokenInt* ) token;
	return new JsonInt( t->value() );
}

JsonBool* JsonParser::createBool( Token* token ) {
    TokenBool*    t = ( TokenBool* ) token;
	return new JsonBool( t->value() );
}

JsonDouble* JsonParser::createDouble( Token* token ) {
	TokenDouble*  t = ( TokenDouble* ) token;
	return new JsonDouble ( t->value() );
}

JsonString* JsonParser::createString( Token* token ) {
	TokenString*  t = ( TokenString* ) token;
	return new JsonString( t->value() );
}

JsonEntity* JsonParser::fromString( const std::string& json ) {
	json_ = json;
	index_ = -1;

	Token     *t = token();

	if ( t->type() == OPEN_BRACE ) {
		return createObject();
	}
	else if ( t->type() == OPEN_BRACKET ) {
		return createArray();
	}
	else {
		std::string err = "createArray: Invalid token \"";
		err += t->typeStr();
		err += "\" at index 0";
		throw std::invalid_argument( err );
	}
	return nullptr;
}