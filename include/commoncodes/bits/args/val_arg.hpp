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

#include <ostream>
#include <string>

namespace commoncodes {
	struct val_arg {
		private:
			std::string _val;

		public:
			inline val_arg(const std::string& val = "") noexcept : _val(val) {}

			inline const std::string& val() const noexcept {
				return _val;
			}
			inline operator std::string() const noexcept {
				return _val;
			}

			inline const std::string& operator*() const noexcept {
				return val();
			}
			inline const std::string* operator->() const noexcept {
				return &_val;
			}

			inline bool operator==(const val_arg& rhs) const noexcept {
				return _val == rhs._val;
			}
			inline bool operator!=(const val_arg& rhs) const noexcept {
				return _val != rhs._val;
			}
	};
}

inline std::ostream& operator<<(std::ostream& stream,
                                const commoncodes::val_arg& val_arg) noexcept {
	return stream << val_arg.val();
}

#endif /* _COMMONCODES_BITS_ARGS_VAL_ARG_HPP */
