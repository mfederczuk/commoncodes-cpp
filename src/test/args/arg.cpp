#include <cassert>
#include <commoncodes/bits/args/arg.hpp>
#include <optional>
#include <sstream>
#include <string>

namespace cc = commoncodes;
using cc::arg;
using cc::opt_arg;
using cc::opt;
using cc::option_id;
using cc::val_arg;
using std::nullopt;
using std::ostringstream;
using std::string;

int main() {
	string s1 = "foobar";
	val_arg va1 = val_arg(s1);
	arg a1 = arg(va1);

	assert(a1.is_val());
	assert(a1.val() == va1);

	val_arg va2 = a1;
	assert(va1 == va2);


	opt o1 = opt(option_id(0), {'f'}, {"foo"});
	string s2 = "-f";
	opt_arg oa1 = opt_arg(o1, s2, nullopt);
	arg a2 = arg(oa1);

	assert(a2.is_opt());
	assert(a2.opt() == oa1);

	opt_arg oa2 = a2;
	assert(oa1 == oa2);


	arg a3 = arg();
	assert(a3.is_val());
	assert(a3.val() == val_arg());


	assert(arg(val_arg(s1)) == a1);
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
