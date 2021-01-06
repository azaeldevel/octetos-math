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

#include "../src/algebra.hh"
#include "../src/geometry.hh"

int main()
{
	geometry::Point point;
	
	std::cout << "Type(point) : " << point.getTypeDescribe() << std::endl;

	geometry::Point point0(1.0,1.0);
	geometry::Point point1(3.0,9.2);

	std::cout << "point0.distance(point1) = " << point0.distance(point1) << std::endl;

	//geometry::Point u(1.0,1.0);
	//std::cout << "Normalizada u: " << (std::string)u << "\n";
	//u.normalize();
	//std::cout << "Normalizada u: " << (std::string)u << "\n";
	//std::cout << "Normalizada P1: " << (std::string)point1 << "\n";
	//point1.rotate(u);
	//std::cout << "Rotado P1: " << (std::string)point1 << "\n";

	//geometry::D2::Vector vect1(point0,point1);
	//std::cout << "Vector vect1: " << (std::string)vect1 << "\n";

	
	geometry::Vector vect2(geometry::Point(1.0,5.0));
	std::cout << "vect2" << (std::string)vect2 << "\n";
	geometry::Vector vect3(geometry::Point(-4.0,9.0/10.0));
	std::cout << "vect3" << (std::string)vect3 << "\n";
	std::cout << "vect2 * vect3 = " << vect2 * vect3 << "\n";

	geometry::Vector vect4 = vect2 + vect3;
	std::cout << "vect4 = vect2 + vect3 = " << (std::string)vect4 << "\n";

	geometry::Vector vect5 = vect4 * 5.3;
	std::cout << "vect5 = vect4 * 5.3 = " << (std::string)vect5 << "\n";
	
	
	geometry::Vector vect6 = vect2 - vect3;
	std::cout << "vect6 = vect2 - vect3= " << (std::string)vect6 << "\n";

	
	geometry::Vector vect7 = vect4 / 2.36;
	std::cout << "vect7 = vect4 / 2.36 = " << (std::string)vect7 << "\n";

	geometry::Point point3(1.0,0.0);
	std::cout << "point3" << (std::string)point3 << "\n";
	//point3.rotate(90);
	//std::cout << "point3 = " << (std::string)point3 << "\n";
	
	return 0;
}

