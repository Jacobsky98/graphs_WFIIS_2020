#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

class AdjacencyList;

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
     * Wypisyje graf do strumienia dla programu gnuplot.
     * @param o Strumien, do ktorego wpisywany jest ciag znakow.
     * @see AdjacencyList::print
*/
    virtual std::ostream &print(std::ostream &o) const = 0;

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
};

#endif
