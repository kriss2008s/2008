import numpy
from PIL import Image

data = numpy.zeros((12800, 8, 1), dtype=numpy.uint8)
data_image = []
data_out=numpy.eye(320)

with open(file='out.dat') as file: #outputImage40, outputImage, Image2, outputImage13_Jenia
  for line in file.readlines():
    data_image.append(int(line, 16))

def qwe(n, m):
  return list(list(y + x for y in range(n,m, 8)) for x in range(0,8))

def count(num=-1):
  def add():
    nonlocal num
    num += 1
    return num

  return add

num_imp = count()
for j, el in enumerate(data):
  for i, _ in enumerate(el):
    data[j][i]=data_image[num_imp()]

bit_ind = []
n, m = 0, 320
for i in range(40):
  for el in qwe(n,m):
   bit_ind+=el
  n=m
  m+=320

bidts_filtres = []
for i, _ in enumerate(data): 
  for el in data[bit_ind[i]]:
      bidts_filtres.append(el)

index = count()
for i in range(320):
  for j in range(320):
    data_out[i][j]=bidts_filtres[index()]



image = Image.fromarray(data_out)
#image.show()
if image.mode != 'RGB':
    image = image.convert('RGB')
image.save('out.bmp')