import Node

def preorder(curr_root):
    if(curr_root == None):
        return
    
    print(curr_root.label)
    preorder(curr_root.leftChild)
    preorder(curr_root.rightChild)

def inorder(curr_root):
    if(curr_root == None):
        return
    
    inorder(curr_root.leftChild)
    print(curr_root.label)
    inorder(curr_root.rightChild)

def postorder(curr_root):
    if(curr_root == None):
        return
    
    postorder(curr_root.leftChild)
    postorder(curr_root.rightChild)
    print(curr_root.label)
    