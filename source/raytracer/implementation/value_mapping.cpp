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

#include "raytracer/value_mapping.hpp"

namespace raytracer::value_map
{
	image::rgb_container color_map(
		image::rgb_container channels,
		raytracer::vector_type render_value )
	{
		static constexpr auto min = static_cast< raytracer::vector_type >( image::MIN_CHANNEL_VALUE );
		static constexpr auto max = static_cast< raytracer::vector_type >( image::MAX_CHANNEL_VALUE );

		return
			render_value == raytracer::vector_type() ?
			image::rgb_container { 0, 0, 0 } :
			image::rgb_container
		{
			static_cast< image::channel_type >( std::clamp( channels[0] * render_value, min, max ) ),
			static_cast< image::channel_type >( std::clamp( channels[1] * render_value, min, max ) ),
			static_cast< image::channel_type >( std::clamp( channels[2] * render_value, min, max ) )
		};
	}
}