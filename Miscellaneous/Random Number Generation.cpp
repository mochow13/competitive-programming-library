#include <bits/stdc++.h>
#include <random>
#include <chrono>

using namespace std;

// Seeding non-deterministically
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

random_device rd;
mt19937 mt(rd());
uniform_real_distribution<double> r1(1.0, 10.0);
uniform_int_distribution<int> r2(1,INT_MAX);
normal_distribution<double> r3(1.0,10.0);
exponential_distribution<> r4(5);

int main()
{
	cout<<rng()<<endl;
	cout<<r1(mt)<<endl;
	cout<<r2(mt)<<endl;
	cout<<r4(mt)<<endl;
	return 0;
}