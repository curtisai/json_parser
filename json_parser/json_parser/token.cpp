#include "token.h"

Token::Token( TokenType t )
	: type_( t ){}

void Token::setType( TokenType new_type ) {
    type_ = new_type;
}

TokenType Token::type() {
    return type_;
}

std::string Token::typeStr() {
	switch ( type() ) {
	case OPEN_BRACE:
		return "{";
	case CLOSE_BRACE:
		return "}";
	case OPEN_BRACKET:
		return "[";
	case CLOSE_BRACKET:
		return "]";
	case COLON:
		return ":";
	case COMMA:
		return ",";
	case SPACE:
		return " ";
	case STRING:
		return "STRING";
	case INTEGER:
		return "INTEGER";
	case DOUBLE:
		return "DOUBLE";
	case BOOLEAN:
		return "BOOLEAN";
	case NULLPTR:
		return "NULL";

	}
}