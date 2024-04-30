import struct
import xml.dom
import xml.etree.ElementTree

def read_iris():
    with open('iris.txt', 'r') as file:
        result = []
        for line in file:
            parts = line.strip().split(',')
            row = [float(part) if part.isdigit() or part.replace('.', '', 1).isdigit() else part for part in parts]
            result.append(row)
    return result

def txt_to_bin():
    result = read_iris()
    with open('zad1.bin', 'wb') as fw:
        for row in result:
            for item in row:
                if isinstance(item, float):
                    fw.write(struct.pack('d', item))
                elif isinstance(item, str):
                    encoded_str = bytes(item, encoding='raw_unicode_escape')
                    length = len(encoded_str)
                    fw.write(struct.pack('I', length))
                    fw.write(encoded_str)

def read_bin():
    result = []
    row = []
    with open('zad1.bin', 'rb') as file:
        while True:
            bytes_read = file.read(4)
            if len(bytes_read) < 4:
                break

            possible_str_len = struct.unpack('I', bytes_read)[0]
            if 0 < possible_str_len < 10000:
                string_bytes = file.read(possible_str_len)
                string_value = string_bytes.decode('raw_unicode_escape')
                row.append(string_value)
            else:
                file.seek(-4, 1)
                bytes_read = file.read(8)
                if len(bytes_read) < 8:
                    break
                value = struct.unpack('d', bytes_read)[0]
                row.append(value)
            if len(row) == 5:
                result.append(row)
                row = []
    return result


def write_to_txt(data, filename="output.txt"):
    with open(filename, 'w') as file:
        for row in data:
            line = ', '.join([str(item) for item in row])
            file.write(line + '\n')


# 1
txt_to_bin()

# 2
result = read_bin()
print(result)

write_to_txt(result)

# 3 & 4
tree = xml.etree.ElementTree.parse('pierwszy.xml')
root = tree.getroot()
third_level_attributes = []
for child in root:
    for grandchild in child:
        third_level_attributes.append(grandchild.attrib)
fourth_level_values = []
for child in root:
    for grandchild in child:
            fourth_level_values.append(grandchild.text.strip())
print("Third Level Attributes:", third_level_attributes)
print("Fourth Level Values:", fourth_level_values)

# 5
first_child = root[0] if len(root) > 0 else None
attributes = ""
if first_child is not None and len(first_child) > 1:
    second_child_of_first_child = first_child[1]
    attributes = second_child_of_first_child.attrib
print(attributes)

# 6
with open('zad6.xml', 'w') as file_xml:
    root = xml.etree.ElementTree.Element('root')
    uczelnia = xml.etree.ElementTree.Element('uczelnia')
    root.append(uczelnia)
    student1 = xml.etree.ElementTree.SubElement(uczelnia, 'student')
    student1.attrib = {'Nrindeksu': '12333'}
    student1.text = 'Anna Kowalska'
    student2 = xml.etree.ElementTree.SubElement(uczelnia, 'student')
    student2.attrib = {'Nrindeksu': '12333'}
    student2.text = 'Przemyslaw Nowak'
    student3 = xml.etree.ElementTree.SubElement(uczelnia, 'student')
    student3.attrib = {'Nrindeksu': '12333'}
    student3.text = 'Piotr Pilawka'
    file_xml.write(xml.etree.ElementTree.tostring(root).decode('utf-8'))
