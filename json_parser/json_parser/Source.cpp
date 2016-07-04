#include "json_parser.h"
#include <string>
#include <iostream>
int main() {
    std::string test = "{"
		"\"glossary\": {"
		"\"title\": \"example glossary\","
			"\"GlossDiv\": {"
			"\"title\": \"S\","
				"\"GlossList\": {"
				"\"GlossEntry\": {"
					"\"ID\": \"SGML\","
						"\"SortAs\": \"SGML\","
						"\"GlossTerm\": \"Standard Generalized Markup Language\","
						"\"Acronym\": \"SGML\","
						"\"Abbrev\": \"ISO 8879:1986\","
						"\"GlossDef\": {"
						"\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\","
							"\"GlossSeeAlso\": [\"GML\", \"XML\"]"
					"},"
						"\"GlossSee\": \"markup\""
		"}"
		"}"
		"}"
		"}"
		"}";

	JsonEntity* result = JsonParser::fromString( test );
	

	return 0;
}