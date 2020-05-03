#include <cassert>
#include <commoncodes/bits/args/opt_arg.hpp>
#include <optional>

namespace cc = commoncodes;
using cc::opt_arg;
using cc::opt_id;
using cc::opt;
using std::nullopt;
using std::string;

int main() {
	opt opt1 = opt(opt_id(0), {'f'}, {"foo"});
	string s1 = "--foo";
	opt_arg oa1 = opt_arg(opt1, s1, nullopt);

	assert(oa1.opt() == opt1);
	assert(oa1.opt_alias() == s1);
	assert(!oa1.has_arg());

	opt opt2 = opt(opt_id(1), {'b'}, {"bar"}, true);
	string s2 = "-b";
	string arg = "arg";
	opt_arg oa2 = opt_arg(opt2, s2, arg);

	assert(oa2.has_arg());
	assert(oa2.arg() == arg);

	assert(opt_arg(opt(), "", nullopt) != oa1);
	assert(oa1 != oa2);
}
