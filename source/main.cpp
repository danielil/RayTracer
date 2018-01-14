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

#include <boost/program_options.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

int main( const int argc, char** argv )
{
	boost::program_options::options_description description( "Allowed options" );
	description.add_options()
		( "help", "List all available arguments." )
		( "scene", boost::program_options::value< std::string >(), "Specify the path to the scene file." )
		( "output-to-window", "Project the output to a window." )
		( "output-to-file", boost::program_options::value< std::string >(),
			"Project the output to a file. Specify the filename and extension. Supported extensions include .bmp, .png, .tga, and .jpg." );

	boost::program_options::variables_map variables_map;

	try
	{
		store( parse_command_line( argc, argv, description ), variables_map );
		notify( variables_map );
	}
	catch ( const boost::program_options::error& error )
	{
		std::cout << error.what() << std::endl;

		return EXIT_FAILURE;
	}

	if ( variables_map.count( "help" ) )
	{
		std::cout << description << std::endl;
	}
	else if ( variables_map.count( "scene" ) )
	{
		const auto& scene_value = variables_map["scene"].as< std::string >();

		std::cout << "Scene file set to " << scene_value << std::endl;

		raytracer::scene scene( scene_value );
		const auto& metadata = scene.get_metadata();

		sf::Texture texture;
		if ( texture.create( unsigned( metadata.columns ), unsigned( metadata.rows ) ) )
		{
			texture.setSmooth( true );
			
			// Minimalistic time-based benchmark
			std::cout << utility::get_timed_callback< std::chrono::milliseconds >( [&texture, &scene]()
			{
				texture.update( raytracer::render().trace( scene ).data() );
			} ).count() << " milliseconds" << std::endl;

			if ( variables_map.count( "output-to-window" ) )
			{
				std::cout << "Output will be projected to a window." << std::endl;

				const sf::Sprite sprite( texture );

				sf::RenderWindow window( sf::VideoMode::getDesktopMode(), "RayTracer", sf::Style::Fullscreen );
				while ( window.isOpen() )
				{
					sf::Event event;
					while ( window.pollEvent( event ) )
					{
						window.clear( sf::Color::Black );
						window.draw( sprite );
						window.display();

						if ( event.type == sf::Event::KeyPressed )
						{
							window.close();
						}
					}
				}
			}
			else
			{
				std::cout << "Output will not be projected to a window." << std::endl;
			}

			if ( variables_map.count( "output-to-file" ) )
			{
				const auto& output_filename = variables_map["output-to-file"].as< std::string >();
				
				std::cout << "Output will be projected to a file. Filename set to " << output_filename << std::endl;

				texture.copyToImage().saveToFile( output_filename );
			}
			else
			{
				std::cout << "Output will not be projected to a file." << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Scene file was not specified." << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}