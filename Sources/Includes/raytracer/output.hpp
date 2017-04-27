/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/raytracer.hpp"
#include "raytracer/value_mapping.hpp"

#include "utilities/netpbm.hpp"

namespace raytracer
{
	void output_to_file( const std::string output )
	{
		constexpr std::size_t rows = 2000;
		constexpr std::size_t columns = 2000;

		image::rgb_image image( rows, columns );
		const auto render_values = raytracer::compute_render_values( rows, columns );

		for ( image::rgb_image::size_type row = 0; row < rows; ++row )
		{
			std::transform(
				std::cbegin( render_values[row] ),
				std::cend( render_values[row] ),
				std::begin( image[row] ),
				raytracer::value_map::color_map );
		}

		utilities::netpbm(
			output,
			utilities::netpbm::format::ppm,
			utilities::netpbm::encoding::ascii,
			rows,
			columns ).write( image );
	}
}