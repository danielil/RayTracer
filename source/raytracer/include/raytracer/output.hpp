/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/alias.hpp"
#include "raytracer/raytracer.hpp"
#include "raytracer/geometry/spatial_vector.hpp"
#include "raytracer/geometry/object/object.hpp"
#include "raytracer/geometry/object/sphere.hpp"

#include "utility/netpbm.hpp"

#include <memory>
#include <vector>

namespace raytracer
{
	object_container generate_spheres();

	void output_to_file(
		const std::size_t rows,
		const std::size_t columns,
		const std::string output );
}