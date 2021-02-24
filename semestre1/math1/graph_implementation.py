class Node:
    def __init__(self, id=None):
        self.__id = id

    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, id):
        self.__id = id

    def __hash__(self):
        return hash(self.__id)

    def __eq__(self, other):
        return self.__id == other.__id

    def __ne__(self, other):
        return not(self == other)

    def __str__(self):
        return str(self.__id)

    def __repr__(self):
        return self.__str__()


class Edge:
    def __init__(self, start, end=None):
        self.__start = start
        self.__end = end
        self.__weight = 0
    
    @property
    def start(self):
        return self.__start

    @start.setter
    def start(self, start):
        self.__start = start

    @property
    def end(self):
        return self.__end

    @end.setter
    def end(self, end):
        self.__end = end

    @property
    def weight(self):
        return self.__weight

    @weight.setter
    def weight(self, weight):
        self.__weight = weight

    def __str__(self):
        return "{} --- {}".format(self.start, self.end)


class Graph:
    __nodes = set()
    __edges = set()
    __adj_list = {}
    __node_info = {}
    __out_edge = {}

    def __str__(self):
        representation = "graph looks like this:\n"
        for node, adj in self.__adj_list.items():
            representation += "{}  ->  {} \n".format(node, adj)
        return representation

    def has_node_with_id(self, id):
        return self.__node_info.get(id)

    def get_node_by_id(self, id):
        assert(self.has_node_with_id(id))
        return self.__node_info[id]
    
    def add_node(self, id):
        node = Node()
        node.id = id
        return self.add_given_node(node)

    def add_given_node(self, node):
        assert(not self.has_node_with_id(node.id))
        self.__adj_list[node] = []
        self.__nodes.add(node)
        self.__node_info[node.id] = node
        return node

    def add_edge_given_ids(self, start_id, end_id):
        start = self.get_node_by_id(start_id)
        end = self.get_node_by_id(end_id)
        return self.add_edge_given_nodes(start, end)
    
    def add_edge_given_nodes(self, start_node, end_node):
        edge = Edge(start_node, end_node)
        return self.__add_edge(edge)

    def __add_edge(self, edge):
        self.__edges.add(edge)
        self.__adj_list[edge.start].append(edge.end)
        try:
            self.__out_edge[edge.start].append(edge)
        except:
            self.__out_edge[edge.start] = []
        return edge

    def count_nodes(self):
        return len(self.__nodes)

    def count_edges(self):
        return len(self.__edges)


graph = Graph()
first = graph.add_node(1)
second = graph.add_node(2)
third = graph.add_node(3)
graph.add_edge_given_ids(1, 2)
graph.add_edge_given_nodes(first, third)
graph.add_edge_given_nodes(second, third)


print(graph)
print(graph.count_edges())
print(graph.count_nodes())