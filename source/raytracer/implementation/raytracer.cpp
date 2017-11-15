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

#include "raytracer/geometry/ray.hpp"
#include "raytracer/geometry/spatial_vector.hpp"

#include "raytracer/value_map.hpp"

namespace raytracer
{
	image::rgba_image render::trace( const scene& scene )
	{
		const auto& metadata = scene.get_metadata();
		const auto& elements = scene.get_elements();

		image::rgba_image traces( metadata.rows, metadata.columns, image::RGBA_CHANNELS );

		#pragma omp parallel for
		for ( metadata::size_type row = 0; row < metadata.rows; ++row )
		{
			for ( metadata::size_type column = 0; column < metadata.columns; ++column )
			{
				const auto& channels = this->trace( row, column, elements );

				for ( image::rgba_container::value_type channel = 0; channel < channels.size(); ++channel )
				{
					traces( row, column, channel ) = channels[channel];
				}
			}
		}

		return traces;
	}

	image::rgba_container render::trace(
		const metadata::size_type row,
		const metadata::size_type column,
		const elements& element )
	{
		// The current ray's origin is always associated with the current row and column scanned.
		const geometry::ray ray
		{
			geometry::point { geometry::point::value_type( row ), geometry::point::value_type( column ), geometry::point::value_type() },
			geometry::spatial_vector { geometry::spatial_vector::value_type(), geometry::spatial_vector::value_type(), geometry::spatial_vector::value_type( 1 ) }
		};

		// Compute the intersection of the ray for every object in the scene. The trace algorithm does not
		// currently support multiple intersecting objects and performs early exit on the first object
		// intersected.
		for ( const auto& object : element.objects )
		{
			// Compute the intersection point of the ray with the object. Color is mapped for the current pixel
			// only if the ray intersects the object. Otherwise, the pixel is rendered black.
			if ( const auto intersection_point = object->intersect( ray ) )
			{
				// Container of all illumination projections unto an object.
				std::vector< vector_type > projections;

				// Calculate the illumination unto an object given every possible illumination in the scene.
				for ( const auto& illumination : element.illuminations )
				{
					// Normal (towards light) at the intersection point
					//
					// Intersection Normal (Vector) = Light (Point) - Intersection (Point)
					// Point - Point -> Vector
					auto intersection_normal_towards_light = illumination - intersection_point.value();

					// Compute the normal (vector) of the object given an intersection point. The normal of the
					// object returned is a unit vector for use in the dot product with the normal intersection
					// towards the point light.
					auto object_normal = object->normal( intersection_point.value() );

					// The normal intersection towards the point light also needs to be a unit vector for use in
					// the dot product calculation.
					geometry::normalize( std::begin( intersection_normal_towards_light ), std::end( intersection_normal_towards_light ) );

					// The value computed is that of the dot product between the normal of the object and the
					// normal at the intersection point towards the point light.
					//
					// The projection of the intersection normal towards the object normal will yield greater
					// values as both vectors become more similarly directed. As these vectors become less
					// similarly directed, the dot product of these two vectors will yield a lower value. In other
					// cases, the angle between both vectors will be greater than 90 degrees and lower than 270
					// degrees, placing them in opposite directions. This will yield a negative dot product due to
					// the cosine of such an angle, which returns a negative value.
					projections.emplace_back(
						std::inner_product(
							std::cbegin( intersection_normal_towards_light ),
							std::cend( intersection_normal_towards_light ),
							std::cbegin( object_normal ),
							vector_type() ) );
				}

				// Given a container of illumination projections unto an object, we need to retrieve a single
				// mapped value. We can simply accumulate all of the projection values for a given object
				// intersection. The more positive projections unto an object intersection, the greater the
				// reflected illuminance at that point.
				//
				// Negative projection values are not accumulated because it would lower the reflectance of an
				// object at given intersection. One light source yielding a negative projection unto an
				// intersection should not lower the overall reflectance because that same intersection could
				// be projected by another light source.
				const auto value =
					std::accumulate(
						std::cbegin( projections ),
						std::cend( projections ),
						vector_type(),
						[]( const auto& first, const auto& second )
						{
							return first + ( second >= vector_type() ? second : vector_type() );
						} );

				// Color mapping is performed on the intensity of the projection computed. Color mapping returns
				// a value linearly proportional to the intensity value. At peak intensity, the pixel reflects
				// the object's maximal color value. This color value decreases (darkens) proportionally to the
				// computed intensity. No color is mapped for negative intensity values, resulting in a black pixel.
				return value_map::channels( object->get_channels(), value );
			}
		}

		return { image::MIN_CHANNEL_VALUE, image::MIN_CHANNEL_VALUE, image::MIN_CHANNEL_VALUE, image::MAX_CHANNEL_VALUE };
	}
}