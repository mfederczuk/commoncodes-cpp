/*
 * C++ command line tool library.
 * Copyright (C) 2020 Michael Federczuk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
