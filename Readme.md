# This is 42's MiniRT 🥳

## Ressources

- [Computerphile video about](https://www.youtube.com/watch?v=ezXGTRSx1g8)
- [Computerphile Vid about Matrix ops and Computer visuals](https://www.youtube.com/watch?v=vQ60rFwh2ig)
- [Wiki about raytracing](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))
- [And another one on homogeneous coords](https://www.youtube.com/watch?v=o-xwmTODTUI)
- [aand another one on 3d game graphics](https://www.youtube.com/watch?v=U0_ONQQ5ZNM)
- [Raytracer in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [An introduction to raytracing in C](https://www.jakobmaier.at/posts/raytracing/)

## Features we implemented

- Interactive UI with ability to move through the scene and control over scene
  parameters like cam fov, ambient light brightness, sub- and supersampling
  level and some more.
- Toggable sidebar for info display
- Objects: plane, sphere, cylinder, triangle, circle, hyperboloid (also gives
  the cone).
- Texture / Bump / Normal mapping: Fully implemented for the sphere, for the
  hyper only texture mapping.
- Checker pattern mapping: sphere, hyper and plane.
- Switchable raytracing method: direct single pixel drawing to he canvas,
  drawing via xpm, multithreaded variants.
- Multithreading is also available for supersampling.

## Learnings

You gotta stop implementing features at some point... :)
