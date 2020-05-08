#include <cassert>
#include <commoncodes/bits/args/option_id.hpp>
#include <commoncodes/bits/args/option.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace cc = commoncodes;
using cc::option_id;
using cc::option;
using cc::unknown_option_id;
using std::ostringstream;
using std::string;
using std::vector;

int main() {
	option_id opt_id1 = option_id(0);
	vector<char> short_aliases1 = {'f'};
	vector<string> long_aliases1 = {"foo"};
	option opt1 = option(opt_id1, short_aliases1, long_aliases1);

	assert(opt1.id() == opt_id1);
	assert(opt1.short_aliases() == short_aliases1);
	assert(opt1.long_aliases() == long_aliases1);
	assert(!opt1.has_arg());

	option_id opt_id2 = option_id(1);
	vector<char> short_aliases2 = {'b'};
	vector<string> long_aliases2 = {"bar"};
	option opt2 = option(opt_id2, short_aliases2, long_aliases2, false);

	assert(opt2.id() == opt_id2);
	assert(opt2.short_aliases() == short_aliases2);
	assert(opt2.long_aliases() == long_aliases2);
	assert(opt2.arg_optional());
	assert(!opt2.arg_required());

	assert(opt1.str() == "-f, --foo");
	assert(opt2.str() == "-b, --bar[=<arg>]");
	assert(option(unknown_option_id, {'a'}, {}, true).str() == "-a<arg>");

	assert(opt1 == option(opt_id1, {'f'}, {"foo"}));
	assert(opt1 != opt2);

	ostringstream os;
	os << opt1;
	assert(os.str() == opt1.str());


	assert(option() == option::builder().build());

	assert(option(opt_id1, {}, {}) == option::builder().id(opt_id1).build());
	assert(option(option_id('a'), {}, {}) == option::builder().id('a').build());
	assert(option(option_id("abc"), {}, {}) == option::builder().id("abc").build());

	assert(option(unknown_option_id, {'a'}, {}) == option::builder().alias('a').build());
	assert(option(unknown_option_id, {}, {"abc"}) == option::builder().alias("abc").build());
	assert(option(unknown_option_id, {'a'}, {"abc"}) == option::builder().alias('a', "abc").build());

	assert(option(unknown_option_id, {'a', 'b'}, {}) == option::builder().short_aliases({'a', 'b'}).build());
	assert(option(unknown_option_id, {}, {"abc", "xyz"}) == option::builder().long_aliases({"abc", "xyz"}).build());
	assert(option(unknown_option_id, {'a', 'b'}, {"abc", "xyz"}) == option::builder().aliases({'a', 'b'}, {"abc", "xyz"}).build());

	assert(option(unknown_option_id, {}, {}) == option::builder().no_arg().build());
	assert(option(unknown_option_id, {}, {}, true) == option::builder().arg_required().build());
	assert(option(unknown_option_id, {}, {}, false) == option::builder().arg_optional().build());
}
