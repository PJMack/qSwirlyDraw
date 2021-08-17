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
 
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <complex>
#include <QColor>

#include "subgraph.h"
#include "color.h"
#define THETA_INC 90
#include "window.h"


namespace graph{
	extern std::vector<float> vertex_array;
	extern std::vector<float> color_array;
	extern bool *drawing;
	extern int rainbowMode;
	///extern unsigned char pixles[];
	extern std::vector<subgraph> subgraph_array;
	///extern int pixel_dim;
	extern Color currentcolor;
	extern double scale;
	extern int rotation;
	extern int innergear;
	extern int outergear;
	extern int offset;
	extern int thirdgear;
	extern const double PI;
	extern double thetamax;
	void CalcThetaMax(void);

	extern double theta;
	extern double theta1;
	extern double theta2;
	extern double theta3;

	std::complex<double> gearStd(double mag, double phase);
	std::complex<double> gearEgg(double mag, double phase);
	std::complex<double> gearPnut(double mag, double phase);
	std::complex<double> gearTri(double mag, double phase);
	std::complex<double> gearSqr(double mag, double phase);

	std::complex<double> Pen(void);
	void advance(double amount);
	std::complex<double> PenDraw(void);
	void ResetGraph(void);
	void CalcGraph(void);
	int lcm(int a, int b);
	int gcd(int a, int b);

	extern std::complex<double> (*innerGear)(double,double);
	extern std::complex<double> (*outerGear)(double,double);
	extern std::complex<double> (*thirdGear)(double,double);
	extern void (*colourOutput)(int r,int g,int b);

	void Stamp(void);
};

#endif // GRAPH_H
