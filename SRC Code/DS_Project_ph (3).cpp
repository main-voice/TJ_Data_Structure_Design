/*��Ŀʮ  8�������㷨�ıȽϰ���*/
/*2053380 ���*/

#include <iostream>
#include <chrono>

#define DEBUG 0//��Ϊ1�������һЩ��Ҫ�ĵ�����Ϣ������ԭ���飬�Լ�����������

//check if the number is positive
bool check(int& number);
inline void swap(int& x, int& y) noexcept {//������������
	int tem = x;
	x = y;
	y = tem;
}

//����chronoʵ�ֶ�����ʱ��ļ���
class Timer
{
private:

	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::duration<float> duration;
public:

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		auto end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		printDuration();
	}
	void printDuration()
	{
		std::cout << "����ʱ�� : " << duration.count() * 1000.f << "ms\n";
	}

};

//�����ַ�������һ���������У�����ͳһ����
//����Ҫʵ����
class Sort
{
private:

	Sort();
	Sort(const Sort&) = delete;
	Sort(Sort&&) = delete; //move ������const�������������Ҫ��ԭ��ָ���ÿ�

public:
	static Sort& GetInstance() {
		static Sort Instance;
		return Instance;
	}

	//ð������
	static void bubbleSort(int array[], int length)
	{
		size_t count = 0;
		if (length == 1 || length == 0) {
			std::cout << "ð�����򽻻�������  " << count << "\n";
			return;
		}
		for (int i = 0; i < length; i++) {
			for (int j = i + 1; j < length; j++) {
				if (array[j] < array[i]) {
					swap(array[j], array[i]);
					count++;
				}
			}
		}
		std::cout << "ð�����򽻻�������  " << count << "\n";
	}

	//ѡ������
	static void selectSort(int array[], int len)
	{
		size_t count = 0;
		if (len == 1 || len == 0) {
			std::cout << "ѡ�����򽻻�������  " << count << "\n";
			return;
		}
		for (int i = 0; i < len - 1; i++) {
			int min = i;//the min is index instead of its value
			for (int j = i + 1; j < len; j++) {
				if (array[j] < array[min]) {
					min = j;
				}
			}
			if (min != i) {
				swap(array[min], array[i]);
				count++;
			}
		}
		std::cout << "ѡ�����򽻻�������  " << count << "\n";
	}

	//ֱ�Ӳ�������
	static void insertSort(int array[], int len)
	{
		size_t count = 0;
		if (len == 1 || len == 0) {
			std::cout << "�������򽻻�������  " << count << "\n";
			return;
		}

		for (int i = 1; i < len; i++) {
			int current = array[i];
			int j = i - 1;

			while (j >= 0 && current < array[j])
			{
				array[j + 1] = array[j];
				count++;
				j--;
			}

			array[j + 1] = current;
			count++;
		}
		std::cout << "�������򽻻�������  " << count << "\n";
	}

	//ϣ������
	static void shellSort(int array[], int length)
	{
		size_t count = 0;
		//����gap��������С����
	//��gap��Ϊ1��ʱ�򣬾�������ͨ�Ĳ�������
		for (int gap = length / 2; gap > 0; gap /= 2) {
			//�ӵ�gap��Ԫ�أ�����������������ֱ�Ӳ����������
			for (int i = gap; i < length; i++) {
				int j = i;
				while (j - gap >= 0 && array[j] < array[j - gap]) {
					//����������ý�����
					swap(array[j], array[j - gap]);
					count++;
					j -= gap;//�˴���ȥgap�Ĳ�����һ��Ĳ������������j--�Ĺ���
				}
			}
		}
		std::cout << "ϣ�����򽻻�������  " << count << "\n";
	}

	//��������
	static void quickSort(int array[], int left, int right)
	{
		static size_t count;//���ڵݹ飬ʹ��static
		static int flag = -1;//Ϊ��ֻ���һ�ν���������ÿ�ε��øú�������һ�Σ�flagΪ0�����


		int L = 0, R(0), temp(0);
		if (left > right)
			return;

		temp = array[left]; //temp�д�ľ��ǻ�׼��
		L = left;
		R = right;
		while (L != R)//�ѵ�ǰright-left���ȵ�������ȫ�ź���
		{
			//˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ��
			while (array[R] >= temp && L < R)
				R--;
			//�����ұߵ�
			while (array[L] <= temp && L < R)
				L++;
			//�����������������е�λ��
			if (L < R)
			{
				int t = 0;
				t = array[L];
				array[L] = array[R];
				array[R] = t;
				count++;
			}
		}
		//���ս���׼����λ
		array[left] = array[L];
		array[L] = temp;

		quickSort(array, left, L - 1);//����������ߵģ�������һ���ݹ�Ĺ���
		quickSort(array, L + 1, right);//���������ұߵģ�������һ���ݹ�Ĺ���

		flag++;//ע�⣺Ӧ���ȵݹ���������

		//std::cout << flag << "\n";

		if (flag == 0)
		{
			std::cout << "�������򽻻�������  " << count << "\n";
		}
	}

