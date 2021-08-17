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
 
#ifndef COLOR_H
#define COLOR_H

#include <cmath>
class Color{
	public:
		//initilizer
		Color(){SetColor(0.0,0.0,0.0);};
		Color(float r, float g, float b){
			SetColor(r,g,b);
		};

		//set
		void SetColor(float r, float g, float b);
		void SetHue(float h);
		float GetHue(){return atan2(0.866025 * (v[1]-v[2]), v[0]+0.5 * v[1] + 0.5 * v[2]);};
		//accesors
		float* GetNormal(){return vn;};
		float* GetLight1(){return vl1;};
		float* GetLight2(){return vl2;};
		float* GetDark1(){return vd1;};
		float* GetDark2(){return vd2;};
		float* GetColor(){return v;};

		operator float*(){return v;};

		unsigned char R(){return (unsigned char)(v[0] * 255);};
		unsigned char G(){return (unsigned char)(v[1] * 255);};
		unsigned char B(){return (unsigned char)(v[2] * 255);};

	public:

		float v[3];
	private:
		float vd1[3];
		float vd2[3];
		float vl1[3];
		float vl2[3];
		float vn[3];
};

#endif // COLOR_H
