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
 
#include "window.h"
#include <QtWidgets>
#include "glwidget.h"
#include <iostream>

Window::Window(QWidget *parent) :
	QWidget(parent)
{
}
void Window::init(){
#ifdef DEMO
	int day=(std::string (getenv("HOME"))).size() % 9;
	day+=1;
	//trial- get the date
	FILE* ntp = popen("ntpdate -q time.nist.gov", "r");
	if(ntp){
		char buff[512];
		fgets(buff, sizeof(buff), ntp);
		fgets(buff, sizeof(buff), ntp);
		std::string timestring = (std::string)buff;
		if(timestring.size()){
			if(timestring.rfind("no server") != std::string::npos){
				sscanf(buff, "%d", &day);
				day %= 10;
			}
		}
		pclose(ntp);
	}
	srand(day);
#endif

	QMenuBar *menuBar = new QMenuBar(this);
	fileMenu = new QMenu(tr("&File"));
	loadAction = fileMenu->addAction(tr("&Load"));
	saveAction = fileMenu->addAction(tr("&Save"));
	exportAction = fileMenu->addAction(tr("E&xport"));
	clearAction = fileMenu->addAction(tr("&Clear"));
	resetAction = fileMenu->addAction(tr("&RESET"));
	stampAction = fileMenu->addAction(tr("Stam&p"));
	helpMenu = new QMenu(tr("&Help"));
	QMenu *langMenu = new QMenu("ar/bn/de/es/...");

	arAction = langMenu->addAction("العربية");
	bnAction = langMenu->addAction("বাংলা");
	deAction = langMenu->addAction("Deutsch");
	pgAction = langMenu->addAction("English");
	esAction = langMenu->addAction("Español");
	frAction = langMenu->addAction("Français");
	hiAction = langMenu->addAction("हिन्दी");
	itAction = langMenu->addAction("Italiano");
	jaAction = langMenu->addAction("日本語");
	koAction = langMenu->addAction("한국어");
	ptAction = langMenu->addAction("Português");
	ruAction = langMenu->addAction("Русский язык");
	swAction = langMenu->addAction("Kiswahili");
	zhAction = langMenu->addAction("中文");

	helpAction = helpMenu->addAction(tr("&Help Page"));
	helpMenu->addMenu(langMenu);



	menuBar->addMenu(fileMenu);
	menuBar->addMenu(helpMenu);

	/** QStatusBar *statusBar = new QStatusBar(this);
	statusBar->showMessage(tr("(C) 2013 Peter Mack"));*/

	redSlider = ColourSlider();
	greenSlider = ColourSlider();
	blueSlider = ColourSlider();
	rainbowSlider = ModeSlider(4);

	redLabel=new QLabel(tr("Red:"));
	greenLabel=new QLabel(tr("Green:"));
	blueLabel=new QLabel(tr("Blue:"));
	rainbowLabel=new QLabel(tr("Rainbow:"));

	QFormLayout *colourSliderLayout = new QFormLayout();
	colourSliderLayout->addRow(redLabel, redSlider);
	colourSliderLayout->addRow(greenLabel, greenSlider);
	colourSliderLayout->addRow(blueLabel, blueSlider);
	colourSliderLayout->addRow(rainbowLabel, rainbowSlider);

	colourRandom = new QPushButton(tr("Randomize"));
	colourColourize = new QPushButton(tr("Colourize"));
	QHBoxLayout *colourButtonsLayout;
	colourButtonsLayout = new QHBoxLayout;
	colourButtonsLayout->addWidget(colourRandom);
	colourButtonsLayout->addWidget(colourColourize);
	QVBoxLayout *colourLayout = new QVBoxLayout;
	colourLayout->addLayout(colourSliderLayout);
	colourLayout->addLayout(colourButtonsLayout);

	colourBox = new QGroupBox(tr("Select Colour"));
	colourBox->setLayout(colourLayout);

	outerGearSize = GearBox(30);
	innerGearSize = GearBox(50);
	thirdGearSize = GearBox(15);
	offset = GearBox(5);

	outerGearMode = ModeSlider(4);
	innerGearMode = ModeSlider(4);
	thirdGearMode = ModeSlider(4);

	gearRandomize = new QPushButton(tr("Randomize"));

	outerLabel=new QLabel(tr("Outer"));
	innerLabel=new QLabel(tr("Inner"));
	thirdLabel=new QLabel(tr("Third"));
	offsetLabel=new QLabel(tr("Offset"));

	QGridLayout *gearBoxLayout = new QGridLayout;
	gearBoxLayout->addWidget(outerLabel,0,0,1,1);
	gearBoxLayout->addWidget(outerGearSize,0,1,1,1);
	gearBoxLayout->addWidget(outerGearMode,0,2,1,1);
	gearBoxLayout->addWidget(innerLabel,1,0,1,1);
	gearBoxLayout->addWidget(innerGearSize,1,1,1,1);
	gearBoxLayout->addWidget(innerGearMode,1,2,1,1);
	gearBoxLayout->addWidget(thirdLabel,2,0,1,1);
	gearBoxLayout->addWidget(thirdGearSize,2,1,1,1);
	gearBoxLayout->addWidget(thirdGearMode,2,2,1,1);
	gearBoxLayout->addWidget(offsetLabel,3,0,1,1);
	gearBoxLayout->addWidget(offset,3,1,1,2);
	gearBoxLayout->addWidget(gearRandomize,4,0,1,3);
	gearBox = new QGroupBox(tr("Select Gears"));
	gearBox->setLayout(gearBoxLayout);

	drawButton = new QPushButton(tr("Draw"));
	drawButton->setCheckable(true);
	drawQuickButton = new QPushButton(tr("Draw Quickly"));
	demoButton = new QPushButton(tr("Demonstration"));
	demoButton->setCheckable(true);
	scaleLabel = new QLabel(tr("Scale:"));
	scaleSlider = new QSlider(Qt::Horizontal);
	scaleSlider->setMinimum(-100);
	scaleSlider->setMaximum(100);
	scaleSlider->setTickPosition(QSlider::NoTicks);
	scaleSlider->setValue(0);
	rotLabel = new QLabel(tr("Rotation:"));
	rotDial = new QDial;
	rotDial->setWrapping(true);
	rotDial->setMinimum(-180);
	rotDial->setMaximum(180);
	rotDial->setNotchesVisible(false);
	rotDial->setValue(0);
	progBar = new QProgressBar;
	progBar->setMinimum(0);
	progBar->setMaximum(256);
	progBar->setValue(0);
	progBar->setFormat("");


	engageBox = new QGroupBox(tr("Engage"));
	QGridLayout *engageBoxLayout = new QGridLayout;
	engageBoxLayout->addWidget(drawButton, 0,0,1,2);
	engageBoxLayout->addWidget(drawQuickButton,1,0,1,2);
	engageBoxLayout->addWidget(demoButton,3,0,1,2);
	engageBoxLayout->addWidget(scaleLabel,4,0,1,1);
	engageBoxLayout->addWidget(scaleSlider,4,1,1,1);
	engageBoxLayout->addWidget(rotLabel,5,0,1,1);
	engageBoxLayout->addWidget(rotDial,5,1,1,1);
	engageBoxLayout->addWidget(progBar,6,0,1,2);
	engageBox->setLayout(engageBoxLayout);


	QVBoxLayout *sideLayout = new QVBoxLayout;
	sideLayout->addWidget(colourBox);
	sideLayout->addWidget(gearBox);
	sideLayout->addWidget(engageBox);


	veiwer = new GLWidget;
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(sideLayout);
	mainLayout->addWidget(veiwer,100);

	connect(redSlider,SIGNAL(valueChanged(int)), veiwer, SLOT(setRed(int)));
	connect(veiwer, SIGNAL(changedRed(int)), redSlider, SLOT(setValue(int)));
	connect(greenSlider,SIGNAL(valueChanged(int)), veiwer, SLOT(setGreen(int)));
	connect(veiwer, SIGNAL(changedGreen(int)), greenSlider, SLOT(setValue(int)));
	connect(blueSlider,SIGNAL(valueChanged(int)), veiwer, SLOT(setBlue(int)));
	connect(veiwer, SIGNAL(changedBlue(int)), blueSlider, SLOT(setValue(int)));
	connect(rainbowSlider,SIGNAL(valueChanged(int)), veiwer, SLOT(setRainbowMode(int)));
	connect(veiwer, SIGNAL(changedRainbowMode(int)), rainbowSlider, SLOT(setValue(int)));
	connect(colourRandom, SIGNAL(clicked()), veiwer, SLOT(randomColour()));
	connect(colourColourize, SIGNAL(clicked()), veiwer, SLOT(colourize()));

	connect(outerGearSize, SIGNAL(valueChanged(int)), veiwer, SLOT(setOuter(int)));
	connect(veiwer, SIGNAL(changedOuter(int)), outerGearSize, SLOT(setValue(int)));
	connect(outerGearMode, SIGNAL(valueChanged(int)), veiwer, SLOT(setOuterGearType(int)));
	connect(veiwer, SIGNAL(changedOuterGearType(int)), outerGearMode, SLOT(setValue(int)));
	connect(innerGearSize, SIGNAL(valueChanged(int)), veiwer, SLOT(setInner(int)));
	connect(veiwer, SIGNAL(changedInner(int)), innerGearSize, SLOT(setValue(int)));
	connect(innerGearMode, SIGNAL(valueChanged(int)), veiwer, SLOT(setInnerGearType(int)));
	connect(veiwer, SIGNAL(changedInnerGearType(int)), innerGearMode, SLOT(setValue(int)));
	connect(thirdGearSize, SIGNAL(valueChanged(int)), veiwer, SLOT(setThird(int)));
	connect(veiwer, SIGNAL(changedThird(int)), thirdGearSize, SLOT(setValue(int)));
	connect(thirdGearMode, SIGNAL(valueChanged(int)), veiwer, SLOT(setThirdGearType(int)));
	connect(veiwer, SIGNAL(changedThirdGearType(int)), thirdGearMode, SLOT(setValue(int)));
	connect(offset, SIGNAL(valueChanged(int)), veiwer, SLOT(setOffset(int)));
	connect(veiwer, SIGNAL(changedOffset(int)), offset, SLOT(setValue(int)));
	connect(gearRandomize, SIGNAL(clicked()), veiwer, SLOT(randomGearing()));

	connect(drawButton, SIGNAL(clicked(bool)), veiwer, SLOT(slowDraw(bool)));
	connect(veiwer, SIGNAL(changedSlowDraw(bool)), drawButton, SLOT(setChecked(bool)));
	connect(drawQuickButton, SIGNAL(clicked()), veiwer, SLOT(drawGraph()));
	connect(demoButton,SIGNAL(clicked(bool)), veiwer, SLOT(screansaver(bool)));
	connect(veiwer, SIGNAL(changedScreansaver(bool)), demoButton, SLOT(setChecked(bool)));
	connect(scaleSlider, SIGNAL(valueChanged(int)), veiwer, SLOT(setScale(int)));
	connect(rotDial, SIGNAL(valueChanged(int)), veiwer, SLOT(setRotation(int)));

	connect(veiwer, SIGNAL(changedDrawingEnabled(bool)), drawButton, SLOT(setEnabled(bool)));
	connect(veiwer, SIGNAL(changedDrawingEnabled(bool)), drawQuickButton, SLOT(setEnabled(bool)));
	connect(veiwer, SIGNAL(changedDrawingEnabled(bool)), demoButton, SLOT(setEnabled(bool)));

	connect(veiwer, SIGNAL(changedGearSelectEnabled(bool)), gearBox, SLOT(setEnabled(bool)));
	connect(veiwer, SIGNAL(changedGearSelectEnabled(bool)), loadAction, SLOT(setEnabled(bool)));
	connect(veiwer, SIGNAL(changedGearSelectEnabled(bool)), saveAction, SLOT(setEnabled(bool)));
	connect(veiwer, SIGNAL(changedGearSelectEnabled(bool)), exportAction, SLOT(setEnabled(bool)));

	connect(veiwer, SIGNAL(changedProgress(int)), progBar, SLOT(setValue(int)));
	connect(veiwer, SIGNAL(changedProgressFormat(QString)), this, SLOT(setProgressFormat(QString)));

	connect(resetAction, SIGNAL(triggered()), veiwer, SLOT(RESET()));
	connect(clearAction, SIGNAL(triggered()), veiwer, SLOT(clearGraph()));
	connect(helpAction, SIGNAL(triggered()), veiwer, SLOT(help()));
	connect(loadAction, SIGNAL(triggered()), veiwer, SLOT(loadFile()));
	connect(saveAction, SIGNAL(triggered()), veiwer, SLOT(saveFile()));
	connect(exportAction, SIGNAL(triggered()), veiwer, SLOT(exportFile()));
	connect(stampAction, SIGNAL(triggered()), veiwer, SLOT(stamp()));

	connect(arAction, SIGNAL(triggered()), this, SLOT(arL()));
	connect(bnAction, SIGNAL(triggered()), this, SLOT(bnL()));
	connect(deAction, SIGNAL(triggered()), this, SLOT(deL()));
	connect(esAction, SIGNAL(triggered()), this, SLOT(esL()));
	connect(frAction, SIGNAL(triggered()), this, SLOT(frL()));
	connect(hiAction, SIGNAL(triggered()), this, SLOT(hiL()));
	connect(itAction, SIGNAL(triggered()), this, SLOT(itL()));
	connect(jaAction, SIGNAL(triggered()), this, SLOT(jaL()));
	connect(koAction, SIGNAL(triggered()), this, SLOT(koL()));
	connect(pgAction, SIGNAL(triggered()), this, SLOT(pgL()));
	connect(ptAction, SIGNAL(triggered()), this, SLOT(ptL()));
	connect(ruAction, SIGNAL(triggered()), this, SLOT(ruL()));
	connect(swAction, SIGNAL(triggered()), this, SLOT(swL()));
	connect(zhAction, SIGNAL(triggered()), this, SLOT(zhL()));

	heart = new QTimer();
	connect(heart, SIGNAL(timeout()), veiwer, SLOT(beat()));
	heart->start(1000/60);

#ifdef DEMO
	redSlider->setEnabled(!day || rand() % 3);
	greenSlider->setEnabled(!day || rand() % 3);
	blueSlider->setEnabled(!day || rand() % 3);
	rainbowSlider->setEnabled(!day || rand() % 3);
	colourRandom->setEnabled(!day || rand() % 3);
	colourColourize->setEnabled(!day || rand() % 3);
	outerGearSize->setEnabled(!day || rand() % 3);
	innerGearSize->setEnabled(!day || rand() % 3);
	thirdGearSize->setEnabled(!day || rand() % 3);
	offset->setEnabled(!day || rand() % 3);
	outerGearMode->setEnabled(!day || rand() % 3);
	innerGearMode->setEnabled(!day || rand() % 3);
	thirdGearMode->setEnabled(!day || rand() % 3);
	gearRandomize->setEnabled(!day || rand() % 3);
	//drawButton->setEnabled(!day || rand() % 3);
	//drawQuickButton->setEnabled(!day || rand() % 3);
	scaleSlider->setEnabled(!day || rand() % 3);
	rotDial->setEnabled(!day || rand() % 3);
	stampAction->setEnabled(false);
	saveAction->setEnabled(false);
	exportAction->setEnabled(false);
	resetAction->setEnabled(!day || rand() % 3);
	clearAction->setEnabled(!day || rand() % 3);
	loadAction->setEnabled(false);

#endif

	this->setLayout(mainLayout);
    veiwer->drawGraph();
}

