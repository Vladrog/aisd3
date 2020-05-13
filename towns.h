#pragma once
#include <iostream>
using namespace std;

struct town
{
	string name;
	town* next;
};

class towns
{
private:
	town* head, * tail;
	int townsAmount;

public:
	towns()
	{
		head = nullptr;
		tail = nullptr;
		townsAmount = 0;
	}

	~towns()
	{
		head = nullptr;
		tail = nullptr;
	}

	void pushBack(string townName)
	{
		if (!head)
		{
			head = new town;
			tail = head;
			head->next = nullptr;
			head->name = townName;
			townsAmount++;
		}
		else
		{
			town *newTown = new town;
			tail->next = newTown;
			newTown->next = nullptr;
			newTown->name = townName;
			tail = newTown;
			townsAmount++;
		}
	}

	int findPosition(string townName) // if town is not in list - returning -1, else returning its position
	{
		if (head)
		{
			town* current;
			int position = 0;
			current = head;
			if (current->name == townName) return position;
			while (current != tail)
			{
				current = current->next;
				position++;
				if (current->name == townName) return position;
			}
			return -1;
		}
		else return -1;
	}

	int townsAmountget()
	{
		return townsAmount;
	}

	void setStartTown(int number) // setting the departure town
	{
		town* buf, *current;
		town* previous = head;
		if (number != 0)
		{
			for (int i = 0; i < number - 1; i++)
			{
				previous = previous->next;
			}
			if (previous->next != tail) // if departure town is not in the end of list
			{
				current = previous->next;
				previous->next = head;
				buf = head->next;
				head->next = current->next;
				current->next = buf;
				head = current;
			}
			else
			{
				current = previous->next;
				previous->next = head;
				current->next = head->next;
				head->next = nullptr;
				tail = head;
				head = current;
			}
		}
	}

	string getName(int number)
	{
		if (head)
		{
			town* current = head;
			for (int i = 0; i < number; i++)
				current = current->next;
			return current->name;
		}
	}

	void outList()
	{
		if (head)
		{
			cout << "Towns:" << endl;
			town* current = head;
			cout << "1) " << current->name << endl;
			for (int i = 1; i < townsAmount; i++)
			{
				current = current->next;
				cout << i + 1 << ") " << current->name << endl;
			}
		}
	}
};