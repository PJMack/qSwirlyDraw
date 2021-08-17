/* © Copyright 2013 Peter J Mack

 * This file is part of qSwirlyDraw.

 * qSwirlyDraw is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * qSwirlyDraw is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with qSwirlyDraw.  If not, see <https://www.gnu.org/licenses/>. */

#include <QApplication>
#include <QDesktopWidget>

#include "window.h"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	win::app=&app;

	win::locale="en";
	QTranslator translator;
	translator.load(QString("SwirlyDraw_") + win::locale);
	win::translator=&translator;
	app.installTranslator(&translator);
	QIcon icon("icon.png");
	app.setWindowIcon(icon);

	Window window;
	win::window=&window;

	window.resize(320, 240);
    window.init();
    window.show();
    //window.init();
	return app.exec();

}
