/*
 * MIT License
 *
 * Copyright (c) 2018 kudima
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef DISPLAY_FIELD
#define DISPLAY_FIELD
#include <gtk/gtk.h>
#include "mines_field.h"

GdkPixmap *pixmap_opened;
GdkPixmap *pixmap_marked;
GdkPixmap *pixmap_closed;
GdkPixmap *pixmap_boom;
GdkPixmap *pixmap_mine;
GdkPixmap *pixmap_pressed;
GdkPixmap *pixmap_numbers[8];

enum actions
{
	ACTION_OPEN,
	ACTION_MARK,
	ACTION_OPEN_AROUND,
};

enum pressed_states
{
	PRESSED_STATE_ALONE,
	PRESSED_STATE_AROUND,
	PRESSED_NONE
};

typedef void (*StateHandler)(GObject*, MinesField*);

/* data */
typedef struct
{
	GtkWidget *widget; /* field display widget */
	GObject *object; /* an object which handle field state changes */
	StateHandler state_handler;
	gint cell_size;
	MinesField *field;
	gint x_prev;
	gint y_prev;
} DisplayField;

/* functions */
DisplayField* display_field_new(MinesField *mf, GObject *object,
								StateHandler state_handler, gint cell_size);

gboolean display_field_expose_event(GtkWidget *widget,
									GdkEventExpose *event,
									gpointer df);

gboolean display_field_button_event(GtkWidget *widget,
									GdkEventButton *event,
									gpointer data);

gboolean display_field_motion_event(GtkWidget *widget,
									GdkEventButton *event,
									gpointer data);

static gboolean display_field_show(GdkDrawable *canvas,
								   DisplayField *df, gboolean full_update);

void display_field_show_pressed(GdkDrawable *draw,
								DisplayField *df, GdkGC *gc,
								gint x, gint y);

void display_field_show_pressed_around(GdkDrawable *draw,
									   DisplayField *df, GdkGC *gc,
									   gint x, gint y);

void display_field_show_number(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
							   gint i, gint j, gint number);

void display_field_show_closed(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
							   gint i, gint j);

void display_field_show_opened(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
							   gint i, gint j);

void display_field_show_marked(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
							   gint i, gint j);

void display_field_show_boom(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
							 gint i, gint j);

void display_field_show_mine(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
							 gint i, gint j);

void display_field_show_pressed(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
								gint i, gint j);

void display_field_show_xpm(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
							gint i, gint j, const gchar *xpm_file);

void display_field_show_pixmap(GdkDrawable *draw, DisplayField *df, GdkGC *gc,
							   gint i, gint j, GdkPixmap *pixmap);
#endif
