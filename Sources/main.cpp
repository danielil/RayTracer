/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/raytracer.hpp"

#include "utilities/netpbm_writer.hpp"

void render_to_file()
{
	constexpr std::size_t rows = 2000;
	constexpr std::size_t columns = 2000;

	image::rgb_image image( rows, columns );

	const auto render_values = raytracer::compute_render_values( rows, columns );

	constexpr image::rgb_container white { 255, 255, 255 };
	constexpr image::rgb_container black { 0, 0, 0 };
	constexpr image::rgb_container blue { 0, 0, 255 };

	for ( std::size_t row = 0; row < rows; ++row )
	{
		for ( std::size_t column = 0; column < columns; ++column )
		{
			for ( std::size_t channel = 0; channel < image::CHANNELS; ++channel )
			{
				image[row][column][channel] =
					render_values[row][column] == raytracer::vector_type() ?
						black[channel] :
						static_cast< image::channel_type >(
							std::clamp(
								blue[channel] + white[channel] * render_values[row][column],
								0.0,
								255.0 ) );
			}
		}
	}

	netpbm::write_color(
		"output",
		netpbm::encoding::ascii,
		image );
}

int main()
{
	render_to_file();
}