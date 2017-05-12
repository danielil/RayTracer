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

#include "raytracer/raytracer.hpp"

namespace raytracer
{
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