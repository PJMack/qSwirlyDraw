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
 
#include "color.h"

#include <cmath>
void Color::SetColor(float r, float g, float b){
	//set the colors
	v[0]=r; v[1]=g; v[2]=b;

	//calculate current color value for scaling
	float value = v[0];
	value = (value < v[1]) ? v[1] : value;
	value = (value < v[2]) ? v[2] : value;

	//scale normal to 0.80
	float mult = 0.80 / value;
	vn[0] = v[0] * mult;
	vn[1] = v[1] * mult;
	vn[2] = v[2] * mult;

	//scale light 1 to 0.95
	mult = 0.95 / value;
	vl1[0] = v[0] * mult;
	vl1[1] = v[1] * mult;
	vl1[2] = v[2] * mult;

	//scale light 2 to 0.87
	mult = 0.87 / value;
	vl2[0] = v[0] * mult;
	vl2[1] = v[1] * mult;
	vl2[2] = v[2] * mult;

	//scale dark 1 to 0.45
	mult = 0.45 / value;
	vd1[0] = v[0] * mult;
	vd1[1] = v[1] * mult;
	vd1[2] = v[2] * mult;

	//scale dark 2 to 0.53
	mult = 0.53 / value;
	vd2[0] = v[0] * mult;
	vd2[1] = v[1] * mult;
	vd2[2] = v[2] * mult;

}

void Color::SetHue(float h){
	float C=1;
	float Y=0.30 * v[0] + 0.59 * v[1] + 0.11 * v[2];
	float H=fmod(3 * h / 3.14159265359, 6);
	float X=C * (1 - fabs(fmod(H,2)-1));
	float R,G,B;
	if(H < 1){
		R=C; G=X; B=0;
	}else if(H < 2){
		R=X; G=C; B=0;
	}else if(H < 3){
		R=0; G=C; B=X;
	}else if(H < 4){
		R=0; G=X; B=C;
	}else if(H < 5){
		R=X; G=0; B=C;
	}else{
		R=C; G=0; B=X;
	}
	float m = Y - (0.30 * R + 0.59 * G + 0.11 * B);
	v[0]=fmax(0,fmin(R+m,1));
	v[1]=fmax(0,fmin(G+m,1));
	v[2]=fmax(0,fmin(B+m,1));
}
