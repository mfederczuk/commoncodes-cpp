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

#include <commoncodes/bits/statuses/v1/3_missing_arguments.hpp>

namespace cc = commoncodes;
using cc::v1::missing_arguments;
using std::string;

string missing_arguments::msg() const noexcept {
	string msg = "missing argument";

	add_prefix(msg, _option);
	add_prefix(msg, _origin);

	const size_t s = _arguments.size();

	if(s != 1) msg += 's';

	if(s > 0) add_suffix(msg, _arguments[0]);
	for(size_t i = 1; i < s; ++i) {
		msg += ", " + _arguments[i];
	}

	return msg;
}
