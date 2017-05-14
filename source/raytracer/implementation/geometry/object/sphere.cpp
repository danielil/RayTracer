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
	std::optional< point > sphere::intersect( const ray& ray ) const
	{
		// Vector between the center of the sphere and the origin of the ray.
		auto origin_to_center_vector = this->center - ray.origin;

		// Dot product between the direction of the ray and the origin to center vector.
		const auto camera_ray_projection =
			std::inner_product(
				std::begin( origin_to_center_vector ),
				std::end( origin_to_center_vector ),
				std::begin( ray.direction ),
				vector_type() );

		// Early return if camera ray projection is negative. In this case, the dot product returns a negative value,
		// meaning both vectors are in opposite directions.
		if ( camera_ray_projection < vector_type() )
		{
			return {};
		}

		// Given the camera and ray vectors, we can visualize a triangle and compute the length of the hypotenuse. This
		// length will represent the distance between the center of the sphere and the reach of the ray direction
		// vector, which will be a point.
		//
		// Hypotenuse (Scalar) =
		//	origin_to_center (Vector) * origin_to_center (Vector) -
		//	camera_ray_projection (Scalar) * camera_ray_projection (Scalar);
		//
		// Vector * Vector - Scalar * Scalar -> Scalar - Scalar -> Scalar
		//
		// An optimization is possible since we never actually need the hypothenuse directly. We can always use the
		// hypothenuse squared.
		const auto hypotenuse_squared = 
			std::inner_product(
				std::begin( origin_to_center_vector ),
				std::end( origin_to_center_vector ),
				std::begin( origin_to_center_vector ),
				vector_type() ) -
			camera_ray_projection * camera_ray_projection;

		// If the computed hypotenuse is within the sphere, the value will be equal to or lower than the radius of the
		// sphere. If the value is greater than the radius of the sphere, we know that the ray direction vector did not
		// intersect the sphere.
		//
		// Since we are using the hypotenuse squared, it must be compared to the radius squared.
		const auto radius_squared = this->radius * this->radius;
		if ( hypotenuse_squared > radius_squared )
		{
			return {};
		}

		// The half length between points is half the length between the intersecting point entering the sphere or the
		// one exiting the sphere. This value will be added or substracted to the camera ray projection to retrieve the
		// distance from the ray origin to either points.
		const auto half_length_between_points = std::sqrt( radius_squared - hypotenuse_squared );

		// The distance between the ray origin and the intersection point entering the sphere is equivalent to the
		// difference between the camera ray projection and the half length between the two points.
		auto entering_intersection_distance = camera_ray_projection - half_length_between_points;

		// The distance between the ray origin and the intersection point entering the sphere is equivalent to the
		// addition of the camera ray projection and the half length between the two points.
		auto exiting_intersection_distance = camera_ray_projection + half_length_between_points;

		// The entering intersection distance cannot be greater than the exiting intersection distance.
		if ( entering_intersection_distance > exiting_intersection_distance )
		{
			std::swap( exiting_intersection_distance, entering_intersection_distance );
		}

		// If the entering intersection point is negative, we want to try to use the exiting intersection point.
		if ( entering_intersection_distance < vector_type() )
		{
			entering_intersection_distance = exiting_intersection_distance;

			// Both the entering and exiting intersection points are negative, so we don't have a solution for the
			// intersection of this ray with the sphere.
			if ( entering_intersection_distance < vector_type() )
			{
				return {};
			}
		}

		// The intersection point is computed by adding the ray origin to the ray direction multiplied by a scalar
		// representing the z-coordinate of the intersection.
		// 
		// Intersection (Point) = Ray Origin (Point) + Ray Direction (Vector) * Center Ray (Scalar)
		// Point + Vector * Scalar -> Point + Vector -> Point
		return ray.origin + ray.direction * entering_intersection_distance;
	}

	spatial_vector sphere::normal( const point& intersection_point ) const
	{
		// The normal of a sphere is simply calculated by subtracting its center from any intersection point. However,
		// this result will still need to be normalized.
		auto normal = intersection_point - center;

		normalize( std::begin( normal ), std::end( normal ) );

		return normal;
	}

	const image::rgb_container& sphere::get_color() const
	{
		return this->channels;
	}
}