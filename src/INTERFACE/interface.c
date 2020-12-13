#include "interface.h"

// Structure of the graphical user interface.

// State of the game.
typedef enum State
{
    READY,                          // Ready state
    DONE,                            // OCR state
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
    GtkButton* OCR_button;          // OCR button
    GtkButton* greyscale_button;    // Greyscale button
    GtkButton* binarisation_button; // Binarisation button
    GtkButton* pretraitement_button;// Pre-traitement button
    GtkButton* segmentation_button; // Segmentation button
    GtkButton* neural_network_button;// Neural Network button
    GtkButton* stop_button;        // Stop Button
} UserInterface;

typedef struct OCR
{
    State state;        //State of the OCR
    UserInterface ui;   //User Interace
    char* image;        //Image for the OCR
} OCR;


// Event handler for the "draw" signal of the drawing area.
gboolean on_draw(cairo_t *cr, gpointer user_data)
{
    OCR *ocr = user_data;
    // Sets the background to white.
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    gtk_image_new_from_file(ocr->image);
    // Propagates the signal.
    return FALSE;
}

// Sets the 'Stop' state.
void set_stop(OCR *ocr)
{
    ocr->state = READY;
    gtk_button_set_label(ocr->ui.OCR_button, "OCR");
    gtk_button_set_label(ocr->ui.greyscale_button, "greyscale");
    gtk_button_set_label(ocr->ui.binarisation_button, "Binarisation");
    gtk_button_set_label(ocr->ui.pretraitement_button, "Pretraitement");
    gtk_button_set_label(ocr->ui.segmentation_button, "Segmentation");
    gtk_button_set_label(ocr->ui.neural_network_button, "Neural Network");
    gtk_widget_set_sensitive(GTK_WIDGET(ocr->ui.stop_button), FALSE);
    // - Set the state field to STOP.
    // - Set the label of the other button
    // - Disable the stop button.
}

// Event handler for the "clicked" signal of the stop button.
void on_stop(gpointer user_data)
{
    set_stop(user_data);
}

int main (int argc, char* argv[])
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
    GtkButton* pretraitement_button = GTK_BUTTON(gtk_builder_get_object(builder,
                "pretraitement_button"));
    GtkButton* segmentation_button = GTK_BUTTON(gtk_builder_get_object(builder,
                "segmentation_button"));
    GtkButton* neural_network_button = GTK_BUTTON(gtk_builder_get_object(builder,
                "neural_network_button"));  

    // Creates the "OCR" structure.
    OCR ocr =
    {
        .state = READY,

        .ui =
        {
            .window = window,                              // Window
            .area = area,                                  // Area
            .OCR_button = ocr_button,                      // OCR button
            .greyscale_button = greyscale_button,          // Greyscale button
            .binarisation_button = binarisation_button,    // Binarisation butto
            .pretraitement_button = pretraitement_button,  // Pre-traitement button
            .segmentation_button = segmentation_button,    // Segmentation button
            .neural_network_button = neural_network_button,// Neural Network button
            .stop_button = stop_button                     // Stop Button
        },

        .image = argv[1]
    };

    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(area, "draw", G_CALLBACK(on_draw), &ocr);
    //g_signal_connect(ocr_button, "clicked", G_CALLBACK(on_ocr), &ocr);
    g_signal_connect(stop_button, "clicked", G_CALLBACK(on_stop), &ocr);
    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
