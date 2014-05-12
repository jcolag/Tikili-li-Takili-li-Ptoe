#include <stdlib.h>
#include <gtk/gtk.h>

GtkButton      *cells[3][3];
GtkLabel       *player_state;
static char     current = 'O';

char state(void);
int check_win_row(char, int);
int check_win_col(char, int);
int check_win_diag(char, int, int);
int check_win(GtkButton *);
void on_cellbutton_clicked(GtkButton *, gpointer);
void on_reset_clicked(GtkButton *, gpointer);

char state(void) {
    /* Check and flip the player state */
    gchar text[32];

    sprintf (text, "%c's Turn", current);
    gtk_label_set_label (player_state, text);
    current = current == 'X' ? 'O' : 'X';
    return current;
}

int check_win_row(char player, int row) {
    const gchar *text;
    int col;
    for(col=0;col<3;col++) {
        text = gtk_button_get_label (cells[row][col]);
        if (text[0] != player) {
            return 0;
        }
    }
    return 1;
}

int check_win_col(char player, int col) {
    const gchar *text;
    int row;
    for(row=0;row<3;row++) {
        text = gtk_button_get_label (cells[row][col]);
        if (text[0] != player) {
            return 0;
        }
    }
    return 1;
}

int check_win_diag(char player, int row, int col) {
    const gchar *text;
    int i;

    if (abs(row - 1) != abs(col - 1)) {
        /* The cell is not on the diagonal */
        return 0;
    }
    if (row - 1 == col - 1) {
        /* The cell is on the downward diagonal */
        for (i=0;i<3;i++) {
            text = gtk_button_get_label (cells[i][i]);
            if (text[0] != player) {
                break;
            }
        }
        if (i == 3) {
            return 1;
        }
    }
    if (row - 1 == 1 - col) {
        /* The cell is on the upward diagonal */
        for (i=0;i<3;i++) {
            text = gtk_button_get_label (cells[i][2-i]);
            if (text[0] != player) {
                break;
            }
        }
        if (i == 3) {
            return 1;
        }
    }
    return 0;
}

int check_win(GtkButton *last) {
    int i, j, win = 0;
    const gchar *text = gtk_button_get_label (last);
    char player = text[0];

    /* Find the button so we can use its coordinates */
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            if (cells[i][j] == last) {
                break;
            }
        }
        if (j < 3) {
            break;
        }
    }
    /* Test the directions */
    win = win || check_win_row(player, i);
    win = win || check_win_col(player, j);
    win = win || check_win_diag(player, i, j);
    return win;
}

void on_cellbutton_clicked(GtkButton *button, gpointer user_data) {
    char    new_label[2],
            player = state();
    gchar   win_text[32];

    /* Claim the button for the current player */
    sprintf(new_label, "%c", player);
    gtk_button_set_label (button, new_label);
    gtk_widget_set_sensitive ((GtkWidget *)button, FALSE);

    if (check_win(button)) {
        sprintf(win_text, "%c Wins!", player);
        gtk_label_set_label (player_state, win_text);
    }
}

void on_reset_clicked(GtkButton *button, gpointer user_data) {
    int        i, j;
    GtkButton *b;

    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            b = cells[i][j];
            gtk_button_set_label (b, "?");
            gtk_widget_set_sensitive ((GtkWidget *)b, TRUE);
        }
    }
    current = 'X';
    state();
}

int main (int argc, char *argv[]) {
    GtkBuilder          *builder;
    GtkWidget           *window;
    char                 name[64];
    int                  i,
                         j;
    
    gtk_init (&argc, &argv);
    
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "tltlp.glade", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "Main_Tltlp"));
    gtk_builder_connect_signals (builder, NULL);      

    /* Get the nine buttons and put them into our grid */
    for (i=0;i<3;i++) {
        for (j=0;j<3;j++) {
            sprintf(name, "Cell_%d_%d", i+1, j+1);
            cells[i][j] = (GtkButton *)GTK_WIDGET (gtk_builder_get_object (builder, name));
        }
    }
    /* Grab the status bar label, too */
    player_state = (GtkLabel *)GTK_WIDGET (gtk_builder_get_object (builder, "Label_Status"));
    g_object_unref (G_OBJECT (builder));

    gtk_window_set_default_size(GTK_WINDOW(window), 230, 150);
    gtk_widget_show (window);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);
    gtk_main ();

    return 0;
}

