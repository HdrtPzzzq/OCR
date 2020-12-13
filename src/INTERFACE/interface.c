//#include "interface.h"

// Structure of the graphical user interface.

// State of the game.
typedef enum State
{
  READY,                          // Ready state
  OCR,                            // OCR state
  GREYSCALE,                      // Greyscale state
  BINARISATION,                   // Binarisation state
  NOISE,                          // Noise state
  PRETRAITEMENT,                  // Pretraitement state
  SEGMENTATION,                   // Segmentation state
  NEURAL_NETWORK,                 // Neural_Network
} State;

typedef struct UserInterface
{
  GtkWindow* window;              // Main window
  GtkDrawingArea* area;           // Drawing area
  GtkButton* Get_image_button     // button to get an image
  GtkButton* OCR_button           // OCR button
  GtkButton* greyscale_button;    // Greyscale button
  GtkButton* binarisation_button; // Binarisation button
  GtkButton* noise_button;        // Noise_reduction button
  GtkButton* pretraitement_button;// Pre-traitement button
  GtkButton* segmentation_button; // Segmentation button
  GtkButton* neural_network_button;// Neural Network button
  GtkButton* reset_button;         // Reset Button
} UserInterface;

typedef struct OCR
{
    State state;        //State of the OCR
    UserInterface ui;   //User Interace
    *char image         //Image for the OCR
}OCR;


// Event handler for the "draw" signal of the drawing area.
gboolean on_draw(GtkWidget *widget, cairo_t *cr, char *image)
{
  // Sets the background to white.
  cairo_set_source_rgb(cr, 1, 1, 1);
  cairo_paint(cr);
  gtk_image_new_from_file(image);
  // Propagates the signal.
  return FALSE;
}


// Sets the 'Stop' state.
void set_reset(OCR *ocr)
{
  OCR->state = READY;
  gtk_button_set_label(OCR->ui.OCR_button, "OCR");
  gtk_button_set_label(OCR->ui.greyscale_button, "greyscale");
  gtk_button_set_label(OCR->ui.binarisation_button, "Binarisation");
  gtk_button_set_label(OCR->ui.noise_button, "Noise");
  gtk_button_set_label(OCR->ui.pretraitement_button, "Pretraitement");
  gtk_button_set_label(OCR->ui.segmentation_button, "Segmentation");
  gtk_button_set_label(OCR->ui.neural_network, "Neural Network");
  gtk_widget_set_sensitive(GTK_WIDGET(OCR->ui.stop_button), FALSE);
  // - Set the state field to STOP.
  // - Set the label of the other button
  // - Disable the stop button.
}

// Event handler for the "clicked" signal of the stop button.
void on_stop(GtkButton *button, gpointer user_data)
{
  set_stop(user_data);
}

void on_ready(GtkButton *button, gpointer user_data)
{
  // Gets the `Game` structure.
  Game *game = user_data;

  // Sets the next state according to the current state.
  switch (game->state)
  {
    case STOP: set_play(game); break;
    case PLAY: set_pause(game); break;
    case PAUSE: set_play(game); break;
  };
}


int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        errx(1, "use : main path_of_an_image");
    }
  // Initializes GTK.
  gtk_init(NULL, NULL);

  // Constructs a GtkBuilder instance.
  GtkBuilder* builder = gtk_builder_new ();

  // Loads the UI description.
  // (Exits if an error occurs.)
  GError* error = NULL;
  if (gtk_builder_add_from_file(builder, "interface.glade", &error) == 0)
  {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }

  // Gets the widgets.
  GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.duel"));
  GtkDrawingArea* area = GTK_DRAWING_AREA(gtk_builder_get_object(builder, "area"));
  GtkButton* ocr_button = GTK_BUTTON(gtk_builder_get_object(builder, "ocr_button"));
  GtkButton* stop_button = GTK_BUTTON(gtk_builder_get_object(builder, "stop_button"));
  GtkButton* greyscale_button = GTK_BUTTON(gtk_builder_get_object(builder,
  "greyscale_button"));
  GtkButton* binarisation_button = GTK_BUTTON(gtk_builder_get_object(builder,
  "binarisation_button"));
  GtkButton* noise_button = GTK_BUTTON(gtk_builder_get_object(builder, "noise_button"));
  GtkButton* pretraitement_button = GTK_BUTTON(gtk_builder_get_object(builder,
  "pretraitement_button"));
  GtkButton* segmentation_button = GTK_BUTTON(gtk_builder_get_object(builder,
  "segmentation_button"));
  GtkButton* neural_network_button = GTK_BUTTON(gtk_builder_get_object(builder,
  "neural_network_button"));
  
  // Connects event handlers.
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(area, "draw", G_CALLBACK(on_draw(argv[1])), &OCR);
  g_signal_connect(ocr_button, "clicked", G_CALLBACK(on_ocr), &OCR);
  g_signal_connect(stop_button, "clicked", G_CALLBACK(on_stop), &OCR);
  // Runs the main loop.
  gtk_main();

  // Exits.
  return 0;
}
