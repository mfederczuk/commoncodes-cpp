// <commoncodes/bits/statuses/v1/1_generic_error.hpp>
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

#ifndef _COMMONCODES_BITS_STATUSES_V1_1_GENERIC_ERROR_HPP
#define _COMMONCODES_BITS_STATUSES_V1_1_GENERIC_ERROR_HPP

#include <commoncodes/bits/config.hpp>
#include <commoncodes/bits/statuses/exit_status_builder.hpp>
#include <string>

namespace commoncodes::v1 {
	struct generic_error : exit_status_builder {
		private:
			std::string _origin = "";
			std::string _info = "";

		public:
			__cc_str_op_mod generic_error() : exit_status_builder(1) {}

			__cc_exsb_prop(generic_error, std::string, origin);
			__cc_exsb_prop(generic_error, std::string, info);

			std::string msg() const noexcept override;
	};
}

#endif /* _COMMONCODES_BITS_STATUSES_V1_1_GENERIC_ERROR_HPP */
