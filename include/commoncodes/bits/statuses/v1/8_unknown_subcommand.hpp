// <commoncodes/bits/statuses/v1/8_unknown_subcommand.hpp>
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

#ifndef _COMMONCODES_BITS_STATUSES_V1_8_UNKNOWN_SUBCOMMAND_HPP
#define _COMMONCODES_BITS_STATUSES_V1_8_UNKNOWN_SUBCOMMAND_HPP

#include <commoncodes/bits/config.hpp>
#include <commoncodes/bits/statuses/exit_status_builder.hpp>
#include <string>

namespace commoncodes::v1 {
	struct unknown_subcommand : exit_status_builder {
		private:
			std::string _origin = "";
			std::string _argument = "";
			bool        _subcommand = false;

		public:
			__cc_str_op_mod unknown_subcommand() : exit_status_builder(8) {}

			__cc_exsb_prop(unknown_subcommand, std::string, origin);
			__cc_exsb_prop(unknown_subcommand, std::string, argument);
			__cc_exsb_prop(unknown_subcommand, bool,        subcommand);

			std::string msg() const override;
	};
}

#endif /* _COMMONCODES_BITS_STATUSES_V1_8_UNKNOWN_SUBCOMMAND_HPP */
