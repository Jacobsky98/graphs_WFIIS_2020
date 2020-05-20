import os.path
import matplotlib.pyplot as plt
import matplotlib.lines as mlines
from random import randint

colors = []
for i in range(500):
  colors.append('#%06X' % randint(0, 0xFFFFFF))

class Edge:
  def __init__(self, src, dest, x, y, layer):
    self.src = src
    self.dest = dest
    self.x = x
    self.y = y
    self.layer = layer
  
  def __str__(self):
    to_ret = ''.join(['s:', str(self.src), '_d:', str(self.dest), '_x:', str(self.x), '_y:', str(self.y), '_la:', str(self.layer), '\n'])
    return to_ret

  def __repr__(self):
    return str(self)

class Graph:
  edges = []
  num_of_layers = 0
  max_nodes = 0
    

  def find_index(self, id):
    i = 0
    for edge in self.edges:
      if edge.src == id:
        return i
        break
      i += 1
    return -1
    

  def plot_graph(self):
    fig, ax = plt.subplots()
    ax = plt.gca()
    for edge in self.edges:
      src_x = edge.x
      src_y = edge.y
      dest_index = self.find_index(edge.dest)
      dest_x = self.edges[dest_index].x
      dest_y = self.edges[dest_index].y

      center_x = (src_x + dest_x) / 2
      center_y = (src_y + dest_y) / 2

      center_x = (center_x + dest_x) / 2
      center_y = (center_y + dest_y) / 2

      line_begin = mlines.Line2D([src_x, center_x], [src_y, center_y], color='black', zorder=5, linewidth=1)
      line_end = mlines.Line2D([center_x, dest_x], [center_y, dest_y], color='red', zorder=0, linewidth=2)

      ax.add_line(line_begin)
      ax.add_line(line_end)
    
    
    for edge in self.edges:
      plt.scatter(edge.x, edge.y, s=500, color = colors[edge.layer], zorder=10)
      plt.annotate(str(edge.src), (edge.x, edge.y), zorder=20)
          
    plt.show()
    # plt.savefig('ploted_layered_graph.png')

  def read_graph_from_file(self):
    
    with open(os.path.dirname(__file__) + "/../output_python.txt", "r") as file:
      line = file.readline()
      self.max_nodes = int(line[14:])
      line = file.readline()
      self.num_of_layers = int(line[7:])
      line = file.readline()
      layer = 0
      nodes_in_layer = 0
      x = 20
      y = 20
      max_y = self.max_nodes * 100
      while line:
        if(line.find("layer") >= 0):
          layer = int(line[line.index(":")+1 : line.index("_")])
          nodes_in_layer = int(line[line.index("_")+1 :])
          x += 100
          y = 20
        elif line != '':
          src = int(line[ : line.index(":")])
          dest = line[line.index(":")+1 :]
          if(dest and dest[0].isdigit()):
            dest = int(dest)
          else:
            dest = -1
          if(self.find_index(src) == -1):
            y += 100
          self.edges.append(Edge(src, dest, x, y, layer))
        line = file.readline()






if __name__ == "__main__":
  graph = Graph()
  graph.read_graph_from_file()
  graph.plot_graph()
