
#include <CUnit/Basic.h>

#include <iostream>
#include <statics.hh>
#include <defines.hh>


using namespace oct::math;

struct Person
{
	double tall;
	
	Person(){}
	Person(double t): tall(t){}
};

void test_statics()
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
	double vtall_mean = mean<double,std::vector<double>>(vtall);
	CU_ASSERT(std::abs(vtall_mean - 1.541) < 0.00001);
	//std::cout << "Promedio de altura : " << vtall_mean << "\n";
	
	double ltall_mean = mean<double,std::list<double>>(ltall);
	CU_ASSERT(std::abs(ltall_mean - 1.541) < 0.00001);
	//std::cout << "Promedio de altura : " << ltall_mean << "\n";
	
	double vperson_mean = mean<Person,std::vector<Person>,double>(vperson,[](const Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(vperson_mean - 1.541) < 0.00001);
	//std::cout << "Promedio de altura : " << vperson_mean << "\n";
			
	double lperson_mean = mean<Person,std::list<Person>,double>(lperson,[](const Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(lperson_mean - 1.541) < 0.00001);
	//std::cout << "List Promedio de altura : " << lperson_mean << "\n";
	
	double vtall_var = variation<double,std::vector<double>,double>(vtall,vtall_mean);
	CU_ASSERT(std::abs(vtall_var - 0.102259) < 0.00001);
	//std::cout << "Variacion de altura : " << vtall_var << "\n";
	
	double vtall_varsample = variation_sample<double,std::vector<double>,double>(vtall,vtall_mean);
	CU_ASSERT(std::abs(vtall_varsample - 0.107641) < 0.00001);
	//std::cout << "Variacion de altura : " << vtall_varsample << "\n";
	
	double ltall_var = variation<double,std::list<double>,double>(ltall,ltall_mean);
	CU_ASSERT(std::abs(ltall_var - 0.102259) < 0.00001);
	//std::cout << "Variacion de altura : " << vtall_var << "\n";
		
	double vperson_variation = variation<Person,std::vector<Person>,double>(vperson,vtall_mean,[](const Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(vperson_variation - 0.102259) < 0.00001);
	//std::cout << "Promedio de altura : " << vperson_variation << "\n";
		
	double lperson_variation = variation<Person,std::list<Person>,double>(lperson,ltall_mean,[](const Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(lperson_variation - 0.102259) < 0.00001);
	//std::cout << "Promedio de altura : " << lperson_variation << "\n";
	
	double lperson_variation_sample = variation_sample<Person,std::list<Person>,double>(lperson,ltall_mean,[](const Person& p)->double{return p.tall;});
	CU_ASSERT(std::abs(lperson_variation_sample - 0.107641) < 0.00001);
	//std::cout << "Promedio de altura : " << lperson_variation << "\n";
	
	std::vector<int> vapples(5);
	vapples[0] = 1;
	vapples[1] = 4;
	vapples[2] = 3;
	vapples[3] = 5;
	vapples[4] = 8;	
	double vapples_mean = mean<int,std::vector<int>,double>(vapples);
	//std::cout << "Promio de manzanas : " << vapples_mean << "\n";
	CU_ASSERT(std::abs(vapples_mean - 4.2) < 0.00001);
		
	std::list<int> lapples;
	lapples.push_back(1);
	lapples.push_back(4);
	lapples.push_back(3);
	lapples.push_back(5);
	lapples.push_back(8);	
	double lapples_mean = mean<int,std::list<int>,double>(lapples);
	//std::cout << "Promedio de manzanas : " << lapples_mean << "\n";
	CU_ASSERT(std::abs(lapples_mean - 4.2) < 0.00001);
	
	std::vector<double> vtall_asc = vtall;
	sort<double>(vtall_asc,[](double f,double s){return f < s;});
	/*for(double n : vtall_asc)
	{
		std::cout  << "Number : " << n << "\n";
	}*/
	CU_ASSERT(std::abs(vtall_asc.front() - 1.02) < 0.00001);
	CU_ASSERT(std::abs(vtall_asc.back() - 1.96) < 0.00001);
	
	std::list<double> ltall_asc = ltall;
	sort<double>(ltall_asc,[](double f,double s){return f < s;});
	/*for(double n : ltall_asc)
	{
		std::cout  << "Number : " << n << "\n";
	}*/
	CU_ASSERT(std::abs(ltall_asc.front() - 1.02) < 0.00001);
	CU_ASSERT(std::abs(ltall_asc.back() - 1.96) < 0.00001);
	
	
	std::vector<Person> vperson2 = vperson;
	sort<Person,double>(vperson2,[](Person& f,Person& s)->bool{return f.tall < s.tall;});
	/*for(const Person& p : vperson2)
	{
		std::cout  << "vector Tall : " << p.tall << "\n";
	}*/	
	CU_ASSERT(std::abs(vperson2.front().tall - 1.02) < 0.00001);
	CU_ASSERT(std::abs(vperson2.back().tall - 1.96) < 0.00001);
	
	std::list<Person> lperson2 = lperson;
	sort<Person,double>(lperson2,[](Person& f,Person& s)->bool{return f.tall < s.tall;});
	/*for(const Person& p : lperson2)
	{
		std::cout  << "Lista Tall : " << p.tall << "\n";
	}*/
	CU_ASSERT(std::abs(lperson2.front().tall - 1.02) < 0.00001);
	CU_ASSERT(std::abs(lperson2.back().tall - 1.96) < 0.00001);
	
	double vtall_median = median<double,std::vector<double>,double>(vtall_asc);
	//std::cout << "Median de altura : " << vtall_median << "\n";
	CU_ASSERT(std::abs(vtall_median - 1.71) < 0.00001);
	
	double vperson2_median = median<Person,std::vector<Person>,double>(vperson2,[](const Person& p)->double{return p.tall;});
	//std::cout << "Median de altura : " << vperson2_median << "\n";
	CU_ASSERT(std::abs(vperson2_median - 1.71) < 0.00001);
	
	unsigned int mode_count = 0;
	double vtall_mode = 0;
	mode<double,std::vector<double>,double>(vtall,vtall_mode,mode_count);
	//std::cout << "Moda de altura : " << vtall_mode << "\n";
	CU_ASSERT(std::abs(vtall_mode - 1.13) < 0.00001);
	CU_ASSERT(mode_count == 3);
	//std::cout << "Modal : " << mode_count << "\n";
	
	const std::vector<double>& vtall_const = vtall;
	double vtall_const_mean = mean<double,std::vector<double>,double>(vtall_const);
}