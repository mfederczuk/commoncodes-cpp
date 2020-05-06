// <commoncodes/bits/args/arg.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_ARG_HPP
#define _COMMONCODES_BITS_ARGS_ARG_HPP

#include <commoncodes/bits/args/opt_arg.hpp>
#include <commoncodes/bits/args/val_arg.hpp>
#include <variant>

namespace commoncodes {
	struct arg {
		private:
			std::variant<val_arg, opt_arg> _arg;

		public:
			inline arg(const val_arg& val_arg) noexcept : _arg(val_arg) {}
			inline arg(const opt_arg& opt_arg) noexcept : _arg(opt_arg) {}
			inline arg() : arg(val_arg()) {}

			constexpr bool is_val() const noexcept {
				return std::holds_alternative<val_arg>(_arg);
			}
			constexpr bool is_opt() const noexcept {
				return std::holds_alternative<opt_arg>(_arg);
			}

			inline const val_arg& val() const {
				return std::get<val_arg>(_arg);
			}
			inline operator val_arg() const {
				return val();
			}

			inline const opt_arg& opt() const {
				return std::get<opt_arg>(_arg);
			}
			inline operator opt_arg() const {
				return opt();
			}

			inline bool operator==(const arg& rhs) const noexcept {
				return _arg == rhs._arg;
			}
			inline bool operator!=(const arg& rhs) const noexcept {
				return _arg != rhs._arg;
			}
	};
}

inline std::ostream& operator<<(std::ostream& stream,
                                const commoncodes::arg& arg) noexcept {
	if(arg.is_val()) {
		stream << arg.val();
	} else if(arg.is_opt()) {
		stream << arg.opt();
	}
	return stream;
}

#endif /* _COMMONCODES_BITS_ARGS_ARG_HPP */
