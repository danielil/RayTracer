/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/alias.hpp"

#include "image/image.hpp"

namespace raytracer::value_map
{
	image::rgb_container color_map( raytracer::vector_type render_value )
	{
		static constexpr auto min = static_cast< raytracer::vector_type >( image::MIN_CHANNEL_VALUE );
		static constexpr auto max = static_cast< raytracer::vector_type >( image::MAX_CHANNEL_VALUE );

		return
			render_value == raytracer::vector_type() ?
			image::rgb_container { 0, 0, 0 } :
			image::rgb_container
		{
			static_cast< image::channel_type >( std::clamp( max * render_value, min, max ) ),
			static_cast< image::channel_type >( std::clamp( max * render_value, min, max ) ),
			static_cast< image::channel_type >( std::clamp( max + max * render_value, min, max ) )
		};
	}
}