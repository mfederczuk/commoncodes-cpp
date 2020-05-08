#include <cassert>
#include <commoncodes/bits/args/option_id.hpp>
#include <commoncodes/bits/args/option.hpp>
#include <commoncodes/bits/args/options.hpp>
#include <string>
#include <typeinfo>
#include <vector>

namespace cc = commoncodes;
namespace options = cc::options;
using cc::option_id;
using cc::option;
using std::string;
using std::type_info;
using std::vector;

commoncodes_option(foo, "::foo").alias('f', "foo").arg_required();
commoncodes_option(bar, "::bar").aliases({'b', 'c'}, {"bar", "baz"});

int main() {
	const type_info& opt_info = typeid(option);
	assert(opt_info == typeid(options::help));
	assert(opt_info == typeid(options::version_info));
	assert(opt_info == typeid(options::commoncodes_version));
	assert(opt_info == typeid(options::verbose));
	assert(opt_info == typeid(options::color));
	assert(opt_info == typeid(options::output));
	assert(opt_info == typeid(options::force));
	assert(opt_info == typeid(options::silent));
	assert(opt_info == typeid(options::quiet));
	assert(opt_info == typeid(options::interactive));
	assert(opt_info == typeid(options::zero));
	assert(opt_info == typeid(options::dry_run));

	assert(foo.id() == option_id("::foo"));
	assert(foo.short_aliases() == vector {'f'});
	assert(foo.long_aliases() == vector<string> {"foo"});
	assert(foo.arg_required());

	assert(bar.id() == option_id("::bar"));
	assert(bar.short_aliases() == vector({'b', 'c'}));
	assert(bar.long_aliases() == vector<string>({"bar", "baz"}));
	assert(!bar.has_arg());
}
