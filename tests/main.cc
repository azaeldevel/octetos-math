/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2021 Azael Reyes <azael.devel@gmail.com>
 * 
 * Math is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Math is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>


#include <../src/metry.hh>

using namespace metry;

int main()
{
	Point point;
	
	std::cout << "Type(point) : " << point.getTypeDescribe() << std::endl;

	Point point0(1.0,1.0);
	std::cout << "point0" << (std::string)point0 << "\n";
	Point point1(3.0,9.2);
	std::cout << "point1" << (std::string)point1 << "\n";

	std::cout << "point0.distance(point1) = " << point0.distance(point1) << std::endl;

	Vector vect2(Point(1.0,5.0));
	std::cout << "vect2" << (std::string)vect2 << "\n";
	Vector vect3(Point(-4.0,9.0/10.0));
	std::cout << "vect3" << (std::string)vect3 << "\n";
	std::cout << "vect2 * vect3 = " << vect2 * vect3 << "\n";

	Vector vect4 = vect2 + vect3;
	std::cout << "vect4 = vect2 + vect3 = " << (std::string)vect4 << "\n";

	Vector vect5 = vect4 * 5.3;
	std::cout << "vect5 = vect4 * 5.3 = " << (std::string)vect5 << "\n";
	
	
	Vector vect6 = vect2 - vect3;
	std::cout << "vect6 = vect2 - vect3= " << (std::string)vect6 << "\n";

	
	Vector vect7 = vect4 / 2.36;
	std::cout << "vect7 = vect4 / 2.36 = " << (std::string)vect7 << "\n";

	Point point3(1.0,0.0);
	std::cout << "point3" << (std::string)point3 << "\n";

	Vector vect8 = vect7.orthogonal();
	std::cout << "vect8" << (std::string)vect8 << "\n";

	Vector vect9(Point(7.0,35.0));
	std::cout << "vect9" << (std::string)vect9 << "\n";
	bool fpv9 = vect9.isParallel(vect2);
	if(fpv9) std::cout << "vect9 is paralle t0 vect2\n";
	else std::cout << "vect9 is not paralle t0 vect2\n";

	
	Vector vect10(Point(7.0,35.001));
	std::cout << "vect10" << (std::string)vect10 << "\n";
	bool fpv10 = vect10.isParallel(vect2);
	if(fpv10) std::cout << "vect10 is paralle t0 vect2\n";
	else std::cout << "vect10 is not paralle t0 vect2\n";
	
	return 0;
}

