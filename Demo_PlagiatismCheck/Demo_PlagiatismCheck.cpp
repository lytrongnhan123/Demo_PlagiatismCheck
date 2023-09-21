#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

struct Node
{
	string Data;
	Node* Next;
};
void convertList(string f, Node*& head)
{
	Node* Tail;
	if (head == nullptr)
	{
		head = new Node;
		head->Data = f;
		head->Next = nullptr;
	}
	else
	{
		Node* temp;
		temp = head;
		while (temp->Next != nullptr)
		{
			temp = temp->Next;
		}
		Tail = temp;
		temp = new Node;
		temp->Data = f;
		temp->Next = nullptr;
		Tail->Next = temp;
		Tail = temp;
	}
}
void Display(Node& head)
{ 
	Node p = head;
	while ((&p) != nullptr)
	{
		cout << p.Data << "\n\n";
		if (p.Next == nullptr)
			break;
		p = *(p.Next);
	}
}
void dive(string& a, vector<string>& b)
{
	string temp = "";
	for (int i = 0; i < (unsigned)a.length(); i++)
	{
		if (a[i] == ' ' || i == (a.length() - 1))
		{
			b.push_back(temp);
			temp = "";
		}
		else
		{
			temp += a[i];
		}
	}
}
double JaroWinkler(string a, string b)
{
	vector<string> s1;
	vector<string> s2;
	dive(a, s1);
	dive(b, s2);
	int max_dist = floor(max(s1.size(), s2.size())) - 1;
	int match = 0;
	const int  len1 = s1.size(),
		len2 = s2.size();
	int* hash_s1 = new int[len1];
	for (auto i = 0; i < len1; i++)
	{
		hash_s1[i] = 0;
	}
	int* hash_s2 = new int[len2];
	for (auto i = 0; i < len2; i++)
	{
		hash_s2[i] = 0;
	}
	for (auto i = 0; i < len1; i++)
	{
		for (auto j = max(0, i - max_dist); j < min(len2, i + max_dist + 1); j++)
		{
			if (s1.at(i) == s2.at(j) && hash_s2[j] == 0)
			{
				hash_s1[i] = 1;
				hash_s2[j] = 1;
				match++;
				break;
			}
		}
	}

	if (match == 0)
	{
		return match;
	}

	double t = 0;
	int point = 0;

	for (int i = 0; i < len1; i++)
	{
		if (hash_s1[i])
		{
			while (hash_s2[point] == 0)
			{
				point++;
				if (s1.at(i) != s2.at(point++))
				{
					t++;
				}
			}
		}
	}
	delete(hash_s1);
	delete(hash_s2);
	t /= 2;
	return(((double)match) / ((double)len1)
		+ ((double)match) / ((double)len2)
		+ ((double)match - t) / ((double)match))
		/ 3;
}
int check(string str, Node* head)
{
	int count = 0;
	Node* temp = head;
	while (temp != nullptr)
	{
		if (JaroWinkler(str, temp->Data) > double(0.5))
			count++;

		temp = temp->Next;
	}
	return count;
	
}
void Paragraphlist(Node* PaList_f1, Node*& PaList_f2)
{
	Node* temp;
	temp = PaList_f1;
	while (temp != nullptr)
	{
		if (PaList_f2 == nullptr)
			convertList(temp->Data, PaList_f2);
		else if (PaList_f2 != nullptr && check(temp->Data, PaList_f2) == 0)
			convertList(temp->Data, PaList_f2);

		temp = temp->Next;
	}
}
void Result(Node* PaList_f1, Node* PaList_f2, Node* PaList)
{
	double sum=0;
	double u=0,v=0;
	vector<int> vct1;
	vector<int> vct2;
	Node* temp = PaList;
	while (temp != nullptr)
	{
		if (check(temp->Data, PaList_f1) > 0)
			vct1.push_back(check(temp->Data, PaList_f1));
		else
			vct1.push_back(0);

		temp = temp->Next;
	}
	while (PaList != nullptr)
	{
		if (check(PaList->Data, PaList_f2) > 0)
			vct2.push_back(check(PaList->Data, PaList_f2));
		else
			vct2.push_back(0);

		PaList = PaList->Next;
	}
	for (int i = 0; i < vct1.size(); i++)
	{
		sum += (vct1[i]*vct2[i]);
		u += (vct1[i]*vct1[i]);
		v += (vct2[i]*vct2[i]);
	}
	double T = (double)sum / (sqrt(u) + sqrt(v));
	cout << "\nMuc do tuong tu giua hai van ban: " << T<<"\n";
}
int main()
{
	string f1;
	string f2;
	Node* Pa_list = nullptr;
	Node* PaList_f1 = nullptr;
	Node* PaList_f2 = nullptr;
	ifstream file1;
	ifstream file2;
	file1.open("data1.txt", ios::in);
	file2.open("data2.txt", ios::in);
	string str1 = "";
	string str2 = "";
	int count = 0;
	while (!(file1.eof()))
	{
		getline(file1, f1);
		str1 += f1;
		if (f1 != "" && f1[f1.size() - 1] == '.')
		{
			convertList(str1, PaList_f1);
			str1 = "";
		}
	}
	if(str1 != "")
		convertList(str1, PaList_f1);
	while (!(file2.eof()))
	{
		getline(file2, f2);
		str2 += f2;
		if (f2 != "" && f2[f2.size() - 1] == '.')
		{
			convertList(str2, PaList_f2);
			str2 = "";
		}
	}
	if (str2 != "")
		convertList(str2, PaList_f2);

	Paragraphlist(PaList_f1, Pa_list);
	Paragraphlist(PaList_f2, Pa_list);
	Result(PaList_f1, PaList_f2, Pa_list);
//	Display(*Pa_list);
	return 0;
}
