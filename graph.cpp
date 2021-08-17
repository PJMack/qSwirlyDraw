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
 

///#include <GL/glut.h>
#include "graph.h"
#include "cmath"
#include <iostream>
#include "subgraph.h"
///#include "buttonfunctions.h"
#include "color.h"
#include "glwidget.h"

namespace graph{
	//large data arrays
	std::vector<float> vertex_array;
	std::vector<float> color_array;


	void (*colourOutput)(int r,int g,int b);
	std::vector<subgraph> subgraph_array;

	bool *drawing;
	int rainbowMode = 0;

	//current color
	Color currentcolor(0.0,0.0,0.0);

	//gear ratios
	int innergear=50;
	int outergear=30;
	int offset=5;
	int thirdgear=15;

	double scale=1;
	int rotation=0;
	//pi
	const double PI=atan2(0,-1);

	//gear positions
	double theta=0;
	double theta1=0;
	double theta2=0;
	double theta3=0;

	double thetamax;

	void ResetGraph(){
			theta=0;
			theta1=0;
			theta2=0;
			theta3=0;
			vertex_array.clear();
			color_array.clear();
	}

	void CalcThetaMax(void){
		int LCM=lcm(innergear,lcm(thirdgear, outergear));
		///if(LCM<=1){ui::setstatus(STATUS_RPRIME);};
		thetamax=abs(2 * PI * LCM / outergear);

	}

	//calculate whole graph
	void CalcGraph(void){
		CalcThetaMax();
		int t = THETA_INC * thetamax;

		try{
			vertex_array.clear();
			vertex_array.reserve(2*t);
			color_array.clear();
			color_array.reserve(3*t);
		}catch(std::exception& ex){
			///ui::setstatus(STATUS_MEMORY);
			std::cout << "Error: " << ex.what() << '\n';
			return;
		}
		double lt=clock();
		for(int i = 0; i < t; i++){
			advance(2 * PI / THETA_INC);
			PenDraw();
			win::window->progBar->setValue(std::max(theta * 256 / thetamax, (clock() - lt) * 64  / CLOCKS_PER_SEC));
			if((clock() - lt) / CLOCKS_PER_SEC > 4){
				//ui::setstatus(STATUS_TOOLONG);
				std::cout << "Graph Calculations cut short\n";
				break;
			}
		}
	}

	int lcm(int a, int b){
		if(a==0){return b;};
		if(b==0){return a;};
		a=std::abs(a);
		b=std::abs(b);
		int lcmab=(a * b) / gcd(a,b);
		std::cout << "lcm(" << a << ',' << b << ") = " << lcmab << "\n";
		return (a * b) / gcd(a,b);
	}

	int gcd(int a, int b){
		a=std::abs(a);
		b=std::abs(b);
		std::cout << "gcd(" << a << "," << b << ") = ";
		if(a == b){
			std::cout << a << "\n";
			return a;
		};
		int d;
		if(a > b){
			d = a;
			a = b;
			b = d;
		}
		for(;;){
			d=b%a;
			if(d==0) break;
			b=a;
			a=d;
		}
		std::cout << a << "\n";
		return a;
	}


	//gearing functions
	std::complex<double> PenDraw(void){
		std::complex<double> point=Pen();
		vertex_array.push_back(point.real());
		vertex_array.push_back(point.imag());


		if(rainbowMode){
			switch (rainbowMode){
				case 2:
					currentcolor.SetHue(theta2);
					break;
				case 3:
					currentcolor.SetHue(theta3);
					break;
				case 4:
					currentcolor.SetHue(50 * scale * abs(point));
					break;
				case 1:
				default:
				currentcolor.SetHue(theta);
			}
			if(*drawing){
				win::window->veiwer->setColour(currentcolor.R(),currentcolor.G(),currentcolor.B());
			}
		}

		color_array.push_back(currentcolor.GetColor()[0]);
		color_array.push_back(currentcolor.GetColor()[1]);
		color_array.push_back(currentcolor.GetColor()[2]);
		return point;
	}

	void advance(double amount){
		theta+=amount;
		theta1=fmod(theta, 2 * PI);
		theta2=fmod(theta * (double)outergear / (double)innergear, 2 * PI);
		if(thirdgear){theta3=fmod(theta * (double)outergear / (double)thirdgear, 2 * PI);} else {theta3=0;}
	};

	std::complex<double> Pen(void){
		std::complex<double> point(0,0);
		point+=(*innerGear)(innergear,theta1);
		point-=(*outerGear)(outergear,theta1);
		point+=(*outerGear)(outergear-offset,theta2);
		point-=(*thirdGear)(thirdgear,theta2);
		point+=std::polar((double)thirdgear,theta3);
		return point;
	};

	//gear functions
	std::complex<double> (*innerGear)(double,double) = gearStd;
	std::complex<double> (*outerGear)(double,double) = gearStd;
	std::complex<double> (*thirdGear)(double,double) = gearStd;

	//geartypefunctions
	std::complex<double> gearStd(double mag, double phase){
		return std::polar(mag,phase);
	};

	std::complex<double> gearEgg(double mag, double phase){
		mag*=0.75+0.25*sin(phase);
		return std::polar(mag,phase);
	};

	std::complex<double> gearPnut(double mag, double phase){
		mag*=0.75+0.25*sin(2*phase-PI/2);
		return std::polar(mag,phase);
	};

	std::complex<double> gearTri(double mag, double phase){
		mag*=0.75+0.25*sin(3*phase);
		return std::polar(mag,phase);
	};

	std::complex<double> gearSqr(double mag, double phase){
		mag*=0.75+0.25*sin(4*phase-PI/2);
		return std::polar(mag,phase);
	};

	void Stamp(void){
			try{
				if(graph::vertex_array.empty() || graph::color_array.empty()){return;};
				subgraph s(graph::vertex_array, graph::color_array, graph::scale, graph::rotation);
				graph::subgraph_array.push_back(s);
			}catch(std::exception &ex){
				///ui::setstatus(STATUS_MEMORY);
				win::window->progBar->setFormat(GLWidget::tr("Memory Error"));
				std::cout << "Error: " << ex.what() << '\n';
			}
		}
};
