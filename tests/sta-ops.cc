
#include <CUnit/Basic.h>

#include <iostream>
#include <sta-ops.hh>
#include <defines.hh>


using namespace oct::sta;

struct Person
{
	double tall;
	
	Person(){}
	Person(double t): tall(t){}
};

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
	vtall[9] = 1.85;
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
	std::vector<Person> vperson(20);
	vperson[0].tall = 1.60;
	vperson[1].tall = 1.30;
	vperson[2].tall = 1.15;
	vperson[3].tall = 1.02;
	vperson[4].tall = 1.20;
	vperson[5].tall = 1.9;
	vperson[6].tall = 1.96;
	vperson[7].tall = 1.11;
	vperson[8].tall = 1.80;
	vperson[9].tall = 1.85;
	vperson[10].tall = 1.80;
	vperson[11].tall = 1.75;
	vperson[12].tall = 1.70;
	vperson[13].tall = 1.72;
	vperson[14].tall = 1.95;
	vperson[15].tall = 1.85;
	vperson[16].tall = 1.13;
	vperson[17].tall = 1.13;
	vperson[18].tall = 1.50;
	vperson[19].tall = 1.40;
	CU_ASSERT(vperson.size() == 20);
	std::list<Person> lperson;
	lperson.push_back(Person(1.60));
	lperson.push_back(Person(1.30));
	lperson.push_back(Person(1.15));
	lperson.push_back(Person(1.02));
	lperson.push_back(Person(1.20));
	lperson.push_back(Person(1.9));
	lperson.push_back(Person(1.96));
	lperson.push_back(Person(1.11));
	lperson.push_back(Person(1.80));
	lperson.push_back(Person(1.85));
	lperson.push_back(Person(1.80));
	lperson.push_back(Person(1.75));
	lperson.push_back(Person(1.70));
	lperson.push_back(Person(1.72));
	lperson.push_back(Person(1.95));
	lperson.push_back(Person(1.85));
	lperson.push_back(Person(1.13));
	lperson.push_back(Person(1.13));
	lperson.push_back(Person(1.50));
	lperson.push_back(Person(1.40));
	CU_ASSERT(lperson.size() == 20);
	//
	double vtall_mean = mean(vtall);
	CU_ASSERT(std::abs(vtall_mean - 1.541) < 0.00001);
	//std::cout << "Promedio de altura : " << vtall_mean << "\n";
	
	double ltall_mean = mean(ltall);
	CU_ASSERT(std::abs(ltall_mean - 1.541) < 0.00001);
	//std::cout << "Promedio de altura : " << ltall_mean << "\n";
	
	double vperson_mean = mean<Person,double>(vperson,[](Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(vperson_mean - 1.541) < 0.00001);
	//std::cout << "Promedio de altura : " << vperson_mean << "\n";
			
	double lperson_mean = mean<Person,double>(lperson,[](Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(lperson_mean - 1.541) < 0.00001);
	//std::cout << "List Promedio de altura : " << lperson_mean << "\n";
	
	double vtall_var = variation(vtall,vtall_mean);
	CU_ASSERT(std::abs(vtall_var - 0.102259) < 0.00001);
	//std::cout << "Variacion de altura : " << vtall_var << "\n";
			
	double ltall_var = variation(ltall,ltall_mean);
	CU_ASSERT(std::abs(ltall_var - 0.102259) < 0.00001);
	//std::cout << "Variacion de altura : " << vtall_var << "\n";
		
	double vperson_variation = variation<Person,double>(vperson,vtall_mean,[](Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(vperson_variation - 0.102259) < 0.00001);
	//std::cout << "Promedio de altura : " << vperson_variation << "\n";
		
	double lperson_variation = variation<Person,double>(lperson,ltall_mean,[](Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(lperson_variation - 0.102259) < 0.00001);
	//std::cout << "Promedio de altura : " << lperson_variation << "\n";
	
	
	
}