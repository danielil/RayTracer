/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/geometry/spatial_vector.hpp"

namespace raytracer::geometry
{
	struct ray
	{
		spatial_vector origin;
		spatial_vector direction;
	};
}