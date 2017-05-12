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

#pragma once

#include "raytracer/geometry/ray.hpp"

namespace raytracer::geometry::object
{
	template< typename T >
	struct cube
	{
		template< typename SpatialVector >
		cube( SpatialVector&& min, SpatialVector&& max ) :
			min( std::forward< SpatialVector >( min ) ),
			max( std::forward< SpatialVector >( max ) )
		{
		}

		/**
		 * Heavily inspired from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
		 */
		bool intersect( const ray< T >& ray ) const
		{
			auto tmin = ( min[0] - ray.origin[0] ) / ray.direction[0];
			auto tmax = ( max[0] - ray.origin[0] ) / ray.direction[0];

			if ( tmin > tmax )
			{
				std::swap( tmin, tmax );
			}

			auto tymin = ( min[1] - ray.origin[1] ) / ray.direction[1];
			auto tymax = ( max[1] - ray.origin[1] ) / ray.direction[1];

			if ( tymin > tymax )
			{
				std::swap( tymin, tymax );
			}

			if ( ( tmin > tymax ) || ( tymin > tmax ) )
			{
				return false;
			}

			tmin = std::max( tymin, tmin );
			tmax = std::min( tymax, tmax );

			auto tzmin = ( min[2] - ray.origin[2] ) / ray.direction[2];
			auto tzmax = ( max[2] - ray.origin[2] ) / ray.direction[2];

			if ( tzmin > tzmax )
			{
				std::swap( tzmin, tzmax );
			}

			if ( ( tmin > tzmax ) || ( tzmin > tmax ) )
			{
				return false;
			}

			tmin = std::max( tzmin, tmin );
			tmax = std::min( tzmax, tmax );

			return true;
		}

		spatial_vector< T > min;
		spatial_vector< T > max;
	};
}