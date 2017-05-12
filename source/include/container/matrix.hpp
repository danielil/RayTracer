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

#include <vector>

namespace container
{
	template< typename T >
	class matrix
	{
	public:
		using value_type = T;

		using inner_container_type = std::vector< value_type >;
		using outer_container_type = std::vector< inner_container_type >;

		using iterator = typename outer_container_type::iterator;
		using const_iterator = typename outer_container_type::const_iterator;
		using reverse_iterator = typename outer_container_type::reverse_iterator;
		using const_reverse_iterator = typename outer_container_type::const_reverse_iterator;

		using size_type = typename outer_container_type::size_type;

		matrix::matrix(
			size_type rows,
			size_type columns ) noexcept :
			container( rows, inner_container_type( columns ) )
		{
		}

		~matrix() noexcept = default;

		matrix( const matrix& ) = default;
		matrix( matrix&& ) noexcept = default;

		matrix& operator=( const matrix& ) = default;
		matrix& operator=( matrix&& ) noexcept = default;

		inner_container_type& operator[]( size_type row_index )
		{
			return this->container[row_index];
		}

		const inner_container_type& operator[]( size_type row_index ) const
		{
			return this->container[row_index];
		}

		const size_type size() const
		{
			return this->container.size();
		}

		iterator begin()
		{
			return std::begin( this->container );
		}

		const_iterator begin() const
		{
			return std::begin( this->container );
		}

		const_iterator cbegin() const
		{
			return std::cbegin( this->container );
		}

		iterator end()
		{
			return std::end( this->container );
		}

		const_iterator end() const
		{
			return std::end( this->container );
		}

		const_iterator cend() const
		{
			return std::cend( this->container );
		}

		iterator rbegin()
		{
			return std::rbegin( this->container );
		}

		const_iterator rbegin() const
		{
			return std::rbegin( this->container );
		}

		const_iterator crbegin() const
		{
			return std::crbegin( this->container );
		}

		iterator rend()
		{
			return std::rend( this->container );
		}

		const_iterator rend() const
		{
			return std::rend( this->container );
		}

		const_iterator crend() const
		{
			return std::crend( this->container );
		}

	private:
		outer_container_type container;
	};
}