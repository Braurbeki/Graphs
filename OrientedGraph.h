#include <iostream>
#include <vector>
#include<map>
#include<iomanip>
using namespace std;

class OrientedGraph
{
private:
	//Указатели на двумерные массивы для хранения матриц инциндентности и смежности
	int** incidenceMatrix, ** adjacencyMatrix;
	//Список вершин
	vector<pair<int, int>> edgesList;
	//Список смежностей
	map<int, vector<int>> adjacencyList;
	//Константы: кол-во вершин 6, кол-во ребёр - 13
	const int numV = 6, numEdges = 14;

	//Выделение памяти под матрицу инциндентности
	void initIncidenceMatrix()
	{
		incidenceMatrix = new int* [numV];
		for (int i = 0; i < numV; i++)
		{
			incidenceMatrix[i] = new int[numEdges];
		}
		fulfillIncidenceMatrix();
	}

	//Заполнение матрицы инциндентности
	//Note: Изначальная иницализация графа происходит именно в матрице инциндентности
	void fulfillIncidenceMatrix()
	{
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				incidenceMatrix[i][j] = 0;
			}
		}
		incidenceMatrix[0][0] = 2;
		incidenceMatrix[0][1] = 1;
		incidenceMatrix[0][2] = 1;
		incidenceMatrix[0][3] = 1;

		incidenceMatrix[1][4] = 1;
		incidenceMatrix[1][5] = 1;
		incidenceMatrix[1][7] = -1;
		incidenceMatrix[1][9] = -1;
		incidenceMatrix[1][2] = -1;
		incidenceMatrix[1][11] = -1;

		incidenceMatrix[2][5] = -1;
		incidenceMatrix[2][6] = 1;
		incidenceMatrix[2][7] = 1;
		incidenceMatrix[2][8] = 2;
		incidenceMatrix[2][13] = -1;

		incidenceMatrix[3][1] = -1;
		incidenceMatrix[3][9] = 1;
		incidenceMatrix[3][10] = 1;

		incidenceMatrix[4][3] = -1;
		incidenceMatrix[4][10] = -1;
		incidenceMatrix[4][11] = 1;
		incidenceMatrix[4][12] = -1;
		incidenceMatrix[4][6] = -1;

		incidenceMatrix[5][12] = 1;
		incidenceMatrix[5][4] = -1;
		incidenceMatrix[5][13] = 1;
	}
	//Функция поиска второй вершины. Применяется при работе с матрицей инциндентности
	int findSecondVertex(int curVert, int e)
	{
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				if (incidenceMatrix[i][j] != 0)
				{
					if (e == j && i != curVert)
					{
						return i;
					}
				}
			}
		}
		return curVert;
	}

	//Функция очищения матрицы
	void clearMatrix(int** matrix, int len, int height)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < len; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}
	//Выделение памяти под матрицу смежности
	void initAdjacenyMatrix()
	{
		adjacencyMatrix = new int* [numV];
		for (int i = 0; i < numV; i++)
		{
			adjacencyMatrix[i] = new int[numV];
		}

		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numV; j++)
			{
				adjacencyMatrix[i][j] = 0;
			}
		}
	}

	//Используется для проверки при переходе из матрицы смежности в матрицу инциндентности
	bool incidenceMatrixContaints(int first_vert, int second_vert)
	{
		for (int i = 0; i < numEdges; i++)
		{
			if (incidenceMatrix[first_vert][i] == 1)
			{
				for (int j = 0; j < numEdges; j++)
				{
					if (incidenceMatrix[second_vert][j] == 1 && j == i)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	//Используется для проверки во избежание повторений при заполнении списка вершин
	bool edgesListContains(int first_vert, int second_vert)
	{
		for (auto it = edgesList.begin(); it != edgesList.end(); it++)
		{
			if (it->first == first_vert && it->second == second_vert)
			{
				return true;
			}
		}
		return false;
	}
	//Добавление нового элемента в список смежностей
	void addToAdjensyList(int key_vert, int vert)
	{
		//Получаем элемент контейнера под ключём key_vert
		auto vect = adjacencyList.find(key_vert);
		//Если элемент существует, добавляем к его значению(вектору вершин) новую вершину
		if (vect != adjacencyList.end())
		{
			vect->second.push_back(vert);
		}
		//В противном случае создаём новый элемент контейнера
		else
		{
			vector<int> tmpVect;
			tmpVect.push_back(vert);
			adjacencyList.insert(pair<int, vector<int>>{key_vert, tmpVect});
		}
	}
public:
	//Конструктор: Выделение памяти, инициализация двумерных массивов для хранения матриц смежности и инциндентности
	OrientedGraph()
	{
		initIncidenceMatrix();
		initAdjacenyMatrix();
	}

	//Вывод матрицы инциндентности
	void showIncidenceMatrix()
	{
		cout << endl << "____Incidence Matrix____" << endl;
		for (int i = 0; i < numV; i++)
		{
			cout << "[";
			for (int j = 0; j < numEdges; j++)
			{
				cout << setw(2) << incidenceMatrix[i][j];
				if (j != numEdges - 1) cout << ", ";
			}
			cout << "]" << endl;
		}
	}
	//С помощью матрицы смежности инициализации списка смежностей
	void adjacenyToAdjacenyList()
	{
		adjacencyList.clear();
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numV; j++)
			{
				if (adjacencyMatrix[i][j] == 1)
				{
					addToAdjensyList(i, j);
				}
			}
		}
	}

	//С помощью матрицы инциндентности инициализации списка смежностей
	void incidenceToAdjacenyList()
	{
		adjacencyList.clear();
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				if (incidenceMatrix[i][j] == 1 || incidenceMatrix[i][j] == 2)
				{
					addToAdjensyList(i, findSecondVertex(i, j));
				}
			}
		}
	}
	//С помощью матрицы инциндентности инициализация списка рёбер
	void incidenceToEdgesList()
	{
		edgesList.clear();
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				if (incidenceMatrix[i][j] == 1 || incidenceMatrix[i][j] == 2)
				{
					edgesList.push_back(pair<int, int>{i, findSecondVertex(i, j)});
				}
			}
		}
	}

	//С помощью матрицы смежности инициализация списка рёбер
	void adjacencyToEdgesList()
	{
		edgesList.clear();
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numV; j++)
			{
				if (adjacencyMatrix[i][j] == 1 && !edgesListContains(i, j))
				{
					edgesList.push_back(pair<int, int>{i, j});
				}
			}
		}
	}


	//Перевод матрицы инциндентности в матрицу смежности
	void incidenceToAdjacency()
	{
		for (int i = 0; i < numV; i++)
		{
			for(int j = 0; j < numEdges; j++)
			{
				if (incidenceMatrix[i][j] == 1 || incidenceMatrix[i][j] == 2)
				{
					adjacencyMatrix[i][findSecondVertex(i, j)] = 1;
				}
			}
		}
	}
	//Перевод матрицы смежности в матрицу инциндентности
	void adjencyToIncidence()
	{
		clearMatrix(incidenceMatrix, numEdges, numV);
		int curEdge = 0;
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numV; j++)
			{
				if (i == j && adjacencyMatrix[i][j] == 1)
				{
					incidenceMatrix[i][curEdge] = 2;
					curEdge++;
				}
				else if (adjacencyMatrix[i][j] == 1 && !incidenceMatrixContaints(i, j))
				{
					incidenceMatrix[i][curEdge] = 1;
					incidenceMatrix[j][curEdge] = -1;
					curEdge++;
				}
			}
		}
	}
	//Вывод матрицы смежностей
	void showAdjacencyMatrix()
	{
		cout << endl << "____Adjency Matrix____" << endl;
		for (int i = 0; i < numV; i++)
		{
			cout << "[";
			for (int j = 0; j < numV; j++)
			{
				cout << adjacencyMatrix[i][j];
				if (j != numV - 1) cout << ", ";
			}
			cout << "]" << endl;
		}
	}
	//Вывод списка ребёр
	void showEdgesList()
	{
		cout << endl << "____EDGES LIST____" << endl;
		for (auto it = edgesList.begin(); it != edgesList.end(); it++)
		{
			cout << it->first << "->" << it->second << " ";
		}
		cout << endl;
	}
	//Вывод списка смежностей
	void showAdjanecyList()
	{
		cout << endl << "____Adjanecy LIST____" << endl;
		for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++)
		{
			cout << it->first << ": ";
			for (int i = 0; i < it->second.size(); i++)
			{
				cout << it->second[i] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	//Очищение списка смежностей
	void clearAdjacenyList()
	{
		adjacencyList.clear();
	}
	//Очищение списка ребёр
	void clearEdgesList()
	{
		edgesList.clear();
	}
	//Заполнение нулями матрицы инциндентности
	void clearIncidenceMatrix()
	{
		clearMatrix(incidenceMatrix, numEdges, numV);
	}
	//Заполнение нулями матрицы смежностей
	void clearAdjacenyMatrix()
	{
		clearMatrix(adjacencyMatrix, numV, numV);
	}

	//Поиск в ширину на основе матрицы инциндентности
	void BreadthFirstSearch()
	{
		//вектор результатов
		vector<int> res;
		//"флажок" посещённых вершин
		bool* visited = new bool[numV];
		for (int i = 0; i < numV; i++)
		{
			visited[i] = false;
		}

		stack<int> st;
		//начинаем обход с нулевой вершины
		visited[0] = true;
		st.push(0);
		res.push_back(0);
		//пока стек не пустой
		while (!st.empty())
		{
			//получаем верхний элемент стека
			int vert = st.top();
			//выкидываем верхний элемент из стека
			st.pop();
			//обход матрицы инциндентности
			for (int i = 0; i < numV; i++)
			{
				for (int j = 0; j < numEdges; j++)
				{
					//если вершина стэка инциндентна с ребром, и на соседней вершине не стоит "флажок" visited, добавляем соседа в результирующее дерево 
					if (i == vert && incidenceMatrix[i][j] == 1)
					{
						int second_vert = findSecondVertex(vert, j);
						if (!visited[second_vert])
						{
							//ставим "флажок" на соседа
							visited[second_vert] = true;
							res.push_back(second_vert);
							//пушим соседа в стек
							st.push(second_vert);
						}
					}
				}
			}
		}
		cout << endl << "Breadth first search: ";
		for (int i = 0; i < res.size(); i++)
		{
			cout << res[i];
			if (i != res.size() - 1)
			{
				cout << "->";
			}
		}
	}
	//Поиск в глубину на основе матрицы инциндентности
	//Note: по реализации аналогичный поиску в ширину, однако вершины выкидываются из стека только после завершения построения дерева
	void DepthFirstSearch()
	{
		vector<int> res;
		bool* visited = new bool[numV];
		for (int i = 0; i < numV; i++)
		{
			visited[i] = false;
		}

		stack<int> st;

		visited[0] = true;
		st.push(0);
		res.push_back(0);
		while (!st.empty())
		{
		beginOfCycle:
			int vert = st.top();
			for (int i = 0; i < numV; i++)
			{
				for (int j = 0; j < numEdges; j++)
				{
					if (i == vert && incidenceMatrix[i][j] == 1)
					{
						int second_vert = findSecondVertex(vert, j);
						if (!visited[second_vert])
						{
							visited[second_vert] = true;
							res.push_back(second_vert);
							st.push(second_vert);
							goto beginOfCycle;
						}
					}
				}
			}
			st.pop();
		}
		cout << endl << "Depth first search: ";
		for (int i = 0; i < res.size(); i++)
		{
			cout << res[i];
			if (i != res.size() - 1)
			{
				cout << "->";
			}
		}
	}
};