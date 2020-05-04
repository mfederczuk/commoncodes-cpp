// <commoncodes/bits/args/opt.hpp>
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

#ifndef _COMMONCODES_BITS_ARGS_OPT_HPP
#define _COMMONCODES_BITS_ARGS_OPT_HPP

#include <commoncodes/bits/args/opt_id.hpp>
#include <cstdint>
#include <string>
#include <vector>

namespace commoncodes {
	struct opt {
		private:
			static constexpr uint8_t _no_arg = 0;
			static constexpr uint8_t _arg_required = 1;
			static constexpr uint8_t _arg_optional = 2;

			opt_id _id;
			std::vector<char> _short_aliases;
			std::vector<std::string> _long_aliases;
			uint8_t _arg;

			inline opt(const opt_id& id,
			           const std::vector<char>& short_aliases,
			           const std::vector<std::string>& long_aliases,
			           uint8_t arg) noexcept
					: _id(id),
					  _short_aliases(short_aliases),
					  _long_aliases(long_aliases),
					  _arg(arg) {
			}

		public:
			inline opt(const opt_id& id,
			           const std::vector<char>& short_aliases,
			           const std::vector<std::string>& long_aliases,
			           bool arg_required) noexcept
					: opt(id,
					      short_aliases,
					      long_aliases,
					      arg_required ? _arg_required : _arg_optional) {
			}
			inline opt(const opt_id& id,
			           const std::vector<char>& short_aliases,
			           const std::vector<std::string>& long_aliases) noexcept
					: opt(id, short_aliases, long_aliases, _no_arg) {
			}
			inline opt() noexcept : opt(unknown_opt_id, {}, {}) {}

			constexpr const opt_id& id() const noexcept {
				return _id;
			}

			inline const std::vector<char>& short_aliases() const noexcept {
				return _short_aliases;
			}
			inline const std::vector<std::string>& long_aliases() const noexcept {
				return _long_aliases;
			}

			constexpr bool has_arg() const noexcept {
				return _arg == _arg_required || _arg == _arg_optional;
			}
			constexpr bool arg_required() const noexcept {
				return _arg == _arg_required;
			}
			constexpr bool arg_optional() const noexcept {
				return _arg == _arg_optional;
			}

			inline bool operator==(const opt& rhs) const noexcept {
				return _id == rhs._id &&
				       _short_aliases == rhs._short_aliases &&
				       _long_aliases == rhs._long_aliases &&
				       _arg == rhs._arg;
			}
			inline bool operator!=(const opt& rhs) const noexcept {
				return _id != rhs._id ||
				       _short_aliases != rhs._short_aliases ||
				       _long_aliases != rhs._long_aliases ||
				       _arg != rhs._arg;
			}

			struct builder {
				private:
					opt_id _id = unknown_opt_id;
					std::vector<char> _short_aliases = {};
					std::vector<std::string> _long_aliases = {};
					uint8_t _arg = _no_arg;

				public:
					inline builder() {}

					inline builder& id(const opt_id& id) noexcept {
						this->_id = id;
						return *this;
					}
					inline builder& id(char id) noexcept {
						return this->id(opt_id(id));
					}
					inline builder& id(const std::string& id) noexcept {
						return this->id(opt_id(id.c_str()));
					}

					inline builder& alias(char short_alias) noexcept {
						this->_short_aliases.push_back(short_alias);
						return *this;
					}
					inline builder& alias(const std::string& long_alias) noexcept {
						this->_long_aliases.push_back(long_alias);
						return *this;
					}
					inline builder& alias(char short_alias,
					                                       const std::string& long_alias) noexcept {
						return alias(short_alias).alias(long_alias);
					}

					inline builder& short_aliases(const std::vector<char>& short_aliases) noexcept {
						this->_short_aliases.insert(this->_short_aliases.end(),
						                            short_aliases.begin(),
						                            short_aliases.end());
						return *this;
					}
					inline builder& long_aliases(const std::vector<std::string>& long_aliases) noexcept {
						this->_long_aliases.insert(this->_long_aliases.end(),
						                           long_aliases.begin(),
						                           long_aliases.end());
						return *this;
					}
					inline builder& aliases(const std::vector<char>& short_aliases,
					                        const std::vector<std::string>& long_aliases) noexcept {
						return this->short_aliases(short_aliases).long_aliases(long_aliases);
					}

					inline builder& no_arg() noexcept {
						_arg = _no_arg;
						return *this;
					}
					inline builder& arg_required(bool required = true) noexcept {
						_arg = required ? _arg_required : _arg_optional;
						return *this;
					}
					inline builder& arg_optional(bool optional = true) noexcept {
						_arg = optional ? _arg_optional : _arg_required;
						return *this;
					}

					inline opt build() const noexcept {
						return opt(_id, _short_aliases, _long_aliases, _arg);
					}
					inline operator opt() const noexcept {
						return build();
					}
			};
	};
}

#endif /* _COMMONCODES_BITS_ARGS_OPT_HPP */
