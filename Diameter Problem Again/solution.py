import sys
from array import array
from math import log2
import bisect

sys.setrecursionlimit(1 << 25)

NINF = -10**30

class LCA:
    def __init__(self, n, g):
        self.init(n, g)

    def init(self, N, g):
        self.n = N
        self.g = g
        self.first = [-1] * (N + 1)
        # euler and depth arrays as typed arrays for memory
        euler_list = []
        depth_list = []
        distRoot = [0] * (N + 1)

        # iterative DFS to produce Euler tour
        stack = [(1, 0, -1, 0, 0)]  # (u, p, it, d, acc)
        while stack:
            u, p, it, d, acc = stack.pop()
            if it == -1:
                # entry
                self.first[u] = len(euler_list)
                euler_list.append(u)
                depth_list.append(d)
                distRoot[u] = acc
                it = 0
                stack.append((u, p, it, d, acc))
                for v,w in reversed(g[u]):
                    if v == p: continue
                    stack.append((v, u, -1, d+1, acc + w))
            else:
                if p != 0:
                    # add parent back to euler
                    euler_list.append(p)
                    depth_list.append(d-1)

        self.euler = array('I', euler_list)
        self.depth = array('i', depth_list)
        self.distRoot = distRoot

        E = len(self.euler)
        self.lg2 = [0] * (E + 1)
        for i in range(2, E + 1):
            self.lg2[i] = self.lg2[i >> 1] + 1

        K = self.lg2[E] + 1
        # st[k][i] stores index into euler array with minimal depth in interval
        self.st = [array('I', [0] * E) for _ in range(K)]
        for i in range(E):
            self.st[0][i] = i
        k = 1
        while (1 << k) <= E:
            length = 1 << k
            half = 1 << (k - 1)
            prev = self.st[k - 1]
            cur = self.st[k]
            for i in range(0, E - length + 1):
                i1 = prev[i]
                i2 = prev[i + half]
                cur[i] = i1 if self.depth[i1] < self.depth[i2] else i2
            # fill tail values (not strictly needed but safe)
            for i in range(max(0, E - length + 1), E):
                cur[i] = prev[i]
            k += 1

    def lca(self, u, v):
        L = self.first[u]; R = self.first[v]
        if L > R:
            L, R = R, L
        k = self.lg2[R - L + 1]
        i1 = self.st[k][L]
        i2 = self.st[k][R - (1 << k) + 1]
        return self.euler[i1] if self.depth[i1] < self.depth[i2] else self.euler[i2]

    def dist(self, u, v):
        a = self.lca(u, v)
        return self.distRoot[u] + self.distRoot[v] - 2 * self.distRoot[a]


class CentroidDecomp:
    def __init__(self, N, g, lca):
        self.n = N
        self.g = g
        self.lca = lca
        self.sub = [0] * (N + 1)
        self.used = [False] * (N + 1)
        self.chain = [[] for _ in range(N + 1)]
        self.decompose(1)
        # sort chains by centroid id for each node
        for u in range(1, N + 1):
            self.chain[u].sort(key=lambda t: t[0])

    def dfs_sz(self, root):
        # iterative post-order to compute subtree sizes in the current unused-subtree
        stack = [(root, 0, 0)]  # (u, p, state) state 0 enter, 1 exit
        order = []
        while stack:
            u, p, state = stack.pop()
            if state == 0:
                stack.append((u, p, 1))
                for v, w in self.g[u]:
                    if v == p or self.used[v]:
                        continue
                    stack.append((v, u, 0))
            else:
                self.sub[u] = 1
                for v, w in self.g[u]:
                    if v == p or self.used[v]:
                        continue
                    self.sub[u] += self.sub[v]
                order.append(u)
        return self.sub[root]

    def find_centroid(self, root, sz):
        u = root
        p = 0
        changed = True
        while changed:
            changed = False
            for v, w in self.g[u]:
                if v == p or self.used[v]:
                    continue
                if self.sub[v] * 2 > sz:
                    p = u
                    u = v
                    changed = True
                    break
        return u

    def collect(self, start, parent, c, childId):
        # DFS stack collecting nodes in subtree starting at start (where parent=c)
        stack = [(start, parent)]
        while stack:
            u, p = stack.pop()
            d = self.lca.dist(u, c)
            self.chain[u].append((c, childId, d))
            for v, w in self.g[u]:
                if v == p or self.used[v]:
                    continue
                stack.append((v, u))

    def decompose(self, entry):
        # recursive decomposition; depth is logN so recursion safe
        def rec(u):
            sz = self.dfs_sz(u)
            c = self.find_centroid(u, sz)
            self.used[c] = True
            childId = 0
            for v, w in self.g[c]:
                if self.used[v]:
                    continue
                self.collect(v, c, c, childId)
                childId += 1
            # centroid maps to itself
            self.chain[c].append((c, -1, 0))
            for v, w in self.g[c]:
                if not self.used[v]:
                    rec(v)

        rec(entry)


def make_agg(a=NINF, b=-2, c=NINF):
    return (a, b, c)

def merge_agg(A, B):
    at1, ach1, at2 = A
    bt1, bch1, bt2 = B
    if at1 >= bt1:
        r_top1 = at1; r_ch1 = ach1
    else:
        r_top1 = bt1; r_ch1 = bch1
    candA = at2 if ach1 == r_ch1 else at1
    candB = bt2 if bch1 == r_ch1 else bt1
    r_top2 = candA if candA > candB else candB
    return (r_top1, r_ch1, r_top2)

def best_excluding(agg, childX):
    top1, ch1, top2 = agg
    if top1 == NINF:
        return NINF
    if childX >= 0 and childX == ch1:
        return top2
    return top1


