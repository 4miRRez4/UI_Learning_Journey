class Node:
    def __init__(self, label, parent):
        self.label = label
        self.parent = parent
        self.leftChild = None
        self.rightChild = None
        
    def __str__(self): # Returns the path from root to node
        if self.parent:
            return str(self.parent) + " " + str(self.label)
        else:
            return str(self.label)
        

