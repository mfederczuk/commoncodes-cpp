// <commoncodes/bits/args/option_argument.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_OPTION_ARGUMENT_HPP
#define _COMMONCODES_BITS_ARGS_OPTION_ARGUMENT_HPP

#include <commoncodes/bits/args/option.hpp>
#include <optional>
#include <ostream>
#include <string>
#include <variant>

namespace commoncodes {
	struct option_argument {
		private:
			option _opt;
			std::variant<char, std::string> _alias_arg;
			std::optional<std::string> _arg;

		public:
			inline option_argument(const option& opt,
			                       char alias_arg,
			                       const std::optional<std::string>& arg) noexcept
					: _opt(opt), _alias_arg(alias_arg), _arg(arg) {
			}
			inline option_argument(const option& opt,
			                       const std::string& alias_arg,
			                       const std::optional<std::string>& arg) noexcept
					: _opt(opt), _alias_arg(alias_arg), _arg(arg) {
			}
			inline option_argument() noexcept
					: option_argument(option(), "", std::nullopt) {
			}

			inline const option& opt() const noexcept {
				return _opt;
			}

			constexpr const std::variant<char, std::string>& alias_arg() const noexcept {
				return _alias_arg;
			}
			inline std::string alias_arg_str() const noexcept {
				switch(_alias_arg.index()) {
					case(0): return std::string(1, '-') + std::get<0>(_alias_arg);
					case(1): return "--" + std::get<1>(_alias_arg);
					default: return "";
				}
			}

			constexpr bool has_arg() const noexcept {
				return _arg.has_value();
			}
			inline std::string arg() const noexcept {
				return _arg.value_or("");
			}

			inline bool operator==(const option_argument& rhs) const noexcept {
				return _opt == rhs._opt &&
				       _alias_arg == rhs._alias_arg &&
				       _arg == rhs._arg;
			}
			inline bool operator!=(const option_argument& rhs) const noexcept {
				return _opt != rhs._opt ||
				       _alias_arg != rhs._alias_arg ||
				       _arg != rhs._arg;
			}
	};
}

std::ostream& operator<<(std::ostream& stream,
                         const commoncodes::option_argument& opt_arg) noexcept;

#endif /* _COMMONCODES_BITS_ARGS_OPTION_ARGUMENT_HPP */
