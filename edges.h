#pragma once

struct edge
{
	int from, to, cost;
	edge* next;
};

class edges
{
private:
	edge* head, * tail, * iterator;
	int edgesAmount;

public:
	edges()
	{
		head = nullptr;
		tail = nullptr;
		iterator = head;
		edgesAmount = 0;
	}

	~edges()
	{
		head = nullptr;
		tail = nullptr;
		iterator = nullptr;
	}

	void pushBack(int fromInput, int toInput, int costInput)
	{
		if (head)
		{
			edge* newEdge = new edge;
			newEdge->from = fromInput;
			newEdge->to = toInput;
			newEdge->cost = costInput;
			newEdge->next = nullptr;
			tail->next = newEdge;
			tail = newEdge;
			edgesAmount++;
		}
		else
		{
			head = new edge;
			head->next = nullptr;
			tail = head;
			head->from = fromInput;
			head->to = toInput;
			head->cost = costInput;
			edgesAmount++;
		}
	}

	int edgesAmountGet()
	{
		return edgesAmount;
	}

	void refreshIterator()
	{
		iterator = head;
	}

	void iteration()
	{
		if (iterator->next) iterator = iterator->next;
	}

	void getIterator(int& fromOutput, int& toOutput, int& costOutput)
	{
		fromOutput = iterator->from;
		toOutput = iterator->to;
		costOutput = iterator->cost;
	}
};