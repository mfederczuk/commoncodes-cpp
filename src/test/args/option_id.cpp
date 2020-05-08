#include <commoncodes/bits/args/option_id.hpp>
#include <cstddef>
#include <functional>

namespace cc = commoncodes;
using cc::option_id;
using cc::unknown_option_id;
using std::hash;

constexpr const option_id foo1 = option_id(64);
constexpr const option_id bar1 = option_id('b');
constexpr const option_id baz1 = option_id("baz");

int main() {
	constexpr const size_t foo_n = 64;
	constexpr const option_id foo2 = foo_n;
	constexpr const option_id bar2 = option_id('b');
	constexpr const option_id baz2 = option_id("baz");

	static_assert(foo1 == foo2);
	static_assert(bar1 == bar2);
	static_assert(baz1 == baz2);

	static_assert(foo1 != bar1);
	static_assert(bar1 != baz1);

	static_assert(foo_n == foo2.id());

	static_assert(foo1 != unknown_option_id);
	static_assert(bar1 != unknown_option_id);
	static_assert(baz1 != unknown_option_id);

	static_assert(hash<option_id>{}(foo1) == foo1.id());
	static_assert(hash<option_id>{}(bar1) == bar1.id());
	static_assert(hash<option_id>{}(baz1) == baz1.id());
	static_assert(hash<option_id>{}(unknown_option_id) == unknown_option_id.id());
}
