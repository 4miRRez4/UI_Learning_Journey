def gray_code_recursive(n):
    if(n == 0):
        codes = [""]
        return codes

    tmp = gray_code_recursive(n-1)
    tmp_reversed = tmp[::-1]

    for i in range(len(tmp)):
        tmp[i] = "0" + tmp[i]
        tmp_reversed[i] = "1" + tmp_reversed[i]
    
    return tmp + tmp_reversed

n = int(input())
for code in gray_code_recursive(n):
    print(code)