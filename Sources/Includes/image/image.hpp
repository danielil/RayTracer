/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "containers/matrix.hpp"

#include <array>

namespace image
{
	using channel_type = std::uint8_t;
	static constexpr auto MAX_CHANNEL_VALUE = std::numeric_limits< channel_type >::max();

	template< typename T >
	using image = containers::matrix< T >;

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