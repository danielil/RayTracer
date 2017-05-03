/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "raytracer/geometry/object/sphere.hpp"

namespace raytracer::geometry::object
{
	spatial_vector sphere::normal( const spatial_vector& pi ) const
	{
		auto normal = ( pi - center ) / radius;

		normalize( std::begin( normal ), std::end( normal ) );

		return normal;
	}

	/**
		* Heavily inspired by https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
		*/
	std::optional< vector_type > sphere::intersect( const ray& ray ) const
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

	const image::rgb_container& sphere::get_channels() const
	{
		return this->channels;
	}
}