#include "headers/IncidenceMatrix.hpp"

IncidenceMatrix::IncidenceMatrix(std::vector<std::vector<int>> const &initializer) : matrix(initializer)
{
    if(initializer.size() > 0)
        _n = initializer[0].size();
    else
        _n = 0;
}

IncidenceMatrix &IncidenceMatrix::loadFromFile(const std::string fileName)
{
    
    IncidenceMatrix *incidenceMatrix = new IncidenceMatrix();
    std::fstream file(fileName);
    incidenceMatrix -> matrix.clear();
    std::string str;
    int i = 0;
    while(getline(file, str))
    {
        incidenceMatrix -> matrix.push_back(std::vector<int>());
        std::istringstream line(str);
        int variable;
        while(line >> variable)
        {
            incidenceMatrix -> matrix[i].push_back(variable);
        }
        i++;     
    }
    incidenceMatrix -> _n = incidenceMatrix -> matrix.size();
    return *incidenceMatrix;
}

Graph &IncidenceMatrix::addVertex()
{
    _n++;
    std::vector<int> newRow;
    newRow.resize(matrix[0].size());
    matrix.push_back(newRow);

    return *this;
}

Graph &IncidenceMatrix::addEdge(int firstVertex, int secondVertex)
{
    bool edgeAlreadyExists = false;
    for(int i = 0; i < _n; i++)
    {
        if(matrix[firstVertex][i] == 1 && matrix[secondVertex][i] == 1)
        {
            edgeAlreadyExists = true;
        }   
    }
    if(!edgeAlreadyExists)
    {    
        for (unsigned int i = 0; i < matrix.size(); ++i)
        {
            if(i == firstVertex || i == secondVertex)
                matrix[i].push_back(1);
            else
                matrix[i].push_back(0);
        }
    }
    return *this;
}

Graph &IncidenceMatrix::removeEdge(int firstVertex, int secondVertex)
{
    for(int column = 0; column < matrix[0].size(); column++)
    {
        if(matrix[firstVertex][column] == 1 && matrix[secondVertex][column] == 1)
        {
            for(int row = 0; row < _n; row++)
                matrix[row].erase(matrix[row].begin()+column);
            break;
        }
    }
    return *this;
}

AdjacencyList IncidenceMatrix::convertToList() const
{
    const int numberOfEdges = matrix[0].size();
    std::vector<std::list<int>> list(_n);
    int first, second;
    for (int column = 0; column < numberOfEdges; ++column)
    {
        first = -1;
        second = -1;
        for (int row = 0; row < _n; ++row)
        {
            if (matrix[row][column] > 0 && first < 0)
                first = row;
            else if (matrix[row][column] > 0 && second < 0) 
            {
                second = row;
        
                //zaklada ze graf jest prosty
                list[first].push_back(second);
                list[second].push_back(first);
                list[first].sort();
                list[second].sort();
                list[first].unique();
                list[second].unique();
                break;
            }
        }
    }
    
    return AdjacencyList(list);
};

Graph &IncidenceMatrix::convertFromList(AdjacencyList const &adjacencyList)
{
    auto list = adjacencyList.getList();
    _n = list.size();
    matrix.clear();
    matrix.resize(_n);
    for (int first = 0; first < _n; first++)
    {
        for (int second : list[first])
        {
            std::cout<< first << " " << second <<std::endl;
            addEdge(first, second);
        }
    }
    return *this;
};

std::ostream &IncidenceMatrix::print(std::ostream &o) const
{
    for(int i = 0; i < (int)matrix.size(); i++)
    {
        for(int j = 0; j < (int)matrix[i].size(); j++)
            o << matrix[i][j] << "\t";
        o << "\n";
    }
    return o;
}

std::ostream &IncidenceMatrix::printToFile(std::ostream &o) const
{
    return convertToList().printToFile(o);
}
