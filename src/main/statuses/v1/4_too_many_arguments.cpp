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

#include <commoncodes/bits/statuses/v1/4_too_many_arguments.hpp>

namespace cc = commoncodes;
using cc::v1::too_many_arguments;
using std::string;
using std::to_string;

string too_many_arguments::msg() const noexcept {
	string msg = "too many arguments";
	add_prefix(msg, _option);
	add_prefix(msg, _origin);
	if(_n != 0) add_suffix(msg, to_string(_n));
	return msg;
}
