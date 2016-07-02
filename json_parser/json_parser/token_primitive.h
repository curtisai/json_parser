#pragma once

#include "token.h"

template<typename T>
class TokenPrimitive : public Token {
  private:

	T             value_;

  public:

	// constructor
	TokenPrimitive( TokenType t, T value );

	// accessor
	T              value();
};

template<typename T>
T TokenPrimitive<T>::value() {
    return value_;
}



typedef TokenPrimitive<std::string>   TokenString;
typedef TokenPrimitive<int>           TokenInt;
typedef TokenPrimitive<double>        TokenDouble;
typedef TokenPrimitive<bool>          TokenBool;