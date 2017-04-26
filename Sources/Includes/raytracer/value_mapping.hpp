/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer.hpp"
#include "image/image.hpp"

namespace raytracer::value_mapping
{
	image::rgb_container color_map_render_value( raytracer::vector_type render_value )
	{
		return
			render_value == raytracer::vector_type() ?
			image::rgb_container { 0, 0, 0 } :
			image::rgb_container
		{
			static_cast< image::channel_type >( std::clamp( 255 * render_value, 0.0, 255.0 ) ),
			static_cast< image::channel_type >( std::clamp( 255 * render_value, 0.0, 255.0 ) ),
			static_cast< image::channel_type >( std::clamp( 255 + 255 * render_value, 0.0, 255.0 ) )
		};
	}
}