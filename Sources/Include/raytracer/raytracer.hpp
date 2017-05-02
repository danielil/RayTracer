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
		const object_container& objects )
	{
		const geometry::spatial_vector light { rows / 2.0, columns / 2.0, 600.0 };

		vector_container elements( rows, columns );

		for ( vector_container::size_type row = 0; row < rows; ++row )
		{
			for ( vector_container::size_type column = 0; column < columns; ++column )
			{
				auto value = vector_type();

				const geometry::ray ray
				{
					geometry::spatial_vector { vector_type( row ), vector_type( column ), 0 },
					geometry::spatial_vector { 0, 0, 1 }
				};
				
				for ( const auto& object : objects )
				{
					if ( auto center_ray = object->intersect( ray ) )
					{
						const auto vector_from_intersection = ray.origin + ray.direction * center_ray.value();
						auto light_from_intersection = light - vector_from_intersection;
						auto normal = object->normal( vector_from_intersection );

						geometry::normalize( std::begin( light_from_intersection ), std::end( light_from_intersection ) );

						value =
							std::inner_product(
								std::begin( light_from_intersection ),
								std::end( light_from_intersection ),
								std::begin( normal ),
								vector_type() );

						elements[row][column] = value_map::color_map( object->get_channels(), value );

						break;
					}
					else
					{
						elements[row][column] = { 0, 0, 0 };
					}
				}
			}
		}

		return elements;
	}
}