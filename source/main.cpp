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

#include "raytracer/scene.hpp"
#include "raytracer/raytracer.hpp"

#include "utility/timer.hpp"
#include "utility/netpbm.hpp"

#include <boost/program_options.hpp>

#include <iostream>

int main( int argc, char** argv )
{
	boost::program_options::options_description description( "Allowed options" );
	description.add_options()
		( "help", "List all available arguments" )
		( "scene", boost::program_options::value< std::string >(), "Path to scene file" )
		( "output", boost::program_options::value< std::string >(), "Output filename" );

	boost::program_options::variables_map variables_map;
	boost::program_options::store( boost::program_options::parse_command_line( argc, argv, description ), variables_map );
	boost::program_options::notify( variables_map );

	if ( variables_map.count( "help" ) )
	{
		std::cout << description << std::endl;

		return EXIT_SUCCESS;
	}

	if ( variables_map.count( "scene" ) )
	{
		std::cout << "Scene file was set to "
			<< variables_map["scene"].as< std::string >() << "." << std::endl;
	}
	else
	{
		std::cout << "Scene file was not specified." << std::endl;

		return EXIT_FAILURE;
	}

	if ( variables_map.count( "output" ) )
	{
		std::cout << "Output filename was set to "
			<< variables_map["output"].as< std::string >() << "." << std::endl;
	}
	else
	{
		std::cout << "Output filename was not specified." << std::endl;

		return EXIT_FAILURE;
	}

	raytracer::scene scene( variables_map["scene"].as< std::string >() );

	const auto& metadata = scene.get_metadata();

	std::cout << utility::get_timed_callback< std::chrono::milliseconds >( [&variables_map, &scene, &metadata]()
	{
		utility::netpbm(
			variables_map["output"].as< std::string >(),
			utility::netpbm::format::ppm,
			utility::netpbm::encoding::ascii,
			metadata.rows,
			metadata.columns ).write(
				raytracer::render().trace(
					scene ) );
	} ).count() << " ticks";

	return EXIT_SUCCESS;
}