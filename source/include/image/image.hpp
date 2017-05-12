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

#include "container/matrix.hpp"

#include <array>

namespace image
{
	using channel_type = std::uint8_t;
	static constexpr auto MIN_CHANNEL_VALUE = std::numeric_limits< channel_type >::min();
	static constexpr auto MAX_CHANNEL_VALUE = std::numeric_limits< channel_type >::max();

	template< typename T >
	using image = container::matrix< T >;

	template < typename T, std::size_t N >
	using channel_container = std::array< T, N >;

	/**
	 * Type of images.
	 */
	using binary_container = channel_container< bool, 1 >;
	using binary_image = image< binary_container >;

	using monochrome_container = channel_container< channel_type, 1U >;
	using monochrome_image = image< monochrome_container >;

	using rgb_container = channel_container< channel_type, 3U >;
	using rgb_image = image< rgb_container >;
}