	//������
	static void heapSort(int array[], int len)
	{
		size_t count = 0;
		// ��ʼ��������һ�����ѣ���������
		for (int i = len / 2 - 1; i >= 0; i--)
			max_heapify(array, i, len - 1); //create a max heap

		//����һ�����ѣ�����Ψһ�ܹ�ȷ����˳����ǶѶ�Ԫ�����arr[0]����˵������Ѿ�������һ�����Ѻ�ͨ��������һ�������һ�����Ͱ����ֵ�ź���λ�ã�֮��ȥ�������ٹ����µ����ѣ����������ֵ��ѭ������
		// 
		for (int i = len - 1; i > 0; i--) {
			swap(array[0], array[i]); // swap first and last node , now the last node is the biggest
			count++;
			max_heapify(array, 0, i - 1); // create max heap on reduced array, because the i-1 is reduced, so as if we remove the last node
		}

		std::cout << "�����򽻻�������    " << count << "\n";

	}

	//�鲢����
	static void mergeSort(int array[], int length)
	{
		static int flag = -1;//Ϊ��ֻ���һ�ν���������ÿ�ε��øú�������һ�Σ�flagΪ0�����
		int* reg = new int[length];
		merge_sort_recursive(array, reg, 0, length - 1, flag);//�ݹ麯��
		delete[] reg;
	}

	//��������
	static void radixSort(int array[], int length)
	{
		if (length <= 1) { return; }

		int max = 0;//they represent the index of number

		for (int i = 0; i < length; i++)
		{
			if (array[i] > array[max]) { max = i; }
		}
		//std::cout << "the biggest number: " << array[max] << "\n";

		max = array[max];

		//��ȡÿһλ�����бȽϣ�λ������ĸ�λ��0
		for (int exp = 1; max / exp > 0; exp *= 10) {
			countSortForRadix(array, length, exp);
		}
		return;
	}

	//-----------����Ϊ���������е��õĺ���������Ҫ�����ã���Ϊprivate
private:

	//��arr���黯Ϊ����
	static void max_heapify(int arr[], int start, int end)
	{

		int dad = start;
		int son = dad * 2 + 1;
		while (son <= end) {
			if (son + 1 <= end && arr[son] < arr[son + 1]) // ѡ�������ӽڵ�
				son++;
			if (arr[dad] > arr[son])
				return;
			else {
				swap(arr[dad], arr[son]);
				dad = son; //from top to bottom
				son = dad * 2 + 1;
			}
		}
	}

	//�鲢�������õ��ĵݹ麯��
	static void merge_sort_recursive(int arr[], int reg[], int start, int end, int flag) {

		static size_t count = 0;
		//static int flag = -1;


		if (start >= end)
			return;
		int len = end - start, mid = (len / 2) + start;
		int start1 = start, end1 = mid;
		int start2 = mid + 1, end2 = end;

		flag++;

		merge_sort_recursive(arr, reg, start1, end1,flag);
		merge_sort_recursive(arr, reg, start2, end2,flag);

		
		int k = start;
		while (start1 <= end1 && start2 <= end2) {
			reg[k++] = arr[start1] < arr[start2]
				? arr[start1++] : arr[start2++];
			count++;
		}

		while (start1 <= end1) {
			reg[k++] = arr[start1++];
			count++;
		}

		while (start2 <= end2) {
			reg[k++] = arr[start2++];
			count++;
		}

		for (k = start; k <= end; k++)//reg����ʱ�����洢����
			arr[k] = reg[k];

		if (flag == 0) {
			std::cout << "�鲢���򽻻�������  " << count << "\n";
		}
	}

	//ר��Ϊ���������ʵ�ֵļ������򣬸��ӷ����������digit ��λȨ����Ϣ
	static void countSortForRadix(int* array, int length, int digit)
	{
		static size_t count = 0;
		static int flag = -1;
		flag++;

		int min = 0, max = 0;//they represent the index of number

		int* copy = new int[length];
		for (int i = 0; i < length; i++) {
			copy[i] = array[i];
		}

		int countBucket[10]{};
		//���ո�λȥ��Ͱ����������һλ���ֻ��ʮ���������0 - 9������ֻ��Ҫ��10��Ԫ�ش�С�Ϳ���

		for (int i = 0; i < length; i++)
		{
			int index = (array[i] / digit) % 10;//��λ��Ȼ��0�����ﵽ�˽϶����ָ�λ�����Ŀ��
			countBucket[index]++;
		}

		for (int i = 1; i < 10; i++) {
			countBucket[i] = countBucket[i] + countBucket[i - 1];
		}

		for (int j = length; j > 0; j--)
		{
			copy[countBucket[(array[j - 1] / digit) % 10] - 1] = array[j - 1];
			count++;
			countBucket[(array[j - 1] / digit) % 10]--;
		}

		for (int i = 0; i < length; i++) {
			array[i] = copy[i];
		}
		if (flag == 0) {
			std::cout << "�������򽻻�������  " << count << "\n";

		}

		delete[] copy;
	}

public:

};


