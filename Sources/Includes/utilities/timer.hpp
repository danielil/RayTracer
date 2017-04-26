/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#pragma once

#include <chrono>
#include <functional>

namespace utilities
{
    template < typename Duration >
    Duration time_callback( std::function< void() >&& callback )
    {
        const auto start = std::chrono::high_resolution_clock::now();

        callback();

        return std::chrono::duration_cast< Duration >( std::chrono::high_resolution_clock::now() - start );
    }
}