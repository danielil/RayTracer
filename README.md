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
  <li>Basic multithreading support with std::thread.</li>
  <li>Basic color mapping given object intrinsic color.</li>
  <li>Supports multiple objects and multiple point light sources.</li>
  <li>Uses a scene file (JSON format) to dynamically render elements at runtime.</li>
</ul>

Usage
------------------
	./RayTracer --help
	./RayTracer --scene path_to_scene.json
	./RayTracer --scene path_to_scene.json --output-to-window
	./RayTracer --scene path_to_scene.json --output_to_file output.[bmp, png, tga, jpg]
	./RayTracer --scene path_to_scene.json --output-to-window --output_to_file output.[bmp, png, tga, jpg]

  The image can be projected to a fullscreen window, an output file, or both. Pressing any key will close the window.

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
    <td>Contiguously-allocated tensor (rank 3)</td>
    <td>Eigen</td>
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
    <td>Scene (JSON) Parsing</td>
    <td>Boost.PropertyTree</td>
  </tr>
  <tr>
    <td>Window</td>
    <td>SFML</td>
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
  <li>Add material support in addition to object color. Make color derived from material rather than object and specify material color reflection/refraction.</li>
  <li>Refactor the std::thread usage with the C++17 execution policies (http://en.cppreference.com/w/cpp/algorithm/execution_policy_tag_t) when they become available.</li>
</ul>