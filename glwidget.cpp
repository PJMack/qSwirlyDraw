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

#include "glwidget.h"
#include <cmath>
#include <cstdlib>
#include "graph.h"
#include "fileio.h"

GLWidget::GLWidget(QWidget *parent) :
	QGLWidget(parent)
{
	ticks=0;
	slowDrawOn=false;
	graph::drawing = &slowDrawOn;
	demoOn=false;
///	graph::colourOutput=setColour;

	emit changedInner(graph::innergear);
	emit changedOuter(graph::outergear);
	emit changedThird(graph::thirdgear);
	emit changedOffset(graph::offset);
}

GLWidget::~GLWidget(){

}

QSize GLWidget::minimumSizeHint() const{
	return QSize(400,400);
}

/** QSize GLWidget::sizeHint() const{
	return QSize(1000,1000);
}*/

int GLWidget::heightForWidth(int w) const{
	return w;
}

void GLWidget::initializeGL(){
	qglClearColor(QColor(255,255,255));
	glShadeModel(GL_FLAT);

}

void GLWidget::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glPushMatrix();

		if(!graph::subgraph_array.empty())
		for(unsigned int i = 0; i < graph::subgraph_array.size(); i++){
			glPushMatrix();
				glScalef(graph::subgraph_array[i].Scale(),graph::subgraph_array[i].Scale(), 1);
				glRotatef(graph::subgraph_array[i].Rotation(),0,0,1);

				if(!graph::subgraph_array[i].Vertex_Array().empty() && !graph::subgraph_array[i].Vertex_Array().empty()){
					glVertexPointer(2, GL_FLOAT, 0, &(graph::subgraph_array[i].Vertex_Array()[0]));
					glColorPointer(3, GL_FLOAT, 0, &(graph::subgraph_array[i].Color_Array()[0]));
					glDrawArrays(GL_LINE_STRIP,0, graph::subgraph_array[i].Vertex_Array().size() / 2);
				}
			glPopMatrix();
		}

		glScalef(graph::scale,graph::scale,1);
		glRotatef(graph::rotation,0,0,1);

		if(!graph::vertex_array.empty() && !graph::color_array.empty()){
			glVertexPointer(2, GL_FLOAT, 0, &(graph::vertex_array[0]));
			glColorPointer(3, GL_FLOAT, 0, &(graph::color_array[0]));
			glDrawArrays(GL_LINE_STRIP,0, graph::vertex_array.size() / 2);
		}
	glPopMatrix();
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

}

void GLWidget::resizeGL(int width, int height){
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200,200,-200,200,-1,1);
	glMatrixMode(GL_MODELVIEW);

}

void GLWidget::mousePressEvent(QMouseEvent *event){

}

void GLWidget::mouseMoveEvent(QMouseEvent *event){

}

void GLWidget::setColour(int r, int g, int b){
	emit changedRed(r);
	emit changedGreen(g);
	emit changedBlue(b);
}

void GLWidget::setRed(int r){
	graph::currentcolor.v[0] = (float)r / 255.0;
}
void GLWidget::setGreen(int g){
	graph::currentcolor.v[1] = (float)g / 255.0;
}
void GLWidget::setBlue(int b){
	graph::currentcolor.v[2] = (float)b / 255.0;
}

void GLWidget::setRainbowMode(int n){
	graph::rainbowMode=n;
}

void GLWidget::setThird(int n){
	graph::thirdgear = n;
}
void GLWidget::setOffset(int n){
	graph::offset = n;
}
void GLWidget::setOuter(int n){
	graph::outergear = n;
}
void GLWidget::setInner(int n){
	graph::innergear = n;
	emit changedDrawingEnabled(n!=0);
}
void GLWidget::setScale(int n){
	graph::scale = pow(10,(double)n / 100.0);
	updateGL();
}
void GLWidget::setRotation(int r){
	graph::rotation = r;
	updateGL();
}

