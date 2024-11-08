class Node:
    def __init__(self):
        self.mark = False
        self.edges = [None] * 26

def trie_insert(node, str, idx=0):
    if(idx == len(str)):
        node.mark = True
        return
    
    char_idx = ord(str[idx]) - ord('a')
    if(node.edges[char_idx] == None):
        node.edges[char_idx] = Node()

    trie_insert(node.edges[char_idx], str, idx+1)


def trie_search(node, str, idx=0):
    if(idx == len(str)):
        return node.mark
    
    char_idx = ord(str[idx]) - ord('a')
    if(node.edges[char_idx] == None):
        return False
    return trie_search(node.edges[char_idx], str, idx+1)

def trie_delete(node, str, idx=0):
    # if(trie_search(node, str) == False):
    #     raise Exception("Item not found")
    
    # for i in range(len(str)):
    #     node = node.edges[ord(str[i]) - ord('a')]
    # node.mark = False

    if(idx == len(str)):
        if(node.mark == False):
            raise Exception("Item not found")
        node.mark = False
        return
    
    if(node.edges[ord(str[idx]) - ord('a')] == None):
        raise Exception("Item not found")
    trie_delete(node.edges[ord(str[idx]) - ord('a')], str, idx+1)



if __name__ == "__main__":
    root = Node()
    trie_insert(root, "hello")
    trie_insert(root, "how")
    trie_insert(root, "what")
    print(trie_search(root, "how"))
    print(trie_search(root, "hell"))
    print(trie_search(root, "hello"))
    trie_delete(root, "hello")
    print(trie_search(root, "hello"))
    # trie_delete(root, "hello")