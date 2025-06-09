from Node import Node
from order import inorder

def insert(node, val):
    if(node.label > val):
        if(node.leftChild != None):
            insert(node.leftChild, val)
        else:
            node.leftChild = Node(val, node)
    else:
        if(node.rightChild != None):
            insert(node.rightChild, val)
        else:
            node.rightChild = Node(val, node)


def find_min(node):
    if(node.leftChild == None):
        return node
    else:
        return find_min(node.leftChild)
    

def find_max(node):
    if(node.rightChild == None):
        return node
    else:
        return find_max(node.rightChild)
    

def search(node, label):
    if(node == None):
        return -1
    if(node.label == label):
        return node
    elif(node.label > label):
        return search(node.leftChild, label)
    else:
        return search(node.rightChild, label)
    
def replaceNodeWithParent(nodeA, nodeB):
    if(nodeA.parent): #nodeA isn't root
        if(nodeA.parent.leftChild == nodeA):
            nodeA.parent.leftChild = nodeB
        else:
            nodeA.parent.rightChild = nodeB


    if(nodeB):
        nodeB.parent = nodeA.parent

def delete(node, val):
    if(node is None): #val not found
        return

    if(node.label < val):
        delete(node.rightChild, val)
    elif(node.label > val):
        delete(node.leftChild, val)
    else: #found
        if(node.rightChild and node.leftChild):
            newNode = find_max(node.leftChild)
            node.label = newNode.label
            delete(newNode, newNode.label)
        elif(node.rightChild):
            replaceNodeWithParent(node, node.rightChild)
        else:
            replaceNodeWithParent(node, node.leftChild)

def LCA(curr_root, a, b):
    if(a < curr_root.label and b < curr_root.label):
        LCA(root.leftChild, a, b)
    elif(a > curr_root.label and b > curr_root.label):
        LCA(curr_root.rightChild, a, b)
    else:
        print(curr_root.label)


def root_left_subtree_size(preorder_list, inorder_list):
    root = preorder_list[0]
    return inorder_list.index(root)

def left_subtree_size(preorder_list, inorder_list, node_label):
    return inorder_list.index(node_label)

def change_order(preorder_list, inorder_list):
    if not preorder_list or not inorder_list:
        return []
    
    root  = preorder_list[0]
    ind_of_root_in_inorder = inorder_list.index(root)

    inorder_left = inorder_list[0: ind_of_root_in_inorder]
    inorder_right = inorder_list[ind_of_root_in_inorder+1: ]

    preorder_left = preorder_list[1:1+ind_of_root_in_inorder]
    preorder_right = preorder_list[ind_of_root_in_inorder+1: ]

    return change_order(preorder_left, inorder_left) + change_order(preorder_right, inorder_right) + [root]

if __name__ == "__main__": 
    root = Node(5, None)
    insert(root, 9)
    insert(root, 10)
    insert(root, 3)
    insert(root, 8)
    insert(root, 7)
    insert(root, 2)
    insert(root, 1)
    insert(root, 4)
    insert(root, 6)
    inorder(root)
    print ("Searching value 8 in tree:", str(search(root, 8)))
    print ("Path to the min node in tree:", find_min(root))
    print ("Path to the max node in tree:", find_max(root))
    delete(root, 8)
    inorder(root)
    print(LCA(root, 5, 10))
    print(change_order([2,1,3], [1,2,3]))