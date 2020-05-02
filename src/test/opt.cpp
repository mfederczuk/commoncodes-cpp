#include <cassert>
#include <commoncodes/bits/args/opt.hpp>
#include <string>
#include <vector>

namespace cc = commoncodes;
using cc::opt_id;
using cc::opt;
using std::string;
using std::vector;

int main() {
	opt_id opt_id1 = opt_id(0);
	vector<char> short_aliases1 = {'f'};
	vector<string> long_aliases1 = {"foo"};
	opt opt1 = opt(opt_id1, short_aliases1, long_aliases1);

	assert(opt1.id() == opt_id1);
	assert(opt1.short_aliases() == short_aliases1);
	assert(opt1.long_aliases() == long_aliases1);
	assert(!opt1.has_arg());

	opt_id opt_id2 = opt_id(1);
	vector<char> short_aliases2 = {'b'};
	vector<string> long_aliases2 = {"bar"};
	opt opt2 = opt(opt_id2, short_aliases2, long_aliases2, false);

	assert(opt2.id() == opt_id2);
	assert(opt2.short_aliases() == short_aliases2);
	assert(opt2.long_aliases() == long_aliases2);
	assert(opt2.arg_optional());
	assert(!opt2.arg_required());

	assert(opt1 == opt(opt_id1, {'f'}, {"foo"}));
	assert(opt1 != opt2);
}
