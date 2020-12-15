#include <gtk/gtk.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <err.h>
#include "binarization.h"
#include "displayBMP.h"
#include "grey_level.h"
#include "pixelBMP.h"
#include "segmentation.h"

struct OCR;
enum State;
struct UserInterface;
gboolean on_draw(cairo_t *cr,gpointer user_data);
void set_doing(gpointer user_data);
void on_doing(gpointer user_data);
void set_stop(gpointer user_data);
void on_stop(gpointer user_data);
int main (int argc, char *argv[]);
