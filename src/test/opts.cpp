#include <cassert>
#include <commoncodes/bits/args/opts.hpp>
#include <typeinfo>
#include <vector>

namespace cc = commoncodes;
namespace opts = cc::opts;
using cc::opt_id;
using cc::opt;
using std::string;
using std::type_info;
using std::vector;

commoncodes_opt(foo, "::foo").alias('f', "foo").arg_required();
commoncodes_opt(bar, "::bar").aliases({'b', 'c'}, {"bar", "baz"});

int main() {
	const type_info& opt_info = typeid(opt);
	assert(opt_info == typeid(opts::help));
	assert(opt_info == typeid(opts::version_info));
	assert(opt_info == typeid(opts::commoncodes_version));
	assert(opt_info == typeid(opts::verbose));
	assert(opt_info == typeid(opts::color));
	assert(opt_info == typeid(opts::output));
	assert(opt_info == typeid(opts::force));
	assert(opt_info == typeid(opts::silent));
	assert(opt_info == typeid(opts::quiet));
	assert(opt_info == typeid(opts::interactive));
	assert(opt_info == typeid(opts::zero));
	assert(opt_info == typeid(opts::dry_run));

	assert(foo.id() == opt_id("::foo"));
	assert(foo.short_aliases() == vector {'f'});
	assert(foo.long_aliases() == vector<string> {"foo"});
	assert(foo.arg_required());

	assert(bar.id() == opt_id("::bar"));
	assert(bar.short_aliases() == vector({'b', 'c'}));
	assert(bar.long_aliases() == vector<string>({"bar", "baz"}));
	assert(!bar.has_arg());
}
