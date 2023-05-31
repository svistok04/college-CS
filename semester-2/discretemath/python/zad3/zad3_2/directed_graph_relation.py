import networkx as nx
import matplotlib.pyplot as plt


def directed_graph_relation():
    start = 1
    end = 100

    graph = nx.DiGraph()

    # add nodes from 1 to 100
    graph.add_nodes_from(range(start, end + 1))

    # find the divisibility relation between the numbers in the set {1, 2 ... 100}
    for num in range(start, end + 1):
        for divisor in range(1, num):
            if num % divisor == 0:
                # add edges representing divisibility relation
                graph.add_edge(divisor, num)

    # create a figure
    plt.figure(figsize=(50, 50))

    # create the graph layout
    pos = nx.spring_layout(graph, k=2.5, scale=3)

    # draw edges
    nx.draw_networkx_edges(graph, pos, arrows=True, width=0.35)
    # draw nodes
    nx.draw_networkx_nodes(graph, pos, node_color='blue', node_size=250)

    # show numbers on nodes
    nx.draw_networkx_labels(graph, pos, font_size=9)

    plt.title("Divisibility Graph (1 to 100)", fontweight='bold', fontsize=200)
    plt.axis('off')

    # save to svg and png
    plt.savefig("divisibility_graph.svg")
    plt.savefig("divisibility_graph.png", dpi=300)

