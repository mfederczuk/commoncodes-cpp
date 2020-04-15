// <commoncodes/bits/statuses/v1/5_invalid_option.hpp>
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

#ifndef _COMMONCODES_BITS_STATUSES_V1_5_INVALID_OPTION_HPP
#define _COMMONCODES_BITS_STATUSES_V1_5_INVALID_OPTION_HPP

#include <commoncodes/bits/config.hpp>
#include <commoncodes/bits/statuses/exit_status_builder.hpp>
#include <string>

namespace commoncodes::v1 {
	struct invalid_option : exit_status_builder {
		private:
			std::string _origin = "";
			std::string _option = "";

		public:
			__cc_str_op_mod invalid_option() : exit_status_builder(5) {}

			__cc_exsb_prop(invalid_option, std::string, origin);
			__cc_exsb_prop(invalid_option, std::string, option);

			std::string msg() const override;
	};
}

#endif /* _COMMONCODES_BITS_STATUSES_V1_5_INVALID_OPTION_HPP */
