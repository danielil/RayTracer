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

#include "image/image.hpp"

#include <fstream>
#include <functional>
#include <unordered_map>

namespace utility
{
	/**
	 * Utility class responsible for outputting netpbm formatted files.
	 */
	class netpbm
	{
	public:
		using textual_type = unsigned int;

		enum class format
		{
			// Portable BitMap
			pbm,
			// Portable GrayMap
			pgm,
			// Portable PixMap
			ppm
		};

		enum class encoding
		{
			ascii,
			binary
		};

		netpbm(
			const std::string filename,
			const format format,
			const encoding encoding,
			const std::size_t rows,
			const std::size_t columns );
		~netpbm() noexcept = default;

		netpbm( const netpbm& ) = delete;
		netpbm( netpbm&& ) noexcept = delete;

		netpbm& operator=( const netpbm& ) = delete;
		netpbm& operator=( netpbm&& ) = delete;

		template< typename T >
		void
		write( const image::image< T >& image )
		{
			for ( auto&& row : image )
			{
				for ( auto&& column : row )
				{
					for ( auto&& channel : column )
					{
						static constexpr auto separator = " ";
						this->output << static_cast< textual_type >( channel ) << separator;
					}
				}

				this->output << std::endl;
			}
		}

	private:
		std::ofstream output;

		const std::unordered_map< format, std::string > format_to_string
		{
			{ format::pbm, "pbm" },
			{ format::pgm, "pgm" },
			{ format::ppm, "ppm" }
		};

		const std::unordered_map<
			format,
			std::unordered_map<
			encoding,
			std::size_t > > format_to_magic_number =
		{
			{
				format::pbm,
				{
					{ encoding::ascii, 1 },
					{ encoding::binary, 4 }
				}
			},
			{
				format::pgm,
				{
					{ encoding::ascii, 2 },
					{ encoding::binary, 5 }
				}
			},
			{
				format::ppm,
				{
					{ encoding::ascii, 3 },
					{ encoding::binary, 6 }
				}
			}
		};
	};
}