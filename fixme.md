# this is a FIXME list for our miniRT

## parsing

- [ ] the subject pdf clearly says:

      Each type of AelementA can be separated by one or more line breaks.

  this means we have to parse the input linewise and also check if there is not
  more than one element per line! maybe this can already be done by ft_splitting
  the read scenefile by newlines again.

- [ ] in a scene file like this:
  ```
  C	-5,0,8	1,0,-0.1	99
  A		0.3								255,255,255
  L		0,0,7.2		0.5				255,255,255
  sp	0,0,5		4					255,0,0
  ```
  the FOV `99` will not be parsed! i already tracked it down to be because of
  `parse_coordinates` is a little bit too hungry. the current implementation

  ```c
  int	is_coordinate(t_tokenizer *tokenizer)
  {
    return ((ft_isdigit(tokenizer->input[tokenizer->position]) || \
          tokenizer->input[tokenizer->position] == '-' || \
          tokenizer->input[tokenizer->position] == '+') && \
        ft_strchr(&tokenizer->input[tokenizer->position], ','));
  }
  ```
  is a bit to simple.. this works for the spheres for example. i started fixing
  this but it definitely needs another look at it.

- [ ] color values should be checked for correctness. meaning if they are really
    3 numbers seperated by commas between 0 and 255. Meaning a value like 256
    should lead to a parsing error and exit.

- [ ] i enter a line like this into one scene file:

  ```
  C	-5,0,affe	1,0,-0.1	99
  ```
  this should also be a parsing error. it is not so far.

- [ ] empty files lead to segfault.

- [ ] `should_fail3.rt`  with only "gotcha!" as content -> segfaults

- [ ] correct file with wrong file ext f.ex. `should_fail.xyz` should error,
  but doesn't atm. check if scene-files end in `.rt`! 

## raytracing

- [ ] handle insides of objects correctly ?!?

- [ ] putting a light source directly on the surface of an object leads to
  ugliness.

- [ ] fix: put light into a big sphere, light should not shine on outside objs

## window management

- [ ] make sure that the requirements regarding window management are met!

## the color problem

What i would want the colors to behave:

Ambient light:

- ambient light (A) is just a basic offset for all obj colors in the scene.
- A.i == 0 => the obj should still retain its color
- A.i == 1 => should not lead to overexposure, rather scale the original objects
  colors to the their full original value. (how to do that when A is colored and
  not only white?)

Spotlights:

- the effect of a light should be proportional to its intensity
- overexposure is allowed! meaning if a high intensity white light is
- a completely Blue light on a completely Red sphere should have **no** effect!
  Meaning: there is some multiplicative color_light_adding going on!
- a white light with 0.3 brightness on a red sphere at 0.1 ambient light should
  definitely have an effect! with

  ```c
	res.r = (uint8_t)fmin(255, c.r * (1.0f - l.i + l.i * l.r / 255.0f));
  ```

  this is not the case bc this simply returns `c.r`!
  ways to fix this:

  1) add the intensities `c.i + l.i` and multiply `c.r` by the result.
  2) be more additive with something like

  ```c
	res.r = (uint8_t)fmin(255, c.r * l.i * l.r / 255.0f);
  ```
- white light on a red sphere should only brighten the red component! not the
  others.