void Window::retranslate(QString locale){
	if(win::translator->load(QString("SwirlyDraw_") + locale)){
		std::cout << locale.toStdString() << "loaded sucessfully\n";
	}else{
		std::cout << "error loading " << locale.toStdString() << "\n";
	}
	win::locale=locale;
	loadAction->setText(tr("&Load"));
	saveAction->setText(tr("&Save"));
	exportAction->setText(tr("E&xport"));
	clearAction->setText(tr("&Clear"));
	resetAction->setText(tr("&RESET"));
	helpAction->setText(tr("&Help Page"));
	stampAction->setText(tr("Stam&p"));
	helpMenu->setTitle(tr("&Help"));
	fileMenu->setTitle(tr("&File"));

	redLabel->setText(tr("Red:"));
	greenLabel->setText(tr("Green:"));
	blueLabel->setText(tr("Blue:"));
	rainbowLabel->setText(tr("Rainbow:"));

	colourRandom->setText(tr("Randomize"));
	colourColourize->setText(tr("Colourize"));

	colourBox->setTitle(tr("Select Colour"));

	gearRandomize->setText(tr("Randomize"));
	gearBox->setTitle(tr("Select Gears"));
	outerLabel->setText(tr("Outer"));
	innerLabel->setText(tr("Inner"));
	thirdLabel->setText(tr("Third"));
	offsetLabel->setText(tr("Offset"));

	engageBox->setTitle(tr("Engage"));
	drawButton->setText(tr("Draw"));
	drawQuickButton->setText(tr("Draw Quickly"));
	demoButton->setText(tr("Demonstration"));
	rotLabel->setText(tr("Rotation:"));
	scaleLabel->setText(tr("Scale:"));

}

