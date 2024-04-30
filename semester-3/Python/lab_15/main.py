import numpy

# Zadanie 1
zad1 = numpy.loadtxt(fname='irisP.txt', delimiter=',', dtype='str')
setosaPetalWidthTotal, versicolorPetalWidthTotal, virginicaPetalWidthTotal = 0, 0, 0
setosaCount, versicolorCount, virginicaCount = 0, 0, 0
for i in range(len(zad1)):
    match zad1[i][4]:
        case 'Iris-setosa':
            setosaPetalWidthTotal += float(zad1[i][3])
            setosaCount += 1
        case 'Iris-versicolor':
            versicolorPetalWidthTotal += float(zad1[i][3])
            versicolorCount += 1
        case 'Iris-virginica':
            virginicaPetalWidthTotal += float(zad1[i][3])
            virginicaCount += 1

# print('Setosa average petal width: ', setosaPetalWidthTotal / setosaCount)
# print('Versicolor average petal width: ', versicolorPetalWidthTotal / versicolorCount)
# print('Virginica average petal width: ', virginicaPetalWidthTotal / virginicaCount)

# Zadanie 2
zad2 = numpy.loadtxt(fname='irisP2.txt', delimiter=',', dtype='str')
setosaPetalLengthTotal, versicolorPetalLengthTotal, virginicaPetalLengthTotal = 0, 0, 0
setosaCount, versicolorCount, virginicaCount = 0, 0, 0
for i in range(len(zad2)):
    if zad2[i][2] != '':
        match zad2[i][4]:
            case 'Iris-setosa':
                setosaPetalLengthTotal += float(zad2[i][2])
                setosaCount += 1
            case 'Iris-versicolor':
                versicolorPetalLengthTotal += float(zad2[i][2])
                versicolorCount += 1
            case 'Iris-virginica':
                virginicaPetalLengthTotal += float(zad2[i][2])
                virginicaCount += 1
for i in range(len(zad2)):
    if zad2[i][2] == '':
        match zad2[i][4]:
            case 'Iris-setosa':
                zad2[i][2] = round(setosaPetalLengthTotal / setosaCount, 1)
            case 'Iris-versicolor':
                zad2[i][2] = round(versicolorPetalLengthTotal / versicolorCount, 1)
            case 'Iris-virginica':
                zad2[i][2] = round(virginicaPetalLengthTotal / virginicaCount, 1)
# print(zad2)

# Zadanie 3
zad3 = numpy.loadtxt(fname='contact_lenses.txt', delimiter='\t', dtype='str')
zad3 = numpy.char.upper(zad3)
# print(zad3)
zad3 = numpy.char.replace(zad3, old='YES', new='TRUE')
zad3 = numpy.char.replace(zad3, old='NO', new='FALSE')
# print(zad3)
numpy.savetxt(fname='./contact-lensne-res.txt', X=zad3, fmt='%s', delimiter='\t')

# Zadanie 4
zad4 = numpy.loadtxt(fname='irisP.txt', delimiter=',', dtype='str')
zad4 = numpy.char.replace(zad4, 'Iris-', '')
numpy.savetxt(fname='./iris-res.txt', X=zad4, fmt='%s', delimiter=',')

# Zadanie 5

def zad5(n, it, xy_min, xy_max):

    def f(x, y):
        return x**2 + 3 * y**2

    P = numpy.random.uniform(xy_min, xy_max, [n, 2])
    V = numpy.random.uniform(-2 * xy_max, 2 * xy_max, [n, 2])

    P_best = numpy.copy(P)
    G_best = P[numpy.argmin(f(P[:, 0], P[:, 1]))]

    for _ in range(it):
        rp, rg = numpy.random.rand(), numpy.random.rand()
        V = 0.8 * V + 2 * rp * (P_best - P) + 2 * rg * (G_best - P)
        P = P + V

        for i in range(n):
            current_value = f(P[i, 0], P[i, 1])
            if current_value < f(P_best[i, 0], P_best[i, 1]):
                P_best[i] = P[i]

        G_best = P_best[numpy.argmin(f(P_best[:, 0], P_best[:, 1]))]

    return G_best, f(G_best[0], G_best[1])

zad5 = zad5(100, 20, -5, 5)
print("G_best:", zad5[0], "Function value:", zad5[1])
