#include <cmath>
#include "resource.h"
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

class MAX {
#define population 200
#define gene 40
#define p_change 50  //�������Ϊ1/p_change
#define edgeR 4.00
time_t rawtime;
public:
	bool pop[population][gene] = { false };  //�洢ÿ��������Ŵ���Ϣ
	char rst[20] = {'\0'};
	double all_x[population][2];
	int popu = population;


	//���룬���Ŵ���Ϣ�Ķ���������
	double *translate(bool R[])
	{
		double sliceLen = pow(2, gene / 2);
		double slice = edgeR * 2. / sliceLen;  //��(-4,4)������ֳ� 2^(gene / 2)С��

		double x[2] = { -edgeR,  -edgeR };

		long long int a = 1;
		//��gene��ǰ�벿�ֺͺ�벿�ֶ�ת��Ϊ�����ƣ�����С�����������������x��y
		for (int i = 0; i < gene/2; i++)
		{
			x[0] += !!R[i] * a * slice;
			a *= 2;
		}

		a = 1;
		for (int i = gene / 2; i < gene; i++)
		{
			x[1] += !!R[i] * a * slice;
			a *= 2;
		}
		return x;
	}
	//Ҫ���ĺ���
	double f(double x, double y)
	{
		return (-pow(x,4) - pow(y, 4) + 10 * ((x - 0.1)*(x - 0.1) + (y + 0.1) * (y + 0.1)));
	}
	//����ֵ�Ĵ���
	void give_num(bool array1[], bool array2[])
	{
		for (int i = 0; i < gene; i++)
		{
			array1[i] = array2[i];
		}
	}
	//��Ӧ�ȴ�С��������ѡ������
	void judge_fitness(bool R[][gene])
	{
		bool mid_R[gene];
		int maxPos;
		double maxVal, thisVal;
		double *xyValue;
		for (int j = 0; j < population - 1; j++)
		{
			xyValue = translate(R[j]);
			maxVal = thisVal = f(xyValue[0], xyValue[1]);
			maxPos = j;
			for (int i = j + 1; i < population; i++)
			{
				double *xyValue = translate(R[i]);
				thisVal = f(xyValue[0], xyValue[1]);
				if (thisVal > maxVal)
				{
					maxVal = thisVal;
					maxPos = i;
				}
			}
			give_num(mid_R, R[j]);
			give_num(R[j], R[maxPos]);
			give_num(R[maxPos], mid_R);
		}
		rand();
	}

	//����
	void change(bool pop[population][gene])
	{
		bool temp[population][gene] = {false};
		for (int i = 0; i < population; i++)
		{
			for (int j = 0; j < gene; j++)
			{
				//���ֵ������������pop�еĸ�λ����ȡ��
				if (!(rand() % p_change))
				{
					temp[i][j] = !pop[i][j];
				}
				else
					temp[i][j] = pop[i][j];
			}
			
			//if (f(xyValue[0], xyValue[1]) > f(xyValue1[0], xyValue1[1]))		 //��ֹ�˻�
			memcpy(pop[i], temp[i], sizeof(temp[i]));
		}
	}
	//��ʼ��
	void init(bool R[])
	{
		for (int i = 0; i < gene; i++)
		{
			R[i] = !!(rand() % 2);
		}
	}

	//��ֳ
	void multiply(bool array1[], bool array2[], bool array3[])
	{
		bool temp[gene] = { false };
		for (int i = 0; i < gene; i++)
		{
			if (rand() % 2)
			{
				temp[i] = array1[i];
			}
			else
			{
				temp[i] = array2[i];
			}
		}
		give_num(array3, temp);
	}

	//���ĺ�����FMAX(��������)
	void FMAX(int generation)
	{
		for (int i = 0; i < generation; i++)
		{
			if (i==0)
				judge_fitness(pop);
			bool pop_[population][gene];
			for (int j = 0; j < population; j++)
			{
				//���Ž���
				double k = rand() / 32676.;
				double l = rand() / 32676.;

				for (int n = 0; n < 2; n++)
				{
					k *= k;
					l *= l;
				}

				multiply(pop[int(k * population )], pop[int(l * population)], pop_[j]);
			}
			//����
			change(pop_);
			//�´�����ȡ���ϴ�����
			memcpy(pop, pop_, sizeof(pop));
			judge_fitness(pop);
		}
	}

	void procForOutput()
	{

		//Ϊ�˷����������ÿ�������Ӧ��x yֵ�ŵ�������
		for (int i = 0; i < population; i++)
		{
			double *xyValue = translate(pop[i]);
			all_x[i][0] = xyValue[0];
			all_x[i][1] = xyValue[1];
		}
		sprintf_s(rst, "%.9f", f(all_x[0][0], all_x[0][1]));
	}
};
