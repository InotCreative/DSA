class Node:
    def __init__(self, value: int):
        self.value: int = value
        self.next = None
        
class LinkedList:
    def __init__(self):
        self.head: Node = None
    
    def append(self, value: int) -> None:
        newNode: Node = Node(value)
        
        if (self.head is None):
            self.head = newNode
            return
        
        temp: Node = self.head
        
        while (temp is not None):
            if (temp.next is None):
                temp.next = newNode
                return
            
            temp = temp.next
    
    def betterAppend(self, data: list[int]):
        for nums in data:
            self.append(nums)
    
    def reverseList(self):
        previous: Node = None
        current: Node = self.head
        next: Node = None
        
        while (current is not None):
            next = current.next
            current.next = previous
            
            previous = current
            
            current = next
        
        self.head = previous
        
    def printList(self):
        temp: Node = self.head
        
        while (temp is not None):
            print(f"{temp.value}->", end="")
            
            temp = temp.next
        
        print("NULL\n")

def main() -> int:
    list: LinkedList = LinkedList()
    
    list.betterAppend([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    list.printList()
    list.reverseList()
    list.printList()

if __name__ == "__main__":
    main()      