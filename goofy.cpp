#include "goofy.h"

bool isGoofy(int a) {
	return ((a % 2) == 0);
}
bool isGoofy(std::string a) {
	std::string vowels("aeiouAEIOU");
	return ((a.length() > 0) && (vowels.find(a[0]) != vowels.npos));
}
