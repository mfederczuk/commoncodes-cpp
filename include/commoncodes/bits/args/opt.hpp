// <commoncodes/bits/args/opt.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_OPT_HPP
#define _COMMONCODES_BITS_ARGS_OPT_HPP

#include <commoncodes/bits/args/opt_id.hpp>
#include <commoncodes/bits/config.hpp>
#include <cstdint>
#include <string>
#include <vector>

#define __cc_opt_op_mod __cc_str_vec_op_mod

namespace commoncodes {
	struct opt {
		private:
			static constexpr uint8_t _no_arg = 0;
			static constexpr uint8_t _arg_required = 1;
			static constexpr uint8_t _arg_optional = 2;

			opt_id _id;
			std::vector<char> _short_aliases;
			std::vector<std::string> _long_aliases;
			uint8_t _arg;

			__cc_str_vec_op_mod opt(const opt_id& id,
			                        const std::vector<char>& short_aliases,
			                        const std::vector<std::string>& long_aliases,
			                        uint8_t arg) noexcept
					: _id(id),
					  _short_aliases(short_aliases),
					  _long_aliases(long_aliases),
					  _arg(arg) {
			}

		public:
			__cc_str_vec_op_mod opt(const opt_id& id,
			                        const std::vector<char>& short_aliases,
			                        const std::vector<std::string>& long_aliases,
			                        bool arg_required) noexcept
					: opt(id,
					      short_aliases,
					      long_aliases,
					      arg_required ? _arg_required : _arg_optional) {
			}
			__cc_str_vec_op_mod opt(const opt_id& id,
			                        const std::vector<char>& short_aliases,
			                        const std::vector<std::string>& long_aliases) noexcept
					: opt(id, short_aliases, long_aliases, _no_arg) {
			}
			__cc_str_vec_op_mod opt() noexcept
					: opt(unknown_opt_id, {}, {}) {
			}

			constexpr opt_id id() const noexcept {
				return _id;
			}

			__cc_vec_op_mod std::vector<char> short_aliases() const noexcept {
				return _short_aliases;
			}
			__cc_str_vec_op_mod std::vector<std::string> long_aliases() const noexcept {
				return _long_aliases;
			}

			constexpr bool has_arg() const noexcept {
				return _arg == _arg_required || _arg == _arg_optional;
			}
			constexpr bool arg_required() const noexcept {
				return _arg == _arg_required;
			}
			constexpr bool arg_optional() const noexcept {
				return _arg == _arg_optional;
			}

			__cc_str_vec_op_mod bool operator==(const opt& rhs) const noexcept {
				return _id == rhs._id &&
				       _short_aliases == rhs._short_aliases &&
				       _long_aliases == rhs._long_aliases &&
				       _arg == rhs._arg;
			}
			__cc_str_vec_op_mod bool operator!=(const opt& rhs) const noexcept {
				return _id != rhs._id ||
				       _short_aliases != rhs._short_aliases ||
				       _long_aliases != rhs._long_aliases ||
				       _arg != rhs._arg;
			}
	};
}

#endif /* _COMMONCODES_BITS_ARGS_OPT_HPP */
