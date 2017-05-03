/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "utility/netpbm.hpp"

namespace utility
{
	netpbm::netpbm(
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
			this->output << static_cast< textual_type >( image::MAX_CHANNEL_VALUE ) << std::endl;
		}
	}
}