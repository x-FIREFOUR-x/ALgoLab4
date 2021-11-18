#pragma once
#include <string>
#include <fstream>
#include "Graph.h"
#include "Algorithm.h"
using namespace std;
class FileWorker
{
	string filename;			// ім'я файла
public:
	FileWorker(string name);
	Graph read_graph();			// зчитати граф в файлі
	void write_graph(Graph& graph);												// записати граф в файл
};


