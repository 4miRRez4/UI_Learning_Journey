class Trie_Node:
    def __init__(self):
        self.cnt = 0
        self.edges = [None]*26

def trie_insert(node, str, idx=0):
        if(len(str) == idx):
            node.cnt += 1
            return
        
        char_idx = ord(str[idx]) - ord('a')
        if(node.edges[char_idx] == None):
            node.edges[char_idx] = Trie_Node()

        trie_insert(node.edges[char_idx], str, idx+1)

def trie_search(node, str, idx=0):
        if(len(str) == idx):
            return node

        char_idx = ord(str[idx]) - ord('a')
        if(node.edges[char_idx] == None):
            return 0
        
        return trie_search(node.edges[char_idx], str, idx+1)
    
def trie_delete(node, str, idx=0):
        if(len(str) == idx):
            if(node.cnt == 0):
                raise Exception("not found!")
            node.cnt = 0
            return

        char_idx = ord(str[idx]) - ord('a')
        if(node.edges[char_idx] == None):
            raise Exception("not found!")
        
        trie_delete(node.edges[char_idx], str, idx+1)

def frequent_extension(prefix_node, frequent):    
    for i in range(26):
        if (prefix_node.edges[i] != None):
            if(prefix_node.edges[i].cnt > frequent[1]):
                 frequent[1] = prefix_node.edges[i].cnt
        
            frequent[0] += chr(ord('a') + i)
            frequent_extension(prefix_node.edges[i], frequent)



if __name__ == "__main__":
    root = Trie_Node()

    n = int(input())
    for i in range(n):
        trie_insert(root, input())

    q = int(input())
    for i in range(q):
         prefix = input()
         prefix_node = trie_search(root, prefix)

         if(prefix_node == 0):
            print(-1)
         else:
            frequent = [prefix, prefix_node.cnt]
            frequent_extension(prefix_node, frequent)
            print(frequent[0])
            print(frequent[1])