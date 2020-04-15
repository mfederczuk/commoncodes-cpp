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

#include <commoncodes/bits/statuses/v1/2_generic_usage_error.hpp>

namespace cc = commoncodes;
using cc::v1::generic_usage_error;
using std::string;

string generic_usage_error::msg() const noexcept {
	string msg = "generic usage error";
	add_prefix(msg, _origin);
	add_suffix(msg, _info);
	return msg;
}
