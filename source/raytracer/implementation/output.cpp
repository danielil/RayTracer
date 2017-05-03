/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
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