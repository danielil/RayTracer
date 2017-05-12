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

#include "raytracer/alias.hpp"

#include <algorithm>
#include <numeric>
#include <valarray>

namespace raytracer::geometry
{
	using spatial_vector = std::valarray< vector_type >;

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