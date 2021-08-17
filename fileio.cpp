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
#include "graph.h"
#include "fileio.h"
#include <string>
#include <iostream>
#include <complex>
#include <algorithm>
#include "glwidget.h"

namespace fileio {
	bool savexpm=false;
	int xpmsize=2047;
	int xpmcenter=1024;

	bool save(std::string name){
#ifdef DEMO
		if(graph::vertex_array.size() >= 500){
			win::window->progBar->setFormat(GLWidget::tr("File Error"));
			return false;
		}
#endif

		win::window->progBar->setFormat(GLWidget::tr("Saving File (Please Wait)"));
		FILE * f;
		f = fopen(name.c_str(), "w");
		if(!f){
			win::window->progBar->setFormat(GLWidget::tr("File Error"));
			return false;
		};
		if(graph::vertex_array.empty() || graph::vertex_array.empty()){
			fprintf(f, "X\n");
		}else{
			fprintf(f,"%f\n", graph::scale);
			fprintf(f,"%i\n[\n", graph::rotation);
			for(unsigned int i = 0; i < graph::vertex_array.size(); i++){
				fprintf(f,"%e\n", graph::vertex_array[i]);
			}
			fprintf(f, "]\n[\n");
			for(unsigned int i = 0; i < graph::color_array.size(); i++){
				fprintf(f,"%f\n", graph::color_array[i]);
			}
			fprintf(f, "]\n");
		}
		if(graph::subgraph_array.empty()){
			fprintf(f, "X\n");
		}else{
			for(unsigned int i = 0; i < graph::subgraph_array.size(); i++){
				fprintf(f, "%f\n", graph::subgraph_array[i].Scale());
				fprintf(f, "%i\n[\n", graph::subgraph_array[i].Rotation());
				for(unsigned int j = 0; j < graph::subgraph_array[i].vertex_array.size(); j++){
					fprintf(f,"%e\n", graph::subgraph_array[i].vertex_array[j]);
				}
				fprintf(f, "]\n[\n");
				for(unsigned int j = 0; j < graph::subgraph_array[i].color_array.size(); j++){
					fprintf(f,"%e\n", graph::subgraph_array[i].color_array[j]);
				}
				fprintf(f, "]\n");
			}
		}
		fclose(f);
		win::window->progBar->setFormat(GLWidget::tr("File Saved Successfully"));
		return true;
	};

	const unsigned int FL = 64;
	bool load(std::string name){
		graph::ResetGraph();
		graph::subgraph_array.clear();
		win::window->progBar->setFormat(GLWidget::tr("Loading File (Please Wait)"));
		if(name[name.size()-1]=='\n'){name.erase(name.size()-1);};
		FILE * f;
		f=fopen(name.c_str(), "r");
		if(!f){
			win::window->progBar->setFormat(GLWidget::tr("File Error"));
			std::cout << "could not open file\n";
			return false;
		};
		char line[FL];
		float temp;
		fgets(line, FL, f);
		if(!(line[0]=='X')){
			sscanf(line, "%f", &temp);
			graph::scale=temp;
			fgets(line, FL, f);
			sscanf(line, "%i", &graph::rotation);
			fgets(line, FL, f); //get [
			fgets(line, FL, f); //get first number
			do{
				sscanf(line, "%e", &temp);
				graph::vertex_array.push_back(temp);
				fgets(line, FL, f);
			}while(line[0] != ']' );
			fgets(line, FL, f); //get [
			fgets(line, FL, f); //get first number
			do{
				sscanf(line, "%f", &temp);
				graph::color_array.push_back(temp);
				fgets(line, FL, f);
			}while(line[0] != ']');
		}
		fgets(line, FL, f);
		if(!(line[0]=='X')){
			do{
				subgraph s;
				sscanf(line, "%f", &temp);
				s.scale=temp;
				fgets(line, FL, f);
				sscanf(line, "%i", &(s.rotation));
				fgets(line, FL, f); //get [
				fgets(line, FL, f); //get first number
				do{
					sscanf(line, "%e", &temp);
					s.vertex_array.push_back(temp);
					fgets(line, FL, f);
				}while(line[0] != ']' );
				fgets(line, FL, f); //get [
				fgets(line, FL, f); //get first number
				do{
					sscanf(line, "%f", &temp);
					s.color_array.push_back(temp);
					fgets(line, FL, f);
				}while(line[0] != ']');
				graph::subgraph_array.push_back(s);
			}while(fgets(line, FL, f));
		}

		fclose(f);
		win::window->progBar->setFormat(GLWidget::tr("File Loaded Successfully"));
		return true;
	};

	QImage pixmap(xpmsize, xpmsize, QImage::Format_ARGB32);

	void setpix(int x, int y, unsigned int c){
		/**if(pixmap.empty()){
			std::cout << "Error: pixmap empty\n";
			return;
		};*/

		x+=xpmcenter;
		y+=xpmcenter;
		if(x >= 0 && y >= 0 && x < xpmsize && y < xpmsize){
			pixmap.setPixel(x,y,c);
		}else{
			std::cout << "Error: pixle out of range\n";
		}
	}

