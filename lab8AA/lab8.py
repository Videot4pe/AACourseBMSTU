def slides(pattern, m):
    slide = 256*[-1]
    for i in range(m):
        slide[ord(pattern[i])] = i;
    return slide

def sufpref(pattern, M, distance):
    len = 0
    distance[0]
    i = 1
    while i < M:
        if pattern[i] == pattern[len]:
            len += 1
            distance[i] = len
            i += 1
        else:
            if len:
                len = distance[len-1]
            else:
                distance[i] = 0
                i += 1

def bm(text, pattern):
    m = len(pattern)
    n = len(text)
    slide = slides(pattern, m)
    s = 0
    while(s <= (n - m)):
        j = m - 1
        while (j >= 0 and pattern[j] == text[s+j]):
            j -= 1
        if (j < 0):
            print(s)
            s += (m-slide[ord(text[s+m])])
        else:
            s += max(1, j-slide[ord(text[s+j])])

def kmp(pattern, text):
    M = len(pattern)
    N = len(text)
    distance = [0]*M
    j = 0
    sufpref(pattern, M, distance)
    i = 0
    while i < N:
        if pattern[j] == text[i]:
            i += 1
            j += 1
        if j == M:
            print(i - j)
            j = distance[j-1]
        elif i < N and pattern[j] != text[i]:
            if j:
                j = distance[j-1]
            else:
                i += 1

if __name__ == '__main__':
    text1 = "JHKLKLKJKJ"
    pattern1 = "KLK"
    kmp(pattern1, text1)
    text2 = "ABCDFDGDABCAAA"
    pattern2 = "ABC"
    bm(text2, pattern2)
    
    kmp(pattern2, text2)
