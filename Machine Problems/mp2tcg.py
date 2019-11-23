import string
import random
import itertools
import operator
import os

INST_LEN = 1000 # Number of instructions
PRBD_I = 1.2 # Probability distribution of which operation to use [0, inf)
PRBD_S = 0.6 # 1.5
PRBD_D = 0.2 # 0.8
PROB_I_EXKEY = 0.01 # Chance that Insert uses existing or deleted keys [0, 1]
PROB_S_EXKEY = 0.85 # Chance that Search uses...
PROB_D_EXKEY = 0.9 # Chance that Delete uses...
EXKEY_THRES = 10 # Threshold for when to use existing or deleted keys

INPUT_FILE = 'mp2inp.txt'
OUTPUT_FILE = 'mp2out.txt'

OP = ['i', 's', 'd']
OP_PRBD = [PRBD_I, PRBD_S, PRBD_D]

def rand_str():
  N = random.randint(1, 100)
  S = '0123456789abcdef'
  return ''.join(random.choice(S) for _ in range(N)).strip()

def rand_op():
  cumpd = list(itertools.accumulate([x / sum(OP_PRBD) for x in OP_PRBD], operator.add))
  r = random.random()

  for i, p in enumerate(cumpd):
    if r < p:
      return OP[i]

def gen_test_case():
  D = {}
  KEYS = []
  PROB_EXKEY_MAP = {
    'i': PROB_I_EXKEY,
    's': PROB_S_EXKEY,
    'd': PROB_D_EXKEY
  }

  fin = open(INPUT_FILE, 'w+')
  fout = open(OUTPUT_FILE, 'w+')

  fin.write('{}\n'.format(INST_LEN))

  for _ in range(INST_LEN):
    op = rand_op()
    key = rand_str()
    prob_exkey = PROB_EXKEY_MAP[op]

    if len(KEYS) >= EXKEY_THRES and random.random() < prob_exkey:
      key = random.choice(KEYS)

    if op == 'i':
      KEYS.append(key)
      value = rand_str()
      D[key] = value
      fin.write('i {} : {}\n'.format(key, value))
      fout.write('INSERT {}\n'.format(key))

    elif op == 's':
      fin.write('s {}\n'.format(key))

      if key in D:
        fout.write('{} : {}\n'.format(key, D[key]))
      else:
        fout.write('KEY-VALUE DOES NOT EXIST\n')

    elif op == 'd':
      fin.write('d {}\n'.format(key))

      if key in D:
        del D[key]
        fout.write('DELETE {}\n'.format(key))
      else:
        fout.write('KEY-VALUE DOES NOT EXIST\n')

  fin.close()
  fout.close()

gen_test_case()
