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

#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <cstdio>
#include <cstdlib>

namespace fileio{
	extern int xpmsize;
	bool save(std::string);
	bool load(std::string);
	bool exportxpm(std::string);
};

#endif // FILEIO_H
