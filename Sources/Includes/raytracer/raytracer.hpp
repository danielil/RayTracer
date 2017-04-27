/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "containers/matrix.hpp"

#include "raytracer/alias.hpp"
#include "raytracer/geometry/ray.hpp"
#include "raytracer/geometry/sphere.hpp"

namespace raytracer
{
	using vector_container = containers::matrix< vector_type >;

	containers::matrix< vector_type > compute_render_values(
		const vector_container::size_type rows,
		const vector_container::size_type columns )
	{
		const geometry::sphere< vector_type > sphere
		(
			geometry::spatial_vector< vector_type >
			{
				columns / 2.0,
				rows / 2.0,
				50.0
			},
			500000
		);

		const geometry::sphere< vector_type > light
		(
			geometry::spatial_vector< vector_type >
			{
				0,
				0,
				50
			},
			1
		);

		vector_container elements( rows, columns );

		for ( vector_container::size_type row = 0; row < rows; ++row )
		{
			for ( vector_container::size_type column = 0; column < columns; ++column )
			{
				auto value = vector_type();

				const geometry::ray< vector_type > ray
				{
					geometry::spatial_vector< vector_type > { vector_type( row ), vector_type( column ), 0 },
					geometry::spatial_vector< vector_type > { 0, 0, 1 }
				};
				
				if ( auto center_ray = sphere.intersect( ray ) )
				{
					const geometry::spatial_vector< vector_type > vector_from_intersection = ray.origin + ray.direction * *center_ray;
					geometry::spatial_vector< vector_type > light_from_intersection = light.center - vector_from_intersection;
					geometry::spatial_vector< vector_type > sphere_normal = sphere.normal( vector_from_intersection );

					geometry::normalize( std::begin( light_from_intersection ), std::end( light_from_intersection ) );

					value =
						std::inner_product(
							std::begin( light_from_intersection ),
							std::end( light_from_intersection ),
							std::begin( sphere_normal ),
							vector_type() );
				}

				elements[row][column] = value;
			}
		}

		return elements;
	}
}