def isThere(word, sentence):
    #is word in sentence
    start =0; #variable for iterating through sentece
    while(start!= len(sentence) - len(word) +1):
        status = True
        for i in range(len(word)): #iterating from start to start + length of word and comparing to word
            if (sentence[start+i] != word[i]):
                status = False
                break
        if(status) : return status
        start+=1
    return False
