// <commoncodes/bits/args/opt_arg.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_OPT_ARG_HPP
#define _COMMONCODES_BITS_ARGS_OPT_ARG_HPP

#include <commoncodes/bits/args/opt.hpp>
#include <optional>
#include <string>
#include <variant>

namespace commoncodes {
	struct opt_arg {
		private:
			commoncodes::opt _opt;
			std::variant<char, std::string> _alias_arg;
			std::optional<std::string> _arg;

		public:
			inline opt_arg(const opt& opt,
			               char alias_arg,
			               const std::optional<std::string>& arg) noexcept
					: _opt(opt), _alias_arg(alias_arg), _arg(arg) {
			}
			inline opt_arg(const opt& opt,
			               const std::string& alias_arg,
			               const std::optional<std::string>& arg) noexcept
					: _opt(opt), _alias_arg(alias_arg), _arg(arg) {
			}
			inline opt_arg() noexcept
					: opt_arg(commoncodes::opt(), "", std::nullopt) {
			}

			inline const commoncodes::opt& opt() const noexcept {
				return _opt;
			}

			inline std::string alias_arg() const noexcept {
				if(std::holds_alternative<char>(_alias_arg)) {
					return std::string(1, '-') + std::get<char>(_alias_arg);
				} else {
					return "--" + std::get<std::string>(_alias_arg);
				}
			}

			constexpr bool has_arg() const noexcept {
				return _arg.has_value();
			}
			inline std::string arg() const noexcept {
				return _arg.value_or("");
			}

			inline bool operator==(const opt_arg& rhs) const noexcept {
				return _opt == rhs._opt &&
				       _alias_arg == rhs._alias_arg &&
				       _arg == rhs._arg;
			}
			inline bool operator!=(const opt_arg& rhs) const noexcept {
				return _opt != rhs._opt ||
				       _alias_arg != rhs._alias_arg ||
				       _arg != rhs._arg;
			}
	};
}

std::ostream& operator<<(std::ostream& stream,
                         const commoncodes::opt_arg& opt_arg) noexcept;

#endif /* _COMMONCODES_BITS_ARGS_OPT_ARG_HPP */
