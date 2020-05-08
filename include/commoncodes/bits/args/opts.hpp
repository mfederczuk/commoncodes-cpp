// <commoncodes/bits/args/opts.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_OPTS_HPP
#define _COMMONCODES_BITS_ARGS_OPTS_HPP

#include <commoncodes/bits/args/opt.hpp>

#define commoncodes_opt(name, id_) \
		inline const ::commoncodes::opt name = ::commoncodes::opt::builder().id(::commoncodes::option_id(id_))

namespace commoncodes::opts {
	#define __cc_opt_id_base "::commoncodes::opts::"
	#define __cc_tmp(name) commoncodes_opt(name, __cc_opt_id_base #name)

	#define __cc_silent_quiet_opt_id __cc_opt_id_base "silent/quiet"

	__cc_tmp(       help)                            .alias('h', "help");
	__cc_tmp(       version_info)                    .alias('V', "version");
	__cc_tmp(       commoncodes_version)             .alias(     "commoncodes-version");
	__cc_tmp(       verbose)                         .alias('v', "verbose");
	__cc_tmp(       color)                           .alias(     "color").arg_optional();
	__cc_tmp(       output)                          .alias('o', "output").arg_required();
	__cc_tmp(       force)                           .alias('f', "force");
	commoncodes_opt(silent, __cc_silent_quiet_opt_id).alias('s', "silent");
	commoncodes_opt(quiet,  __cc_silent_quiet_opt_id).alias('q', "quiet");
	__cc_tmp(       interactive)                     .alias('i', "interactive");
	__cc_tmp(       zero)                            .alias('z', "zero");
	__cc_tmp(       dry_run)                         .alias(     "dry-run");

	#undef __cc_silent_quiet_opt_id

	#undef __cc_tmp
	#undef __cc_opt_id_base
}

#endif /* _COMMONCODES_BITS_ARGS_OPTS_HPP */
