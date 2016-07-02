#pragma once
#include <string>

enum TokenType {
    OPEN_BRACE,
	CLOSE_BRACE,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	COLON,
	COMMA,
	SPACE,
	STRING,
	INTEGER,
	DOUBLE,
	BOOLEAN,
    NULLPTR
};

class Token {
  private:
	TokenType          type_;

  public:
	Token( TokenType t );

	TokenType         type();

	void              setType( TokenType new_type );

	std::string       typeStr();

};