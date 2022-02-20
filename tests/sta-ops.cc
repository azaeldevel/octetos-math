
#include <CUnit/Basic.h>

#include <iostream>
#include <sta-ops.hh>
#include <defines.hh>


using namespace oct::sta;


void test_sta_ops()
{
	std::vector<double> vtall(20);
	vtall[0] = 1.60;
	vtall[1] = 1.30;
	vtall[2] = 1.15;
	vtall[3] = 1.02;
	vtall[4] = 1.20;
	vtall[5] = 1.9;
	vtall[6] = 1.96;
	vtall[7] = 1.11;
	vtall[8] = 1.80;
	vtall[5] = 1.85;
	vtall[10] = 1.80;
	vtall[11] = 1.75;
	vtall[12] = 1.70;
	vtall[13] = 1.72;
	vtall[14] = 1.95;
	vtall[15] = 1.85;
	vtall[16] = 1.13;
	vtall[17] = 1.13;
	vtall[18] = 1.50;
	vtall[19] = 1.40;
	CU_ASSERT(vtall.size() == 20);
	std::list<double> ltall;
	ltall.push_back(1.60);
	ltall.push_back(1.30);
	ltall.push_back(1.15);
	ltall.push_back(1.02);
	ltall.push_back(1.20);
	ltall.push_back(1.9);
	ltall.push_back(1.96);
	ltall.push_back(1.11);
	ltall.push_back(1.80);
	ltall.push_back(1.85);
	ltall.push_back(1.80);
	ltall.push_back(1.75);
	ltall.push_back(1.70);
	ltall.push_back(1.72);
	ltall.push_back(1.95);
	ltall.push_back(1.85);
	ltall.push_back(1.13);
	ltall.push_back(1.13);
	ltall.push_back(1.50);
	ltall.push_back(1.40);
	CU_ASSERT(ltall.size() == 20);
	
	//
	double vtall_mean = mean<double,double>(vtall);
	CU_ASSERT(vtall_mean - 1.541 < EPSILON);
	//std::cout << "Promedio de altura : " << vtall_mean << "\n";
	
	double ltall_mean = mean(ltall);
	CU_ASSERT(ltall_mean - 1.541 < EPSILON);
	//std::cout << "Promedio de altura : " << ltall_mean << "\n";
	
}