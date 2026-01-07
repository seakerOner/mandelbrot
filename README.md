# Mandelbrot set to .ppm images

[!Mandelbrot gif](https://github.com/seakerOner/mandelbrot/blob/main/mandelbrot.gif)

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
