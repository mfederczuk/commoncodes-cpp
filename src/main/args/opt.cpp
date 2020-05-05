#include <commoncodes/bits/args/opt.hpp>
#include <string>
#include <vector>

namespace cc = commoncodes;
using cc::opt;
using std::string;
using std::vector;

string opt::str() const noexcept {
	vector<string> aliases;

	for(const char short_alias : _short_aliases) {
		const char str[] = {'-', short_alias, '\0'};
		aliases.push_back(string(str));
	}
	for(const string& long_alias : _long_aliases) {
		aliases.push_back("--" + long_alias);
	}

	string str;
	const size_t s = aliases.size();

	if(s > 0) str += aliases[0];

	for(size_t i = 1; i < s; ++i) {
		str += ", " + aliases[i];
	}

	if(has_arg()) {
		if(!_long_aliases.empty()) {
			if(arg_required()) {
				str += "=<arg>";
			} else if(arg_optional()) {
				str += "[=<arg>]";
			}
		} else if(!_short_aliases.empty()) {
			if(arg_required()) {
				str += "<arg>";
			} else if(arg_optional()) {
				str += "[<arg>]";
			}
		}
	}

	return str;
}
