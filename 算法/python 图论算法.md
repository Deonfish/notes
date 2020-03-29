# python 图论算法

### Dijkstra + heap

```python
import heapq

class HeapNode:
    def __init__(self, u, d):
        self.u = u
        self.d = d

    def __lt__(self, other):
        return self.d < other.d

# s: 起点编号, adj: 临接表dic{ u: (v, w)}, n: 顶点数
def Dijkstra(s, adj, n):  # return list d
  	d = [float('inf') for i in range(0, n+1)]
    vis = [False for i in range(0, n + 1)]
    d[s] = 0
    q = []
    heapq.heappush(q, Foo(s, 0))
    while len(q) != 0:
        f = heapq.heappop(q)
        u = f.u
        if vis[u]:
            continue
        vis[u] = True
        if u not in adj:
            continue
        for v, w in adj[u]:
            if not vis[v] and d[v] > d[u] + w:
                d[v] = d[u] + w
                heapq.heappush(q, Foo(v, d[v]))
    return d


```

### SPFA

可以计算负权图，可以判断是否有负环，复杂度O(kE)

```python
import queue
# s: 起点编号, adj: 临接表dic{ u: (v, w)}, n: 顶点数
def SPFA(s, adj, n):  # return list d
    inq = [False for i in range(0, n+1)]  # node: 0~n-1
    d = [float('inf') for i in range(0, n+1)]
    q = queue.Queue()
    q.put(s)
    d[s] = 0
    inq[s] = True
    while not q.empty():
        u = q.get()
        inq[u] = False
        if u not in adj:
            continue
        for v, w in adj[u]:
            if d[v] > d[u] + w:
                d[v] = d[u] + w
                if not inq[v]:
                    q.put(v)
                    inq[v] = True
    return d

```

