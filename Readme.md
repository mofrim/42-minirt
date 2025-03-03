# This is going to 42's MiniRT 🥳

## Ressources

- [Computerphile video about](https://www.youtube.com/watch?v=ezXGTRSx1g8)
- [Another Computerphile Vid about Matrix ops and Computer visuals](https://www.youtube.com/watch?v=vQ60rFwh2ig)
- [Wiki about raytracing](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))


## Project Overview

1) Parsing and reading input files
2) Intersections and ray tracing
3) Light, shadows and colors
4) The UI
4) Graphic management (windows, hooks, etc.). with the minilibx

## Questions?!

- What can i improve considering my structure from the fdf project? Especially
  when it comes to code architecture and making the code extensible and
  maintainable from the very beginning.
- What will my master struct contain and when will i use it?
- How to layout everything from the very beginning to
  + allow for more objects to be added?
  + for the bonus special effects to be added?
  + for multiple light sources to be added.
  + How to make the UI extensible?

## Architecture

1. Parse input file f.ex. `parse_scenefile()` returns: some `t_scene` struct
   which contains all necessary data.
2. Do window MLX / X / openGL whatever setup
3. Add all necessary mlx stuff to master struct together with the scene struct.
4. Pass this to the rendering function -> display window, program is running
5. 

