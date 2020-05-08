#include <cassert>
#include <commoncodes/bits/args/option_argument.hpp>
#include <commoncodes/bits/args/option_id.hpp>
#include <commoncodes/bits/args/option.hpp>
#include <optional>
#include <sstream>
#include <string>

namespace cc = commoncodes;
using cc::option_argument;
using cc::option_id;
using cc::option;
using std::nullopt;
using std::ostringstream;
using std::string;

int main() {
	option opt1 = option(option_id(0), {'f'}, {"foo"});
	string s1 = "foo";
	option_argument oa1 = option_argument(opt1, s1, nullopt);

	assert(oa1.opt() == opt1);
	assert(oa1.alias_arg_str() == "--" + s1);
	assert(!oa1.has_arg());

	option opt2 = option(option_id(1), {'b'}, {"bar"}, true);
	char c1 = 'b';
	string arg = "arg";
	option_argument oa2 = option_argument(opt2, c1, arg);

	assert(oa2.has_arg());
	assert(oa2.alias_arg_str() == string(1, '-') + c1);
	assert(oa2.arg() == arg);

	assert(option_argument(option(), "", nullopt) != oa1);
	assert(oa1 != oa2);

	ostringstream os;

	os << oa1;
	assert(os.str() == "--foo");

	os.str(""), os.clear();
	os << oa2;
	assert(os.str() == "-barg");

	os.str(""), os.clear();
	os << option_argument(option(), "yee", "haw");
	assert(os.str() == "--yee=haw");
}
