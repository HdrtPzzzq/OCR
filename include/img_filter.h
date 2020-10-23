#ifndef IMG_FILTER_H
#define IMG_FILTER_H

void filter(SDL_Surface *image);
Uint32 sum_9(SDL_Surface *image, int x, int y);
int get_x(int x);
int get_range_x(int w, int x);
int get_y(int y);
int get_range_y(int h, int y);

#endif