void GLWidget::drawGraph(){
	emit changedProgressFormat(tr("Calculating (%p% complete"));
	graph::ResetGraph();
	graph::CalcGraph();
	emit changedRed(graph::currentcolor.R());
	emit changedGreen(graph::currentcolor.G());
	emit changedBlue(graph::currentcolor.B());
	emit changedProgressFormat(tr("Calculations Complete"));
	updateGL();
	emit changedProgressFormat(tr("Drawing Complete"));
}
void GLWidget::clearGraph(){
	graph::ResetGraph();
	updateGL();

}
void GLWidget::slowDraw(bool t){
	graph::ResetGraph();
	graph::CalcThetaMax();
	slowDrawOn=t;
	emit changedGearSelectEnabled(!t);
	emit changedScreansaver(false);
	emit changedProgressFormat(tr("Drawing (%p% complete)"));
}

void GLWidget::setOuterGearType(int n){
	switch (n){
		case 1:
			graph::outerGear=graph::gearEgg;
			break;
		case 2:
			graph::outerGear=graph::gearPnut;
			break;
		case 3:
			graph::outerGear=graph::gearTri;
			break;
		case 4:
			graph::outerGear=graph::gearSqr;
			break;
		case 0:
			graph::outerGear=graph::gearStd;
			break;
		default:
			graph::outerGear=graph::gearStd;
	}
}
void GLWidget::setInnerGearType(int n){
	switch (n){
		case 1:
			graph::innerGear=graph::gearEgg;
			break;
		case 2:
			graph::innerGear=graph::gearPnut;
			break;
		case 3:
			graph::innerGear=graph::gearTri;
			break;
		case 4:
			graph::innerGear=graph::gearSqr;
			break;
		case 0:
			graph::innerGear=graph::gearStd;
			break;
		default:
			graph::innerGear=graph::gearStd;
	}
}
void GLWidget::setThirdGearType(int n){
	switch (n){
		case 1:
			graph::thirdGear=graph::gearEgg;
			break;
		case 2:
			graph::thirdGear=graph::gearPnut;
			break;
		case 3:
			graph::thirdGear=graph::gearTri;
			break;
		case 4:
			graph::thirdGear=graph::gearSqr;
			break;
		case 0:
			graph::thirdGear=graph::gearStd;
			break;
		default:
			graph::thirdGear=graph::gearStd;
	}
}

void GLWidget::colourize(void){
	graph::theta=0;
	graph::theta1=0;
	graph::theta2=0;
	graph::theta3=0;
	for(unsigned int i = 0; i < graph::color_array.size() / 3; i++){
		if(graph::rainbowMode){
			std::complex<float> point(graph::vertex_array[2 * i], graph::vertex_array[2 * i + 1]);
			switch (graph::rainbowMode){
				case 2:
				graph::currentcolor.SetHue(graph::theta2);
					break;
				case 3:
					graph::currentcolor.SetHue(graph::theta3);
					break;
				case 4:
					graph::currentcolor.SetHue(50 * graph::scale * abs(point));
					break;
				case 1:
					graph::currentcolor.SetHue(graph::theta);
					break;
				default:
					;
			}
		}
		graph::color_array[3 * i + 0] = graph::currentcolor[0];
		graph::color_array[3 * i + 1] = graph::currentcolor[1];
		graph::color_array[3 * i + 2] = graph::currentcolor[2];
		graph::advance(2 * graph::PI / THETA_INC);
	}
	emit changedRed(graph::currentcolor.R());
	emit changedGreen(graph::currentcolor.G());
	emit changedBlue(graph::currentcolor.B());

	updateGL();
}
void GLWidget::help(void){
	if(win::locale == "en"){
		std::system("xdg-open /opt/SwirlyDraw/qWebpage.html");
	}else{
        QString cmd = QString("http://translate.google.com/translate?hl=") + win::locale + QString("&sl=en&tl=") + win::locale + QString("&u=https%3A%2F%2Fdl.dropboxusercontent.com%2Fu%2F20374671%2FSwirlyDraw%2FqSwirlyDraw.htm");
		std::cout << "executing: " << cmd.toStdString().c_str() << "\n";
		///std::system(cmd.toStdString().c_str());
		QDesktopServices::openUrl(cmd);

	}
}

