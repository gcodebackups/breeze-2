/*****************************************************/
/* breeze Engine Math Module    (c) Tobias Zirr 2011 */
/*****************************************************/

#ifndef BE_MATH_CONSTANTS
#define BE_MATH_CONSTANTS

namespace beMath
{

/// Constants.
namespace Constants
{

/// e.
#define BE_MATH_E 2.7182818284590452354

/// PI.
#define BE_MATH_PI 3.14159265358979323846

// WARNING: Always use #defines, never reference other dependent constants
// WARNING: Visual C++' implementation of unordered initialization is really just that: UNORDERED

/// e constants.
template <class Numeric>
struct e
{
	/// e.
	static const Numeric one;
	/// e.
	static const Numeric value;
};

template <class Numeric>
const Numeric e<Numeric>::value = Numeric(BE_MATH_E);
template <class Numeric>
const Numeric e<Numeric>::one = Numeric(BE_MATH_E);

/// Pi constants.
template <class Numeric>
struct pi
{
	/// pi.
	static const Numeric value;

	/// pi / 4.
	static const Numeric quarter;
	/// pi / 2.
	static const Numeric half;
	/// pi.
	static const Numeric one;
	/// 3/2 x pi.
	static const Numeric three_halves;
	/// 2 x pi.
	static const Numeric two;
};

template <class Numeric>
const Numeric pi<Numeric>::value = Numeric(BE_MATH_PI);

template <class Numeric>
const Numeric pi<Numeric>::quarter = Numeric(0.25 * BE_MATH_PI);
template <class Numeric>
const Numeric pi<Numeric>::half = Numeric(0.5 * BE_MATH_PI);
template <class Numeric>
const Numeric pi<Numeric>::one = Numeric(BE_MATH_PI);
template <class Numeric>
const Numeric pi<Numeric>::three_halves = Numeric(1.5 * BE_MATH_PI);
template <class Numeric>
const Numeric pi<Numeric>::two = Numeric(2.0 * BE_MATH_PI);

/// Degree constants.
template <class Numeric>
struct degrees
{
	/// pi / 180.
	static const Numeric deg2rad;
	/// 180 / pi.
	static const Numeric rad2deg;
};

template <class Numeric>
const Numeric degrees<Numeric>::deg2rad = Numeric(BE_MATH_PI / 180.0);
template <class Numeric>
const Numeric degrees<Numeric>::rad2deg = Numeric(180.0 / BE_MATH_PI);

} // namespace

using namespace Constants;

} // namespace

#endif