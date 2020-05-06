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
#include <variant>

namespace cc = commoncodes;
using cc::opt_arg;
using std::holds_alternative;
using std::ostream;
using std::string;
using std::variant;

ostream& operator<<(ostream& stream, const opt_arg& opt_arg) noexcept {
	stream << opt_arg.alias_arg_str();

	if(opt_arg.has_arg()) {
		const variant<char, string>& alias_arg = opt_arg.alias_arg();

		if(holds_alternative<char>(alias_arg)) {
			stream << opt_arg.arg();
		} else if(holds_alternative<string>(alias_arg)) {
			stream << '=' << opt_arg.arg();
		}
	}

	return stream;
}
