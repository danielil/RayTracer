/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "raytracer/output.hpp"

#define BOOST_TEST_MODULE
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( raytracer_tests )

BOOST_AUTO_TEST_CASE( raytracer_test )
{
	constexpr std::size_t rows = 2000;
	constexpr std::size_t columns = 2000;

	const std::string extension = ".ppm";
	const auto input_filename = "input" + extension;
	const auto output_filename = "output" + extension;

	raytracer::output_to_file( rows, columns, output_filename );

	std::ifstream input( "data/" + input_filename );
	std::ifstream output( output_filename );

	BOOST_REQUIRE(
		std::equal(
			std::istream_iterator< char >( input ),
			std::istream_iterator< char >(),
			std::istream_iterator< char >( output ),
			std::istream_iterator< char >() ) );
}

BOOST_AUTO_TEST_SUITE_END()