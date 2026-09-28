import sys

def main():
    # Lee todo como texto
    data = sys.stdin.read().split()
    if not data:
        return

    n = int(data[0])
    k = int(data[1])
    words = data[2 : 2 + n]

    c = 0
    count = [0] * 26
    a_ord = ord('a') 
    result_words = []

    for w in words:
        out_chars = []
        for ch in w:
            e = ord(ch) - a_ord
            l = (e - c) % 26
            out_chars.append(chr(a_ord + l))
            count[l] += 1
            if count[l] % k == 0:
                c += 1
                
        result_words.append(''.join(out_chars))

    print(' '.join(result_words))

if __name__ == "__main__":
    main()