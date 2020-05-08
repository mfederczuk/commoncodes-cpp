#include <cassert>
#include <commoncodes/bits/args/argument.hpp>
#include <commoncodes/bits/args/option_argument.hpp>
#include <commoncodes/bits/args/option_id.hpp>
#include <commoncodes/bits/args/option.hpp>
#include <commoncodes/bits/args/value_argument.hpp>
#include <optional>
#include <sstream>
#include <string>

namespace cc = commoncodes;
using cc::argument;
using cc::option_argument;
using cc::option_id;
using cc::option;
using cc::value_argument;
using std::nullopt;
using std::ostringstream;
using std::string;

int main() {
	string s1 = "foobar";
	value_argument va1 = value_argument(s1);
	argument a1 = argument(va1);

	assert(a1.is_val());
	assert(a1.val() == va1);

	value_argument va2 = a1;
	assert(va1 == va2);


	option o1 = option(option_id(0), {'f'}, {"foo"});
	string s2 = "-f";
	option_argument oa1 = option_argument(o1, s2, nullopt);
	argument a2 = argument(oa1);

	assert(a2.is_opt());
	assert(a2.opt() == oa1);

	option_argument oa2 = a2;
	assert(oa1 == oa2);


	argument a3 = argument();
	assert(a3.is_val());
	assert(a3.val() == value_argument());


	assert(argument(value_argument(s1)) == a1);
	assert(a1 != a2);


	ostringstream os1;
	ostringstream os2;

	os1 << a1;
	os2 << va1;
	assert(os1.str() == os2.str());

	os1.str(""), os1.clear();
	os2.str(""), os2.clear();
	os1 << a2;
	os2 << oa1;
	assert(os1.str() == os2.str());
}
