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

#include <commoncodes/bits/args/opt_arg.hpp>
#include <ostream>
#include <string>

namespace cc = commoncodes;
using cc::opt_arg;
using std::ostream;
using std::string;

ostream& operator<<(ostream& stream, const opt_arg& opt_arg) noexcept {
	const string alias_arg = opt_arg.alias_arg();
	stream << alias_arg;

	if(opt_arg.has_arg()) {
		if(alias_arg.length() > 2 && alias_arg.substr(0, 2) == "--") {
			stream << '=' << opt_arg.arg();
		} else if(alias_arg.length() > 1 && alias_arg[0] == '-') {
			stream << opt_arg.arg();
		}
	}

	return stream;
}
