# Mandelbrot set to .ppm images

<video width="1200" height="800" controls>
  <source src="./mandelbrot.mp4" type="video/mp4">
</video>

Using the simplicity of the .ppm format and the Mandelbrot set to create complex shapes

To execute the program and create frames in the `./frames/` directory:
```bash
make run
```

## FFMPEG

You can use the .ppm files to create videos with ffmpeg. A command to do that should look something like this:

```bash
ffmpeg -i ./frames/brot-%03d.ppm -r 60 mandelbrot.mp4
```
