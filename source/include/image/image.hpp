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

#define NOMINMAX

#include <eigen3/unsupported/Eigen/CXX11/Tensor>

#include <array>

namespace image
{
	// The base type of a channel value.
	using channel_type = std::uint8_t;

	// The lowest value a channel can hold.
	static constexpr auto MIN_CHANNEL_VALUE = std::numeric_limits< channel_type >::min();

	// The greatest value a channel can hold.
	static constexpr auto MAX_CHANNEL_VALUE = std::numeric_limits< channel_type >::max();

	// The type of the value using for indexing a tensor.
	using tensor_size_type = std::size_t;

	// The number of image channels.
	static constexpr tensor_size_type CHANNELS = 4U;
	using channels = std::array< channel_type, CHANNELS >;

	// The order of the tensor.
	static constexpr auto RANK = 3;

	// An image is a contiguously-allocated tensor of rank 3.
	using image = Eigen::Tensor< channels::value_type, RANK, Eigen::RowMajor, tensor_size_type >;
}