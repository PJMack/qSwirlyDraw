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
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
		Q_OBJECT
	public:
		explicit GLWidget(QWidget *parent = 0);
		~GLWidget();

		QSize minimumSizeHint() const;
		///QSize sizeHint() const;
		int heightForWidth(int w) const;

		void setColour(int r, int g, int b);

	signals:
		void changedRed(int r);
		void changedGreen(int g);
		void changedBlue(int b);
		void changedRainbowMode(int n);

		void changedThird(int n);
		void changedOffset(int n);
		void changedOuter(int n);
		void changedInner(int n);
		void changedScale(int n);
		void changedRotation(int r);

		void changedThirdGearType(int n);
		void changedInnerGearType(int n);
		void changedOuterGearType(int n);

		void changedSlowDraw(bool t);
		void changedScreansaver(bool t);

		void changedGearSelectEnabled(bool t);
		void changedDrawingEnabled(bool t);
		void changedProgress(int p);
		void changedProgressFormat(QString format);

	public slots:
		void setRed(int r);
		void setGreen(int g);
		void setBlue(int b);
		void setRainbowMode(int n);
		void setThird(int n);
		void setOffset(int n);
		void setOuter(int n);
		void setInner(int n);
		void setScale(int n);
		void setRotation(int r);

		void drawGraph();
		void clearGraph();
		void slowDraw(bool t);

		void setThirdGearType(int n);
		void setInnerGearType(int n);
		void setOuterGearType(int n);

		void colourize(void);
		void help(void);

		void randomColour(void);
		void randomGearing(void);
		void RESET(void);
		void screansaver(bool t);

		void saveFile(void);
		void exportFile(void);
		void loadFile(void);
		void stamp(void);
		void beat();
	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
	private:
		int ticks;
		bool slowDrawOn;
		bool demoOn;
};

#endif // GLWIDGET_H
