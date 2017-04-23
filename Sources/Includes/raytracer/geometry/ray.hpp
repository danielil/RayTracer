/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/geometry/spatial_vector.hpp"

namespace raytracer::geometry
{
	template< typename T >
	struct ray
	{
		vector< T > origin;
		vector< T > direction;
	};
}