#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <stack>

class AdjacencyList;
class AdjacencyMatrix;

class Graph
{
public:
    /**
     * Destruktor dla klas potomnych.
*/
    virtual ~Graph() = default;

    /**
     * Dodaje wierzcholek na koniec grafu.
*/
    virtual Graph &addVertex() = 0;

    /**
     * Dodaje wiele wierzcholkow na koniec grafu.
     * @param vertices Ilosc wierzcholkow do dodania.
*/
    virtual Graph &addVertex(unsigned int vertices);

    /**
     * Dodaje krawedz miedzy podanymi wierzcholkami.
*/
    virtual Graph &addEdge(int firstVertex, int secondVertex) = 0;

    /*
    *   Usuwa krawędź pomiędzy podanymi wierzchołkami
    */
    virtual Graph &removeEdge(int firstVertex, int secondVertex) = 0;
    /**
     * Konwertuje graf do listy sasiedztwa.
     * @return Lista sasiedztwa.
*/
    virtual AdjacencyList convertToList() const = 0;

    /**
     * Zmienia graf na podstawie listy sasiedztwa.
     * @param adjacencyList Lista sasiedztwa, na podstawie ktorej zostanie zmieniony graf.
*/
    virtual Graph &convertFromList(AdjacencyList const &adjacencyList) = 0;

/**
     * Wypisyje graf do strumienia w surowej postaci listy/macierzy.
     * @param o Strumien, do ktorego wpisywany jest ciag znakow.
*/
    virtual std::ostream &print(std::ostream &o) const = 0;

    /**
     * Wypisyje graf do strumienia dla programu gnuplot.
     * @param o Strumien, do ktorego wpisywany jest ciag znakow.
     * @see AdjacencyList::printToFile
*/
    virtual std::ostream &printToFile(std::ostream &o) const = 0;

    /**
     * Wypisyje graf do strumienia dla programu gnuplot.
     * @param o Strumien, do ktorego wpisywany jest ciag znakow.
*/
    friend std::ostream &operator<<(std::ostream &o, Graph const *graph);

    /**
     * Konwertuje dowolna reprezentacje grafu na inna - tez dowolna reprezentacje.
     * @param source Reprezentacja grafu z bedzie kopiowany graf.
     * @param destination Graf (w swojej reprezentacji), do ktorego beda przekopiowane dane.
*/
    static Graph &convert(Graph const &source, Graph &destination);

 /**
     * Generuje graf losowy G(n,l).
     * @param n Ilosc wierzcholkow.
     * @param l Ilosc krawedzi.
     * @return Wygenerowany graf losowy.
*/
    static AdjacencyList randomByEdges(unsigned int n, unsigned int l);

     /**
     * Generuje graf losowy G(n,p).
     * @param n Ilosc wierzcholkow.
     * @param p Prawdopodobienstwo istnienia krawedzi miedzy dowolnymi wierzcholkami od 0 do 1.
     * @return Wygenerowany graf losowy.
*/
    static AdjacencyList randomByProbability(unsigned int n, double p);

    /**
     * Sprawdza czy sekwencja liczb naturalnych jest ciagiem graficznym
     * @param A sekwencja liczb naturalnych
*/
    static bool degreeSequence(std::vector<int> A);

    /**
     * Sprawdza czy sekwencja liczb naturalnych jest ciagiem graficznym i jezeli tak tworzy graf prosty
     * @param A sekwencja liczb naturalnych
*/
    static AdjacencyList constuctGraphFromDegreeSequence(std::vector<int>& A);

    /**
     * Znajduje najwieksza wspolna skladowa grafu
     * @param adjacencyMatrix graf
*/
    static void largestComponent(AdjacencyList adjacencyList);

     /**
     * Generuje eulerowski graf losowy G(n).
     * @param n Ilosc wierzcholkow.
     * @return Wygenerowany eulerowski graf losowy.
*/
    static void randomEuler(unsigned int n);
    
    /**
     * Wyznacza cykl eulera w grafie (i sprawdza czy istnieje)
     * @param adjacencyMatrix kopia macierzy sasiedztwa
     * @param start wierzcholek startowy
*/
    static bool findEulerCycle(AdjacencyMatrix& adjacencyMatrix); 
    /*
    *   Randomizuje zadaną ilość losowych krawędzi.
    *   @param howMany ilość żądanych randomizacji
    *   @param graph Gra, który ma zostać poddany randomizacji
    */
    static AdjacencyList randomizeEdges(unsigned int howMany,const Graph& graph);

    /**
     * Generuje losowy graf k-regularny
     * @param n liczba wierzcholkow
     * @param k stopien wierzcholkow
*/
    static AdjacencyList generateKRegularGraph(unsigned int n, unsigned int k);

    /**
     * Wyszukuje cykl Hamiltona w grafie, procedura startowa
     * @param adjacencyMatrix graf w postaci macierzy sasiedztwa
*/
    static bool hamiltonCycleFind(AdjacencyMatrix& adjacencyMatrix);

private:
    /**
     * Przeszukuje graf w poszukiwaniu skladowych
     * @param nr graf
     * @param i iteracja w largestComponent
     * @param list lista sasiedztwa
     * @param comp tablica skladowych sciezki
*/
    static void components_r(int nr, int i, std::vector<std::list<int>> list, int* comp);


    /**
     * Wyszukuje cykl Hamiltona w grafie
     * @param adjacencyMatrix graf w postaci macierzy sasiedztwa
     * @param path tablica do przechowywania cyklu Hamiltona
     * @param pos aktualny wierzcholek
*/
    static bool hamiltonCycle(AdjacencyMatrix& adjacencyMatrix, int path[], int pos);


};

#endif
