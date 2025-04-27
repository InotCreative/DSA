class Node:
    def __init__(self, value: int):
        self.data: int = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.head: Node = None
    
    def linearAppend(self, value: int) -> None:
        newNode: Node = Node(value)
        
        if (self.head is None):
            self.head = newNode
            return
        
        temp: Node = self.head
        
        while (temp is not None):
            if (temp.next is None):
                temp.next = newNode
                
                break

            temp = temp.next
    
    def convertLinearToCircular(self):
        temp: Node = None
        
        while (temp is not None):
            if (temp.next is None):
                temp.next = self.head
                break
    
    def betterAppend(self, data: list[int]) -> None:
        for nums in data:
            self.linearAppend(nums)
    
    def printList(self):
        temp: Node = self.head
        
        while (temp != None):
            print(f"{temp.data}->", end="")
            
            if (temp.next == self.head):
                break
            
            temp = temp.next
        
        print("NULL\n")

def main() -> int:
    linkedList = LinkedList()
    
    listData = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    linkedList.betterAppend(listData)
    linkedList.printList()
    
    linkedList.convertLinearToCircular()
    linkedList.printList()
    
if __name__ == "__main__":
    main()        