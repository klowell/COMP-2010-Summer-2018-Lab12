/*****************************************************************************************
Project Name: Lab 12
Name: Kristopher Lowell
Date Completed: 8/10/2018
Purpose: Given two strings, find all the longest matching substrings allowing for gaps.
*****************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void get_strings(string *str1, string *str2);

int longer_string(string *str1, string *str2);

vector <string> get_fwd_lmsafg(string str1, string str2);

string reverse_string(string str);
vector <string> get_rev_lmsafg(string str1, string str2);

vector <string> consolidate_lmsafg(vector <string> *fwd, vector <string> *rev);

void print_lmsafg(vector <string> *list);


int main(int argc, char *argv[])
{

	string str1, str2;

	get_strings(&str1, &str2);

	vector <string> fwd, rev;

	if (longer_string(&str1, &str2) > 0)
	{
		fwd = get_fwd_lmsafg(str1, str2);
		rev = get_rev_lmsafg(str1, str2);
	}
	else
	{
		fwd = get_fwd_lmsafg(str2, str1);
		rev = get_rev_lmsafg(str2, str1);

	}

	vector <string> all = consolidate_lmsafg(&fwd, &rev);

	print_lmsafg(&all);

	cin >> str1;
}

void get_strings(string *str1, string *str2)
{
	cout << "Enter the first string: ";
	cin >> *str1;

	cout << "Enter the second string: ";
	cin >> *str2;
}

int longer_string(string *str1, string *str2)
{
	return (int)str1->length() - (int)str2->length();
}

vector <string> get_fwd_lmsafg(string str1, string str2)
{
	vector <string> list, tried, temp, lmsafg;

	string buffer, test;

	char ch1, ch2;

	unsigned longest = 0;

	bool already;

	for (unsigned start = 0; start < str1.length() - longest + 1; start++)
	{
		for (unsigned i = start; i < str1.length(); i++)
		{
			ch1 = str1[i];
			buffer.push_back(ch1);
			test.push_back(ch1);

			already = false;
			for (unsigned j = 0; j < tried.size() && !already; j++)
				if (buffer == tried[j])
					already = true;

			if (!already)
			{
				tried.push_back(buffer);

				for (int j = (int)str2.length() - 1; j >= 0 && !test.empty(); j--)
				{
					ch2 = str2[j];
					if (ch2 == test.back())
						test.pop_back();
				}

				if (test.empty())
				{
					test.append(buffer);
					list.push_back(buffer);
					temp.push_back(buffer);

					if (buffer.length() >= longest)
						longest = buffer.length();
				}
				else
				{
					buffer.pop_back();
					test.clear();
					test.append(buffer);
				}
			}
			else
			{
				buffer.pop_back();
				test.pop_back();
			}

			if (i == str1.length() - 1 && temp.size() > 1)
			{
				temp.pop_back();
				buffer.clear();
				test.clear();
				buffer.append(temp.back());
				test.append(buffer);

				i = start;
				for (unsigned j = 0; j < buffer.length(); j++)
				{
					for (unsigned k = i; k < str1.length(); k++)
					{
						if (str1[k] != buffer[j])
							i++;
						else
							k = str1.length();
					}
				}
			}
			else if (i == str1.length() - 1 && temp.size() == 1)
				temp.pop_back();
		}

		buffer.clear();
		test.clear();
		temp.clear();
	}

	for (unsigned i = 0; i < list.size(); i++)
		if (list[i].length() == longest)
			lmsafg.push_back(list[i]);

	return lmsafg;
}

string reverse_string(string str)
{
	string result;

	for (int i = (int)str.length() - 1; i >= 0; i--)
		result.push_back(str[i]);

	return result;
}

vector <string> get_rev_lmsafg(string str1, string str2)
{
	str1 = reverse_string(str1);
	str2 = reverse_string(str2);

	return get_fwd_lmsafg(str1, str2);
}

vector <string> consolidate_lmsafg(vector <string> *fwd, vector <string> *rev)
{
	vector <string> all;
	bool duplicate;

	for (unsigned i = 0; i < fwd->size(); i++)
		all.push_back(fwd->at(i));

	for (unsigned i = 0; i < rev->size(); i++)
	{
		duplicate = false;

		for (unsigned j = 0; j < all.size() && !duplicate; j++)
			if (all[j] == rev->at(i))
				duplicate = true;

		if (!duplicate)
			all.push_back(rev->at(i));
	}

	return all;
}

void print_lmsafg(vector <string> *list)
{
	cout << endl << endl << "Longest Matching Substrings Allowing For Gaps:" << endl;

	for (unsigned i = 0; i < list->size() - 1; i++)
		cout << list->at(i) << ", ";

	cout << list->back() << endl;
}