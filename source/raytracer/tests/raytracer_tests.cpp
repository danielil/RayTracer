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