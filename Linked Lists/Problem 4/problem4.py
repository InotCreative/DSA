class Node:
    def __init__(self, data: int):
        self.data: int = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head: Node = None
    
    def append(self, data: int) -> None:
        newNode: Node = Node(data)
        newNode.next = None

        if (self.head is None):
            self.head = newNode
            self.head.next = self.head
            return
        
        temp: Node = self.head
        
        while (temp is not None):
            if (temp.next == self.head):
                temp.next = newNode
                newNode.next = self.head
                return

            temp = temp.next
    
    def betterAppedn(self, data: list[int]):
        for nums in data:
            self.append(nums)
    
    def printList(self):
        temp: Node = self.head

        while (temp is not None):
            print(f"{temp.data}->", end="")

            temp = temp.next

            if (temp == self.head):
                break
            
        print("NULL\n")

def main() -> int:
    list: LinkedList = LinkedList()

    list.betterAppedn([1, 2, 3, 4, 5, 6])
    list.printList()
    
    return 0

if __name__ == "__main__":
    main()        