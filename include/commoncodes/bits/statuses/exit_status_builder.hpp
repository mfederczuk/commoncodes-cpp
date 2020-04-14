// <commoncodes/bits/statuses/exit_status_builder.hpp>
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

#ifndef _COMMONCODES_BITS_STATUSES_EXIT_STATUS_BUILDER_HPP
#define _COMMONCODES_BITS_STATUSES_EXIT_STATUS_BUILDER_HPP

#include <commoncodes/bits/config.hpp>
#include <commoncodes/bits/statuses/exit_status.hpp>
#include <iostream>
#include <string>

#define __cc_exsb_prop(cls, type, name) \
	inline cls& name(const type& name) { \
		this->_ ## name = name; \
		return *this; \
	}

namespace commoncodes {
	struct exit_status_builder {
		private:
			int _code;

		public:
			constexpr exit_status_builder(int code = 0) : _code(code) {}

			constexpr int code() const noexcept {
				return _code;
			}
			constexpr operator int() const noexcept {
				return code();
			}

			virtual std::string msg() const = 0;
			inline operator std::string() const {
				return msg();
			}

			inline exit_status also_send(std::ostream& stream = std::cerr) const {
				return build().also_send(stream);
			}
			inline exit_status operator()(std::ostream& stream = std::cerr) const {
				return also_send(stream);
			}

			inline exit_status build() const {
				return exit_status(code(), msg());
			}
			inline operator exit_status() const {
				return build();
			}

		protected:
			static __cc_str_op_mod void add_prefix(std::string& msg,
			                                       const std::string& pfx) {
				if(!pfx.empty()) msg = pfx + ": " + msg;
			}
			static __cc_str_op_mod void add_suffix(std::string& msg,
			                                       const std::string& sfx) {
				if(!sfx.empty()) msg += ": " + sfx;
			}
	};
}

inline std::ostream& operator<<(std::ostream& stream,
                                const commoncodes::exit_status_builder& exit_status_builder) {
	return stream << exit_status_builder.msg();
}

#endif /* _COMMONCODES_BITS_STATUSES_EXIT_STATUS_BUILDER_HPP */