def main():
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    try:
        n = int(next(it))
    except StopIteration:
        return
    g = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u = int(next(it)); v = int(next(it)); w = int(next(it))
        g[u].append((v, w)); g[v].append((u, w))

    lca = LCA(n, g)
    cd = CentroidDecomp(n, g, lca)

    # Precompute per-node parallel arrays for centroid ids, child ids and dists for fast binary search
    chain_ids = [None] * (n + 1)
    chain_child = [None] * (n + 1)
    chain_d = [None] * (n + 1)
    for u in range(1, n + 1):
        lst = cd.chain[u]
        if not lst:
            chain_ids[u] = []
            chain_child[u] = []
            chain_d[u] = []
            continue
        ids = [t[0] for t in lst]
        child = [t[1] for t in lst]
        d = [t[2] for t in lst]
        chain_ids[u] = ids
        chain_child[u] = child
        chain_d[u] = d

    m = int(next(it))

    # dynamic array A (1-based); A[0] unused
    A = [0]

    B = 700  # block size, tuned
    blocks = []  # list of dicts with L,R,dirty,map

    def ensure_blocks():
        length = len(A) - 1
        need = (length + B - 1) // B
        while len(blocks) < need:
            bi = len(blocks)
            L = bi * B + 1
            R = min((bi + 1) * B, length)
            blocks.append({'L': L, 'R': R, 'dirty': True, 'agg': [], 'map': {}})
        if blocks:
            blocks[-1]['R'] = len(A) - 1
            if blocks[-1]['L'] > blocks[-1]['R']:
                blocks[-1]['dirty'] = False

    def rebuild_block(bi):
        b = blocks[bi]
        b['agg'].clear()
        b['map'].clear()
        L = b['L']; R = b['R']
        if L > R:
            b['dirty'] = False
            return
        # Use dictionary aggregation to avoid sorting: O(k) instead of O(k log k)
        # per (cid, child) keep max distance
        per_cid = {}
        for i in range(L, R + 1):
            ai = A[i]
            for (cid, child, d) in cd.chain[ai]:
                cmap = per_cid.get(cid)
                if cmap is None:
                    cmap = {}
                    per_cid[cid] = cmap
                prev = cmap.get(child)
                if prev is None or d > prev:
                    cmap[child] = d
        # compute top1/top2 per cid
        for cid, cmap in per_cid.items():
            best1 = NINF; best2 = NINF; ch1 = -2
            for child, mx in cmap.items():
                if mx > best1:
                    if ch1 != child:
                        best2 = best1
                    best1 = mx; ch1 = child
                elif child != ch1 and mx > best2:
                    best2 = mx
            agg = (best1, ch1, best2)
            b['map'][cid] = agg
        b['dirty'] = False

    def append(x):
        A.append(x)
        ensure_blocks()
        if blocks:
            blocks[-1]['dirty'] = True

    def pop_back():
        if len(A) <= 1: return
        A.pop()
        ensure_blocks()
        if blocks:
            blocks[-1]['dirty'] = True
        while blocks and blocks[-1]['L'] > blocks[-1]['R']:
            blocks.pop()

    def find_in_chain(node, cid):
        ids = chain_ids[node]
        if not ids:
            return (NINF, -2, NINF)
        i = bisect.bisect_left(ids, cid)
        if i < len(ids) and ids[i] == cid:
            return (chain_d[node][i], chain_child[node][i], NINF)
        return (NINF, -2, NINF)

    def find_in_block(b, cid):
        ag = b['map'].get(cid)
        return ag if ag is not None else (NINF, -2, NINF)

    def query_centroid_on_range(l, r, cid):
        acc = (NINF, -2, NINF)
        if l > r: return acc
        bl = (l - 1) // B; br = (r - 1) // B
        merge = merge_agg
        find_chain = find_in_chain
        find_block = find_in_block
        blks = blocks
        if bl == br:
            if blocks[bl]['dirty']: rebuild_block(bl)
            for i in range(l, r + 1):
                acc = merge(acc, find_chain(A[i], cid))
            return acc
        # left partial
        if blks[bl]['dirty']: rebuild_block(bl)
        for i in range(l, blks[bl]['R'] + 1):
            acc = merge(acc, find_chain(A[i], cid))
        # full blocks
        for bidx in range(bl + 1, br):
            if blks[bidx]['dirty']: rebuild_block(bidx)
            acc = merge(acc, find_block(blks[bidx], cid))
        # right partial
        if blks[br]['dirty']: rebuild_block(br)
        for i in range(blks[br]['L'], r + 1):
            acc = merge(acc, find_chain(A[i], cid))
        return acc

    out_lines = []
    last_ans = 0

    for _ in range(m):
        tp = int(next(it))
        if tp == 1:
            x = int(next(it))
            x = ((x ^ abs(last_ans)) % n) + 1
            append(x)
        elif tp == 2:
            pop_back()
        else:
            l = int(next(it)); r = int(next(it)); x = int(next(it))
            length = len(A) - 1
            if length == 0:
                out_lines.append('0')
                last_ans = 0
                continue
            l = ((l ^ abs(last_ans)) % length) + 1
            r = ((r ^ abs(last_ans)) % length) + 1
            if l > r: l, r = r, l
            x = ((x ^ abs(last_ans)) % n) + 1
            best = NINF
            ids = chain_ids[x]
            chs = chain_child[x]
            ds = chain_d[x]
            for idx in range(len(ids)):
                c = ids[idx]; child = chs[idx]; dx = ds[idx]
                ag = query_centroid_on_range(l, r, c)
                add = best_excluding(ag, child)
                if add != NINF:
                    cand = dx + add
                    if cand > best: best = cand
            if best == NINF: best = 0
            out_lines.append(str(best))
            last_ans = best

    sys.stdout.write('\n'.join(out_lines))


if __name__ == '__main__':
    main()