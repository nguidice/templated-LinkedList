#include <iostream> 
#include <vector>
#include <cassert>
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

bool add_prepend_append_int(GLL<int> &gint, int n, bool doubles, int &count) {
	count = 0;
	if (!gint.isEmpty()) {
		cout << "add_prepend_append_int() should be called with " << 
			" an empty gll" << endl;
		return false;
	}
	for (int i=1; i <= n; i++) {
		if (gint.prepend(i))
			count++;
		if ((doubles) && (gint.append(i * 2)))
			count++;
	}
	// cout << "add_prepend_append_int() added " << count << " items" << endl;
	if (count != (n + (doubles ? n : 0)))
		return false;
	return true;
}

bool counts(int count, int zcount, int nzcount) {
	//cout << "counts() -- count: " << count << " = " << 
	//		zcount << " goofy " <<
	//		nzcount << " not goofy?" << endl;
	return (count == (zcount + nzcount));
}

bool remove_all(GLL<int> &gint, bool goofy_first, int expected) {
        int zcount, nzcount;
        if (goofy_first)
		zcount = gint.purgeGoofy();
	
        nzcount = gint.keepGoofy();
        
        if (!goofy_first)
		zcount = gint.purgeGoofy();
	assert(counts(expected, zcount, nzcount));
	return true;
}

bool flush_test() {
	GLL<int> gint;
	assert(gint.isEmpty());
	gint.flush();
	assert(gint.isEmpty());
	return true;
}

// Test prepend() and append()
// Requires that flush() works properly
bool prepend_append_test() {
	GLL<int> gint;
	int count;
	assert(add_prepend_append_int(gint, 0, true, count));
	gint.flush();
	for (int i = 1; i <= 1000; i *= 10) {
		assert(add_prepend_append_int(gint, i, true, count));
		assert(count == (2*i));
		gint.flush();
		assert(add_prepend_append_int(gint, i, false, count));
		assert(count == i);
		gint.flush();
	}
	return true;
}

// Test removeGoofy() and purgeGoofy()
// Requires that flush() and isEmpty() work properly
// Requires that prepend() and append() work properly
bool remove_by_goofyness_test() {
	GLL<int> gint;
	int count;
	assert(add_prepend_append_int(gint, 0, true, count));

	assert(remove_all(gint, false, count));
	assert(remove_all(gint, true, count));
	
	for (int i = 1; i <= 10000; i *= 10) {
		assert(add_prepend_append_int(gint, i, true, count));
		
		assert(count == (2*i));
		assert(remove_all(gint, true, count));
		
		
                gint.reset();
     int value;
     while (!gint.finished()){
       value = gint.proceed();
       cout << value << endl;
     }
     gint.reset();
     
		assert(gint.isEmpty());
		assert(add_prepend_append_int(gint, i, true, count));
		assert(count == (2*i));
		assert(remove_all(gint, false, count));
		assert(gint.isEmpty());
		assert(add_prepend_append_int(gint, i, false, count));
		assert(count == i);
		assert(remove_all(gint, true, count));
		assert(gint.isEmpty());
		assert(add_prepend_append_int(gint, i, false, count));
		assert(count == i);
		assert(remove_all(gint, false, count));
		assert(gint.isEmpty());
	}
	return true;
}

// Requires operator<< to work on type T
// Requires GLL::append() to work
template <typename T>
bool iterator_output_test(int expected) {
	GLL<int> mygll;
	T value;
	mygll.reset();
	while (!mygll.finished()) {
		value = mygll.proceed();
		cout << "[" << value << "]";
	}
	cout << endl;
	return true;
}

// Requires prepend() to work
// Tests reset(), proceed(), finished()
bool iterator_test() {
	GLL<int> mygll;
	bool entered = false;
	// "go through" an empty gll
	while (!mygll.finished()) {
		entered = true;
		mygll.proceed();
	}
	assert(!entered);
	assert(!mygll.reset());
	while (!mygll.finished()) {
		entered = true;
		mygll.proceed();
	}
	assert(!entered);

	mygll.prepend(17);
	mygll.reset();
	while (!mygll.finished()) {
		entered = true;
		mygll.proceed();
	}
	assert(entered);

	entered = false;
	mygll.reset();
	while (!mygll.finished()) {
		entered = true;
		mygll.proceed();
	}

	GLL<int> biggll;
	int i;
	for (i = 0; i < 1000; i++)
		biggll.prepend(i);	
	int v;
	biggll.reset();
	do {
		v = biggll.proceed();
		i--;
		assert(v == i);
	       	
	} while	(!biggll.finished());
	assert(i == 0);
	return true;
}

