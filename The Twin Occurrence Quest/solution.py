import sys

def solve_robust():
    data = sys.stdin.read().split()
    
    if not data:
        return

    data_iter = iter(data)
    
    try:
        N = int(next(data_iter))
        Q = int(next(data_iter))
        
        A = []
        for _ in range(N):
            A.append(int(next(data_iter)))
            
    except StopIteration:
        return

    map_positions = {}
    for i in range(N):
        value = A[i]
        position_1_indexed = i + 1
        
        if value not in map_positions:
            map_positions[value] = [position_1_indexed, position_1_indexed]
        else:
            map_positions[value][1] = position_1_indexed

    results = []
    for _ in range(Q):
        try:
            X = int(next(data_iter))
        except StopIteration:
            break
        
        if X in map_positions:
            first, last = map_positions[X]
            results.append(f"{first} {last}")
        else:
            results.append("-1 -1")

    sys.stdout.write('\n'.join(results) + '\n')


if __name__ == "__main__":
    solve_robust()