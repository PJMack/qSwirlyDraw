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

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QtWidgets>

#include "glwidget.h"



class Window : public QWidget
{
		Q_OBJECT
	public:
		explicit Window(QWidget *parent = 0);
		void init(void);

		GLWidget *veiwer;
		QProgressBar *progBar;

	signals:
		
	public slots:
		void setProgressFormat(QString format);
		void arL();
		void bnL();
		void deL();
		void esL();
		void frL();
		void hiL();
		void itL();
		void jaL();
		void koL();
		void pgL();
		void ptL();
		void ruL();
		void swL();
		void zhL();
	private:
		QSlider *ColourSlider();
		QSlider *ModeSlider(int modes);
		QSpinBox *GearBox(int def);
		void retranslate(QString locale);

		QMenu *fileMenu;
		QAction *saveAction;
		QAction *exportAction;
		QAction *loadAction;
		QAction *clearAction;
		QAction *resetAction;
		QAction *helpAction;
		QAction *stampAction;
		QMenu *helpMenu;

		QAction *arAction;
		QAction *bnAction;
		QAction *deAction;
		QAction *esAction;
		QAction *frAction;
		QAction *hiAction;
		QAction *itAction;
		QAction *jaAction;
		QAction *koAction;
		QAction *pgAction;
		QAction *ptAction;
		QAction *ruAction;
		QAction *swAction;
		QAction *zhAction;

		QLabel *redLabel;
		QLabel *greenLabel;
		QLabel *blueLabel;
		QLabel *rainbowLabel;

		QSlider *redSlider;
		QSlider *greenSlider;
		QSlider *blueSlider;
		QSlider *rainbowSlider;
		QPushButton *colourRandom;
		QPushButton *colourColourize;
		QGroupBox *colourBox;

		QLabel *outerLabel;
		QLabel *innerLabel;
		QLabel *thirdLabel;
		QLabel *offsetLabel;

		QGroupBox *gearBox;
		QSpinBox *outerGearSize;
		QSpinBox *innerGearSize;
		QSpinBox *thirdGearSize;
		QSpinBox *offset;
		QSlider *outerGearMode;
		QSlider *innerGearMode;
		QSlider *thirdGearMode;
		QPushButton *gearRandomize;

		QGroupBox *engageBox;
		QPushButton *drawButton;
		QPushButton *drawQuickButton;
		QPushButton *demoButton;
		QLabel *scaleLabel;
		QSlider *scaleSlider;
		QLabel *rotLabel;
		QDial *rotDial;

		QTimer *heart;

};

namespace win{
	extern Window *window;
	extern QTranslator *translator;
	extern QApplication *app;
	extern QString locale;
}
#endif // WINDOW_H
