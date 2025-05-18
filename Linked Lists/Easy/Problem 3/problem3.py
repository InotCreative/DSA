class Node:
    def __init__(self, value: int):
        self.data = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None
    
    def append(self, value: int):
        newNode: Node = Node(value)

        if (self.head is None):
            self.head = newNode
            return
        