// <commoncodes/bits/args/argument.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_ARGUMENT_HPP
#define _COMMONCODES_BITS_ARGS_ARGUMENT_HPP

#include <commoncodes/bits/args/option_argument.hpp>
#include <commoncodes/bits/args/value_argument.hpp>
#include <ostream>
#include <variant>

namespace commoncodes {
	struct argument {
		private:
			std::variant<value_argument, option_argument> _arg;

		public:
			inline argument(const value_argument& val_arg) noexcept
					: _arg(val_arg) {
			}
			inline argument(const option_argument& opt_arg) noexcept
					: _arg(opt_arg) {
			}
			inline argument() : argument(value_argument()) {}

			constexpr bool is_val() const noexcept {
				return std::holds_alternative<value_argument>(_arg);
			}
			constexpr bool is_opt() const noexcept {
				return std::holds_alternative<option_argument>(_arg);
			}

			inline const value_argument& val() const {
				return std::get<value_argument>(_arg);
			}
			inline operator value_argument() const {
				return val();
			}

			inline const option_argument& opt() const {
				return std::get<option_argument>(_arg);
			}
			inline operator option_argument() const {
				return opt();
			}

			inline bool operator==(const argument& rhs) const noexcept {
				return _arg == rhs._arg;
			}
			inline bool operator!=(const argument& rhs) const noexcept {
				return _arg != rhs._arg;
			}
	};
}

inline std::ostream& operator<<(std::ostream& stream,
                                const commoncodes::argument& arg) noexcept {
	if(arg.is_val()) {
		stream << arg.val();
	} else if(arg.is_opt()) {
		stream << arg.opt();
	}
	return stream;
}

#endif /* _COMMONCODES_BITS_ARGS_ARGUMENT_HPP */
