import random

OUTPUT_FILE = "lab8out.txt"
MIN = 50
MAX = 800
STEP = 3
SIZE = 15

fout = open(OUTPUT_FILE, 'w+')

random_list = random.sample(range(MIN, MAX + 1, STEP), SIZE)

fout.write('{}\n'.format(SIZE))
for i in random_list:
    fout.write('{} '.format(i))