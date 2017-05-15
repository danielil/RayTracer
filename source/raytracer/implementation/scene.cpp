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

#include <boost/property_tree/json_parser.hpp>
#include <raytracer/geometry/object/sphere.hpp>

namespace raytracer
{
	scene::scene( const std::string filename )
	{
		boost::property_tree::json_parser::read_json( filename, this->property_tree );

		this->parse_root();
	}

	const metadata& scene::get_metadata() const
	{
		return this->metadata;
	}

	const scene::illumination_container& scene::get_illuminations() const
	{
		return this->illuminations;
	}

	const scene::object_container& scene::get_objects() const
	{
		return this->objects;
	}

	void scene::parse_root()
	{
		const auto node = this->property_tree.get_child( "scene" );

		this->parse_metadata( node.get_child( "metadata" ) );
		this->parse_element( node.get_child( "element" ) );
	}

	void scene::parse_metadata( const boost::property_tree::ptree& metadata_node )
	{
		this->metadata.rows = metadata_node.get< metadata::size_type >( "height" );
		this->metadata.columns = metadata_node.get< metadata::size_type >( "width" );
	}

	void scene::parse_element( const boost::property_tree::ptree& element_node )
	{
		this->parse_illumination( element_node.get_child( "illumination" ) );
		this->parse_object( element_node.get_child( "object" ) );
	}

	void scene::parse_illumination( const boost::property_tree::ptree& illumination_node )
	{
		for ( const auto& point_node : illumination_node )
		{
			const auto point = parse_array< vector_type >( point_node.second.get_child( "point" ) );

			this->illuminations.emplace_back( point.data(), point.size() );
		}
	}

	void scene::parse_object( const boost::property_tree::ptree& object_node )
	{
		this->parse_sphere( object_node.get_child( "sphere" ) );
	}

	void scene::parse_sphere( const boost::property_tree::ptree& sphere_node )
	{
		for ( const auto& sphere : sphere_node )
		{
			const auto point = parse_array< vector_type >( sphere.second.get_child( "point" ) );
			const auto radius = sphere.second.get< vector_type >( "radius" );
			const auto color = parse_array< image::channel_type >( sphere.second.get_child( "color" ) );

			image::rgb_container rgb_container;

			std::copy( std::cbegin( color ), std::cend( color ), std::begin( rgb_container ) );

			this->objects.emplace_back(
				std::make_shared< geometry::object::sphere >(
					geometry::point( point.data(), point.size() ),
					radius,
					rgb_container ) );
		}
	}
}