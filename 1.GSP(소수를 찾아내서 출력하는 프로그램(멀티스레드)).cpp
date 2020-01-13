#include<vector>
#include<iostream>
#include<chrono>
#include<thread>
#include<memory>

using namespace std;
using namespace chrono;
const int MaxCount = 150000;
const int ThreadCount = 4;

bool IsPrimeNumber(int Number)
{
	if (Number == 1)
		return false;
	if (Number == 2 || Number == 3)
		return true;

	for (int i = 2; i < Number - 1; ++i)
	{
		if ((Number % i) == 0)
			return false;
	}
	return true;
}

void PrintNumbers(const vector<int>&primes)
{
	for (int v : primes)
	{
		cout << v << endl;
	}
}

void main()
{
	//각 스레드는 여기서 값을 꺼내 온다.
	int num = 1;

	vector<int> primes;

	auto t0 = chrono::system_clock::now();

	vector<thread> threads;

	for (int i = 1; i < ThreadCount; ++i)
	{
		threads.emplace_back([&]()
		{
			// 각 스레드의 메인 함수.
			// 값을 가져올 수 있으면 루프를 돈다.
			while (true)
			{
				int n;
				n = num;
				num++;
				
				if (n >= MaxCount)
					break;

				if (IsPrimeNumber(n))
				{
					primes.push_back(n);
				}
			}
		});
	}

	for (auto & thread : threads)
	{
		thread.join();
	}
	//끝

	auto t1 = system_clock::now();
	auto duration = duration_cast<milliseconds>(t1 - t0).count();
	cout << "Took " << duration << " milliseconds." << endl;
	//PrintNumbers(primes);
	
	system("pause");
}