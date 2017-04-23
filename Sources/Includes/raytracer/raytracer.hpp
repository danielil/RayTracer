/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "containers/matrix.hpp"

#include "raytracer/geometry/ray.hpp"
#include "raytracer/geometry/sphere.hpp"

namespace raytracer
{
	using vector_type = double;

	containers::matrix< vector_type > compute_render_values( const std::size_t rows, const std::size_t columns )
	{
		const geometry::sphere< vector_type > sphere( geometry::vector< vector_type > { columns / 2.0, rows / 2.0, 50.0 }, 500000 );
		const geometry::sphere< vector_type > light( geometry::vector< vector_type > { 0, 0, 50 }, 1 );

		containers::matrix< vector_type > elements( rows, columns );

		for ( std::size_t row = 0; row < rows; ++row )
		{
			for ( std::size_t column = 0; column < columns; ++column )
			{
				vector_type value = vector_type();

				const geometry::ray< vector_type > ray { geometry::vector< vector_type > { double( row ), double( column ), 0 }, geometry::vector< vector_type > { 0, 0, 1 } };
				if ( auto center_ray = sphere.intersect( ray ) )
				{
					const geometry::vector< vector_type > vector_from_intersection = ray.origin + ray.direction * *center_ray;
					geometry::vector< vector_type > light_from_intersection = light.center - vector_from_intersection;
					geometry::vector< vector_type > sphere_normal = sphere.normal( vector_from_intersection );

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