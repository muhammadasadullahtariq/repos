#include<iostream>
#include"node.h"
using namespace std;

AVL::AVL()
{
	num = 0;
	as = 0;
}

void AVL::insert()
{
	node *ptr = new node;
	cout << "Enter number:";
	cin >> num;
	ptr->num = num;
	ptr->L = NULL;
	ptr->R = NULL;
	ptr->h = 0;
	if (root == NULL)
	{
		root = ptr;
	}
	else
	{
		in(root, ptr);
	}
}

void AVL::in(node *&ptr, node*tem)
{
	if (tem->num < ptr->num)
	{
		if (ptr->L == NULL)
		{
			ptr->L = tem;
			ptr->h = 1;
			checkHight(ptr);
			return;
		}
		else
		{
			(ptr->L, tem);
			if (ptr->R == NULL)
			{
				ptr->h = ptr->L->h + 1;
			}
			else if (ptr->L->h >= ptr->R->h)
			{
				ptr->h = ptr->L->h + 1;
			}
			else
			{
				ptr->h = ptr->R->h + 1;
			}
			checkHight(ptr);
		}
	}
	else if (tem->num >= ptr->num)
	{
		if (ptr->R == NULL)
		{
			ptr->R = tem;
			ptr->h = 1;
			checkHight(ptr);
			return;
		}
		else
		{
			in(ptr->R, tem);
			if (ptr->L == NULL)
			{
				ptr->h = ptr->R->h + 1;
			}
			else if (ptr->L->h >= ptr->R->h)
			{
				ptr->h = ptr->L->h + 1;
			}
			else
			{
				ptr->h = ptr->R->h + 1;
			}
			checkHight(ptr);
		}
	}
}

void AVL::inOrder()
{
	inOrder(root);
}

void AVL::inOrder(node *ptr)
{
	if (ptr == NULL)
		return;
	inOrder(ptr->L);
	cout << ptr->num << "\t" << ptr->h << endl;
	inOrder(ptr->R);
}

void AVL::checkHight(node *&ptr)
{
	int r = 0, l = 0, res = 0;
	if (ptr->R == NULL)
	{
		r = -1;
	}
	else
	{
		r = ptr->R->h;
	}
	if (ptr->L == NULL)
	{
		l = -1;
	}
	else
	{
		l = ptr->L->h;
	}
	res = l - r;
	res = abs(res);
	if (res == 2)
	{
		if (l > r)
		{
			checkCase(ptr, 1);
		}
		else
		{
			checkCase(ptr, 0);
		}
	}
}

int AVL::height(node *ptr)
{
	if (ptr == NULL)
		return -1;
	else
		return ptr->h;
}

int AVL::max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

void AVL::checkCase(node *&ptr, int n)
{
	if (n == 0)
	{
		if (ptr->R->num >= num)
		{
			ptr = rotateRight(ptr->R);
			ptr = rotataLeft(ptr);
		}
		else
		{
			ptr = rotataLeft(ptr);
		}
	}
	else if (n == 1)
	{
		if (ptr->L->num >= num)
		{
			ptr = rotataLeft(ptr->L);
			ptr = rotateRight(ptr);
		}
		else
		{
			ptr = rotateRight(ptr);
		}
	}
}

void AVL::deleteNode()
{
	cout << "Enter Key to search:\n"; int num;
	cin >> num;
	searchn(num, root);
	//cout << "Data Not Found:\n";
}

void AVL::searchn(int num, node *&ptr)
{
	if (ptr == NULL)
	{
		cout << "Number Not Found:\n";
		return;
	}
	else if (ptr->num == num)
	{
		deleten(ptr);
		return;
	}
	else if (num > ptr->num)
	{
		searchn(num, ptr->R);
	}
	else if (num < ptr->num)
	{
		searchn(num, ptr->L);
	}
}

void AVL::deleten(node *&ptr1)
{
	bool flag = 0;
	if (ptr1->L == NULL && ptr1->R == NULL)
	{
		node *temp = ptr1;
		ptr1 = ptr1->R;
		delete temp;
		flag = 1;
	}
	else if (ptr1->L == NULL)
	{
		node *temp = ptr1;
		ptr1 = ptr1->R;
		delete temp;
	}
	else if (ptr1->R == NULL)
	{
		node *temp = ptr1;
		ptr1 = ptr1->L;
		delete temp;
	}
	else
	{
		node *temp = ptr1;
		temp = temp->R;
		while (temp->L != NULL)
		{
			temp = temp->L;
		}
		temp->L = ptr1->L;
		temp = ptr1;
		ptr1 = ptr1->R;
		delete temp;
	}
	if (flag == 0)
	{
		ptr1->h = max(height(ptr1->L), height(ptr1->R)) + 1;
		checkHight(ptr1);
	}
}

