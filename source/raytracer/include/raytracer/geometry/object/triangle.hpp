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
#include "raytracer/geometry/ray.hpp"
#include "raytracer/geometry/spatial_vector.hpp"
#include "raytracer/geometry/object/object.hpp"

#include <optional>

namespace raytracer::geometry::object
{
	/**
	 * Defines a triangle.
	 */
	class triangle : public object
	{
	public:
		~triangle() noexcept override = default;

		template< typename Point >
		triangle(
			Point&& center,
			vector_type radius,
			image::channels channels ) :
			center( std::forward< Point >( center ) ),
			radius( radius ),
			channels( channels )
		{
		}

		/**
		 */
		std::optional< point > intersect( const ray& ray ) const override;

		/**
		 * Returns the normal vector of the triangle given an intersection point.
		 */
		spatial_vector normal( const point& intersection_point ) const override;

		/*
		 * Returns the triangle's color.
		 */
		const image::channels& get_channels() const override;

	private:
		point center;
		vector_type radius;
		image::channels channels;
	};
}