/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include <algorithm>
#include <numeric>
#include <valarray>

namespace raytracer::geometry
{
	template< typename T >
	using vector = std::valarray< T >;

	template< typename Iterator >
		void normalize(
			Iterator begin,
			Iterator end )
	{
		using value_type = std::iterator_traits< Iterator >::value_type;

		value_type root_sum_squared =
			std::sqrt(
				std::accumulate( begin, end, value_type(), []( const value_type& left, const value_type& right )
				{
					return left + right * right;
				} ) );

		std::transform( begin, end, begin, [&root_sum_squared]( value_type element )
		{
			return element / root_sum_squared;
		} );
	}
}