void AVL::callArray(int num)
{
	arr[as] = num;
	as++;
}

void AVL::search()
{
	int no = 0;
	cout << "Enter number to search:"; int num;
	cin >> num;
	node *ptr = root;
	while (ptr != NULL)
	{
		if (ptr->num == num)
		{
			cout << "Number Found:\n";
			cout << "HEIGHT for root:" << root->h - ptr->h << "\tNumber of nodes:" << no << endl;
			return;
		}
		if (num > ptr->num)
		{
			ptr = ptr->R;
			no++;
		}
		else
		{
			ptr = ptr->L;
			no++;
		}
	}
	cout << "Number Not Found:\n";
}

void AVL::preOrder()
{
	pre(root);
	cout << "Array After changing\n";
	for (int i = 0; i < as; i++)
		cout << arr[i] << endl;
}

void AVL::pre(node *ptr)
{
	if (ptr == NULL)
		return;
	callArray(ptr->num);
	pre(ptr->L);
	pre(ptr->R);
}

void AVL::rotateArray()
{
	cout << "Enter Length of Array:"; int len;
	cin >> len;
	arr = new int[len];
	for (int i = 0; i < len; i++)
	{
		cout << "Enter number";
		cin >> num;
		arr[i] = num;
		insertArray(num);
	}
	cout << "Array Entered:\n";
		for (int i = 0; i < len; i++)
		{
			cout << arr[i] << endl;
		}
		preOrder();
}

void AVL::insertArray(int num)
{
	node *ptr = new node;
	ptr->num = num;
	ptr->L = NULL;
	ptr->R = NULL;
	ptr->h = 0;
	if (root == NULL)
	{
		root = ptr;
	}
	else
	{
		in(root, ptr);
	}
}

void AVL::findShortestPath()
{
	int n = root->h;
	int boola = 0;
	arr = new int[n * 3];
	pre(root);
	cout << "Enter First number to search:"; int num1;
	cin >> num1;
	cout << "Enter second number to search:"; int num2;
	cin >> num2;
	for (int i = 0; i < as; i++)
	{
		if (boola == 0)
		{
			if (arr[i] == num1)
			{
				boola = 1;
				cout << arr[i] << "\t";
			}
			if (arr[i] == num2)
			{
				boola = 2;
				cout << arr[i] << "\t";
			}
		}
		else if (boola == 1)
		{
			cout << arr[i] << "\t";
			if (arr[i] == num2)
			{
				cout<< "\n";
				break;
			}
		}
		else if (boola == 2)
		{
			cout << arr[i] << "\t";
			if (arr[i] == num1)
			{
				cout<< "\n";
				break;
			}
		}
	}
}

void AVL::post(node *ptr)
{
	if (ptr == NULL)
		return;
	post(ptr->L);
	post(ptr->R);
	callArray(ptr->num);
}

void AVL::inO(node *ptr)
{
	if (ptr == NULL)
		return;
	inO(ptr->L);
	callArray(ptr->num);
	inO(ptr->R);
}

void AVL::compareArray()
{
	cout << "Enter size of Array:"; int nu;
	cin >> nu;
	arr = new int[nu];
	int *arr1 = new int[nu];
	for (int i = 0; i < nu; i++)
	{
		cout << "Enter Array elements:";
		cin >> arr1[i];
	}
	cout << "Enter traversal method\nA\tpreorder\nB\tpostorder\nC\tInorder\n:";
	char sel;
	cin >> sel;
	sel = toupper(sel);
	if (sel == 'A')
		pre(root);
	else if (sel == 'B')
		post(root);
	else if (sel == 'C')
		inO(root);
	else
	{
		cout << "Invalid choice:\n";
		return;
	}
	int i;
	for (i = 0; i < nu; i++)
	{
		if (arr[i] != arr1[i])
		{
			cout << "Incorrect:\n";
			return;
		}
	}
	cout << "correct:\n";
}