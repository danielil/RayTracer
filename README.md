RayTracer
================
A basic CPU RayTracer written in modern C++.

About
------------------
Author: `Daniel Sebastian Iliescu, http://dansil.net`  
License: `MIT License (MIT), http://opensource.org/licenses/MIT`  

Features
------------------
<ul>
  <li>Basic multithreading support with OpenMP.</li>
  <li>Basic color mapping given object intrinsic color.</li>
  <li>Supports multiple objects and multiple point light sources</li>
  <li>Uses a scene file (JSON format) to render elements at runtime</li>
</ul>

Usage
------------------
	./RayTracer --scene path_to_scene.json --output output_filename

Requirements
------------------
C++17 conforming compiler.

Dependencies
------------------
<table>
  <tr>
    <th>Type</th>
    <th>Dependency</th>
  </tr>
  <tr>
    <td>Parallelization</td>
    <td>OpenMP</td>
  </tr>
  <tr>
    <td>Program Arguments</td>
    <td>Boost.Program_options</td>
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
    <td>Scene (JSON) Parsing</td>
    <td>Boost.PropertyTree</td>
  </tr>
</table>

Screenshot
================
Output image showing how light is traced and intersected by spheres of different colors at different locations (radially outwards).

<img src="documentation/images/output.jpg" alt="Output SCreenshot" width="500">

Output image showing similar setup with point light in top right corner.

<img src="documentation/images/output_angled.jpg" alt="Output SCreenshot" width="500">

Limitations/ToDo
------------------
<ul>
  <li>Multiple object intersections is not supported. The RayTracer will simply render the first object intersected, even if there is an object behind it. This is a direct consequence of the RayTracer not being recursive. This should change in the near future.
  <li>Add material support in addition to object color. Make color derived from material rather than object and specify material color reflectance efficiency.</li>
  <li>Refactor the OpenMP usage with the C++17 execution policies (http://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t) when they become available.</li>
  <li>Proper matrix/tensor/multidimensional container allocated contiguously and indexed linearly. The current matrix class uses two levels of pointer indirection. That is, it contains a collection of nested containers of heap allocated data. As a result, the buffer is not contiguous in memory and destroys the cache line.</li>
  <li>QT-based GUI</li>
</ul>