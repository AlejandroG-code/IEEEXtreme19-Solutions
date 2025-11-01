import sys

def solve():
    data = sys.stdin.read().split()
    if not data:
        return

    it = iter(data)
    T = int(next(it))
    
    results = []
    
    for _ in range(T):
        try:
            N = int(next(it))
            K = int(next(it))
            S = next(it)
        except StopIteration:
            break
        
        total_flips = 0
        
        flip_end_counts = [0] * (N + 1)
        
        active_flips = 0
        
        for i in range(N):
            
            if i >= K:
                active_flips = (active_flips + flip_end_counts[i]) % 2
            
            original_state = S[i]
            
            is_happy = (original_state == 'H')
            
            if active_flips == 1:
                is_happy = not is_happy
            
            
            if not is_happy:
                
                if i + K > N:
                    total_flips = -1
                    break
                
                total_flips += 1
                active_flips = (active_flips + 1) % 2
                
                if i + K <= N:
                    flip_end_counts[i + K] = (flip_end_counts[i + K] + 1) % 2
        results.append(str(total_flips))

    sys.stdout.write('\n'.join(results) + '\n')

if __name__ == '__main__':
    if sys.stdin.isatty():
        pass
    else:
        sys.setrecursionlimit(2000)
        solve()