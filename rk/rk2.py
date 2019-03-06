import re

def printWord(text, n):
    j = n
    while text[j] != " " and j > -1:
        j = j - 1
    j = j + 1
    while j < n + 1:
        print(text[j], end = "")
        j = j + 1

def findInf(text):
    s = len(text)
    i = 0
    while i < s:
        if text[i] == 'ь' or text[i] == 'и':
            if i > 0:
                if text[i-1] == 'т':
                    print("\n")
                    printWord(text, i)
    
        i = i + 1

if __name__ == '__main__':
    text = "ходить идти но не бежать но не плыть и никак не забывать красивый зачет по АА, полученный в начале марта *_0"
    #findInf(text)
    print("\n")
    print(re.findall("\w*ть", text))
    print(re.findall("\w*ти", text))


    print("\n")
    words = text.split()
    for word in words:
        if (word[-2::1] == 'ть' or
            word[-2::1] == 'ти'):
            print(word)

print("\n")