	int sign(int x){
		if(x<0) return -1;
		if(x>0) return 1;
		return 0;
	}
	void drawline(int x1, int y1, int x2, int y2, unsigned int c){
		if(x1 == x2 && y1 == y2){
			setpix(x2,y2,c);
			return;
		}
		int x, y;
		if(abs(x2-x1) > abs(y2 - y1)){
			for(int i = 0; i < abs(x2-x1); i++){
				x=x1+(i* sign(x2-x1));
				y=y1+(int)round(((double)(i * sign(x2-x1) * (y2-y1))) / ((double)(x2-x1)));
				setpix(x, y, c);
			}
		}else{
			for(int i = 0; i < abs(y2-y1); i++){
				y=y1+(i* sign(y2-y1));
				x=x1+(int)round(((double)(i * sign(y2-y1) * (x2-x1))) / ((double)(y2-y1)));
				setpix(x, y, c);
			}
		}
	}

	int getColorCode(float r, float g, float b){
		unsigned int R=(unsigned int)(r * 255.0);
		unsigned int G=(unsigned int)(g * 255.0);
		unsigned int B=(unsigned int)(b * 255.0);
		return 0xFF000000 + R * 0x10000 + G * 0x100 + B * 0x1;
	}

	const std::string xpmchartable = "!@#$%&*()-_=+[]{};:<>/?|1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

	unsigned int charpercode=4;

	std::string getxpmcode(int val){
		std::string ret;
		for(unsigned int i = 0; i < charpercode; i++){
			ret+=xpmchartable[val % xpmchartable.size()];
			val /= xpmchartable.size();
		}
		return ret;
	}

	unsigned int binsearch(int val, std::vector<int> &v, unsigned int first, unsigned int last){
		if(val == v[first]) return first;
		if(val == v[last]) return last;
		unsigned int center = (first+last) / 2;
		if(val < v[center]) return binsearch(val, v, first, center);
		if(val > v[center]) return binsearch(val, v, center, last);
		if(val == v[center]) return center;
		std::cout << "Error: binsearch\n";
		return 0;
	}

	bool exportxpm(std::string name){
#ifdef DEMO
		if(graph::vertex_array.size() >= 500){
			win::window->progBar->setFormat(GLWidget::tr("File Error"));
			return false;
		}
#endif
		/** //open file
		std::cout << "opening file to export\n";
		FILE *fp = fopen(name.c_str(), "w");
		if(!fp){
			win::window->progBar->setFormat(GLWidget::tr("File Error"));
			return false;
		}*/
		//prepair subgraphs
		std::cout << "prepairing subgraphs\n";
		graph::Stamp();
		if(graph::subgraph_array.empty()) return false;
		//initalize bitmap
		win::window->progBar->setValue(0);
		win::window->progBar->setFormat(GLWidget::tr("Initializing Pixmap"));
		std::cout << "initilizing pixmap\n";
		/** pixmap.resize(xpmsize*xpmsize);
		for(unsigned int i = 0; i < pixmap.size(); i++){
			///win::window->progBar->setValue(i * 256 / pixmap.size());
			pixmap[i]=-1;
		}*/
		pixmap.fill(QColor(255,255,255,0));
		//find the full scale of graphs
		win::window->progBar->setValue(64);
		win::window->progBar->setFormat(GLWidget::tr("Prescaling Graph"));
		std::cout << "prescaling graph\n";
		float fullradius=0;
		float mag;
		for(unsigned int i = 0; i < graph::subgraph_array.size(); i++){
			for(unsigned int j = 0; j < graph::subgraph_array[i].vertex_array.size(); j++){
				mag=graph::subgraph_array[i].Scale() * graph::subgraph_array[i].vertex_array[j];
				if(mag > fullradius) fullradius = mag;
			}
		}
		//transform graphs into the pixmap
		win::window->progBar->setValue(128);
		win::window->progBar->setFormat(GLWidget::tr("Generating Pixmaps"));
		std::cout << "writing graph to pixmap\n";

		std::complex<float>  xy1, xy2;
		for(unsigned int i = graph::subgraph_array.size() - 1; i < graph::subgraph_array.size(); i--){
			std::cout << "   subgraph " << i << "\n";
			std::complex<float> mult = std::polar((float)(xpmsize * graph::subgraph_array[i].scale / (2.2 * fullradius)), (float)(graph::subgraph_array[i].rotation * graph::PI / 180.0));
			for(unsigned int j = 0; j < (graph::subgraph_array[i].vertex_array.size() / 2) - 1; j++){
				xy1=mult * std::complex<float>(graph::subgraph_array[i].vertex_array[2 * j],
										graph::subgraph_array[i].vertex_array[2 * j + 1]);
				xy2=mult * std::complex<float>((graph::subgraph_array[i].vertex_array[2 * j + 2]),
										graph::subgraph_array[i].vertex_array[2 * j + 3]);
				drawline((int)xy1.real(), (int) xy1.imag(), (int) xy2.real(), (int) xy2.imag(),
							getColorCode(	graph::subgraph_array[i].color_array[3 * j],
											graph::subgraph_array[i].color_array[3 * j + 1],
											graph::subgraph_array[i].color_array[3 * j + 2]));
			}
		}
		win::window->progBar->setValue(192);
		win::window->progBar->setFormat(GLWidget::tr("Writing File"));

		if(pixmap.save(QString(name.c_str()))){
			win::window->progBar->setValue(256);
			win::window->progBar->setFormat(GLWidget::tr("Export Successful"));
		}else{
			win::window->progBar->setFormat(GLWidget::tr("File Error"));
		}

		//clean up
		graph::subgraph_array.pop_back();

		return true;
	};
}
