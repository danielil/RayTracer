/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include "image/image.hpp"

#include <fstream>
#include <functional>
#include <unordered_map>

namespace utilities
{
	class netpbm
	{
	public:
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
			const std::size_t columns )
		{
			this->output = std::ofstream( filename + "." + this->format_to_string.at( format ) );
			const auto magic_number = this->format_to_magic_number.at( format ).at( encoding );

			this->output << "P" << magic_number << std::endl;
			this->output << rows << " " << columns << std::endl;

			if ( format != format::pbm )
			{
				this->output << static_cast< unsigned int >( image::MAX_CHANNEL_VALUE ) << std::endl;
			}
		}

		~netpbm() noexcept = default;

		netpbm( const netpbm& ) = delete;
		netpbm( netpbm&& ) noexcept = delete;

		netpbm& operator=( const netpbm& ) = delete;
		netpbm& operator=( netpbm&& ) = delete;

		template< typename Image >
		void
		write( Image&& image )
		{
			for ( auto&& row : image )
			{
				for ( auto&& column : row )
				{
					for ( auto&& channel : column )
					{
						static constexpr auto separator = " ";
						this->output << static_cast< unsigned int >( channel ) << separator;
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
			unsigned int > > format_to_magic_number =
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