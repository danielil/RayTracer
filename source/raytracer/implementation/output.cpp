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

#include "raytracer/output.hpp"

namespace raytracer
{
	object_container generate_spheres()
	{
		static constexpr vector_type RADIUS = 500;
		static constexpr vector_type MULTIPLIER = 100;

		object_container container;

		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS, RADIUS, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 139, 0, 139 } ) );
		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS * 2, RADIUS, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 38, 84, 124 } ) );
		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS * 3, RADIUS, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 239, 71, 111 } ) );
		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS, RADIUS * 2, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 255, 209, 102 } ) );
		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS * 2, RADIUS * 2, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 0, 178, 202 } ) );
		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS * 3, RADIUS * 2, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 239, 71, 111 } ) );
		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS, RADIUS * 3, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 255, 209, 102 } ) );
		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS * 2, RADIUS * 3, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 38, 84, 124 } ) );
		container.emplace_back(
			std::make_shared< geometry::object::sphere >(
				geometry::spatial_vector { RADIUS * 3, RADIUS * 3, RADIUS / MULTIPLIER },
				RADIUS * MULTIPLIER,
				image::rgb_container { 139, 0, 139 } ) );

		return container;
	}

	void output_to_file(
		const std::size_t rows,
		const std::size_t columns,
		const std::string output )
	{
		utility::netpbm(
			output,
			utility::netpbm::format::ppm,
			utility::netpbm::encoding::ascii,
			rows,
			columns ).write(
				generate_image(
					rows,
					columns,
					generate_spheres() ) );
	}
}