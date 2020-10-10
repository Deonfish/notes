import queue
import heapq

times = [[1, 2, 1], [2, 3, 2], [1, 3, 4]]
N = 3
K = 1
adj = {}  # { u : (v, w) }
n = N

vis = []


def dfs(u):
    if u == -1:
        return
    vis[u] = True
    #
    for v, w in adj[u]:
        if not vis[v]:
            dfs(v)


vis = []


def bfs(s):
    q = queue.Queue()
    q.put(s)
    while not q.empty():
        u = q.get()
        vis[u] = True
        for v, w in adj[u]:
            if not vis[v]:
                q.put(v)


def SPFA(s, adj, n):  # return list d
    inq = [False for i in range(0, n + 1)]  # node: 0~n-1
    d = [float('inf') for i in range(0, n + 1)]
    pre = [-1 for i in range(0, n + 1)]
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
                pre[v] = u
                if not inq[v]:
                    q.put(v)
                    inq[v] = True
    return d, pre


class HeapNode:
    def __init__(self, u, d):
        self.u = u
        self.d = d

    def __lt__(self, other):
        return self.d < other.d


# s: 起点编号, adj: 临接表dic{ u: (v, w)}, n: 顶点数
def Dijkstra(s, adj, n):  # return list d
    d = [float('inf') for i in range(0, n + 1)]
    vis = [False for i in range(0, n + 1)]
    pre = [-1 for i in range(0, n + 1)]
    d[s] = 0
    q = []
    heapq.heappush(q, HeapNode(s, 0))
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
                pre[v] = u
                heapq.heappush(q, HeapNode(v, d[v]))
    return d, pre


def Floyd(adj, n):
dist = [[float('inf') for i in range(0, n)] for i in range(0, n)]
for i in range(0, n):
    dist[i][i] = 0
for i in adj:
    for v, w in adj[i]:
        dist[i][v] = w
        dist[v][i] = w
for k in range(0, n):
    for i in range(0, n):
        for j in range(0, n):
            if dist[i][k] != float('inf') and dist[k][j] != float('inf') and dist[i][k] + dist[k][j] < dist[i][j]:
                dist[i][j] = dist[i][k] + dist[k][j]
return dist





def init_path(pre, n):
    ans = []
    for u in range(1, n + 1):
        path = []
        v = u
        while v != -1:
            path.append(v)
            v = pre[v]
        path.reverse()
        ans.append(path)
    return ans


for u, v, w in times:
    if u not in adj:
        adj[u] = []
    adj[u].append((v, w))





# d, pre = Dijkstra(K, adj, N)
d, pre = SPFA(K, adj, N)
paths = init_path(pre, N)
print(d[1:])
print(paths)
