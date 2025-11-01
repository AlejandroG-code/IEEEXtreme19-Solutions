def modinv(a, p):
    return pow(a, p - 2, p)

def add_points(a, b, p, x1, y1, x2, y2):
    if x1 == x2 and (y1 + y2) % p == 0:
        return "POINT_AT_INFINITY"
    
    if x1 == x2 and y1 == y2:
        denom = (2 * y1) % p
        if denom == 0:
            return "POINT_AT_INFINITY"
        m = ((3 * x1 * x1 + a) * modinv(denom, p)) % p
    else:
        denom = (x2 - x1) % p
        if denom == 0:
            return "POINT_AT_INFINITY"
        m = ((y2 - y1) * modinv(denom, p)) % p
    x3 = (m * m - x1 - x2) % p
    y3 = (m * (x1 - x3) - y1) % p
    return f"{x3} {y3}"

def solve():
    import sys
    data = sys.stdin.read().strip().split()
    T = int(data[0])
    out = []
    idx = 1
    for _ in range(T):
        a = int(data[idx]); b = int(data[idx+1]); p = int(data[idx+2])
        x1 = int(data[idx+3]); y1 = int(data[idx+4])
        x2 = int(data[idx+5]); y2 = int(data[idx+6])
        idx += 7
        out.append(add_points(a, b, p, x1, y1, x2, y2))
    print("\n".join(out))

if __name__ == "__main__":
    solve()
