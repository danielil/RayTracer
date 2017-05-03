/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "container/matrix.hpp"

#include "image/image.hpp"

#include "raytracer/alias.hpp"
#include "raytracer/value_mapping.hpp"
#include "raytracer/geometry/ray.hpp"
#include "raytracer/geometry/spatial_vector.hpp"
#include "raytracer/geometry/object/object.hpp"

#include <memory>
#include <vector>

namespace raytracer
{
	using vector_container = image::rgb_image;
	using object_container = std::vector< std::shared_ptr< geometry::object::object > >;

	vector_container generate_image(
		const vector_container::size_type rows,
		const vector_container::size_type columns,
		const object_container& objects );
}