import numpy
import scipy
from matplotlib.pyplot import imread, imsave

# zadanie 1
img = imread('logo.png')
imsave('./logoN.png', 1 - img)

# Zadanie 2
cropped = img[0:200, 0:140]
gray = numpy.dot(cropped[..., :3], [0.299, 0.587, 0.114])
bright = numpy.clip(cropped - 0.7, 0, 1)
rotated = scipy.ndimage.rotate(bright, 45)
imsave('./logo2.png', numpy.clip(rotated, 0, 1))

# Zadanie 3
img2 = imread('obraz1.png')
cropped2 = img2[0:160, 0:160]
rotated90 = scipy.ndimage.rotate(cropped2, 90)
rotated180 = scipy.ndimage.rotate(cropped2, 180)
rotated270 = scipy.ndimage.rotate(cropped2, 270)
combined_image = numpy.vstack((numpy.hstack((cropped2, rotated270)), numpy.hstack((rotated90, rotated180))))
imsave('./obraz2.png', combined_image)


# Zadanie 4
def zad4_1(x) -> float:
    x1, x2 = x
    return (x1 + 2*x2 - 7)**2 + (2*x1 + x2 - 5)**2


x0 = numpy.array([-10, -10])
tol = 1e-6
zad4_1 = scipy.optimize.minimize(zad4_1, x0, tol=tol)
print('zad4_1')
print(zad4_1.x[0], zad4_1.x[1], zad4_1.fun, zad4_1.nit)


def zad4_2(x) -> float:
    x1, x2 = x
    return 0.5 + (numpy.sin(x1**2 - x2**2)**2 - 0.5) / (1 + 0.001*(x1**2 + x2**2))**2


x0 = numpy.array([-5, 5])
zad4_2 = scipy.optimize.minimize(zad4_2, x0, tol=tol)
print('zad4_2')
print(zad4_2.x[0], zad4_2.x[1], zad4_2.fun, zad4_2.nit)
print()

# Zadanie 5
bound = numpy.array([(2, 10), (1, 8)])
constraints = [
    {'type': 'ineq', 'fun': lambda x: 2*x[0] + x[1] - 6},
    {'type': 'ineq', 'fun': lambda x: -x[0] + x[1] - 1},
]
x0 = numpy.array([1, 2])


def zad5(x) -> float:
    x1, x2 = x
    return x1 - 3*x2 + 2


zad5 = scipy.optimize.minimize(zad5, x0, tol=tol, bounds=bound, constraints=constraints)
print('zad5')
print(zad5.x[0], zad5.x[1], zad5.fun, zad5.nit)
print()

# Zadanie 6


def zad6_1(x, y) -> float:
    return numpy.e**(x+2*y)


zad6_1 = scipy.integrate.nquad(zad6_1, [[0, 1], [0, 1]])
print('zad6_1')
print(zad6_1[0])


def zad6_2(x, y) -> float:
    return x+y**2*x


zad6_2 = scipy.integrate.nquad(zad6_2, [[2, 3], [0, 2]])
print('zad6_2')
print(zad6_2[0])


def zad6_3(x, y) -> float:
    return x*numpy.sin(x)+6*y**2


zad6_3 = scipy.integrate.nquad(zad6_3, [[0, numpy.pi], [0, 2]])
print('zad6_3')
print(zad6_3[0])

# Zadanie 7


def zad7(x):
    return -x**4 + 4*x**3 + 2*x**2 + 8


def zad7_trapezow(x) -> float:
    dx = (x[-1] - x[0]) / (len(x) - 1)
    total = sum(zad7(xi) for xi in x[1:-1]) * 2
    return (total + zad7(x[0]) + zad7(x[-1])) * dx / 2


def zad7_simpsona(x) -> float:
    if len(x) % 2 == 0:  # Check if the number of points is odd
        print("Error: Simpson's rule requires an odd number of points.")
        return 0.0
    dx = (x[-1] - x[0]) / (len(x) - 1)
    total = sum(zad7(xi) for xi in x[1:-1:2]) * 4 + sum(zad7(xi) for xi in x[2:-1:2]) * 2
    return (total + zad7(x[0]) + zad7(x[-1])) * dx / 3


print('zad7')
x = numpy.array(numpy.arange(-1, 12))
# print(x)
trapezow = zad7_trapezow(x)
simpsona = zad7_simpsona(x)
exact_integral = scipy.integrate.quad(zad7, -1, 11)
print(f"Trapezoidal rule: {trapezow}")
print(f"Simpson's rule: {simpsona}")
print(f"Exact : {exact_integral[0]}")
print(f"Error of trapezoidal rule: {abs(trapezow - exact_integral[0]) / exact_integral[0]}")
print(f"Error of Simpson's rule: {abs(simpsona - exact_integral[0]) / exact_integral[0]}")

# Zadanie 8

interpolator = scipy.interpolate.interp1d([7, 10, 11, 15, 19], [7, 12, 13, 15, 13], kind='cubic')
times = numpy.array([9.75, 12.1, 17])
temps = interpolator(times)
for time, temp in zip(times, temps):
    print(f"Estimated temperature at {time} hours: {temp:.2f} C")
