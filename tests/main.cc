
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

#include <CUnit/Basic.h>
#include <iostream>


#include <metry.hh>

using namespace metry;



void testVector()
{
	rect::Vector vect2(1.0,5.0);
	//std::cout << "vect2" << (std::string)vect2 << "\n";
	if(fabs(vect2.getX() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect2.getY() - 5.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	rect::Vector vect3(-4.0,9.0/10.0);
	//std::cout << "vect3" << (std::string)vect3 << "\n";
	if(fabs(vect3.getX() + 4.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect3.getY() - (9.0/10.0)) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	OCTETOS_MATH_DECIMAL ps = vect2 * vect3;
	//std::cout << "vect2 * vect3 = " << ps << "\n";
	if(fabs(ps - 0.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	rect::Vector vect4 = vect2 + vect3;
	//std::cout << "vect4 = vect2 + vect3 = " << (std::string)vect4 << "\n";
	if(fabs(vect4.getX() + 3.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect4.getY() - 5.9) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	rect::Vector vect5 = vect4 * 5.3;
	//std::cout << "vect5 = vect4 * 5.3 = " << (std::string)vect5 << "\n";
	if(fabs(vect5.getX() + 15.9) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect5.getY() - 31.27) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	rect::Vector vect6 = vect2 - vect3;
	//std::cout << "vect6 = vect2 - vect3= " << (std::string)vect6 << "\n";
	if(fabs(vect6.getX() - 5.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect6.getY() - 4.1) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	rect::Vector vect7 = vect4 / 2.36;
	//std::cout << "vect7 = vect4 / 2.36 = " << (std::string)vect7 << "\n";
	if(fabs(vect7.getX() + 1.271186) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect7.getY() - 2.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
		

	rect::Vector vect8 = vect7.orthogonal();
	//std::cout << "vect8" << (std::string)vect8 << "\n";
	if(fabs(vect8.getX() + 2.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect8.getY() + 1.271186) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	rect::Vector vect9(7.0,35.0);
	//std::cout << "vect9" << (std::string)vect9 << "\n";
	bool fpv9 = vect9.isParallel(vect2);
	//if(fpv9) std::cout << "vect9 is paralle t0 vect2\n";
	//else std::cout << "vect9 is not paralle t0 vect2\n";
	if(fpv9)CU_ASSERT(true)
	else CU_ASSERT(false)
	
	rect::Vector vect10(7.0,35.001);
	//std::cout << "vect10" << (std::string)vect10 << "\n";
	bool fpv10 = vect10.isParallel(vect2);
	//if(fpv10) std::cout << "vect10 is paralle to vect2\n";
	//else std::cout << "vect10 is not paralle to vect2\n";
	if(fpv10)CU_ASSERT(false)
	else CU_ASSERT(true)
	
	rect::Vector vect11(2.0,1.0);
	//std::cout << "vect11" << (std::string)vect11 << "\n";
	rect::Vector vect12(-6.0,-3.0);
	//std::cout << "vect12" << (std::string)vect12 << "\n";
	bool fpv12 = vect11.isParallel(vect12);
	//if(fpv12) std::cout << "vect11 is paralle to vect12\n";
	//else std::cout << "vect11 is not paralle to vect12\n";
	if(fpv12) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	rect::Vector vect13(2.0,1.0);
	vect13.normalize();
	//std::cout << "vect13:" << (std::string)vect13 << ", size " << vect13.length() << "\n";
	OCTETOS_MATH_DECIMAL v13l = vect13.length();
	if(fabs(v13l - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	//if(vect8.isOrthogonal(vect7)) std::cout << "vect8 is orthogonal to vect7\n";
	//else std::cout << "vect8 is not orthogonal to vect7\n";
	if(vect8.isOrthogonal(vect7))CU_ASSERT(true)
	else CU_ASSERT(false)

	//if(vect9.isOrthogonal(vect2)) std::cout << "vect9 is orthogonal t0 vect2\n";
	//else std::cout << "vect9 is not orthogonal to vect2\n";
	if(vect9.isOrthogonal(vect2))CU_ASSERT(false)
	else CU_ASSERT(true)

	rect::Vector vect14(2.0,5.0);
	rect::Vector vect15(-1.0,2.0);
	//std::cout << "La componente de vect14 en la direccion de vect15 es "  << vect14.Comp(vect15) << "\n";
	//std::cout << "La proyeccion de vect14 en la direccion de vect15 es "  << (std::string)vect14.Proj(vect15) << "\n";
	OCTETOS_MATH_DECIMAL compa = vect14.Comp(vect15);
	if(fabs(compa - 3.57771) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	//vector::Vector vect16(Point(2.0,5.0),Point(-1.0,2.0));
	//vector::Vector vect17(vect16.orthogonal());
	//OCTETOS_MATH_DECIMAL ps1617 = vect16 * vect17;
	//std::cout << "ps1617 = " << ps1617 << " \n";

	//bool isnull = rect::NullVector.isNull();
	//if(isnull)CU_ASSERT(true)
	//else CU_ASSERT(false)
}

void testPoint()
{
	rect::Point point0(1.0,1.0);
	//std::cout << "point0" << (std::string)point0 << "\n";
	if(fabs(point0.getX() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(fabs(point0.getY() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	rect::Point point1(3.0,9.2);
	//std::cout << "point1" << (std::string)point1 << "\n";
	if(fabs(point1.getX() - 3.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false);	
	if(fabs(point1.getY() - 9.2) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	OCTETOS_MATH_DECIMAL dp0p1 = point0.distance(point1);
	//std::cout << "point0.distance(point1) = " << dp0p1 << std::endl;
	if(fabs(dp0p1 - 8.44038) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	
	rect::Point point3(1.0,0.0);
	//std::cout << "point3" << (std::string)point3 << "\n";
	if(fabs(point3.getX() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(fabs(point3.getY() - 0.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
}

int init(void)
{
	return 0;
}

int clean(void)
{
	return 0;
}



void testDeveloping()
{
	rect::Line line2(rect::Vector(-5.0,8.0),rect::Vector(3.0,0.0));
	//std::cout << "line2" << (std::string)line2 << "\n";
	rect::Line line3(rect::Vector(-2.0,0.0),rect::Vector(1.0,-3.0));
	//std::cout << "line3" << (std::string)line3 << "\n";
	bool l23 = line2.isParallel(line3);
	//if(l23) std::cout << "line2 is paralle to line3\n";
	//else std::cout << "line2 is not paralle to line3\n";
	if(l23)CU_ASSERT(true)
	else CU_ASSERT(false)

	rect::Line line4(rect::Vector(0.0,5.0),rect::Vector(2.0,1.0));
	rect::Vector pl4(2.0,-3.0);
	OCTETOS_MATH_DECIMAL pl4Leng = line4.distance(pl4);
	//std::cout << "line2 : " << (std::string)line4 << "\n";
	//std::cout << "pl4Leng = " << pl4Leng << "\n";
	if(fabs(pl4Leng - 1.78885) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	//Pag 105
	rect::Vector c(7.0,17.0/3.0);
	rect::Vector a(3.0,1.0);
	rect::Vector b(1.0,2.0);
	OCTETOS_MATH_DECIMAL s,t;
	c.combLineal (a,b,s,t);
	//std::cout << "s = " << s << ", t = " << t << "\n";
	if(fabs(t - 2.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(s - (5.0/3.0)) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	rect::Vector vec17(1.0,1.0),vec18(1.0,0.0),vec19(1.5,3.5);
	//std::cout << "vec17 : " << (std::string)vec17 << "\n";
	//std::cout << "vec18 : " << (std::string)vec18 << "\n";
	//std::cout << "vec19 : " << (std::string)vec19 << "\n";
	if(fabs(vec17.getX() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec17.getY() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec18.getX() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec18.getY() - 0.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)	
	if(fabs(vec19.getX() - 1.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec19.getY() - 3.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	vec17.translate(vec18);
	if(fabs(vec17.getX() - 2.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec17.getY() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	vec17.translate (vec19);
	if(fabs(vec17.getX() - 3.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec17.getY() - 4.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	//std::cout << "vec17 : " << (std::string)vec17 << "\n";

	rect::Vector vec20(1.0,1.0), vec21(5.0,0.0);
	if(fabs(fabs(vec20.getX()) - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(fabs(vec20.getY()) - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	bool fv21n = vec20.normalize();
	if(fv21n) CU_ASSERT(true)
	else CU_ASSERT(false)
	bool fv21 = vec20.rotate(vec20);	
	if(fv21) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	rect::Vector vec23(5.0,0.0);
	vec23.rotate(1.5708);
	//std::cout << "vec23 : " << (std::string)vec23 << "\n";
}



int main()
{
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = CU_add_suite("Testing Math..", init, clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite, "Test for Point class", testPoint)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}	
	
	if ((NULL == CU_add_test(pSuite, "Test for Vector class", testVector)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Test for developing", testDeveloping)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
	
	return 0;
}

