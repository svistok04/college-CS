import matplotlib.pyplot as pyplot
import matplotlib.colors as mcolors
import numpy

# Zadanie 1
x = numpy.linspace(-numpy.pi, numpy.pi, 128)
pyplot.plot(x, numpy.sign(x), 'r', x, numpy.cos(x), 'k')
pyplot.legend(('sign', 'cos'), loc='upper left')
pyplot.xticks(numpy.linspace(-numpy.pi, numpy.pi, 5))
pyplot.yticks((-1, 0, 1))
pyplot.savefig('plot.png')
pyplot.close()

# Zadanie 2
fig = pyplot.figure()
ax = fig.add_subplot(projection='3d')


def f(x, y):
    return numpy.sin(x)*numpy.cos(y-1)


x = y = numpy.arange(-5, 6)
X, Y = numpy.meshgrid(x, y)
ax.plot_surface(X, Y, f(X, Y), cmap='coolwarm')
# fig.colorbar(pyplot.cm.ScalarMappable(cmap='coolwarm'))
pyplot.savefig('plot2.png')
pyplot.close(fig)
#
# # Zadanie 3
fig, main_ax = pyplot.subplots()
x = numpy.linspace(-numpy.pi, numpy.pi, 128)
main_ax.plot(x, numpy.sin(10*x), 'b')
main_ax.set_xlim(-(numpy.pi + 0.5), numpy.pi + 0.5)
main_ax.set_ylim(-1, 3)
inset_ax = fig.add_axes([0.3, 0.6, 0.4, 0.2])
inset_ax.plot(x, numpy.cos(5*x), 'b')
inset_ax.set(xlim=(-3.5, 3.5), xticks=numpy.arange(-3, 4), yticks=numpy.arange(-1, 2))
pyplot.savefig('plot3.png')
pyplot.show()
pyplot.close(fig)
#
# # Zadanie 4
x = numpy.random.default_rng().uniform(size=1000)
y = numpy.random.default_rng().uniform(size=1000)
distances = numpy.hypot(x - 0.5, y - 0.5)

norm = mcolors.Normalize(vmin=min(distances), vmax=max(distances))

pyplot.scatter(x, y, s=10, c=distances, cmap='Spectral', norm=norm)
pyplot.tick_params(labelleft=False, labelbottom=False, labelright=False, labeltop=False)
pyplot.show()
pyplot.close()
#
# # Zadanie 5
#
# # Zadanie 6
x = numpy.arange(12)
y = numpy.random.normal(size=12)
pyplot.bar(x, y, color='red', edgecolor='black')
for i in range(len(X)):
    pyplot.text(x[i], y[i], f'{y[i]:.2f}', ha='center', va='bottom')
pyplot.show()
pyplot.close()
#
# # Zadanie 7
x = numpy.linspace(-2, 2, 256)
y = numpy.linspace(-2, 2, 256)
X, Y = numpy.meshgrid(x, y)
Z = -y**3 + X**2 + Y**2 + 2*X - 1
pyplot.contourf(X, Y, Z, levels=10, cmap='hot')
pyplot.clabel(pyplot.contour(X, Y, Z, levels=10, colors='black'), inline=1, fontsize=18)
pyplot.show()
pyplot.close()
#
# # Zadanie 8
