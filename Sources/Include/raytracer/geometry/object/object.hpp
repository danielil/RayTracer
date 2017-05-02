/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "image/image.hpp"

#include "raytracer/alias.hpp"

#include <optional>

namespace raytracer::geometry::object
{
	class object
	{
	public:
		virtual ~object() noexcept = default;

		virtual spatial_vector normal( const spatial_vector& pi ) const = 0;
		virtual std::optional< vector_type > intersect( const ray& ray ) const = 0;

		virtual const image::rgb_container& get_channels() const = 0;
	};
}