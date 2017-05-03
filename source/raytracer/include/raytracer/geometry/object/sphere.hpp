/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/alias.hpp"
#include "raytracer/geometry/ray.hpp"
#include "raytracer/geometry/spatial_vector.hpp"
#include "raytracer/geometry/object/object.hpp"

#include <optional>

namespace raytracer::geometry::object
{
	class sphere : public object
	{
	public:
		~sphere() noexcept override = default;

		template< typename SpatialVector >
		sphere(
			SpatialVector&& center,
			vector_type radius,
			image::rgb_container channels ) :
			center( std::forward< SpatialVector >( center ) ),
			radius( radius ),
			channels( channels )
		{
		}

		spatial_vector normal( const spatial_vector& pi ) const override;

		/**
		 * Heavily inspired by https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
		 */
		std::optional< vector_type > intersect( const ray& ray ) const override;

		const image::rgb_container& get_channels() const override;

	private:
		spatial_vector center;
		vector_type radius;
		image::rgb_container channels;
	};
}