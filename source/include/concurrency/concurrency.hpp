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

#include <algorithm>
#include <thread>
#include <utility>
#include <functional>

#include <queue>
#include <list>

namespace concurrency
{
	class scoped_thread
	{
	public:
		template<
			typename Function,
			typename... Arguments >
		scoped_thread(
			Function&& callback,
			Arguments&&... arguments ) :
			thread(
				std::forward< Function >( callback ),
				std::forward< Arguments >( arguments )... )
		{
		}

		~scoped_thread()
		{
			if ( this->thread.joinable() )
			{
				this->thread.join();
			}
		}

		scoped_thread( const scoped_thread& ) = default;
		scoped_thread( scoped_thread&& ) = default;

		scoped_thread& operator=( const scoped_thread& ) = default;
		scoped_thread& operator=( scoped_thread&& ) = default;

	private:
		std::thread thread;
	};

	template< typename Index >
	void parallel_for(
		const Index& begin,
		const Index& end,
		std::function< void( const Index& ) >&& callback,
		const std::size_t thread_count = std::thread::hardware_concurrency(),
		const std::size_t threshold = 1 )
	{
		const auto bucket =
			std::max(
				threshold,
				( end - begin ) / thread_count );

		std::queue< scoped_thread, std::list< scoped_thread > > threads;

		for ( auto it = begin; it < end; it += bucket )
		{
			const auto last = std::min( it + bucket, end );

			threads.emplace(
				[it, last, &callback]()
				{
					for ( auto index = it; index != last; ++index )
					{
						callback( index );
					}
				} );
		}
	}
}