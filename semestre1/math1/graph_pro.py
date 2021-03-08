import networkx as nx
import matplotlib.pyplot as plt

# graph = nx.DiGraph()
# graph.add_weighted_edges_from([(1, 2, 0.5), (3, 1, 0.75)])
# graph.out_degree(1, weight='weight')
# graph.degree(1, weight='weight')


# graph.add_edge(1, 2, weight=4.7 )
# graph.add_edges_from([(3, 4), (4, 5)], color='red')
# graph.add_edges_from([(1, 2, {'color': 'blue'}), (2, 3, {'weight': 8})])
# graph[1][2]['weight'] = 4.7
# graph.edges[3, 4]['weight'] = 4.2



G=nx.Graph()
i=1
G.add_node(i,pos=(i,i))
G.add_node(2,pos=(2,2))
G.add_node(3,pos=(1,0))
G.add_edge(1,2,weight="a")
G.add_edge(1,3,weight="b")
pos=nx.get_node_attributes(G,'pos')
nx.draw(G,pos)
labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
plt.savefig("graph.png")


# graph.add_nodes_from([
#     (1, {"color": "red"}),
#     (2, {"color": "green"}),
#     (3, {"color": "green"}),
# ])
# graph.add_edges_from([(1, 2), (1, 2), (1, 3)])

# print("Nodes", graph.number_of_nodes(), list(graph.nodes))
# print("Edges", graph.number_of_edges(), list(graph.edges))
# print("Adjacents", list(graph.adj[1]))
# print("Grade", graph.degree[1])

# print(graph.nodes[1])

# plt.subplot(111)
# nx.draw(graph, with_labels=True, font_weight='bold')
# plt.show()