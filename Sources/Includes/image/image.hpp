/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "containers/matrix.hpp"

#include <array>

namespace image
{
	template< typename T >
	using image_container = containers::matrix< T >;

	using binary_image = image_container< bool >;

	using channel_type = std::uint8_t;
	using monochrome_image = image_container< channel_type >;

	static constexpr std::size_t CHANNELS = 3;
	static constexpr std::size_t RED_CHANNEL = 3;
	static constexpr std::size_t GREEN_CHANNEL = 3;
	static constexpr std::size_t BLUE_CHANNEL = 3;
	using rgb_container = std::array< channel_type, CHANNELS >;
	using rgb_image = image_container< rgb_container >;

	static constexpr auto MAX_CHANNEL_VALUE = std::numeric_limits< channel_type >::max();
}