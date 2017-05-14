RayTracer
================
A basic CPU RayTracer written in modern C++.

About
------------------
Author: `Daniel Sebastian Iliescu, http://dansil.net`  
License: `MIT License (MIT), http://opensource.org/licenses/MIT`  

Dependencies
------------------
<table>
  <tr>
    <th>Type</th>
    <th>Dependency</th>
  </tr>
  <tr>
    <td>Unit Testing</td>
    <td>Boost.Test</td>
  </tr>
  <tr>
    <td>Contiguously allocated multidimensional container (TODO: Matrix refactor)</td>
    <td>Boost.MultiArray</td>
  </tr>
  <tr>
    <td>JSON Parsing (TODO: Scene File)</td>
    <td>Boost.PropertyTree</td>
  </tr>
</table>

Requirements
------------------
C++17 conforming compiler.

Screenshot
================
Output image showing how light is traced and intersected by spheres of different colors at different locations (radially outwards).

<img src="documentation/images/output.jpg" alt="Output SCreenshot" width="500">

Output image showing similar setup with point light in top right corner.

<img src="documentation/images/output_angled.jpg" alt="Output SCreenshot" width="500">

Limitations
------------------
This software RayTracer is entirely educational. It is currently inaccurate and unoptimized.

TODO
------------------
<ul>
  <li>Input-based scene files as well as support for additional objects and materials.</li>
  <li>Proper multithreading support to significantly improve performance (e.g. std::thread, OpenMP, etc. ). Ideally the C++17 execution policies (http://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t) would be used to avoid deploying my own threading model.</li>
  <li>Proper matrix/tensor/multidimensional container allocated contiguously and indexed linearly. The current matrix class uses two levels of pointer indirection. That is, it contains a collection of nested containers of heap allocated data. As a result, the buffer is not contiguous in memory and destroys the cache line.</li>
  <li>QT-based GUI</li>
</ul>