// <commoncodes/bits/args/option_id.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_OPTION_ID_HPP
#define _COMMONCODES_BITS_ARGS_OPTION_ID_HPP

#include <cstddef>
#include <functional>

namespace commoncodes {
	struct option_id {
		private:
			static constexpr size_t hash_str(const char* str) noexcept {
				size_t hash = 1;

				for(size_t i = 0; str[i] != '\0'; ++i) {
					hash = 37 * hash + str[i];
				}

				return hash;
			}

			size_t _id;

		public:
			constexpr option_id(size_t id) noexcept : _id(id) {}
			constexpr option_id(int id) noexcept : option_id((size_t)id) {}

			explicit constexpr option_id(char short_alias) noexcept
					: option_id((size_t)short_alias * 2) {
			}
			explicit constexpr option_id(const char* long_alias) noexcept
					: option_id(hash_str(long_alias)) {
			}

			constexpr size_t id() const noexcept {
				return _id;
			}

			constexpr bool operator==(const option_id& rhs) const noexcept {
				return _id == rhs._id;
			}
			constexpr bool operator!=(const option_id& rhs) const noexcept {
				return _id != rhs._id;
			}

			friend struct std::hash<option_id>;
	};

	inline constexpr const option_id unknown_option_id = option_id((size_t)-1);
}

namespace std {
	template<>
	struct hash<commoncodes::option_id> {
		constexpr size_t operator()(const commoncodes::option_id& opt_id) const noexcept {
			return opt_id._id;
		}
	};
}

#endif /* _COMMONCODES_BITS_ARGS_OPTION_ID_HPP */
