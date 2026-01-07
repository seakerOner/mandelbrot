#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define UNUSED(var) (void)var

#define WIDTH 1200
#define HEIGHT 800

#define MAX_COLOR_VAL 255

#define FPS 60
#define DURATION_SECS 4

#define ANGLE_ROTATION_RATE_PER_FRAME 0.04
#define STARTING_ZOOM 1.4
#define ZOOM_INCREMENT_RATE_PER_FRAME 0.03
#define CAMERA_CENTER_DRIFT_RE 0.017
#define CAMERA_IMAGINARY_CENTER_DRIFT_IM 0.0017

#define MANDELB_THRESHOLD 4
#define MANDELB_MAXITERATIONS 1000

#define OUTPUT_DIR "./frames/"
#define FILENAME "brot"

int mandelbrot_iteration(const double c_re, const double c_im,
                         const double threshold);

int main(void) {
  int curr_frame = 1;
  for (int second = 0; second < DURATION_SECS; second += 1) {
    char buf[255];
    for (int frame = 0; frame < FPS; frame += 1) {
      double zoom = STARTING_ZOOM + (((double)curr_frame) * ZOOM_INCREMENT_RATE_PER_FRAME);
      double center_re = (-0.5 * ((double)curr_frame * CAMERA_CENTER_DRIFT_RE)) +
                         (double)curr_frame * 0.002;
      double center_im =
          (0.5 * ((double)curr_frame * CAMERA_IMAGINARY_CENTER_DRIFT_IM));
      double width = 3.0 / zoom;
      double height = width * ((double)HEIGHT / WIDTH);

      snprintf(buf, sizeof(buf), "%s%s-%03d.ppm", OUTPUT_DIR, FILENAME,
               curr_frame);
      curr_frame += 1;

      FILE *img = fopen(buf, "w");
      fprintf(img, "P6\n");
      fprintf(img, "%d %d\n", WIDTH, HEIGHT);
      fprintf(img, "%d\n", MAX_COLOR_VAL);
      for (int y = 0; y < HEIGHT; y += 1) {
        for (int x = 0; x < WIDTH; x += 1) {
          double angle = curr_frame * ANGLE_ROTATION_RATE_PER_FRAME;
          double c_re =
              center_re - width / 2 + ((double)x / (WIDTH - 1)) * width;
          double c_im =
              center_im + height / 2 - ((double)y / (HEIGHT - 1)) * height;

          double r_re = c_re - center_re;
          double r_im = c_im - center_im;
          double rot_re = r_re * cos(angle) - r_im * sin(angle);
          double rot_im = r_re * sin(angle) + r_im * cos(angle);
          c_re = rot_re + center_re;
          c_im = rot_im + center_im;
          int tries = mandelbrot_iteration(c_re, c_im, MANDELB_THRESHOLD);

          uint8_t color =
              (uint8_t)(255 * ((double)tries / MANDELB_MAXITERATIONS));
          fputc(color, img);
          fputc(color, img);
          fputc(color, img);
        }
      }
      printf("[DONE] SEC: %d FRAME: %d\n", (second + 1), frame);
      fclose(img);
    }
  }
  return 0;
}

int mandelbrot_iteration(const double c_re, const double c_im,
                         const double threshold) {
  double zr = 0;
  double zi = 0;

  for (int i = 0; i < MANDELB_MAXITERATIONS; i += 1) {
    double old_zr = zr;
    zr = zr * zr - zi * zi + c_re;
    zi = 2 * old_zr * zi + c_im;

    if (zr * zr + zi * zi > threshold)
      return i;
  }

  return MANDELB_MAXITERATIONS;
}
