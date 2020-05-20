#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <stack>
#include "Edge.hpp"

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
     * Dodaje krawedz skierowana miedzy podanymi wierzcholkami.
    */
    virtual Graph &addDirectedEdge(int firstVertex, int secondVertex, int weight) = 0;

    /**
     * Dodaje krawedz miedzy podanymi wierzcholkami.
*/
    virtual Graph &addEdge(int firstVertex, int secondVertex, int weight) = 0;

    /*
    *   Usuwa krawędź pomiędzy podanymi wierzchołkami
    */
    virtual Graph &removeEdge(int firstVertex, int secondVertex) = 0;

    /*
    *   Usuwa skierowaną krawędź pomiędzy podanymi wierzchołkami
    */
    virtual Graph &removeDirectedEdge(int firstVertex, int secondVertex) = 0;

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
    static AdjacencyList constuctGraphFromDegreeSequence(std::vector<int> &A);

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
    static bool findEulerCycle(AdjacencyMatrix &adjacencyMatrix);

    /*
    *   Randomizuje zadaną ilość losowych krawędzi. Wagi losuje.
    *   @param howMany ilość żądanych randomizacji
    *   @param graph Gra, który ma zostać poddany randomizacji
    */
    static AdjacencyList randomizeEdges(unsigned int howMany, const Graph &graph);

    /**
     * Generuje losowy graf k-regularny
     * @param n liczba wierzcholkow
     * @param k stopien wierzcholkow
*/
    static AdjacencyList generateKRegularGraph(unsigned int n, unsigned int k);

    /**
     * Algorytm Prima - najmniejsze drzewo rozpinajace
     * @return Najmniejsze drzewo rozpinajace
*/
    AdjacencyList primsAlgorithm() const;

    /**
     * Wyszukuje cykl Hamiltona w grafie, procedura startowa
     * @param adjacencyMatrix graf w postaci macierzy sasiedztwa
*/
    static bool hamiltonCycleFind(AdjacencyMatrix &adjacencyMatrix);

    /*
    *   Sprawdza czy krawędź o podanych wierzchołkach istnieje
    *   @param  firstVertex numer pierwszego wierzchołka
    *   @param  secondVertex numer drugiego wierzchołka
    */
    virtual bool doesEdgeExists(int firstVertex, int secondVertex) const = 0;

    /*
    *   Sprawdza czy wierzchołek jest izolowany
    *   @param vertex Numer sprawdzanego wierzchołka
    */
    virtual bool isVertexIsolated(int vertex) const = 0;

    /*
    *   Zlicza wymiar wierzchołka
    *   @param vertex Numer wierzchołka
    */
    virtual int dimOfVertex(int vertex) const = 0;

    /*
    *   Generuje wektor wierzchołków połączonych z zadanym wierzchołkiem
    *   @param vertex Numer wierzchołka
    */
    virtual std::vector<int> getVectorOfVerticesConnectedTo(int vertex) const = 0;

    /*
    *   Zlicza wierzchołki
    */
    virtual int getVertexAmount() const = 0;

    /*
    *   Generuje spójny graf ważony
    *   @param vertexNum rozmiar grafu do wygenerowania liczony w wierzchołkach
    *   @param edgeProbability Szansa na wystapienie krawędzi(zawsze conajmniej jedna)
    */
    static AdjacencyList createRandomWeightedConnectedGraph(int vertexNum, float edgeProbability = 0.2);

    static std::vector<int> dijkstraAlgorithm(const Graph &graph, const int &beginningVertex, const bool &wantToDisplay);

    static bool bellmanFordAlgorithm(const Graph &graph, const int &beginningVertex, std::vector<int> &result, bool wantToDisplay);

    static AdjacencyList createRandomDigraph(int vertexNum, float edgeProbability = 0.2, int min = 1, int max = 1);

    virtual bool isDirectedGraph() const = 0;

    /**
    * Algorytm Kosaraju oznaczajacy silnie spojne skladowe w grafie skierowanym
    * @param graph wejsciowy graf
    */
    static std::vector<int> kosarajuAlgorithm(const Graph &graph, bool display = true, bool *isCoherent = nullptr);

    /**
    * funkcja pomocnicza dla johnsonAlgorithm
    * @param graph zmieniany graph
    */
    static void add_s(Graph &graph);

    /**
    * Algorym johnsona odległości w grafie skierowanym
    * @param graph wejsciowy graf
    * @param display pokazuje wynik
    */
    static std::vector<int> johnsonAlgorithm(Graph &graph, bool display = true);

private:
    /**
     * Przeszukuje graf w poszukiwaniu skladowych
     * @param nr graf
     * @param i iteracja w largestComponent
     * @param list lista sasiedztwa
     * @param comp tablica skladowych sciezki
*/
    static void components_r(int nr, int i, std::vector<std::list<Edge>> list, int *comp);

    /**
     * Wyszukuje cykl Hamiltona w grafie
     * @param adjacencyMatrix graf w postaci macierzy sasiedztwa
     * @param path tablica do przechowywania cyklu Hamiltona
     * @param pos aktualny wierzcholek
*/
    static bool hamiltonCycle(AdjacencyMatrix &adjacencyMatrix, int path[], int pos);

    /*
    *   Inicjalizuje pierwotne wartości pomocniczych wektorów do algorytmu dijkstry
    *   @param beginningVertex Index wierzchołka od którego zaczynamy
    *   @param ds Pomocniczy wektor z najlepszymi do tej pory ścieżkami
    *   @param ps Pomocniczy wektor z poprzednim elementem w ścieżce
    *   @param graph Graf na którym pracujemy
    */
    static void dijkstraInit(const Graph &graph, const int &beginningVertex, std::vector<int> &ds, std::vector<int> &ps);

    /*
    *   Relaksajca krawędzi do algorytmu dijkstry
    *   @param firstVertex Index pierwszego wierzchołka incydentnego do sprawdzanej krawędzi.
    *   @param secondVertex Index drugiego wierzchołka incydentnego do sprawdzanej krawędzi.
    *   @param weight Waga obecnie sprawdzanej krawędzi.
    *   @param ds Pomocniczy wektor z najlepszymi do tej pory ścieżkami
    *   @param ps Pomocniczy wektor z poprzednim elementem w ścieżce
    */
    static void dijkstraRelax(std::vector<int> &ds, std::vector<int> &ps, const int &firstVertex, const int &secondVertex, const int &weight);

    /**
     * Przeszukiwanie grafu do wyznaczania silnie spojnych skladowych do algorytmu Kosaraju
     * @param v numer wierzcholka
     * @param adjacencyList lista sasiedztwa przeszukiwanego grafu
     * @param d wektor przechowujacy czas od poczatku dzialania algorytmu do odwiedzenia wierzcholka
     * @param f wektor przechowujacy czas przetworzenia wierzcholka v
     * @param t aktualny czas od poczatku trwania algorytmu
     */
    static void kosarajuDFS_visit(int v, AdjacencyList &adjacencyList, std::vector<int> &d, std::vector<int> &f, int &t);

    /**
     * Przypisywanie silnie spojnych skladowych do algorytmu Kosaraju
     * @param nr numer silnie spojnej skladowej
     * @param v numer wierzcholka
     * @param adjacencyListT lista sasiedztwa transponowana
     * @param comp wektor przechowujacy numer silnie spojnych skladowych dla danych wierzcholkow
     */
    static void kosarajuComponents_r(int &nr, int &v, AdjacencyList &adjacencyListT, std::vector<int> &comp);
};

#endif

