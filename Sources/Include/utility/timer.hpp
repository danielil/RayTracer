/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include <chrono>
#include <functional>

namespace utility
{
	template < typename Duration >
	Duration get_timed_callback( std::function< void() >&& callback )
	{
		using clock_type = std::chrono::high_resolution_clock;

		const auto start = clock_type::now();
		callback();
		return std::chrono::duration_cast< Duration >( clock_type::now() - start );
	}
}