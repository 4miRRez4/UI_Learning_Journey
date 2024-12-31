def gray_code_bitwise(n):
    if n == 0:
        return []
    
    codes = []
    num_elements = 1 << n
    
    for i in range(num_elements):
        code = i ^ (i >> 1)
        codes.append(bin(code)[2:].zfill(n))  

    return codes

n = int(input())
for code in gray_code_bitwise(n):
    print(code)