void GLWidget::randomColour(void){
	srand(time(NULL));
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	graph::currentcolor[0] = (float)r / 255;
	graph::currentcolor[1] = (float)g / 255;
	graph::currentcolor[2] = (float)b / 255;
	graph::rainbowMode = rand() % 5;

	emit changedRed(r);
	emit changedGreen(g);
	emit changedBlue(b);
	emit changedRainbowMode(graph::rainbowMode);

}
void GLWidget::randomGearing(void){
	srand(time(NULL) + graph::innergear + graph::outergear + graph::thirdgear + graph::offset);
	do {graph::innergear = (rand() % 300) - 150;} while (!graph::innergear);
	do {graph::outergear = (rand() % 300) - 150;} while (!graph::outergear);
	graph::thirdgear = (rand() % 300) - 150;
	graph::offset = (rand() % 300) - 150;
	int O = rand()%5;
	int I = rand()%5;
	int T = rand()%5;
	setOuterGearType(O);
	setInnerGearType(I);
	setThirdGearType(T);
	//check if memory can be allocated, if not, try again;
	try{
		graph::CalcThetaMax();
		if(rand() % 2){
			graph::vertex_array.reserve(graph::thetamax * THETA_INC * 2);
			graph::color_array.reserve(graph::thetamax * THETA_INC * 3);
		}else{
			graph::color_array.reserve(graph::thetamax * THETA_INC * 3);
			graph::vertex_array.reserve(graph::thetamax * THETA_INC * 2);
		}
	}catch(std::exception &ex){
		std::cout << "Error: " << ex.what() << '\n';
		randomGearing();
	}
	emit changedInner(graph::innergear);
	emit changedOuter(graph::outergear);
	emit changedThird(graph::thirdgear);
	emit changedOffset(graph::offset);
	emit changedInnerGearType(I);
	emit changedOuterGearType(O);
	emit changedThirdGearType(T);

}
void GLWidget::RESET(void){
	graph::ResetGraph();
	graph::subgraph_array.clear();
	updateGL();
}
void GLWidget::screansaver(bool t){
	demoOn=t;
	slowDrawOn=t;
	emit changedGearSelectEnabled(!t);
	emit changedSlowDraw(t);
	emit changedProgressFormat(tr("Demo Mode"));
}

void GLWidget::saveFile(void){
	///slowDraw(false);
	QString filename = QFileDialog::getSaveFileName(this, tr("Save \"swirlydraw\" File"), "/home/", tr("All Files"));
	if(filename.isNull()) return;
	try{
		fileio::save(filename.toStdString());
	}catch (std::exception &ex){
		emit changedProgressFormat(tr("File Error"));
	}
}

void GLWidget::exportFile(void){
	///slowDraw(false);
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Image File"), "/home/", "*.png");
	if(filename.isNull()) return;
	try{
		fileio::exportxpm(filename.toStdString());
	}catch (std::exception &ex){
		emit changedProgressFormat(tr("File Error"));
	}
}

void GLWidget::loadFile(void){
	QString filename = QFileDialog::getOpenFileName(this, tr("Load \"swirlydraw\" File"), "/home/", tr("All Files"));
	if(filename.isNull()) return;
	///slowDraw(false);
	try{
		if(!fileio::exportxpm(filename.toStdString())){
			emit changedProgressFormat(tr("File Error"));
		}
	}catch(std::exception &ex){
		emit changedProgressFormat(tr("File Error"));
	}
}

void GLWidget::stamp(void){
	graph::Stamp();
}

void GLWidget::beat(){
	//for drawing slowly;
	const double t=2 * graph::PI / THETA_INC;
	if(slowDrawOn){
		try{
			graph::PenDraw();
			emit changedProgress(graph::theta * 256 / graph::thetamax);

		}catch(std::exception &ex){
			emit changedSlowDraw(false);
			emit changedScreansaver(false);
			emit changedGearSelectEnabled(true);
			std::cout << "Abborted SlowDraw at" << ticks << "\n";
			emit changedProgressFormat(tr("Memory Error"));
		}
		if(graph::theta > graph::thetamax){
			if(demoOn){
				graph::ResetGraph();
				randomGearing();
				randomColour();
				graph::CalcThetaMax();
			}else{
				emit changedSlowDraw(false);
				slowDrawOn=false;
				emit changedGearSelectEnabled(true);
				std::cout << "Ended SlowDraw at " << ticks << "\n";
				emit changedProgressFormat(tr("Drawing Complete"));
			}
		}
		graph::advance(t);
        ///updateGL();
	}

    if(slowDrawOn || !(ticks%64))
        updateGL();

	ticks++;
	if(!(ticks%2048) && demoOn){
		graph::ResetGraph();
		randomGearing();
		randomColour();
		graph::CalcThetaMax();

	}

}
