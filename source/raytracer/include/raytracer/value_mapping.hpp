/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/alias.hpp"

#include "image/image.hpp"

#include <algorithm>

namespace raytracer::value_map
{
	image::rgb_container color_map(
		image::rgb_container channels,
		raytracer::vector_type render_value );
}