import sys

# constant used in the bitstream update (from the reference program)
C = 9223372036854775821

# chunk size for table-driven processing (power of two recommended)
CHUNK = 8


def _build_chunk_table(t=CHUNK):
    size = 1 << t
    masks = [0] * size
    outs = [b''] * size
    cons = [0] * size
    ones = [0] * size
    K = C
    for x in range(size):
        rtmp = x
        out = bytearray()
        for _ in range(t):
            bit = rtmp & 1
            out.append(bit)
            if bit:
                rtmp = (rtmp >> 1) ^ K
            else:
                rtmp = (rtmp >> 1)
        masks[x] = rtmp & ((1 << 64) - 1)
        outs[x] = bytes(out)
        oc = out.count(1)
        ones[x] = oc
        cons[x] = t + oc
    return masks, outs, cons, ones


# build chunk table once
_MASK64 = (1 << 64) - 1
_TABLE_MASKS, _TABLE_OUTS, _TABLE_CONS, _TABLE_ONES = _build_chunk_table(CHUNK)

def process_case(s, n):
    # initialize as in the reference
    f = 0
    na = 0.0
    ng = 0
    a = -19.0
    r = -19

    s2 = float(s) * float(s)

    # reuse bytearray for v0 (we only need to store v0)
    v0 = bytearray()

    C_local = C
    inv19 = 1.0 / 19.0
    inv1919 = 1.0 / 1919.0

    while a < s2:
        na += inv19
        f1 = f

        # build v0 using chunked table when possible
        v0.clear()
        m = n
        r_local = r
        append = v0.append
        tbl_mask = _TABLE_MASKS
        tbl_outs = _TABLE_OUTS
        tbl_cons = _TABLE_CONS
        CH = CHUNK
        chunk_mask = (1 << CH) - 1
        while m > 0:
            if m >= 2*CH:
                low = r_local & chunk_mask
                consv = tbl_cons[low]
                if consv <= m:
                    # apply chunk
                    outb = tbl_outs[low]
                    v0.extend(outb)
                    r_local = (r_local >> CH) ^ tbl_mask[low]
                    m -= consv
                    continue
            # fallback single-step
            bit = r_local & 1
            append(bit)
            if bit:
                r_local = (r_local >> 1) ^ C_local
            else:
                r_local = (r_local >> 1)
            m -= 1 + bit

        # now r_local is r after rep0; set r to it
        r = r_local

        # build v1 but compare on the fly with v0 for common prefix using chunks
        m = n
        idx = 0
        equal_prefix = True
        len0 = len(v0)
        tbl_outs = _TABLE_OUTS
        tbl_cons = _TABLE_CONS
        tbl_mask = _TABLE_MASKS
        while m > 0:
            if equal_prefix and m >= 2*CH and idx < len0:
                low = r & ((1 << CH) - 1)
                consv = tbl_cons[low]
                if consv <= m:
                    outb = tbl_outs[low]
                    # prepare memoryview for fast slice compares
                    memv0 = memoryview(v0)
                    # compare up to len0
                    if idx + CH <= len0:
                        if equal_prefix and outb != memv0[idx:idx+CH]:
                            equal_prefix = False
                    else:
                        # partial compare
                        upto = min(CH, len0 - idx)
                        if upto > 0 and equal_prefix and outb[:upto] != memv0[idx:idx+upto]:
                            equal_prefix = False
                    idx += CH
                    r = (r >> CH) ^ tbl_mask[low]
                    m -= consv
                    continue
            # fallback single-step
            bit = r & 1
            if equal_prefix and idx < len0 and bit != v0[idx]:
                equal_prefix = False
            idx += 1
            if bit:
                r = (r >> 1) ^ C_local
            else:
                r = (r >> 1)
            m -= 1 + bit

        # After generating v1 fully, equal_prefix reflects whether all positions i<min(len0,len1) matched
        if min(len0, idx) == 0:
            equal_prefix = False

        if equal_prefix:
            ng += s
            f = round(ng / na)
            if f == f1:
                a = a + inv1919
            else:
                a = 0.0

    return f

def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    T = int(next(it))
    out_lines = []
    for _ in range(T):
        s = int(next(it)); n = int(next(it))
        out_lines.append(str(process_case(s, n)))
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()