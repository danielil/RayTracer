/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "raytracer/output.hpp"
#include "utility/timer.hpp"

#include <iostream>

int main()
{
	constexpr std::size_t rows = 2000;
	constexpr std::size_t columns = 2000;

	std::cout << utility::get_timed_callback< std::chrono::milliseconds >([=]()
	{
		raytracer::output_to_file( rows, columns, "output" );
	} ).count() << " ticks";
}