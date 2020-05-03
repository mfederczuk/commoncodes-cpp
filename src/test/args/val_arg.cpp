#include <cassert>
#include <commoncodes/bits/args/val_arg.hpp>
#include <string>

namespace cc = commoncodes;
using cc::val_arg;
using std::string;

int main() {
	string s1 = "foobar";
	val_arg va1 = val_arg(s1);

	assert(va1.val() == s1);

	string s2 = va1;
	assert(s2 == s1);

	assert(s1 == *va1);

	assert(va1->length() == s1.length());

	val_arg va2 = val_arg(s2);
	assert(va1 == va2);

	val_arg va3 = val_arg("yeehaw");
	assert(va1 != va3);
}
