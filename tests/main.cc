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
	geometry::D2::Point point;
	geometry::D2::Plane plane;
	
	std::cout << "Type(point) : " << point.getTypeDescribe() << std::endl;
	std::cout << "Type(plane) : " << plane.getTypeDescribe() << std::endl;

	geometry::D2::Point point0(1.0,1.0);
	geometry::D2::Point point1(3.0,9.2);

	std::cout << "Distance p0 -> p1 : " << point0.distance(point1) << std::endl;

	geometry::D2::Point u(1.0,1.0);
	std::cout << "Normalizada u: " << (std::string)u << "\n";
	u.normalize();
	std::cout << "Normalizada u: " << (std::string)u << "\n";
	std::cout << "Normalizada P1: " << (std::string)point1 << "\n";
	point1.rotate(u);
	std::cout << "Rotado P1: " << (std::string)point1 << "\n";

	//geometry::D2::Vector vect1(point0,point1);
	//std::cout << "Vector vect1: " << (std::string)vect1 << "\n";

	
	geometry::D2::Vector vect2(geometry::D2::Point(1.0,5.0));
	std::cout << "Vector vect2: " << (std::string)vect2 << "\n";
	geometry::D2::Vector vect3(geometry::D2::Point(-4.0,9.0/10.0));
	std::cout << "Vector vect3: " << (std::string)vect3 << "\n";
	std::cout << "vect2 * vect3 = " << vect2 * vect3 << "\n";

	geometry::D2::Vector vect4 = vect2 + vect3;
	std::cout << "vect4 = " << (std::string)vect4 << "\n";

	geometry::D2::Vector vect5 = vect4 * 5.3;
	std::cout << "vect5 = " << (std::string)vect5 << "\n";
	
	
	geometry::D2::Vector vect6 = vect2 - vect3;
	std::cout << "vect6 = " << (std::string)vect6 << "\n";

	
	geometry::D2::Vector vect7 = vect4 / 2.36;
	std::cout << "vect7 = " << (std::string)vect7 << "\n";
	
	return 0;
}