int main()
{
	using namespace std;

	cout << " �����㷨�Ƚ�\n\n";
	cout << " 1. ð������\n";
	cout << " 2. ѡ������\n";
	cout << " 3. ֱ�Ӳ�������\n";
	cout << " 4. ϣ������\n";
	cout << " 5. ��������\n";
	cout << " 6. ������\n";
	cout << " 7. �鲢����\n";
	cout << " 8. ��������\n";
	cout << " 9. �˳�\n";

	cout << "������Ҫ������������ĸ�������ܰ��ʾ��������޷���ʾ���\n";
	int Size;
	cin >> Size;
	check(Size);

	int* array = new int[Size];
	int* copy = new int[Size];
	srand((unsigned)time(NULL));
	//ͨ�ù�ʽ: a + rand() % n�����е� a ����ʼֵ��n �������ķ�Χ��

	//initialize
	for (int i = 0; i < Size; i++)
	{
		array[i] = copy[i] = rand() % (Size * 3 + 1) + 0;

#if DEBUG
		cout << array[i] << " ";
		if (i % 10 == 0 && i)cout << "\n";
#endif // DEBUG
	}
	cout << "\n";

	int choice = 0;
	enum CHOICE { nul, bubble, select, insert, shell, quick, heap, merge, radix, quit };

	while (1)
	{
		cout << "ѡ��һ�������㷨\n";
		cin >> choice;
		check(choice);

		switch (choice)
		{
		case bubble:
		{
			Timer timer;
			cout << "bubble!\n";

#if DEBUG
			cout << "before sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 20 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif			
			Sort::bubbleSort(array, Size);
#if DEBUG

			cout << "after sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 20 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif // DEBUG

			for (int i = 0; i < Size; i++)
			{
				array[i] = copy[i];//�ָ�����ԭ��
			}
			break;
		}
		case select:
		{
			Timer timer;
			cout << "select!\n";
#if DEBUG
			cout << "before sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 20 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif		

			Sort::selectSort(array, Size);
#if DEBUG

			cout << "after sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 10 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif // DEBUG

			for (int i = 0; i < Size; i++)
			{
				array[i] = copy[i];//�ָ�����ԭ��
			}
			break;
		}
		case insert:
		{
			cout << "insert!\n";

#if DEBUG
			cout << "before sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 20 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif		

			Timer timer;
			Sort::insertSort(array, Size);
#if DEBUG

			cout << "after sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 10 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif // DEBUG

			for (int i = 0; i < Size; i++)
			{
				array[i] = copy[i];//�ָ�����ԭ��
			}
			break;
		}
		case shell:
		{
#if DEBUG
			cout << "before sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 20 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif		
			cout << "shell!\n";
			Timer timer;
			Sort::shellSort(array, Size);
#if DEBUG

			cout << "after sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 10 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif // DEBUG

			for (int i = 0; i < Size; i++)
			{
				array[i] = copy[i];//�ָ�����ԭ��
			}
			break;
		}
		case quick:
		{
			cout << "quick!\n";
			Timer timer;
			Sort::quickSort(array, 0, Size - 1);
#if DEBUG

			cout << "after sort\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 10 == 0 && i)cout << "\n";
			}
			cout << "\n\n";
#endif // DEBUG

			for (int i = 0; i < Size; i++)
			{
				array[i] = copy[i];//�ָ�����ԭ��
			}
			break;
		}
		case heap:
		{
			cout << "heap!\n";
			Timer timer;
			Sort::heapSort(array, Size);
#if DEBUG

			cout << "after sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 10 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif // DEBUG

			for (int i = 0; i < Size; i++)
			{
				array[i] = copy[i];//�ָ�����ԭ��
			}
			break;
		}
		case merge:
		{
			cout << "merge!\n";
			Timer timer;
			Sort::mergeSort(array, Size);
#if DEBUG

			cout << "after sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 10 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif // DEBUG

			for (int i = 0; i < Size; i++)
			{
				array[i] = copy[i];//�ָ�����ԭ��
			}
			break;
		}
		case radix:
		{
			cout << "radix!\n";
			Timer timer;
			Sort::radixSort(array, Size);
#if DEBUG

			cout << "after sort\n\n";
			for (int i = 0; i < Size; i++)
			{
				cout << array[i] << " ";
				if (i % 10 == 0 && i)cout << "\n";
			}
			cout << "\n";
#endif // DEBUG

			for (int i = 0; i < Size; i++)
			{
				array[i] = copy[i];//�ָ�����ԭ��
			}
			break;
		}
		case quit:
		{
			cout << "quit!\n";
			cout << "���س����˳�.\n";
			delete[] array;
			delete[] copy;
			std::cin.get();
			std::cin.get();
			return 0;
		}
		default:
		{
			;
		}
		}


	}

	delete[] array;
	delete[] copy;
	return 0;
}

bool check(int& number)
{
	using namespace std;
	while (std::cin.fail() || number <= 0)
	{
		cout << "error input, please input again.\n";
		cin.clear();
		cin.ignore(65535, '\n');
		cin >> number;
	}
	return true;
}
