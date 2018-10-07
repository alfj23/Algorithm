#include<iostream>
#include<random>
#include<cmath>
using namespace std;

struct Point
{
	int x;
	int y;
};
Point Point_Array[30] = { {316, 353}, {253, 857}, {743, 851}, {183, 998}, {262, 439}, {330, 732}, {418, 232}, {856, 448}, {596, 658}, {266, 100}, {890, 793}, {665, 864}, {238, 657}, {636, 731}, {735, 606},{562, 203}, {492, 701}, {306, 393}, {798, 939}, {921, 176}, {637, 780}, {620, 975}, {718, 94}, {887, 749}, {756, 560}, {525, 805}, {229, 29}, {352, 570}, {670, 589}, {644, 821},};
Point rand_points[30] = { 0 };

void Sort_Array(Point *Array);
float Divide(Point *Array, int left, int right);//������ ����, ����
float Check_MiddleArea(Point *Array,int left, int mid, int right, float MIN);//�߰����� ������ �Ÿ��� ���ϴ� �Լ�, �¿� ���� �ּҰ��� ��.
void Make_Random_Points();
void PrintArray(Point* Array);

int main()
{
	float Minimum = 0;
	
	/*for (int i = 0; i < 30; i++)
	{
		cout << "After Sort : " << Point_Array[i].x << "\t" << Point_Array[i].y << endl;
	}*/
	//Minimum = Divide(Point_Array, 0, 29);
	Make_Random_Points();
	Sort_Array(rand_points);
	PrintArray(rand_points);
	Minimum = Divide(rand_points, 0, 29);
	cout << "\n �ִܰŸ� : " << Minimum << endl;
	system("pause");
}
void PrintArray(Point* Array)
{
	for (int i = 0; i < 30; i++)
	{
		if (i == 29)
			cout << "[" << Array[i].x << ", " << Array[i].y << "]" << endl << endl;
		else
			cout << "[" << Array[i].x << ", " << Array[i].y << "], ";
	}
}
void Sort_Array(Point* Array)
{
	Point tmp = { 0 };
	for (int i = 0; i < 30-1; i++)
	{
		for (int j = 0; j < 30 - 1 - i; j++)
		{
			if (Array[j].x > Array[j + 1].x)
			{
				tmp = Array[j];
				Array[j] = Array[j + 1];
				Array[j + 1] = tmp;
			}
		}
	}
}
float Divide(Point *Array, int left, int right)
{
	int Numofindex = right - left + 1;
	int Mid = (left + right) / 2;
	float Min = 0;
	if (Numofindex < 4)//���̻� ������ �� ���� ���.
	{
		if (Numofindex == 3)
		{
			//�� ������ ���� ��
			float length1, length2, length3;
			length1 = length2 = length3 = 0;
			length1 = sqrt(pow(Array[left].x - Array[Mid].x, 2) + pow(Array[left].y - Array[Mid].y, 2));
			length2 = sqrt(pow(Array[Mid].x - Array[right].x, 2) + pow(Array[Mid].y - Array[right].y, 2));
			length3 = sqrt(pow(Array[right].x - Array[left].x, 2) + pow(Array[right].y - Array[left].y, 2));
			Min = (length1 < length2) ? length1 : length2;
			Min = (Min < length3) ? Min : length3;
			if(Min == length1)//���� �κп��� �ֱ��� �ְ� �Ÿ� ���
				cout << "[" << Array[left].x << ", " << Array[left].y << "], [" << Array[Mid].x << ", " << Array[Mid].y << "] ==> " << length1 << endl;
			else if (Min == length2)
				cout << "[" << Array[Mid].x << ", " << Array[Mid].y << "], [" << Array[right].x << ", " << Array[right].y << "] ==> " << length2 << endl;
			else
				cout << "[" << Array[right].x << ", " << Array[right].y << "], [" << Array[left].x << ", " << Array[left].y << "] ==> " << length3 << endl;
			//cout << endl;
			return Min;
		}
		else if (Numofindex == 2)
		{
			//������ �ϳ��̱� ������ �ٷ� ����
			Min = sqrt(pow(Array[left].x - Array[right].x, 2)+ pow(Array[left].y - Array[right].y, 2));
			cout << "[" << Array[left].x << ", " << Array[left].y << "], [" << Array[right].x << ", " << Array[right].y << "] ==> " << Min << endl;
			//cout << endl;
			return Min;
		}
	}
	else
	{
		float L_min = 0, R_min = 0, M_min = 0;
		L_min = Divide(Array, left, Mid);
		R_min = Divide(Array, Mid + 1, right);
		Min = (L_min < R_min) ? L_min : R_min;
		M_min = Check_MiddleArea(Array,left, Mid, right, Min);
		Min = (Min < M_min) ? Min : M_min;//�߰����������� �ּҰŸ��� �¿쿵������ ���� �ּҰŸ� ��
		cout << left << "���� " << right << "�ε��������� �ּ� �Ÿ� : " << Min << endl << endl;
		return Min;
	}
}
float Check_MiddleArea(Point *Array,int left, int mid, int right, float MIN)
{
	//Mid ��ǥ(x��ǥ ����), �¿� ������ �ּҰ���ŭ ������ ������ x��ǥ ���� ���ԵǴ� ���� ���� �Ÿ��� �˻���.
	//���� array[Mid].x - MIN <= �ش� ������ x ��. <= array[Mid].x + MIN  �����ϴ� ��ǥ���� ã�� ������.
	//������ ��ǥ�鰣�� �Ÿ��� ���Ѵ�. �� �߰����� �ֱ��� ���� ã��, �� �Ÿ��� �¿� �������� ���� �ּ� �Ÿ��� ���Ѵ�.
	Point Mid_points[20] = {0};
	int index_count = 0;
	float tmp = 0, min = 2000.0;//min�� �ſ� ū ���� ��Ƴ���
	for (int i = left ; i <= right ; i++)//�߰������ȿ� ���� ��ǥ ã�� ����
	{
		if (Array[i].x >= (float)Array[mid].x - MIN && Array[i].x <= (float)Array[mid].x + MIN)
		{
			Mid_points[index_count] = Point_Array[i];
			index_count++;
		}
	}
	for (int i = 0; i < index_count; i++)//�ڱ� �ڽ��� ������ �ٸ� ��� ������� �Ÿ��� ���Ѵ�.
	{
		for (int j = i+1 ; j < index_count; j++)
		{
			tmp = sqrt(pow((Mid_points[i].x - Mid_points[j].x), 2) + pow((Mid_points[i].y - Mid_points[j].y), 2));// [0][1] ~ [0][3] �� �Ÿ��� ���ؾ���.
			cout << "[" << Mid_points[i].x << ", " << Mid_points[i].y << "] , [" << Mid_points[j].x << ", " << Mid_points[j].y << "] <�߰�����> ==> " <<tmp << endl;
			min = (min < tmp) ? min : tmp;//�� ó�� ���ϴ� �Ÿ��� min�� 2000���� tmp���� ������Ʈ, ���� �Ÿ� ���� �۾����� ������Ʈ.
		}
	}
	if(min != 2000)
		cout <<"<�߰������� �ּҰŸ�> : " << min << endl;
	return min;
}
void Make_Random_Points()
{
	random_device rd;
	default_random_engine rnd(rd());
	uniform_int_distribution<int> range(1, 999);
	for (int i = 0; i < 30; i++)
	{
		rand_points[i].x = range(rnd);
		rand_points[i].y = range(rnd);
	}
}