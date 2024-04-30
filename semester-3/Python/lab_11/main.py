def read_iris():
    file = open('iris.txt')
    for count, line in enumerate(open('iris.txt')):
        pass
    result = [[0]*5 for _ in range(count+1)]

    for i in range(count+1):
        line = file.readline().replace('\n', '').split(',')
        for j in range(5):
            try:
                line[j] = float(line[j])
            except ValueError:
                pass
            result[i][j] = line[j]
    return result


# 1
file = open('zad1.txt')
file2 = open('zad1.txt')
list_file = []
for line in file:
    list_file.append(line)
list_file2 = file2.readlines()
print(list_file)
print(list_file2)
# 2 & 3
result = read_iris()
print(result)
lines = []
for i in range(len(result)):
    lines.append(result[i])
fw = open('zad3.txt', 'w')
for line in lines:
    fw.write("%s\n" % ','.join(str(e) for e in line))
lines = []
cnt = 0
lines.append(result[0])
for i in range(len(result)-1):
    if result[i+1][0] > 5:
        cnt += 1
        lines.append(result[i+1])
print(cnt)
fw = open('zad4.txt', 'w')
for line in lines:
    fw.write("%s\n" % ' '.join(str(e) for e in line))
