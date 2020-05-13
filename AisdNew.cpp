#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cmath>
#include "towns.h"
#include "edges.h"
using namespace std;
int inf = 1000000; // value that bigger every weight of edges

void townsInput(towns*& townsList) // function of initializing towns
{
    ifstream file; // input file
    string lineInput, town; // read line and town name
    int length, townRead; // length of line and amount of already read town in line
    file.open("input.txt");
    while (getline(file, lineInput))
    {
        townRead = 0; // its 0 towns read now
        length = lineInput.length(); 
        for (int i = 0; i < length; i++) // for whole line
        {
            if (lineInput[i] == ';') 
            {
                if (townsList->findPosition(town)==-1) townsList->pushBack(town); // if town is not in list - add it
                town = ""; // clear the town line
                townRead++; // one more town read
            }
            else if (townRead<2) // if we need to read one or two towns more
            {
                town += lineInput[i]; // add symbol 
            }
            else break; // if 2 towns read
        }
    }
    file.close();
}

void matrixBuild(int *&matrix, towns *& townsList, int townsAmount) // building the matrix
{
    ifstream file; // input file
    file.open("input.txt");
    string lineInput, townFrom, townTo, costForward, costBack;
    int lastPosition, length, cost, from, to; // last position in line
    for (int i = 0; i < townsAmount; i++)
        for (int j = 0; j < townsAmount; j++)
            matrix[i*townsAmount+j] = inf; // filling the matrix with infinities
    for (int i = 0; i < townsAmount; i++)
        matrix[i*townsAmount+i] = 0; // filling the diagonal elements
    while (getline(file, lineInput))
    {
        townFrom = "";
        townTo = "";
        costForward = "";
        costBack = "";
        length = lineInput.length();
        for (int i = 0; i < length; i++) // reading the first town
        {
            if (lineInput[i] == ';')
            {
                lastPosition = i+1; // setting the position for next town
                break;
            }
            else townFrom += lineInput[i];
        }
        for (int i = lastPosition; i < length; i++) // reading the second town
        {
            if (lineInput[i] == ';')
            {
                lastPosition = i+1;
                break;
            }
            else townTo += lineInput[i];
        }
        for (int i = lastPosition; i < length; i++) // reading the first cost
        {
            if (lineInput[i] == ';')
            {
                lastPosition = i+1;
                break;
            }
            else costForward += lineInput[i];
        }
        for (int i = lastPosition; i < length; i++) // reading the second cost
        {
            if (lineInput[i] == ';') break;
            else costBack += lineInput[i];
        }
        if (costForward != "N/A")
        {
            cost = 0;
            length = costForward.length();
            for (int i = 0; i < length; i++)
            {
                cost += pow(10, length - i - 1) * (costForward[i] + (0 - '0')); // counting the cost from line
            }
            from = townsList->findPosition(townFrom);
            to = townsList->findPosition(townTo);
            if (cost < matrix[from*townsAmount+to]) matrix[from*townsAmount+to] = cost;
        }
        if (costBack != "N/A")
        {
            cost = 0;
            length = costBack.length();
            for (int i = 0; i < length; i++)
            {
                cost += pow(10, length - i - 1) * (costBack[i] + (0 - '0'));
            }
            from = townsList->findPosition(townTo);
            to = townsList->findPosition(townFrom);
            if (cost < matrix[from*townsAmount+to]) matrix[from*townsAmount+to] = cost;
        }
    }
    file.close();
}

void edgesBuild(int* matrix, int townsAmount, edges* edgesList) // building the edges
{
    for (int i=0;i<townsAmount;i++)
        for (int j = 0; j < townsAmount; j++)
        {
            if ((matrix[i * townsAmount + j] < inf) && (matrix[i * townsAmount + j] > 0)) // if weigth is bigger 0 and smaller inf - here is the edge
            {
                edgesList->pushBack(i, j, matrix[i * townsAmount + j]);
            }
        }
}

void bellmanFord(edges* edgesList, towns* townsList, int townsAmount, int lastPoint) // Bellman-Ford algorithm
{
    int* distance = new int[townsAmount]; // shortest distance to each peak
    int* parent = new int[townsAmount]; // previous peak with shortest way
    for (int i = 1; i < townsAmount; i++) distance[i] = inf;
    for (int i = 0; i < townsAmount; i++) parent[i] = inf;
    distance[0] = 0;
    int edgesAmount = edgesList->edgesAmountGet();
    int from, to, cost;
    for (int i = 0; i < townsAmount - 1; i++)
    {
        edgesList->refreshIterator(); // setting iterator on first town
        edgesList->getIterator(from, to, cost); // getting the parameters of town
        if ((distance[from] < inf) && (distance[from] + cost < distance[to])) // if there is path to this peak and this edge is better way - we choose it
        {
            distance[to] = distance[from] + cost;
            parent[to] = from;
        }
        for (int j = 1; j < edgesAmount; j++)
        {
            edgesList->iteration();
            edgesList->getIterator(from, to, cost);
            if ((distance[from] < inf) && (distance[from] + cost < distance[to]))
            {
                distance[to] = distance[from] + cost;
                parent[to] = from;
            }
        }
    }
    if (distance[lastPoint] < inf) // if there is path to this peak
    {
        string path = townsList->getName(lastPoint); // last point is arrival town
        cout << "Общая стоимость перелёта: " << distance[lastPoint] << endl;
        cout << "План перелётов: ";
        while (lastPoint != 0) // while we dont get to start
        {
            path = townsList->getName(parent[lastPoint]) + "->" + path; // add previous peak
            lastPoint = parent[lastPoint]; // set lastPoint to previous peak
        }
        cout << path << endl;
    }

    cout << endl;
    delete[] distance;
    delete[] parent;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    towns* townsList = new towns;
    edges* edgesList = new edges;
    int townsAmount, choose;
    int* matrix;

    townsInput(townsList);
    townsAmount = townsList->townsAmountget();
    townsList->outList();
    cout << "Выберите город для отправления (введите номер): ";
    cin >> choose;
    while ((choose < 1) || (choose > townsAmount))
    {
        cout << "Ошибка ввода, повторите попытку" << endl;
        cin >> choose;
    }
    townsList->setStartTown(choose-1); // set departure town
    cout << endl;
    townsList->outList();
    cout << endl;
    cout << "Выберите город прибытия (введите номер): ";
    cin >> choose;
    while ((choose < 1) || (choose > townsAmount))
    {
        cout << "Ошибка ввода, повторите попытку" << endl;
        cin >> choose;
    }
    cout << endl;

    matrix = new int[townsAmount * townsAmount];
    matrixBuild(matrix, townsList, townsAmount);
    cout << "Matrix:" << endl;
    for (int i = 0; i < townsAmount; i++)
    {
        for (int j = 0; j < townsAmount; j++)
        {
            if (matrix[i * townsAmount + j] == inf) cout << "inf ";
            else cout << matrix[i * townsAmount + j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    edgesBuild(matrix, townsAmount, edgesList);
    bellmanFord(edgesList, townsList, townsAmount, choose-1); // last parameter is number of arrival town

    delete townsList;
    delete edgesList;
    return 0;
}
