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
 
#ifndef SUBGRAPH_H
#define SUBGRAPH_H

#include <vector>
#include <iostream>

class subgraph
{
	public:
		subgraph(){scale=1;rotation=0;}
		subgraph(std::vector<float> v, std::vector<float> c, double s, int r){
			vertex_array=v;
			color_array=c;
			scale=s;
			rotation=r;
		}
		std::vector<float> Vertex_Array(){return vertex_array;};
		std::vector<float> Color_Array(){return color_array;};

		double Scale(){return scale;};
		int Rotation(){return rotation;};
	public:
		std::vector<float> vertex_array;
		std::vector<float> color_array;
		double scale;
		int rotation;
};
std::ostream &operator<<(std::ostream &os, subgraph g);
std::istream &operator>>(std::istream &is, subgraph &g);

#endif // SUBGRAPH_H
