#include<iostream>
using namespace std;

//Node, Stack and Queue Classes
template <typename dataType>
class Node
{
	public:
		dataType data;
		Node<dataType>* next;
		Node(dataType d = 0)
		{
			data = d;
			next = NULL;
		}
};

template <typename dataType>
class Stack
{
	Node<dataType>* head;
	int stackSize;
	public:
		Stack()
		{
			head = NULL;
			stackSize = 0;
		}
		void push(dataType d)
		{
			Node<dataType>* p = new Node<dataType>(d);
			if (head != NULL)
			{
				p->next = head;
			}
			head = p;
			stackSize++;
		}
		dataType pop()
		{
			if (head != NULL)
			{
				Node<dataType>* p = head;
				dataType temp = head->data;
				head = head->next;
				delete p;
				stackSize--;
				return temp;
			}
		}
		dataType peek()
		{
			if (head != NULL)
			{
				return head->data;
			}
		}
		bool isEmpty()
		{
			if (head == NULL)
			{
				return true;
			}
			return false;
		}
		int size()
		{
			return stackSize;
		}
};

template <typename dataType>
class Queue
{
	Node<dataType>* front;
	Node<dataType>* rear;
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
	}
	void Enqueue(dataType d)
	{
		Node<dataType>* newNode = new Node<dataType>(d);
		newNode->next = rear;
		rear = newNode;
		if (front == NULL)
		{
			front = newNode;
		}
	}
	dataType Dequeue()
	{
		Node<dataType>* p = rear;
		Node<dataType>* removeNode;
		if (front != rear)
		{
			while (p->next != front)
			{
				p = p->next;
			}
			p->next = NULL;
			removeNode = front;
			front = p;
		}
		else
		{
			removeNode = front;
			front = NULL;
			rear = NULL;
		}
		dataType temp = removeNode->data;
		delete removeNode;
		return temp;
	}
	dataType peek(int index = 1)
	{
		dataType total = 0;
		Node<dataType>* p = front;
		while (index != 0)
		{
			if (p != NULL)
			{
				total += p->data;
				p = p->next;
			}
			index--;
		}
		return total;
	}
	bool isEmpty()
	{
		if (front == NULL && rear == NULL)
		{
			return true;
		}
		return false;
	}
	void makeEmpty()
	{
		while (!isEmpty())
		{
			Dequeue();
		}
	}
};

//Q1 Time Complexity O(n + k)
string largestString(string str, int k)
{
	Stack<char> largest;
	int stringIndex = 0;
	int removeCount = 0;
	while (1)
	{
		if (!largest.isEmpty() && str[stringIndex] > largest.peek() && removeCount < k)
		{
			largest.pop();
			removeCount++;
		}
		else if (str[stringIndex] == '\0')
		{
			break;
		}
		else
		{
			largest.push(str[stringIndex]);
			stringIndex++;
		}
	}
	int stringSize = largest.size();
	char* result = new char[stringSize];
	result[stringSize] = '\0';
	while (!largest.isEmpty())
	{
		result[stringSize - 1] = largest.pop();
		stringSize--;
	}
	return result;
}

//Q2 Time Complexity O(n + k)
string solve(string number, int k)
{
	Stack<char> largest;
	int numberIndex = 0;
	int removeCount = 0;
	int firstNum = 0;
	int numZeroes = 0;
	bool popUntilFirst = false;
	while (1)
	{
		if (popUntilFirst)
		{
			largest.pop();
			removeCount++;
			if (largest.size() == 0)
			{
				largest.push(number[numberIndex]);
				numberIndex++;
				popUntilFirst = false;
			}
		}
		else if (!largest.isEmpty() && number[numberIndex] < largest.peek() && removeCount < k)
		{
			if (number[numberIndex] == '0' && largest.size() == 1)
			{
				largest.push(number[numberIndex]);
				numberIndex++;
			}
			else if (number[numberIndex] < firstNum && largest.size() + removeCount < k && number[numberIndex] != '0')
			{
				popUntilFirst = true;
			}
			else
			{
				largest.pop();
				removeCount++;
			}
		}
		else if (number[numberIndex] < firstNum && largest.size() + removeCount < k && number[numberIndex] != '0')
		{
			popUntilFirst = true;
		}
		else if (number[numberIndex] == '\0')
		{
			break;
		}
		else
		{
			if (!largest.isEmpty() || number[numberIndex] != '0')
			{
				largest.push(number[numberIndex]);
			}
			else
			{
				removeCount++;
			}
			numberIndex++;
		}
		if (largest.size() == 1)
		{
			firstNum = largest.peek();
		}
	}
	int numberSize = largest.size();
	char* result = new char[numberSize];
	result[numberSize] = '\0';
	while (!largest.isEmpty())
	{
		result[numberSize - 1] = largest.pop();
		numberSize--;
	}
	string ans = result;
	cout << ans << '\n';
	return ans;
}

//Q3 Time Complexity O(n + k)
int* maxSubsequence(int nums[], int size, int k) 
{
	Queue<int> largest;
	int Max = -10000;
	int Total = 0;
	int startQ = 0;
	int finalStart = 0;
	int Qindex = 0;
	for (int loop = 0; loop < size; loop++)
	{
		if (Qindex < k)
		{
			Total += nums[loop];
			largest.Enqueue(nums[loop]);
			Qindex++;
		}
		else
		{
			Total -= largest.Dequeue();
			Total += nums[loop];
			largest.Enqueue(nums[loop]);
			startQ++;
		}
		if (Total > Max && Qindex == k)
		{
			finalStart = startQ;
			Max = Total;
		}
	}
	Qindex = 0;
	int* result = new int[k];
	for (int fill = 0; fill < k; fill++)
	{
		result[Qindex] = nums[fill + finalStart];
		Qindex++;
	}
	return result;
}