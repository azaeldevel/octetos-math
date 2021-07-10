
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
#include <math.h>
#include <typeinfo>
#include <metry.hh>

#include <Intervals.hh>
#include "../src/funcs.hh"
#include "../src/funcs-ext.hh"
#include "../src/Prime.hh"
#include "../src/statics.hh"
#include "../src/matrix.hh"


void testVector()
{
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//Contructores
	oct::math::Vector<double> vect2(1.0,5.0);
	//std::cout << "vect2" << (std::string)vect2 << "\n";
	if(fabs(vect2.getX() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect2.getY() - 5.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	oct::math::Vector<double> vect3(-4.0,9.0/10.0);
	//std::cout << "vect3" << (std::string)vect3 << "\n";
	if(fabs(vect3.getX() + 4.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect3.getY() - (9.0/10.0)) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::Vector<double> vec17(1.0,1.0),vec18(1.0,0.0),vec19(1.5,3.5);
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

	//std::cout << "vec18 : " << (std::string)vec18 << "\n";
	//std::cout << "vec17 : " << (std::string)vec17 << "\n";
	vec17.translate(vec18);
	//std::cout << "vec17 : " << (std::string)vec17 << "\n";
	if(fabs(vec17.getX() - 2.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec17.getY() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	vec17.translate (vec19);
	//std::cout << "vec17 : " << (std::string)vec17 << "\n";
	if(fabs(vec17.getX() - 3.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec17.getY() - 4.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	//std::cout << "vec17 : " << (std::string)vec17 << "\n";
		
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//operaciones

	OCTETOS_MATH_DECIMAL ps = vect2 * vect3;
	//std::cout << "vect2 * vect3 = " << ps << "\n";
	if(fabs(ps - 0.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::Vector<double> vect4 = vect2 + vect3;
	//std::cout << "vect4 = vect2 + vect3 = " << (std::string)vect4 << "\n";
	if(fabs(vect4.getX() + 3.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect4.getY() - 5.9) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::Vector<double> vect5 = vect4 * 5.3;
	//std::cout << "vect5 = vect4 * 5.3 = " << (std::string)vect5 << "\n";
	if(fabs(vect5.getX() + 15.9) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect5.getY() - 31.27) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	oct::math::Vector<double> vect6 = vect2 - vect3;
	//std::cout << "vect6 = vect2 - vect3= " << (std::string)vect6 << "\n";
	if(fabs(vect6.getX() - 5.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect6.getY() - 4.1) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	oct::math::Vector<double> vect7 = vect4 / 2.36;
	//std::cout << "vect7 = vect4 / 2.36 = " << (std::string)vect7 << "\n";
	if(fabs(vect7.getX() + 1.271186) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect7.getY() - 2.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	oct::math::Vector<double> vect8 = vect7.orthogonal();
	//std::cout << "vect8" << (std::string)vect8 << "\n";
	if(fabs(vect8.getX() + 2.5) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vect8.getY() + 1.271186) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::Vector<double> vect9(7.0,35.0);
	//std::cout << "vect9" << (std::string)vect9 << "\n";
	bool fpv9 = vect9.isParallel(vect2);
	//if(fpv9) std::cout << "vect9 is paralle t0 vect2\n";
	//else std::cout << "vect9 is not paralle t0 vect2\n";
	if(fpv9)CU_ASSERT(true)
	else CU_ASSERT(false)
	
	oct::math::Vector<double> vect10(7.0,35.001);
	//std::cout << "vect10" << (std::string)vect10 << "\n";
	bool fpv10 = vect10.isParallel(vect2);
	//if(fpv10) std::cout << "vect10 is paralle to vect2\n";
	//else std::cout << "vect10 is not paralle to vect2\n";
	if(fpv10)CU_ASSERT(false)
	else CU_ASSERT(true)
	
	oct::math::Vector<double> vect11(2.0,1.0);
	//std::cout << "vect11" << (std::string)vect11 << "\n";
	oct::math::Vector<double> vect12(-6.0,-3.0);
	//std::cout << "vect12" << (std::string)vect12 << "\n";
	bool fpv12 = vect11.isParallel(vect12);
	//if(fpv12) std::cout << "vect11 is paralle to vect12\n";
	//else std::cout << "vect11 is not paralle to vect12\n";
	if(fpv12) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	oct::math::Vector<double> vect13(2.0,1.0);
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

	oct::math::Vector<double> vect14(2.0,5.0);
	oct::math::Vector<double> vect15(-1.0,2.0);
	//std::cout << "La componente de vect14 en la direccion de vect15 es "  << vect14.Comp(vect15) << "\n";
	//std::cout << "La proyeccion de vect14 en la direccion de vect15 es "  << (std::string)vect14.Proj(vect15) << "\n";
	OCTETOS_MATH_DECIMAL compa = vect14.Comp(vect15);
	if(fabs(compa - 3.57771) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::Vector<double> vec20(1.0,1.0), vec21(5.0,0.0);
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
	
	oct::math::Vector<double> vec23(5.0,0.0);
	vec23.rotate(1.5708);//rota 90 grados
	//std::cout << "vec23 : " << (std::string)vec23 << "\n";
	if(fabs(vec23.getX()) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec23.getY()) - 5.0) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::Vector<double> vec24(2.0,1.0);
	oct::math::Vector<double> vec25(1.0,2.0);
	OCTETOS_MATH_DECIMAL valcos = vec24.cos(vec25);
	if(fabs(valcos - (4.0/5.0)) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	OCTETOS_MATH_DECIMAL valsen = vec24.sen(vec25);
	if(fabs(valsen - (3.0/5.0)) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	OCTETOS_MATH_DECIMAL valtan = vec24.tan(vec25);
	if(fabs(valtan - (3.0/4.0)) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	//comprobar que vec28 es el vetor unitario para rotar vec26 hacia vec27
	oct::math::Vector<double> vec26(1.0,2.0);
	oct::math::Vector<double> vec27(-3.0,1.0);
	oct::math::Vector<double> vec28 = vec26.rotateCreate(vec27);
	//std::cout << "vec28 : " << (std::string)vec28 << "\n";
	OCTETOS_MATH_DECIMAL vec28Leng = vec28.length ();
	if(fabs(vec28.getX() + (1.0/sqrt(50))) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec28.getY() - (7.0/sqrt(50))) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec28Leng - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	//comprobar que el vector unitario vec28 rota vec29 correctamente.
	oct::math::Vector<double> vec29(1.0,2.0);
	vec29.rotate(vec28);
	//std::cout << "vec29 : " << (std::string)vec29 << "\n";
	if(fabs(vec29.getX() + (3.0/sqrt(2))) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(vec29.getY() - (1.0/sqrt(2))) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	//Pag 105
	oct::math::Vector<double> c(7.0,17.0/3.0);
	oct::math::Vector<double> a(3.0,1.0);
	oct::math::Vector<double> b(1.0,2.0);
	OCTETOS_MATH_DECIMAL s,t;
	c.combLineal (a,b,s,t);
	//std::cout << "s = " << s << ", t = " << t << "\n";
	if(fabs(t - 2.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	if(fabs(s - (5.0/3.0)) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
}

void testPoint()
{
	oct::math::Point<double> point0(1.0,1.0);
	//std::cout << "point0" << (std::string)point0 << "\n";
	if(fabs(point0.getX() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(fabs(point0.getY() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	oct::math::Point<double> point1(3.0,9.2);
	//std::cout << "point1" << (std::string)point1 << "\n";
	if(fabs(point1.getX() - 3.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false);	
	if(fabs(point1.getY() - 9.2) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
			
	OCTETOS_MATH_DECIMAL dp0p1 = point0.distance(point1);
	//std::cout << "point0.distance(point1) = " << dp0p1 << std::endl;
	if(fabs(dp0p1 - 8.44038) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	oct::math::Point<double> point3(1.0,0.0);
	//std::cout << "point3" << (std::string)point3 << "\n";
	if(fabs(point3.getX() - 1.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(fabs(point3.getY() - 0.0) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	//Integer
	oct::math::Point<int> point4(2,3);
	//std::cout << "point4" << (std::string)point4 << "\n";
	if(point4.getX() == 2) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(point4.getY() == 3) CU_ASSERT(true)
	else CU_ASSERT(false)

	
	oct::math::Point<int> point5(9,11);
	//std::cout << "point5" << (std::string)point5 << "\n";
	if(point5.getX() == 9) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(point5.getY() == 11) CU_ASSERT(true)
	else CU_ASSERT(false)

	//oct::math::Point<double> point6;
	//point6.setX(10);
		
	//oct::math::Point<double> point7;
	//point7.set(0,10);

	oct::math::Point<float> point8(5.3,2.9);
	if(fabs(point8.getX() - 5.3) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(fabs(point8.getY() - 2.9) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::Point<float> point9(10.3,9.3);
	if(fabs(point9.getX() - 10.3) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(fabs(point9.getY() - 9.3) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	OCTETOS_MATH_DECIMAL dp8p9 = point8.distance(point9);
	//std::cout << "point8.distance(point9) = " << dp8p9 << std::endl;
	if(fabs(dp8p9 - 8.121576202) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::Point<int> point10(20,14);
	if(point10.getX() == 20) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(point10.getY() == 14) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::Point<int> point11(53,15);
	if(point11.getX() == 53) CU_ASSERT(true)
	else CU_ASSERT(false);
	if(point11.getY() == 15) CU_ASSERT(true)
	else CU_ASSERT(false)
	OCTETOS_MATH_DECIMAL dp10p11 = point10.distance(point11);
	//std::cout << "point10.distance(point11) = " << dp10p11 << std::endl;
	if(fabs(dp10p11 - 33.015148038) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	oct::math::Point<double> point13(3.0,9.2);
	if(point1 == point13) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	oct::math::Point<int> point12(20,14);
	if(point10 == point12) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	oct::math::Point<float> point14(5.3,2.9);
	if(point8 == point14) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	oct::math::Point<long> point15(20,14);
	oct::math::Point<long> point16(20,14);
	if(point15 == point16) CU_ASSERT(true)
	else CU_ASSERT(false)
}

void testLines()
{
	oct::math::Line<double> line2(oct::math::Vector<double>(-5.0,8.0),oct::math::Vector<double>(3.0,0.0));
	//std::cout << "line2" << (std::string)line2 << "\n";
	oct::math::Line<double> line3(oct::math::Vector<double>(-2.0,0.0),oct::math::Vector<double>(1.0,-3.0));
	//std::cout << "line3" << (std::string)line3 << "\n";
	bool l23 = line2.isParallel(line3);
	//if(l23) std::cout << "line2 is paralle to line3\n";
	//else std::cout << "line2 is not paralle to line3\n";
	if(l23)CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::Line<double> line4(oct::math::Vector<double>(0.0,5.0),oct::math::Vector<double>(2.0,1.0));
	oct::math::Vector<double> pl4(2.0,-3.0);
	OCTETOS_MATH_DECIMAL pl4Leng = line4.distance(pl4);
	//std::cout << "line4 : " << (std::string)line4 << "\n";
	//std::cout << "pl4Leng = " << pl4Leng << "\n";
	if(fabs(pl4Leng - 1.788828764) < OCTETOS_MATH_EPSILON) CU_ASSERT(true)
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
	//point : 10
	//vector : 29
	//line : 6

	oct::math::Point<double> point8(3.0,0.0);
	oct::math::Point<double> point9(-3.0,0.0);
	oct::math::Positives<double> P;
	//math::Naturals<double> N;
	if(P.check(point8.getX())) CU_ASSERT(true)
	else CU_ASSERT(false)		
	if(P.check(point9.getX())) CU_ASSERT(false)
	else CU_ASSERT(true)
		
	oct::math::funcs::C<double> FC1(10.0);
	double FC1_v1 = FC1(5.0);
	if(fabs(FC1_v1 - 10.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::funcs::C<double>& DFC1 = FC1.D();
	double DFC1_v1 = DFC1(5.0);
	if(DFC1_v1 < oct::math::epsilon) CU_ASSERT(true)//la derivada de una constante es 0
	else CU_ASSERT(false)
	
	oct::math::funcs::I<double> FI1(P);
	double FI1_v1 = FI1(5.0);
	if(fabs(FI1_v1 - 5.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::funcs::C<double>& DFI1 = FI1.D();
	double DFI1_v1 = DFI1(5.0);
	if(fabs(DFI1_v1 - 1.0) < oct::math::epsilon) CU_ASSERT(true)//la derivada de una constante es 0
	else CU_ASSERT(false)
	
	
	oct::math::funcs::Parameters<double> N2(1.0,20.0,1.0);
	oct::math::funcs::I<double> FI2(P);
	oct::math::funcs::C<double> FC2(P,2.0);
	oct::math::funcs::Sum<double> FSum1(FI2,FC2);
	double FSum1_y3 = FSum1(3);
	if(FSum1_y3 - 5.0 < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	//std::cout << "FSum1(" << 3 << ") = " << FSum1(3) << "\n";
	
	std::map<double,double> coorF;
	coorF.insert(std::pair<double, double>(1.0, 3.0));
	coorF.insert(std::pair<double, double>(2.0, 4.0));
	coorF.insert(std::pair<double, double>(3.0, 5.0));
	coorF.insert(std::pair<double, double>(4.0, 6.0));
	std::map<double,double> coorG;
	coorG.insert(std::pair<double, double>(0.0, -3.0));
	coorG.insert(std::pair<double, double>(3.0, 2.0));
	coorG.insert(std::pair<double, double>(4.0, 1.0));
	oct::math::funcs::List<double> FCOOF(coorF);
	oct::math::funcs::List<double> FCOOG(coorG);
	oct::math::funcs::Composition<double> FCOMP1(FCOOF,FCOOG);
	double FCOMP1_x = 3.0;
	double FCOMP1_y = FCOMP1(FCOMP1_x);
	if(FCOMP1_y - 4.0 < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	//std::cout << "FCOMP1(" << 4.0 << "," << << ") = "  << "\n";

	oct::math::funcs::I<double> FI3(P);
	std::list<oct::math::Point<double>> pairs1;
	oct::math::funcs::Parabolic<double> parabo1(FI3);
	double parabo1_val1 = parabo1(2.0);
	//std::cout << "parabo1_val1 " << parabo1_val1 << "\n";
	if(fabs(parabo1_val1 - 4.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::funcs::SecantLine<double> secL1(parabo1,10,pairs1,2);
	double secL1_val = secL1(1);
	//std::cout << "secL1_val " << secL1_val << "\n";
	if(fabs(secL1_val - 19.9824) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	for(auto p : pairs1)
	{
		//std::cout << "P" << (std::string)p << "\n";
	}
	
	std::list<oct::math::Point<double>> pairs2;
	oct::math::funcs::SecantLine<double> secL2(parabo1,10,pairs2,3);
	double secL1_val2 =secL2(1);
	if(secL1_val2 - 20.0 < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	for(auto p : pairs2)
	{
		//std::cout << "P" << (std::string)p << "\n";
	}
	
	/*std::list<math::Point<double>> pairs3;
	math::funcs::ExerciesSecante<double> exercies(0,pairs3,2);
	double secsen_val1 = exercies.secsen(0.5);
	if(secsen_val1 - 1.0 < math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	for(auto p : pairs3)
	{
		//std::cout << "P" << (std::string)p << "\n";
	}*/
	
	//suma
	oct::math::funcs::Sum<double> sum1(FI3,FI3);
	double sum1_v1 = sum1(6.0);
	//std::cout << "sum1_v1 : " << sum1_v1 << "\n";
	if(fabs(sum1_v1 - 12.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::Equation<double>& sum1_D1 = sum1.D();
	double Dsum1_v1 = sum1_D1(6.0);
	if(fabs(Dsum1_v1 - 2.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	//minus
	oct::math::funcs::Minus<double> min1(FI3,FI3);
	double min1_v1 = min1(6.0);
	//std::cout << "min1_v1 : " << min1_v1 << "\n";
	if(min1_v1 < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::funcs::Minus<double>& min1_D1 = min1.D();
	double min1_Dv1 = min1_D1(6.0);
	//std::cout << "min1_D1 : " << sum1_D1 << "\n";
	if( min1_Dv1 < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	//multi
	oct::math::funcs::Multiply<double> mul1(FI3,FI3);
	double mul1_v1 = mul1(6.0);
	//std::cout << "mul1_v1 : " << mul1_v1 << "\n";
	if(fabs(mul1_v1 - 36.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::Equation<double>& mul1_D1 = mul1.D();
	double mul1_vD1 = mul1_D1(6.0);
	//std::cout << "mul1_D1 : " << mul1_D1 << "\n";
	if(fabs(mul1_vD1 - 12.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)

	//div
	oct::math::funcs::Divide<double> div1(FI3,FI3);
	double div1_v1 = div1(6.0);
	//std::cout << "div1_v1 : " << div1_v1 << "\n";
	if(fabs(div1_v1 - 1.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::Equation<double>& div1_D1 = div1.D();
	double div1_v1D = div1_D1(10.0);
	//std::cout << "div1_D1 : " << div1_D1 << "\n";
	if(div1_v1D < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::funcs::Power<double> pow1(FI3,4);
	double pow1_v1 = pow1(6.0);
	//std::cout << "pow1_v1 : " << pow1_v1 << "\n";
	if(fabs(pow1_v1 - 1296.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::Equation<double>& pow1_D1 = pow1.D();
	double pow1_Dv1 = pow1_D1(6.0);
	//std::cout << "pow1_Dv1 : " << pow1_Dv1 << "\n";
	if(fabs(pow1_Dv1 - 864.0) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::funcs::Sin<double> sin1(P);
	double sin1_v1 = sin1(0.5);
	//std::cout << "sin1_v1 : " << sin1_v1 << "\n";
	if(fabs(sin1_v1 - 0.479425) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::Equation<double>& sin1_D1 = sin1.D();
	//std::cout << "sin1_D1 : " << sin1_D1 << "\n";
	double sin1_v1D = sin1_D1(0.5);
	if(fabs(sin1_v1D - 0.877582) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
		
	oct::math::funcs::Cos<double> cos1(P);
	double cos1_v1 = cos1(0.5);
	//std::cout << "cos1_v1 : " << cos1_v1 << "\n";
	if(fabs(cos1_v1 - 0.877582) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	oct::math::Equation<double>& cos1_D1 = cos1.D();
	double cos1_vD1 = cos1_D1(0.5);
	//std::cout << "sin1_D1 : " << sin1_D1 << "\n";
	if(fabs(cos1_vD1 + 0.479425) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	//[ejer] pag 398
	oct::math::funcs::VolumenTubo<double> vt1(P,10.0);	
	//math::Point<double> point6(1.0/6.0,0.0);
	oct::math::Equation<double>& vt1_D1 = vt1.D();
	double vt1_D1v = vt1_D1(1.0/6.0);
	//std::cout << "vt1_D1 : " << vt1_D1 << "\n";
	if(fabs(vt1_D1v - 10.472) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	double vt1_dV = vt1.dV(1.0/6.0,1.0/48.0);
	//std::cout << "vt1_dV : " << vt1_dV << "\n";
	if(fabs(vt1_dV - 0.218166) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)
	double vt1_p1 = vt1.peso(1.0/6.0,1.0/48.0,450.0);//679.5094536
	//std::cout << "vt1_p1 : " << vt1_p1 << "\n";
	if(fabs(vt1_p1 - 98.1748) < oct::math::epsilon) CU_ASSERT(true)
	else CU_ASSERT(false)

	oct::math::funcs::VolumenTubo<double> vt2(P,12.700);
	//math::Point<double> point10(8.890/2.0,0.0);
	double vt2_dV = vt2.dV(8.890/2.0,0.025);//0.005001465
	//std::cout << "vt2_dV : " << vt2_dV << "\n";
	if(fabs(vt2_dV - 8.86738) < oct::math::epsilon) CU_ASSERT(true)//1.774
	else CU_ASSERT(false)
			
	//[1] : ejerc pag 404

	//numeros primos
	math::Prime prime;
	/*for(int i = 1; i <= 100; i++)
	{
		if(prime.isPrime(i)) std::cout << "Numero : " << i << "\n";
	}*/
	math::Prime prime2;
	if(prime2.isPrime(97)) CU_ASSERT(true)
	else CU_ASSERT(false)		
	math::Prime prime3;
	if(!prime3.isPrime(100)) CU_ASSERT(true)
	else CU_ASSERT(false)
	
	
	
	//statics
	
	oct::math::Dataset<int> dt;
	dt.add(12);
	dt.add(3);
	dt.add(25);
	dt.add(28);
	dt.add(14);
	dt.add(14);
	dt.add(5);
	dt.add(27);
	dt.add(30);
	dt.add(16);
	dt.add(9);
	dt.add(10);
	dt.add(22);
	dt.add(25);
	dt.add(11);
	dt.add(10);
	dt.add(8);
	dt.add(7);
	dt.add(21);
	dt.add(18);
	dt.add(8);
	dt.add(7);
	dt.add(12);
	dt.add(15);
	dt.add(21);
	dt.add(26);
	dt.add(7);
	dt.add(12);
	dt.add(15);
	dt.add(8);
	dt.add(27);
	dt.add(6);
	dt.add(13);
	dt.add(16);
	dt.add(9);
	dt.add(14);
	dt.add(13);
	dt.add(19);
	dt.add(21);
	dt.add(10);
	dt.add(13);
	dt.add(12);
	dt.add(18);
	dt.add(20);
	dt.add(9);
	dt.add(14);
	dt.add(21);
	dt.add(17);
	dt.add(14);
	dt.add(9);
	dt.add(7);
	dt.add(6);
	dt.add(4);
	dt.add(9);
	dt.add(8);
	dt.add(6);
	dt.add(4);
	dt.add(12);
	dt.add(18);
	dt.add(32);
	dt.add(11);
	dt.add(12);
	dt.add(20);
	dt.add(16);
	dt.add(14);
	dt.add(4);
	dt.add(31);
	dt.add(22);
	dt.add(5);
	dt.add(24);
	dt.add(23);
	dt.add(8);
	dt.add(26);
	dt.add(31);
	dt.add(7);
	dt.add(25);
	dt.add(30);
	dt.add(18);
	dt.add(26);
	dt.add(12);

	//std::cout << "Count : " << dt.getCounter() << "\n";
	CU_ASSERT(dt.counter() == 80);
	
	dt.sort();
	CU_ASSERT(dt.max() == 32);
	//std::cout << "Max : " << dt.getMax() << "\n";
	CU_ASSERT(dt.min() == 3)
	//std::cout << "Min : " << dt.getMin() << "\n";
	
	CU_ASSERT(dt.categories() == 7);
	//std::cout << "Cat : " << dt.getCategories() << "\n";
	
	CU_ASSERT(dt.amplitudeClass() == 4);
	
	oct::math::FrecuencyTable<int> frecTab(dt);
	/*for(const oct::math::Frecuency<int>& row : frecTab)
	{
		std::cout << row.frec << "\n";
	}*/
	CU_ASSERT(frecTab.size() == 8);
	oct::math::FrecuencyTable<int>::iterator rowTF;
	rowTF = frecTab.begin();
	CU_ASSERT((*rowTF).frec == 9);
	rowTF++;
	CU_ASSERT((*rowTF).frec == 18);
	rowTF++;
	CU_ASSERT((*rowTF).frec == 18);
	rowTF++;
	CU_ASSERT((*rowTF).frec == 10);
	rowTF++;
	CU_ASSERT((*rowTF).frec == 9);
	rowTF++;
	CU_ASSERT((*rowTF).frec == 8);
	rowTF++;
	CU_ASSERT((*rowTF).frec == 5);
	rowTF++;
	CU_ASSERT((*rowTF).frec == 3);
	
	frecTab.frecageater();
	/*for(const oct::math::Frecuency<int>& row : frecTab)
	{
		std::cout << row.frecageater << "\n";
	}*/
	
	frecTab.frecp();
	frecTab.frecpageater();
	/*for(const oct::math::Frecuency<int>& row : frecTab)
	{
		std::cout << row.frecpagreater << "\n";
	}*/
	
	//std::cout << "media : " << dt.mean() << "\n";
	CU_ASSERT(15.15 - dt.mean() < oct::math::epsilon);
	
	//std::cout << "mediana : " << dt.median() << "\n";
	CU_ASSERT(13 == dt.median());
	
	//std::cout << "desviacion media : " << dt.dm() << "\n";
	CU_ASSERT(6.50125 - dt.md() < oct::math::epsilon);
	
	//std::cout << "varianza : " << dt.variance(true) << "\n";
	CU_ASSERT(59.3525 - dt.variance(true) < oct::math::epsilon);
	
	
	//
	oct::math::Matrix<float> m1(3,4);
	CU_ASSERT(m1.rows() == 3);
	
	m1[0][0] = 2;
	m1[0][1] = 1;
	m1[0][2] = -4;
	m1[0][3] = -3;
	//
	m1[1][0] = 0;
	m1[1][1] = -1;
	m1[1][2] = 0;
	m1[1][3] = -1;
	//
	m1[2][0] = -1;
	m1[2][1] = 2;
	m1[2][2] = -2;
	m1[2][3] = 1;
	
	//m1.print(std::cout);
	
	oct::math::Matrix<float> m2;
	m1.transposed(m2);
	//std::cout << "\n";
	//m2.print(std::cout);
	CU_ASSERT(m2[0][0] == 2);
	CU_ASSERT(m2[0][1] == 0);
	CU_ASSERT(m2[0][2] == -1);
	
	CU_ASSERT_FALSE(m1.isSquared());
	CU_ASSERT_FALSE(m2.isSquared());
	oct::math::Matrix<float> m3(3);
	CU_ASSERT(m3.isSquared());
	
	oct::math::Matrix<float> m4(4);	
	m4[0][0] = 1;
	m4[0][1] = 0;
	m4[0][2] = 0;
	m4[0][3] = 0;
	//
	m4[1][0] = 0;
	m4[1][1] = 1;
	m4[1][2] = 0;
	m4[1][3] = 0;
	//
	m4[2][0] = 0;
	m4[2][1] = 0;
	m4[2][2] = 1;
	m4[2][3] = 0;
	//
	m4[3][0] = 0;
	m4[3][1] = 0;
	m4[3][2] = 0;
	m4[3][3] = 1;
	//m4.print(std::cout);
	CU_ASSERT(m4.isDiagonal());
	
	//
	oct::math::Matrix<float> m5 = m1;
	//std::cout << "\n";
	//m1.print(std::cout);
	//std::cout << "\n";
	oct::math::Matrix<float> m6 = m1 + m5;
	CU_ASSERT(m6[0][0] == 4);
	CU_ASSERT(m6[0][1] == 2);
	CU_ASSERT(m6[0][2] == -8);
	CU_ASSERT(m6[0][3] == -6);
	//std::cout << "\n";
	//m6.print(std::cout);
	oct::math::Matrix<float> m7 = m6 - m1;
	CU_ASSERT(m7[0][0] == 2);
	CU_ASSERT(m7[0][1] == 1);
	CU_ASSERT(m7[0][2] == -4);
	CU_ASSERT(m7[0][3] == -3);
	//std::cout << "\n";
	//m7.print(std::cout);
	oct::math::Matrix<float> m8 = m1 * m2;
	//std::cout << "\n";
	//m8.print(std::cout);

	CU_ASSERT(m1 == m5);
	
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
	
	if ((NULL == CU_add_test(pSuite, "Test for Line class", testLines)))
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

