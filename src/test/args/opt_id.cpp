#include <commoncodes/bits/args/opt_id.hpp>
#include <cstddef>
#include <functional>

namespace cc = commoncodes;
using cc::opt_id;
using cc::unknown_opt_id;
using std::hash;

constexpr const opt_id foo1 = opt_id(64);
constexpr const opt_id bar1 = opt_id('b');
constexpr const opt_id baz1 = opt_id("baz");

int main() {
	constexpr const size_t foo_n = 64;
	constexpr const opt_id foo2 = foo_n;
	constexpr const opt_id bar2 = opt_id('b');
	constexpr const opt_id baz2 = opt_id("baz");

	static_assert(foo1 == foo2);
	static_assert(bar1 == bar2);
	static_assert(baz1 == baz2);

	static_assert(foo1 != bar1);
	static_assert(bar1 != baz1);

	static_assert(foo_n == foo2.id());

	static_assert(foo1 != unknown_opt_id);
	static_assert(bar1 != unknown_opt_id);
	static_assert(baz1 != unknown_opt_id);

	static_assert(hash<opt_id>{}(foo1) == foo1.id());
	static_assert(hash<opt_id>{}(bar1) == bar1.id());
	static_assert(hash<opt_id>{}(baz1) == baz1.id());
	static_assert(hash<opt_id>{}(unknown_opt_id) == unknown_opt_id.id());
}