// Requires prepend() and append() to work
// Requires reset(), finished(), and proceed() to work
// Tests merge()
bool merge_test() {
	GLL<int> gll; 
	// Merge an empty list to itself... shouldn't do anything but
	// should return true.
	assert(gll.merge(gll)); 

	// Merge an empty list to itself... shouldn't do anything but
	// should return true.
	int addme = 999;
	int a;
	gll.prepend(addme);
	gll.reset();
        a = gll.proceed();
	assert(addme == a);

	//assert(gll.merge(gll)); // should return true
	assert(gll.merge(gll)); // should return true

	assert(gll.finished() == true);
	bool finished_already = gll.finished();
	assert(finished_already);

	GLL<int> glla, gllb, gllc;
	int testSize = 1000;
	for (int i=0; i < testSize; i++) {
		glla.append(i);
	}
	assert(glla.merge(gllb)); // should return true and leave glla unchanged
	for (int i=0; i < testSize; i++)
		gllc.append(i);
	assert(gllb.merge(gllc)); // should return true and move gllc's elements
				// to gllb
	assert(gllb.merge(glla)); // should return true and move glla's elements
				// to gllb
	int val;		
	vector<int> test(testSize);
	for (int i = 0; i < testSize; i++)
		test[i] = 0;
	gllb.reset();
	while (!gllb.finished()) {
		val = gllb.proceed(); 
		assert((val >= 0) && (val < testSize));
		test[val]++;
	}
	for (int i = 0; i < testSize; i++)
		assert(test[i] == 2);
	return true;
}

bool add_and_assign_test() {
	GLL<int> gll; 
	// Merge an empty list to itself... shouldn't do anything but
	// should return true.
	gll += gll;

	int addme = 999;
	int a;
	gll.prepend(addme);
	gll += gll;
	gll.reset();
        a = gll.proceed();
	assert(addme == a);

	GLL<int> glla, gllb, gllc;
	int testSize = 1000;
	for (int i=0; i < testSize; i++) {
		glla.append(i);
	}
	glla += gllb; // add an empty list

	for (int i=0; i < testSize; i++)
		gllc.append(i);
	gllb += gllc; // add to an empty list
	gllb += gllc; // add 1000 elements of c into b
	glla += gllb; // add 2000 elements of b into a
	glla += gllc; // add 1000 elements of c into a

	int val;		
	vector<int> test(testSize);
	for (int i = 0; i < testSize; i++)
		test[i] = 0;
	glla.reset();
	while (!glla.finished()) {
		val = glla.proceed(); 
		assert((val >= 0) && (val < testSize));
		test[val]++;
	}
	for (int i = 0; i < testSize; i++)
		assert(test[i] == 4);
	return true;
}

bool subtract_and_assign_test() {
	GLL<int> glla, gllb, gllc, glld;
	int testSize = 15;
	for (int i=0; i < testSize; i++) {
		glla.append(i);
	}
	for (int i=0; i < testSize; i+=3) {
		gllb.append(i);
	}
	for (int i=1; i < testSize; i+=3) {
		gllc.append(i);
	}
	for (int i=2; i < testSize; i+=3) {
		glld.append(i);
	}
	assert(!glla.isEmpty());
	glla -= glld;
	assert(!glla.isEmpty());
	glla -= gllb;
	gllb -= gllc; // nothing in common
	glla -= glld;
	assert(!glla.isEmpty());
	glla -= gllb;
	glla -= gllc;
	assert(glla.isEmpty());
	return true;
}

bool odd_first(GLL<int> &gll) {
	gll.reset();
	bool gotEven = false;
	int val;
	while (!gll.finished()) {
		val = gll.proceed();
		if (gotEven && ((val % 2)==1))
			return false;
		if ((val % 2) == 0)
			gotEven = true;
	}
	return true;
}

void show(GLL<int> &gll) {
	gll.reset();
	while (!gll.finished()) 
		cout << gll.proceed() << endl;
}

bool demote_goofy_test() {
	int testSize;
	GLL<int> gll;

	assert(odd_first(gll));
	gll.append(2);
	gll.demoteGoofy();
	assert(odd_first(gll));
	gll.append(1);
	gll.demoteGoofy();
	assert(odd_first(gll));
	gll.append(3);
	gll.demoteGoofy();
	assert(odd_first(gll));
	gll.append(4);
	gll.demoteGoofy();
	gll.prepend(6);
	gll.append(7);
	gll.demoteGoofy();
	assert(odd_first(gll));

	GLL<int> gll2;
	testSize = 100;
	for (int i=0; i < testSize; i++)
		gll2.append(i);
	gll2.demoteGoofy();
	assert(odd_first(gll2));
	gll2.flush();
	for (int i=0; i < testSize; i+=2)
		gll2.append(i);
	gll2.demoteGoofy();
	assert(odd_first(gll2));
	gll2.flush();
	for (int i=1; i < testSize; i+=2)
		gll2.append(i);
	gll2.demoteGoofy();
	assert(odd_first(gll2));
	gll2.flush();
	for (int i=0; i < testSize; i+=2)
		gll2.append(i);
	for (int i=1; i < testSize; i+=2)
		gll2.append(i);
	gll2.demoteGoofy();
	assert(odd_first(gll2));
	gll2.flush();

	return true;
}

int main() {
	cout << "flush_test: ";
	assert(flush_test());
	cout << "passed" << endl;

	cout << "prepend_append_test: ";
	assert(prepend_append_test());
	cout << "passed" << endl;

	cout << "remove_by_goofyness_test: ";
	assert(remove_by_goofyness_test());
	cout << "passed" << endl;

	cout << "iterator_test: ";
	assert(iterator_test());
	cout << "passed" << endl;

	cout << "merge_test: ";
	assert(merge_test());
	cout << "passed" << endl;

	cout << "add_and_assign_test: ";
	assert(add_and_assign_test());
	cout << "passed" << endl;

	cout << "subtract_and_assign_test: ";
	assert(subtract_and_assign_test());
	cout << "passed" << endl;

		cout << "demote_goofy_test: ";
	assert(demote_goofy_test());
	cout << "passed" << endl;
}
