#pragma once
#include <iostream>
#include "FileWorker.h"
#include "Algorithm.h"
using namespace std;
class Interface
{
public:
	void console_interface();				// консольний ≥нтерфейс програми
private:
	void write_graph(Graph graph);				// вивести граф на екран
	void write_cliques(Algorithm algo);			// вивести попул€ц≥ю(кл≥ки) на екран
};

