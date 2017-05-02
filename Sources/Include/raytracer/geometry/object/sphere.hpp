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

		spatial_vector normal( const spatial_vector& pi ) const override
		{
			auto normal = ( pi - center ) / radius;

			normalize( std::begin( normal ), std::end( normal ) );

			return normal;
		}

		/**
		 * Heavily inspired by https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
		 */
		std::optional< vector_type > intersect( const ray& ray ) const override
		{
			auto vector_between_origin_and_center = center - ray.origin;

			const auto normal_coefficient =
				std::inner_product(
					std::begin( vector_between_origin_and_center ),
					std::end( vector_between_origin_and_center ),
					std::begin( ray.direction ),
					vector_type() );
			const auto distance_squared =
				std::inner_product(
					std::begin( vector_between_origin_and_center ),
					std::end( vector_between_origin_and_center ),
					std::begin( vector_between_origin_and_center ),
					vector_type() ) - normal_coefficient * normal_coefficient;

			if ( distance_squared > radius )
			{
				return {};
			}

			const auto normal_coefficient_within_sphere = std::sqrt( radius - distance_squared );

			auto center_ray = normal_coefficient - normal_coefficient_within_sphere;
			auto passthrough_ray = normal_coefficient + normal_coefficient_within_sphere;

			if ( center_ray > passthrough_ray )
			{
				std::swap( passthrough_ray, center_ray );
			}

			if ( center_ray < 0 )
			{
				center_ray = passthrough_ray;

				if ( center_ray < 0 )
				{
					return {};
				}
			}

			return center_ray;
		}

		const image::rgb_container& get_channels() const override
		{
			return this->channels;
		}

	private:
		spatial_vector center;
		vector_type radius;
		image::rgb_container channels;
	};
}