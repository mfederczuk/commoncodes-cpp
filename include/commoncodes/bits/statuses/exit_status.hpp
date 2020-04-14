// <commoncodes/bits/statuses/exit_status.hpp>
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

#ifndef _COMMONCODES_BITS_STATUSES_EXIT_STATUS_HPP
#define _COMMONCODES_BITS_STATUSES_EXIT_STATUS_HPP

#include <commoncodes/bits/config.hpp>
#include <iostream>
#include <string>

namespace commoncodes {
	struct exit_status {
		private:
			int _code;
			std::string _msg;

		public:
			__cc_str_op_mod exit_status(int code, const std::string& msg)
					: _code(code), _msg(msg) {
			}
			__cc_str_op_mod exit_status() : exit_status(0, "success") {}

			constexpr int code() const noexcept {
				return _code;
			}
			constexpr operator int() const noexcept {
				return code();
			}

			__cc_str_op_mod std::string msg() const noexcept {
				return _msg;
			}
			__cc_str_op_mod operator std::string() const noexcept {
				return msg();
			}

			inline const exit_status& also_send(std::ostream& stream = std::cerr) const {
				stream << msg() << std::endl;
				return *this;
			}
			inline const exit_status& operator()(std::ostream& stream = std::cerr) const {
				return also_send(stream);
			}
	};
}

inline std::ostream& operator<<(std::ostream& stream,
                                const commoncodes::exit_status& exit_status) {
	return stream << exit_status.msg();
}

#endif /* _COMMONCODES_BITS_STATUSES_EXIT_STATUS_HPP */
