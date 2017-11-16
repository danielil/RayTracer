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
		( "help", "List all available arguments" )
		( "scene", boost::program_options::value< std::string >(), "Path to scene file" );

	boost::program_options::variables_map variables_map;
	store( parse_command_line( argc, argv, description ), variables_map );
	notify( variables_map );

	if ( variables_map.count( "help" ) )
	{
		std::cout << description << std::endl;
	}
	else if ( variables_map.count( "scene" ) )
	{
		const auto& value = variables_map["scene"].as< std::string >();

		std::cout << "Scene file was set to " << value << std::endl;

		raytracer::scene scene( value );
		const auto& metadata = scene.get_metadata();

		sf::Texture texture;
		if ( texture.create( int( metadata.columns ), int( metadata.rows ) ) )
		{
			texture.setSmooth( true );

			std::cout << utility::get_timed_callback< std::chrono::milliseconds >([&texture, &scene]()
			{
				texture.update( raytracer::render().trace( scene ).data() );
			}).count() << " milliseconds";

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
	}
	else
	{
		std::cout << "Scene file was not specified." << std::endl;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}