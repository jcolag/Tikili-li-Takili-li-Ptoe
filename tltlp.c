#include <stdlib.h>
#include <gtk/gtk.h>
#include "tltlp_glade.h"

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
    gtk_label_set_label (tltlp_Label_Status, text);
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
        gtk_label_set_label (tltlp_Label_Status, win_text);
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
    char path[256];
    unsigned int index;

    for(index=0;index<sizeof(path);index++) {
        path[index] = '\000';
    }
    readlink("/proc/self/exe", path, sizeof(path));
    for(index = sizeof(path) - 1; index > 0 && path[index] != '/'; index--) {
        path[index] = '\000';
    }

    gtk_init (&argc, &argv);
    load_tltlp_from_file (path, 0);

    /* Get the nine buttons and put them into our grid */
    cells[0][0] = tltlp_Cell_1_1;
    cells[0][1] = tltlp_Cell_1_2;
    cells[0][2] = tltlp_Cell_1_3;
    cells[1][0] = tltlp_Cell_2_1;
    cells[1][1] = tltlp_Cell_2_2;
    cells[1][2] = tltlp_Cell_2_3;
    cells[2][0] = tltlp_Cell_3_1;
    cells[2][1] = tltlp_Cell_3_2;
    cells[2][2] = tltlp_Cell_3_3;

    gtk_widget_show ((GtkWidget *)tltlp_Main_Tltlp);
    g_signal_connect_swapped(G_OBJECT(tltlp_Main_Tltlp), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);
    gtk_main ();

    return 0;
}

