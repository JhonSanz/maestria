import networkx as nx
import matplotlib.pyplot as plt

graph = nx.Graph()
graph.add_nodes_from([
    (1, {"color": "red"}),
    (2, {"color": "green"}),
])
graph.add_edges_from([(1, 2), (1, 2)])

print("Nodes", graph.number_of_nodes(), list(graph.nodes))
print("Edges", graph.number_of_edges(), list(graph.edges))
print("Adjacents", list(graph.adj[1]))
print("Grade", graph.degree[1])

print(graph.nodes[1])

plt.subplot(111)
nx.draw(graph, with_labels=True, font_weight='bold')
plt.show()