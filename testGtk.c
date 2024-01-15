
#include <gtk/gtk.h>
#include "image.h"  // Include the image header
#include "arbrezpixel.h"


void on_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = GTK_WIDGET(user_data);
    gtk_widget_hide(window);
}

void write_bmp(const char *filename, const Image *image) {
    g_print("ecriture de fichier bmp");
    if (image == NULL || image->pixels == NULL) {
        fprintf(stderr, "Error: Invalid image structure or pixel data.\n");
        return;
    }

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening BMP file for writing");
        return;
    }

    unsigned char bmp_header[54] = {
        'B', 'M',             
        0, 0, 0, 0,         
        0, 0, 0, 0,          
        54, 0, 0, 0,          
        40, 0, 0, 0,         
        0, 0, 0, 0,           
        0, 0, 0, 0,          
        1, 0,                 
        24, 0,                
        0, 0, 0, 0,          
        0, 0, 0, 0,           
        0, 0, 0, 0,           
        0, 0, 0, 0,          
        0, 0, 0, 0,         
        0, 0, 0, 0           
    };

    int file_size = 54 + image->rowstride * image->hauteur;
    int image_width = image->largeur;
    int image_height = image->hauteur;
    int image_size = image->rowstride * image->hauteur;

    memcpy(bmp_header + 2, &file_size, 4);
    memcpy(bmp_header + 18, &image_width, 4);
    memcpy(bmp_header + 22, &image_height, 4);
    memcpy(bmp_header + 34, &image_size, 4);

    fwrite(bmp_header, sizeof(unsigned char), 54, file);

    fwrite(image->pixels, sizeof(unsigned char), image_size, file);

    fclose(file);
}

void open_dialog(GtkMenuItem *menuitem, gpointer user_data) {
    g_print("ouvrir\n");

    GtkBuilder *builder = GTK_BUILDER(user_data); 
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File",
                                                   GTK_WINDOW(gtk_builder_get_object(builder, "window")),
                                                   action,
                                                   "Cancel", GTK_RESPONSE_CANCEL,
                                                   "Open", GTK_RESPONSE_ACCEPT,
                                                   NULL);

    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter, "*.bmp");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    gtk_widget_show_all(dialog);
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == GTK_RESPONSE_ACCEPT) {
        gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if (filename != NULL) {
            g_print("Selected file: %s\n", filename);

            GtkWidget *image_widget = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));

            GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, NULL);
            
            if (pixbuf != NULL) {
                g_print("construction de l'arbre");
                gtk_image_set_from_pixbuf(GTK_IMAGE(image_widget), pixbuf);

                int width = gdk_pixbuf_get_width(pixbuf);
                int height = gdk_pixbuf_get_height(pixbuf);
                int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
                guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);

                Image image;
                image.largeur = width;
                image.hauteur = height;
                image.rowstride = rowstride;
                image.pixels = g_malloc(rowstride * height);
                memmove(image.pixels, pixels, rowstride * height);

                GNode* CreateArbre = CreateArbreZpixel(0, 0, width*height, &image, &degradationTaille);
                Image * imag = copie_image(CreateArbre, &image, 1);


                if(CreateArbre == NULL){
                    printf("La creation de l'arbre a echoué");
                }
                write_bmp("images/result.bmp",imag);
                GtkWidget *image_widgetDeg = GTK_WIDGET(gtk_builder_get_object(builder, "image2"));
                GdkPixbuf *pixbufDegrad = gdk_pixbuf_new_from_file("images/result.bmp", NULL);
                gtk_image_set_from_pixbuf(GTK_IMAGE(image_widgetDeg), pixbufDegrad);

        }


                // g_object_unref(pixbuf);

               
            g_free(filename);
            // g_object_unref(pixbuf);
        }
    }

    gtk_widget_destroy(dialog);
}


void on_about_activate(GtkMenuItem *menuitem, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkWidget *window_apropos = GTK_WIDGET(gtk_builder_get_object(builder, "A propos"));
    gtk_widget_show_all(window_apropos);
}

void on_fichier_activate(GtkMenuItem *menuitem, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);
    GtkWidget *window_apropos = GTK_WIDGET(gtk_builder_get_object(builder, "fichier"));
    gtk_widget_show_all(window_apropos);
}

int main(int argc, char *argv[]) {
    GtkWidget *main_window;
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "UnimageIhm.glade", NULL)) {
        g_printerr("Error loading Glade file.\n");
        return 1;
    }

    main_window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    GtkWidget *aboutMenuItem = GTK_WIDGET(gtk_builder_get_object(builder, "aboutItem"));
    g_signal_connect(aboutMenuItem, "activate", G_CALLBACK(on_button_clicked), builder);

    if (aboutMenuItem == NULL) {
        g_printerr("Error: Could not find 'aboutItem' menu item.\n");
        return 1;
    }

    GtkWidget *chooseFile = GTK_WIDGET(gtk_builder_get_object(builder, "openFile"));
    g_signal_connect(chooseFile, "activate", G_CALLBACK(open_dialog), builder); 
    GtkWidget *okButton = GTK_WIDGET(gtk_builder_get_object(builder, "finApropos"));
    g_signal_connect(okButton, "activate", G_CALLBACK(on_button_clicked), main_window);

    gtk_widget_show_all(main_window);

    gtk_main();
    return 0;
}

