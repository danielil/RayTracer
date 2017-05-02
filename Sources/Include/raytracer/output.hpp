/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "raytracer/alias.hpp"
#include "raytracer/raytracer.hpp"
#include "raytracer/value_mapping.hpp"
#include "raytracer/geometry/spatial_vector.hpp"
#include "raytracer/geometry/object/object.hpp"
#include "raytracer/geometry/object/sphere.hpp"

#include "utility/netpbm.hpp"

#include <memory>
#include <vector>

namespace raytracer
{
	object_container generate_spheres()
	{
		static constexpr vector_type RADIUS = 500;
		static constexpr vector_type MULTIPLIER = 100;

		object_container container;

		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS, RADIUS, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );
		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS * 2, RADIUS, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );
		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS * 3, RADIUS, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );
		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS, RADIUS * 2, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );
		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS * 2, RADIUS * 2, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );
		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS * 3, RADIUS * 2, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );
		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS, RADIUS * 3, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );
		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS * 2, RADIUS * 3, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );
		container.emplace_back( std::move( std::make_unique< geometry::object::sphere >( geometry::spatial_vector { RADIUS * 3, RADIUS * 3, RADIUS / MULTIPLIER }, RADIUS * MULTIPLIER ) ) );

		return container;
	}

	void output_to_file( const std::string output )
	{
		constexpr std::size_t rows = 2000;
		constexpr std::size_t columns = 2000;

		image::rgb_image image( rows, columns );
		const auto render_values = compute_render_values( rows, columns, generate_spheres() );

		for ( image::rgb_image::size_type row = 0; row < rows; ++row )
		{
			std::transform(
				std::cbegin( render_values[row] ),
				std::cend( render_values[row] ),
				std::begin( image[row] ),
				raytracer::value_map::color_map );
		}

		utility::netpbm(
			output,
			utility::netpbm::format::ppm,
			utility::netpbm::encoding::ascii,
			rows,
			columns ).write( image );
	}
}