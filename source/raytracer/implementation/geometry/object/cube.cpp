/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

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