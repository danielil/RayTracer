/**
 * The MIT License (MIT)
 * Copyright (c) 2017-2017 Daniel Sebastian Iliescu, http://dansil.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "raytracer/geometry/object/sphere.hpp"

namespace raytracer::geometry::object
{
	/**
	 * Heavily inspired by https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
	 */
	std::optional< point > sphere::intersect( const ray& ray ) const
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

		// The intersection point is computed by adding the ray origin to the ray direction
		// multiplied by a scalar representing the z coordinate of the intersection.
		// 
		// Intersection (Point) = Ray Origin (Point) + Ray Direction (Vector) * Center Ray (Scalar)
		// Point + Vector * Scalar -> Point + Vector -> Point
		return ray.origin + ray.direction * center_ray;
	}

	spatial_vector sphere::normal( const point& intersection_point ) const
	{
		// The normal of a sphere is simply calculated by subtracting its center
		// from any intersection point. However, this result will still need
		// to be normalized.
		auto normal = intersection_point - center;

		normalize( std::begin( normal ), std::end( normal ) );

		return normal;
	}

	const image::rgb_container& sphere::get_color() const
	{
		return this->channels;
	}
}