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

#include "subgraph.h"

#include <climits>
#include <iostream>

std::ostream &operator<<(std::ostream &os, subgraph g){
	os << g.scale << '\n';
	os << g.rotation << '\n';
	os << "[\n";
	for(unsigned int i = 0; i < g.vertex_array.size(); i++){
		os << g.vertex_array[i] << '\n';
	}
	os << "]\n[\n";
	for(unsigned int i = 0; i < g.color_array.size(); i++){
		os << g.color_array[i] << '\n';
	}
	os << "]\n";
	return os;
};

std::istream &operator>>(std::istream &is, subgraph &g){
	std::cout << "reading stream\n";
	is >> g.scale >> g.rotation;
	is.ignore(INT_MAX,'[');
	g.vertex_array.clear();
	g.color_array.clear();
	float temp;
	do{
		is >> temp;
		g.vertex_array.push_back(temp);
	}while(is.peek() != ']');
	is.ignore(INT_MAX,'[');
	do{
		is >> temp;
		g.color_array.push_back(temp);
	}while(is.peek() != ']');
	is.ignore(INT_MAX, '\n');
	std::cout << "stream read\n";
	return is;
};

