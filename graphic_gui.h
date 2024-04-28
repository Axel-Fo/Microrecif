/*
* Fichier : graphic_gui.hh
* Auteurs : Nestor Guibentif et Axel Fouet
* Version : V2
*/

#ifndef GRAPHIC_GUI_H
#define GRAPHIC_GUI_H

#include <gtkmm/drawingarea.h>
#include "graphic.h"

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);

#endif // GRAPHIC_GUI_H