/*****************************************************/
/* breeze Engine Math Module    (c) Tobias Zirr 2011 */
/*****************************************************/

#ifndef BE_MATH_PLANE
#define BE_MATH_PLANE

#include "beMath.h"
#include "bePlaneDef.h"
#include "beVector.h"
#include "beMatrix.h"

namespace beMath
{

/// Makes a plane from the given point & normal.
template <class Tuple, class Component, size_t Dimension>
LEAN_INLINE plane<Component, Dimension> mkplane(const class tuple<Tuple, Component, Dimension> &normal, const Component &dist)
{
	return plane<Component, Dimension>(normal, dist);
}

/// Makes a plane from the given point & normal.
template <class Tuple1, class Tuple2, class Component, size_t Dimension>
LEAN_INLINE plane<Component, Dimension> mkplane(const class tuple<Tuple1, Component, Dimension> &normal, const class tuple<Tuple2, Component, Dimension> &point)
{
	return plane<Component, Dimension>(normal, dot(point, normal));
}

/// Transforms the given plane.
template <class Component, size_t Dimension>
LEAN_INLINE plane<Component, Dimension> mul(const matrix<Component, Dimension + 1, Dimension + 1> &left, const plane<Component, Dimension> &right)
{
	return plane<Component, Dimension>( mul(left, right.tpl()) );
}

/// Transforms the given plane.
template <class Component, size_t Dimension>
LEAN_INLINE plane<Component, Dimension> mul(const plane<Component, Dimension> &left, const matrix<Component, Dimension + 1, Dimension + 1> &right)
{
	return plane<Component, Dimension>( mul(left.tpl(), right) );
}

/// Computes the signed distance of the given point from the given plane.
template <class Tuple, class Component, size_t Dimension>
LEAN_INLINE Component sdist(const plane<Component, Dimension> &left, const tuple<Tuple, Component, Dimension> &right)
{
	return dot(left.n(), right) - left.d();
}

/// Computes the distance of the given point from the given plane.
template <class Tuple, class Component, size_t Dimension>
LEAN_INLINE Component dist(const plane<Component, Dimension> &left, const tuple<Tuple, Component, Dimension> &right)
{
	return abs(sdist(left, right));
}

/// Computes the distance of the given point from the given plane.
template <class Tuple1, class Tuple2, class Component, size_t Dimension>
LEAN_INLINE Component intersect(const plane<Component, Dimension> &plane,
	const tuple<Tuple1, Component, Dimension> &orig, const tuple<Tuple2, Component, Dimension> &dir)
{
	return -sdist(plane, orig) / dot(plane.n(), dir);
}

/// Normalizes the given vector.
template <class Component, size_t Dimension>
inline plane<Component, Dimension> normalize(const plane<Component, Dimension> &plane)
{
	return plane * (Component(1) / length(plane.n()));
}


namespace Types
{
	using beMath::mkplane;

} // namespace

} // namespace

#endif