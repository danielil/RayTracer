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

#include "raytracer/metadata.hpp"
#include "raytracer/element.hpp"

#include <boost/property_tree/ptree.hpp>

#include <string>
#include <vector>

namespace raytracer
{
	/**
	 * Class responsible for parsing scene files.
	 */
	class scene
	{
	public:
		scene( const std::string filename );
		~scene() noexcept = default;

		scene( const scene& ) = default;
		scene( scene&& ) noexcept = delete;

		scene& operator=( const scene& ) = default;
		scene& operator=( scene&& ) noexcept = delete;

		const metadata& get_metadata() const;
		const element& get_element() const;

	private:
		void parse_root();

		void parse_metadata( const boost::property_tree::ptree& metadata_node );
		void parse_element( const boost::property_tree::ptree& element_node );

		void parse_illumination( const boost::property_tree::ptree& illumination_node );
		void parse_object( const boost::property_tree::ptree& object_node );

		void parse_sphere( const boost::property_tree::ptree& sphere_node );

		template< typename T >
		static std::vector< T > parse_array( const boost::property_tree::ptree& array_node )
		{
			std::vector< T > elements;

			for ( const auto& element : array_node )
			{
				elements.emplace_back( element.second.get_value< T >() );
			}

			return elements;
		}

		boost::property_tree::ptree property_tree;

		metadata metadata;
		element element;
	};
}