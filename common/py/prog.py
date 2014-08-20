class Node:
    pass

def getNode(val):
  node = Node()
  node.left = None
  node.right = None
  node.value = val
  return node


def fact(n):
  if n <= 0:
    return 1
  return n * fact(n - 1)


def constructTree(seq, node):
  if len(seq) == 0:
    return
  ls = [i for i in seq if i < node.value]
  rs = [i for i in seq if i > node.value]
  if len(ls) > 0:
    ln = getNode(seq[0])
    node.left = ln
    constructTree(ls[1:], ln)
  if len(rs) > 0:
    rn = getNode(seq[0])
    node.right = rn
    constructTree(rs[1:], rn)


def getnumways(node):
  if node == None:
    return (0, 1)
  v1 = getnumways(node.left)
  v2 = getnumways(node.right)
  nw = fact(v1[0] + v2[0]) / (fact(v1[0]) * fact(v2[0]))
  nw = nw * v1[1] * v2[1]
  return (v1[0] + v2[0] + 1, nw)


def answer(seq):
  root = getNode(seq[0])
  constructTree(seq[1:], root)
  return getnumways(root)[1]

if __name__ == '__main__':
  print answer([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
