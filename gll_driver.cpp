#include <iostream> 
using namespace std;

#include "goofy.h"
#include "Thing.h"
#include "GLL.h"

template <typename T>
void reportGoofy(const T &param) {
	cout << param << " is ";
	if (!isGoofy(param)) cout << "not ";
	cout << "goofy" << endl;
}

int main() {
        int one = 1;
	int two = 2;
	string one_str = "one";
	string two_str = "Two";
	reportGoofy(one);
	reportGoofy(two);
	reportGoofy(one_str);
	reportGoofy(two_str);
	Thing one_thing("Grape", "purple");
	Thing two_thing("Blueberry", "blue");
	reportGoofy(one_thing);
	reportGoofy(two_thing);

	GLL<int> gll1;
	GLL<string> gll2;
	GLL<Thing> gll3;
	gll1.append(1);
	gll2.append("two");
	gll3.append(one_thing);
}
