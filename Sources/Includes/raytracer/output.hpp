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

		for ( std::size_t row = 0; row < rows; ++row )
		{
			for ( std::size_t column = 0; column < columns; ++column )
			{
				image[row][column] = raytracer::value_mapping::color_map_render_value( render_values[row][column] );
			}
		}

		io::netpbm(
			output,
			io::netpbm::format::ppm,
			io::netpbm::encoding::ascii,
			rows,
			columns ).write( image );
	}
}