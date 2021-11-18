#include "FileWorker.h"

FileWorker::FileWorker(string name)
{
	filename = name;
}

Graph FileWorker::read_graph()
{
	ifstream fin;
	fin.open(filename);
	int size;
	fin >> size;
	Graph graph(size);

	int element;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fin >> element;
			graph.set_element(i, j, element);
		}

	}
	
	fin.close();

	return graph;
}

void FileWorker::write_graph(Graph& graph)
{
	ofstream fout;
	fout.open(filename);
	fout << graph.get_size() << "\n";
	for (int i = 0; i < graph.get_size(); i++)
	{
		for (int j = 0; j < graph.get_size(); j++)
		{
			fout << graph.get_element(i, j) << " ";
		}
		fout << "\n";
	}
	fout.close();
}


