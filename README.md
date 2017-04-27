RayTracer
================

A basic CPU RayTracer written in C++.

Screenshot
================
![Output Screenshot](Resources/output)

About
------------------

Author: `Daniel Sebastian Iliescu, http://dansil.net`  
License: `MIT License (MIT), http://opensource.org/licenses/MIT`  

Requirements
------------------

C++17 conforming compiler.

Limitations
------------------

This software RayTracer is entirely educational. It is inaccurate with respect to physical dimensions and not optimized. This is very basic groundwork meant to be improved upon. It is in no way a complete solution. Rendering is CPU-based.

TODO
------------------
Proper input-based scene files should be added to be parsed by the application. This also means adding support for additional objects.

Drop-in multithreading should improve the performance significantly (either through std::thread or OpenMP). I am waiting for a complete implementation of the C++17 execution policies for use with standard algorithms (http://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t) to avoid deploying my own threading model. Some of the std::transform calls should hopefully be able to make use of these.

Offloading some of the computation to the GPU is also something that I want to get to eventually.

Implemented as a quick proof of concept, the matrix class unfortunately uses two levels of pointer indirection. That is, it contains a collection of nested containers of heap allocated data. As a result, the buffer is not contiguous in memory and destroys the cache line. This class should be updated to only use a single level of indirection and indexing should occur linearly. Ideally, a templatized approach for an n-dimensional (tensor) container would be even better.