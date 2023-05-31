import matplotlib.pyplot as plt


def discrete_plot_relation():

    start = 1
    end = 100
    relation = []

    # find the divisibility relation between the numbers in the set {1, 2 ... 100}
    for num in range(start, end + 1):
        for divisor in range(1, num + 1):
            if num % divisor == 0:
                # add the coordinates of the dot
                relation.append((divisor, num))

    # place relation to coordinates
    x_coords, y_coords = zip(*relation)

    # create a figure
    plt.figure(figsize=(30, 30))

    # create a scatter plot of the dots
    plt.scatter(x_coords, y_coords, color='blue', marker='o', s=80)

    # make the tittle big, bold and add padding
    plt.title("Divisibility Relation for numbers from 1 to 100)", fontsize=70, fontweight="bold", pad=30)
    # make the labels big and add padding
    plt.xlabel("Divisor", fontsize=30, labelpad=18)
    plt.ylabel("Number (Dividend)", fontsize=30, labelpad=18)

    # make labels on both sides
    plt.tick_params(axis='x', which='both', labelbottom=True, labeltop=True)
    plt.tick_params(axis='y', which='both', labelleft=True, labelright=True)

    # set limits on axes from 0 to 101
    plt.xlim(0, end + 1)
    plt.ylim(0, end + 1)

    # set the range of numbers printed on labels from 1 to 100
    plt.xticks(range(1, end + 1))
    plt.yticks(range(1, end + 1))

    # add dotted grid
    plt.grid(True, linestyle='dotted')

    # save to svg and png
    plt.savefig("divisibility_plot.svg")
    plt.savefig("divisibility_plot.png", dpi=300)
