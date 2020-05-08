#include <cassert>
#include <commoncodes/bits/args/value_argument.hpp>
#include <sstream>
#include <string>

namespace cc = commoncodes;
using cc::value_argument;
using std::ostringstream;
using std::string;

int main() {
	string s1 = "foobar";
	value_argument va1 = value_argument(s1);

	assert(va1.val() == s1);

	string s2 = va1;
	assert(s2 == s1);

	assert(s1 == *va1);

	assert(va1->length() == s1.length());

	value_argument va2 = value_argument(s2);
	assert(va1 == va2);

	value_argument va3 = value_argument("yeehaw");
	assert(va1 != va3);

	ostringstream os;
	os << va1;
	assert(os.str() == va1.val());
}
