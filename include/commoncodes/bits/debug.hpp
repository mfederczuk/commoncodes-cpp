// <commoncodes/bits/debug.hpp>
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

#ifndef _COMMONCODES_BITS_DEBUG_HPP
#define _COMMONCODES_BITS_DEBUG_HPP

#if _COMMONCODES_DEBUG == 1
	#include <iostream>
	#define COMMONCODES_DEBUG_MSG(msg) \
			do { \
				::std::cout << "\e[1m" << __FILE__ << ":" << __LINE__ << ":\e[0m " \
				               "In function \e[1m" << __func__ << ":\e[0m " \
				               "debug: " << (msg) << ::std::endl; \
			} while(0)
#else
	#define COMMONCODES_DEBUG_MSG(msg) do {} while(0)
#endif

#endif /* _COMMONCODES_BITS_DEBUG_HPP */
