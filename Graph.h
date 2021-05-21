#include <iostream>
#include <vector>
#include<map>
#include<stack>
using namespace std;

class Graph
{
private:
	//��������� �� ��������� ������� ��� �������� ������ �������������� � ���������
	int** incidenceMatrix, **adjacencyMatrix;
	//������ ������
	vector<pair<int, int>> edgesList;
	//������ ����������
	map<int, vector<int>> adjacencyList;
	//���������: ���-�� ������ 6, ���-�� ���� - 13
	const int numV = 6, numEdges = 13;

	//��������� ������ ��� ������� ��������������
	void initIncidenceMatrix()
	{
		incidenceMatrix = new int* [numV];
		for (int i = 0; i < numV; i++)
		{
			incidenceMatrix[i] = new int[numEdges];
		}
		fulfillIncidenceMatrix();
	}

	//���������� ������� ��������������
	//Note: ����������� ������������ ����� ���������� ������ � ������� ��������������
	void fulfillIncidenceMatrix()
	{
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				incidenceMatrix[i][j] = 0;
			}
		}
		incidenceMatrix[0][0] = 1;
		incidenceMatrix[0][1] = 1;
		incidenceMatrix[0][2] = 1;

		incidenceMatrix[1][0] = 1;
		incidenceMatrix[1][3] = 1;
		incidenceMatrix[1][4] = 1;
		incidenceMatrix[1][5] = 1;
		incidenceMatrix[1][6] = 1;

		incidenceMatrix[2][7] = 1;
		incidenceMatrix[2][8] = 1;
		incidenceMatrix[2][3] = 1;

		incidenceMatrix[3][2] = 1;
		incidenceMatrix[3][9] = 1;
		incidenceMatrix[3][10] = 1;
		incidenceMatrix[3][6] = 1;

		incidenceMatrix[4][1] = 1;
		incidenceMatrix[4][5] = 1;
		incidenceMatrix[4][8] = 1;
		incidenceMatrix[4][11] = 1;
		incidenceMatrix[4][9] = 1;

		incidenceMatrix[5][11] = 1;
		incidenceMatrix[5][4] = 1;
		incidenceMatrix[5][7] = 1;
		incidenceMatrix[5][12] = 1;
	}
	//������� ������ ������ �������. ����������� ��� ������ � �������� ��������������
	int findSecondVertex(int curVert, int e)
	{
		int secondIndex = 0;
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				if (curVert != i && j == e && incidenceMatrix[i][j] == 1)
				{
					return i;
				}
				else if (curVert == i && j == e && incidenceMatrix[i][j] == 1)
				{
					secondIndex = i;
				}
			}
		}
		return secondIndex;
	}

	//������� �������� �������
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
	//��������� ������ ��� ������� ���������
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

	//������������ ��� �������� ��� �������� �� ������� ��������� � ������� ��������������
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
	//������������ ��� �������� �� ��������� ���������� ��� ���������� ������ ������
	bool edgesListContains(int first_vert, int second_vert)
	{
		for (auto it = edgesList.begin(); it != edgesList.end(); it++)
		{
			if (it->first == first_vert && it->second == second_vert)
			{
				return true;
			}
			else if (it->first == second_vert && it->second == first_vert)
			{
				return true;
			}
		}
		return false;
	}
	//���������� ������ �������� � ������ ����������
	void addToAdjensyList(int key_vert, int vert)
	{
		//�������� ������� ���������� ��� ������ key_vert
		auto vect = adjacencyList.find(key_vert);
		//���� ������� ����������, ��������� � ��� ��������(������� ������) ����� �������
		if (vect != adjacencyList.end())
		{
			vect->second.push_back(vert);
		}
		//� ��������� ������ ������ ����� ������� ����������
		else
		{
			vector<int> tmpVect;
			tmpVect.push_back(vert);
			adjacencyList.insert(pair<int, vector<int>>{key_vert, tmpVect});
		}
	}
public:
	//�����������: ��������� ������, ������������� ��������� �������� ��� �������� ������ ��������� � ��������������
	Graph()
	{
		initIncidenceMatrix();
		initAdjacenyMatrix();
	}
	
	//����� ������� ��������������
	void showIncidenceMatrix()
	{
		cout << endl << "____Incidence Matrix____" << endl;
		for (int i = 0; i < numV; i++)
		{
			cout << "[";
			for (int j = 0; j < numEdges; j++)
			{
				cout << incidenceMatrix[i][j];
				if(j != numEdges - 1) cout << ", ";
			}
			cout << "]" << endl;
		}
	}
	//� ������� ������� ��������� ������������� ������ ����������
	void adjacenyToAdjacenyList()
	{
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

	//� ������� ������� �������������� ������������� ������ ����������
	void incidenceToAdjacenyList()
	{
		adjacencyList.clear();
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				if (incidenceMatrix[i][j] == 1)
				{
					addToAdjensyList(i, findSecondVertex(i, j));
				}
			}
		}
	}
	//� ������� ������� �������������� ������������� ������ ����
	void incidenceToEdgesList()
	{
		edgesList.clear();
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				if (incidenceMatrix[i][j] == 1)
				{
					edgesList.push_back(pair<int, int>{i, findSecondVertex(i, j)});
				}
			}
		}
	}

	//� ������� ������� ��������� ������������� ������ ����
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

	
	//������� ������� �������������� � ������� ���������
	void incidenceToAdjacency()
	{
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numEdges; j++)
			{
				if (incidenceMatrix[i][j] == 1)
				{
					adjacencyMatrix[i][findSecondVertex(i, j)] = 1;
				}
			}
		}
	}
	//������� ������� ��������� � ������� ��������������
	void adjencyToIncidence()
	{
		clearMatrix(incidenceMatrix, numEdges, numV);
		int curEdge = 0;
		for (int i = 0; i < numV; i++)
		{
			for (int j = 0; j < numV; j++)
			{
				if (adjacencyMatrix[i][j] == 1 && !incidenceMatrixContaints(i, j))
				{
					incidenceMatrix[i][curEdge] = 1;
					incidenceMatrix[j][curEdge] = 1;
					curEdge++;
				}
				else if (i == j && adjacencyMatrix[i][j] == 1)
				{
					incidenceMatrix[i][curEdge] = 1;
					curEdge++;
				}
			}
		}
	}
	//����� ������� ����������
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
	//����� ������ ����
	void showEdgesList()
	{
		cout << endl << "____EDGES LIST____" << endl;
		for (auto it = edgesList.begin(); it != edgesList.end(); it++)
		{
			cout << it->first << "-" << it->second << " ";
		}
		cout << endl;
	}
	//����� ������ ����������
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

	void clearAdjacenyList()
	{
		adjacencyList.clear();
	}
	
	void clearEdgesList()
	{
		edgesList.clear();
	}

	void clearIncidenceMatrix()
	{
		clearMatrix(incidenceMatrix, numEdges, numV);
	}

	void clearAdjacenyMatrix()
	{
		clearMatrix(adjacencyMatrix, numV, numV);
	}

	//����� � ������ �� ������ ������� ��������������
	void BreadthFirstSearch()
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
			int vert = st.top();
			st.pop();
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
	//����� � ������� �� ������ ������� ��������������
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
			st.pop();
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