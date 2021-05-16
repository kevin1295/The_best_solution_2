// The_best_solution_2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <math.h>
#include <algorithm>
#include <Windows.h>

using namespace std;

long long N = 36000;											// 10*x^2
double t[3] = { 0, 1, 3 };										// time of car and man going past a point

struct Examples {
	bool Statements[61];
} Ex[36001];
int Parkpoint[36001][4], Possibility[60];						// 50 parking spots
double Time[36001][4], Sum_time[4];

int main()
{
	FILE* stream1;												// prepare to write into documents

	freopen_s(&stream1, "result.csv", "w", stdout);
	printf("number of spaces,method_1,method_2,method_3\n");
	freopen_s(&stream1, "CON", "w", stdout);
	printf("--------------------monitoring--------------------\n");

	freopen_s(&stream1, "result.txt", "w", stdout);
	printf("\n");
	for (int lots = 40; lots <= 60; lots+=2) {
		memset(Time, 0, sizeof(Time));
		memset(Sum_time, 0, sizeof(Sum_time));
		N = 10 * lots * lots;
		freopen_s(&stream1, "CON", "w", stdout);
		srand(time(0));											// initialization
		printf("--------------------monitoring--------------------\n");
		for (int i = 1; i <= lots; i++) {						// arrange possibility
			Possibility[i] = N - 10 * i * i;
			if (Possibility[i] < 0) {
				Possibility[i] = 0;
			}
		}

		for (int i = 1; i <= lots; i++) {						// build point No.1
			long long j = Possibility[i], points = 0;
			printf("%lld\n", j);								// monitor how many cars have parked on the point
			while (j >= 0) {									// have j points rest
				long long rest = rand() % (N - points + 1) + 1;
				for (int k = 1; k <= N; k++) {
					if (Ex[k].Statements[i] == false) {
						--rest;
						if (rest == 1) {
							Ex[k].Statements[i] = true;
							points++;
							break;
						}
					}
				}
				j--;
			}
		}


		freopen_s(&stream1, "out.txt", "w", stdout);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= lots + 1; j++) {
				printf("%c", Ex[i].Statements[j] ? 'x' : 'o');
			}
			printf("\n");
		}

		freopen_s(&stream1, "CON", "w", stdout);				// return to write in CMD
		printf("--------------------results--------------------\n");

		freopen_s(&stream1, "out1.txt", "w", stdout);
		for (int i = 1; i <= N; i++) {
			for (int j = lots; j > 0; j--) {
				if ((Ex[i].Statements[j] == false) && (Ex[i].Statements[j - 1] == true)) {
					Parkpoint[i][1] = j;
					break;
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= lots; j++) {
				if (Ex[i].Statements[j] == false) {
					Parkpoint[i][2] = j;
					break;
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			for (int j = lots - 2; j > 0; j--) {
				if ((Ex[i].Statements[j - 1] == true) && (Ex[i].Statements[j] == false) && (Ex[i].Statements[j + 1] == false) && (Ex[i].Statements[j + 2] == true)) {
					Parkpoint[i][3] = j;
					break;
				}
				if (j == 1) {
					for (int j = 1; j <= lots; j++) {
						if (Ex[i].Statements[j] == false) {
							Parkpoint[i][3] = (t[2] - t[1]) / (t[1] + t[2]) * j;
							break;
						}
					}
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			Time[i][1] = (lots - Parkpoint[i][1]) * t[1] + Parkpoint[i][1] * t[2];
			Time[i][2] = lots * t[1] + Parkpoint[i][1] * t[1] + Parkpoint[i][1] * t[2];
			Time[i][3] = (lots - Parkpoint[i][3]) * t[1] + Parkpoint[i][3] * t[2];
			Sum_time[1] += Time[i][1];
			Sum_time[2] += Time[i][2];
			Sum_time[3] += Time[i][3];
			printf("%llf     %llf     %llf\n", Time[i][1], Time[i][2], Time[i][3]);
		}
		freopen_s(&stream1, "CON", "w", stdout);
		printf("Sum_time of 1 = %lf s\nand average is %lf s\n", Sum_time[1], Sum_time[1] / N);
		printf("Sum_time of 2 = %lf s\nand average is %lf s\n", Sum_time[2], Sum_time[2] / N);
		printf("Sum_time of 3 = %lf s\nand average is %lf s\n", Sum_time[3], Sum_time[3] / N);

		freopen_s(&stream1, "result.csv", "a+", stdout);
		printf("%d,", lots);
		printf("%lf,", Sum_time[1] / N);
		printf("%lf,", Sum_time[2] / N);
		printf("%lf\n", Sum_time[3] / N);

		freopen_s(&stream1, "CON", "w", stdout);

	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
