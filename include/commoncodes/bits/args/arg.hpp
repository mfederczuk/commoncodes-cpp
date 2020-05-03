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
			__cc_str_op_mod arg(const val_arg& val_arg) noexcept
					: _arg(val_arg) {
			}
			__cc_str_vec_op_mod arg(const opt_arg& opt_arg) noexcept
					: _arg(opt_arg) {
			}
			__cc_str_op_mod arg() : arg(val_arg()) {}

			constexpr bool is_val() const noexcept {
				return std::holds_alternative<val_arg>(_arg);
			}
			constexpr bool is_opt() const noexcept {
				return std::holds_alternative<opt_arg>(_arg);
			}

			__cc_str_op_mod val_arg val() const {
				return std::get<val_arg>(_arg);
			}
			__cc_str_op_mod operator val_arg() const {
				return val();
			}

			__cc_str_vec_op_mod opt_arg opt() const {
				return std::get<opt_arg>(_arg);
			}
			__cc_str_vec_op_mod operator opt_arg() const {
				return opt();
			}

			__cc_str_vec_op_mod bool operator==(const arg& rhs) const noexcept {
				return _arg == rhs._arg;
			}
			__cc_str_vec_op_mod bool operator!=(const arg& rhs) const noexcept {
				return _arg != rhs._arg;
			}
	};
}

#endif /* _COMMONCODES_BITS_ARGS_ARG_HPP */
