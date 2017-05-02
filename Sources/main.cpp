/**
 * Daniel Sebastian Iliescu, http://dansil.net
 * MIT License (MIT), http://opensource.org/licenses/MIT
 */

#include "raytracer/output.hpp"
#include "utility/timer.hpp"

#include <iostream>

int main()
{
	std::cout << utility::get_timed_callback< std::chrono::milliseconds >([]()
	{
		raytracer::output_to_file("output");
	} ).count() << " ticks";
}