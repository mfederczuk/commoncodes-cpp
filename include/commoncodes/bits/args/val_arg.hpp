// <commoncodes/bits/args/val_arg.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_VAL_ARG_HPP
#define _COMMONCODES_BITS_ARGS_VAL_ARG_HPP

#include <commoncodes/bits/config.hpp>
#include <string>

namespace commoncodes {
	struct val_arg {
		private:
			std::string _val;

		public:
			__cc_str_op_mod val_arg(const std::string& val = "") noexcept
					: _val(val) {
			}

			__cc_str_op_mod const std::string& val() const noexcept {
				return _val;
			}
			__cc_str_op_mod operator std::string() const noexcept {
				return _val;
			}

			__cc_str_op_mod const std::string& operator*() const noexcept {
				return val();
			}
			__cc_str_op_mod const std::string* operator->() const noexcept {
				return &_val;
			}

			__cc_str_op_mod bool operator==(const val_arg& rhs) const noexcept {
				return _val == rhs._val;
			}
			__cc_str_op_mod bool operator!=(const val_arg& rhs) const noexcept {
				return _val != rhs._val;
			}
	};
}

#endif /* _COMMONCODES_BITS_ARGS_VAL_ARG_HPP */
