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
float Divide(Point *Array, int left, int right);//점들을 분할, 병합
float Check_MiddleArea(Point *Array,int left, int mid, int right, float MIN);//중간지점 점들의 거리를 구하는 함수, 좌우 영역 최소값과 비교.
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
	cout << "\n 최단거리 : " << Minimum << endl;
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
	if (Numofindex < 4)//더이상 분할할 수 없는 경우.
	{
		if (Numofindex == 3)
		{
			//세 선분의 길이 비교
			float length1, length2, length3;
			length1 = length2 = length3 = 0;
			length1 = sqrt(pow(Array[left].x - Array[Mid].x, 2) + pow(Array[left].y - Array[Mid].y, 2));
			length2 = sqrt(pow(Array[Mid].x - Array[right].x, 2) + pow(Array[Mid].y - Array[right].y, 2));
			length3 = sqrt(pow(Array[right].x - Array[left].x, 2) + pow(Array[right].y - Array[left].y, 2));
			Min = (length1 < length2) ? length1 : length2;
			Min = (Min < length3) ? Min : length3;
			if(Min == length1)//말단 부분에서 최근접 쌍과 거리 출력
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
			//선분이 하나이기 때문에 바로 리턴
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
		Min = (Min < M_min) ? Min : M_min;//중간영역에서의 최소거리와 좌우영역에서 얻은 최소거리 비교
		cout << left << "에서 " << right << "인덱스까지의 최소 거리 : " << Min << endl << endl;
		return Min;
	}
}
float Check_MiddleArea(Point *Array,int left, int mid, int right, float MIN)
{
	//Mid 좌표(x좌표 기준), 좌우 영역의 최소값만큼 증감한 영역에 x좌표 값이 포함되는 점들 간의 거리를 검사함.
	//먼저 array[Mid].x - MIN <= 해당 영역의 x 값. <= array[Mid].x + MIN  만족하는 좌표들을 찾아 저장함.
	//저장한 좌표들간의 거리를 구한다. 비교 중간영역 최근접 쌍을 찾고, 그 거리를 좌우 영역에서 나온 최소 거리와 비교한다.
	Point Mid_points[20] = {0};
	int index_count = 0;
	float tmp = 0, min = 2000.0;//min을 매우 큰 수로 잡아놓음
	for (int i = left ; i <= right ; i++)//중간영역안에 들어가는 좌표 찾아 저장
	{
		if (Array[i].x >= (float)Array[mid].x - MIN && Array[i].x <= (float)Array[mid].x + MIN)
		{
			Mid_points[index_count] = Point_Array[i];
			index_count++;
		}
	}
	for (int i = 0; i < index_count; i++)//자기 자신을 제외한 다른 모든 점들과의 거리를 구한다.
	{
		for (int j = i+1 ; j < index_count; j++)
		{
			tmp = sqrt(pow((Mid_points[i].x - Mid_points[j].x), 2) + pow((Mid_points[i].y - Mid_points[j].y), 2));// [0][1] ~ [0][3] 의 거리를 비교해야함.
			cout << "[" << Mid_points[i].x << ", " << Mid_points[i].y << "] , [" << Mid_points[j].x << ", " << Mid_points[j].y << "] <중간영역> ==> " <<tmp << endl;
			min = (min < tmp) ? min : tmp;//맨 처음 비교하는 거리로 min을 2000에서 tmp으로 업데이트, 이후 거리 값이 작아지면 업데이트.
		}
	}
	if(min != 2000)
		cout <<"<중간영역의 최소거리> : " << min << endl;
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