#include "json_parser.h"
#include <exception>

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