QSlider* Window::ColourSlider(){
	QSlider* slider = new QSlider(Qt::Horizontal);
	slider->setTickPosition(QSlider::NoTicks);
	slider->setMinimum(0);
	slider->setMaximum(255);
	slider->setTickInterval(1);
	return slider;

}

QSlider* Window::ModeSlider(int modes){
	QSlider* slider = new QSlider(Qt::Horizontal);
	slider->setTickPosition(QSlider::TicksBelow);
	slider->setMinimum(0);
	slider->setMaximum(modes);
	slider->setTickInterval(1);
	return slider;
}

QSpinBox* Window::GearBox(int def){
	QSpinBox* spinBox = new QSpinBox;
	spinBox->setMinimum(-300);
	spinBox->setMaximum(300);
	spinBox->setSingleStep(1);
	spinBox->setValue(def);
	return spinBox;
}
void Window::setProgressFormat(QString format){
	progBar->setFormat(format);
}

namespace win{
	Window *window;
	QTranslator *translator;
	QApplication *app;
	QString locale;
}

void Window::arL(){retranslate("ar");}
void Window::bnL(){retranslate("bn");}
void Window::deL(){retranslate("de");}
void Window::esL(){retranslate("es");}
void Window::frL(){retranslate("fr");}
void Window::hiL(){retranslate("hi");}
void Window::itL(){retranslate("it");}
void Window::jaL(){retranslate("ja");}
void Window::koL(){retranslate("ko");}
void Window::pgL(){retranslate("en");}
void Window::ptL(){retranslate("pt");}
void Window::ruL(){retranslate("ru");}
void Window::swL(){retranslate("sw");}
void Window::zhL(){retranslate("zh");}
