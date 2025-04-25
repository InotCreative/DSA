'''
Input: linked list: 1->2->3->4->5
Output: 3 
Explanation: There are 5 nodes in the linked list and there is one middle node whose value is 3.


Input: linked list = 10 -> 20 -> 30 -> 40 -> 50 -> 60
Output: 40
Explanation: There are 6 nodes in the linked list, so we have two middle nodes: 30 and 40, but we will return the second middle node which is 40.
'''

class Node:
    def __init__(self, data: int):
        self.data: int = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head: Node = None

    def append(self, data: int) -> None:
        newNode: Node = Node(data)

        if (self.head is None):
            self.head = newNode
            return

        temp: Node = self.head

        while (temp is not None):
            if (temp.next is None):
                temp.next = newNode
                return

            temp = temp.next
    
    def betterAppend(self, dataList: list[int]) -> None:
        for i in dataList:
            self.append(i)
    
    def printList(self) -> None:
        temp: Node = self.head

        while (temp is not None):
            print(f"{temp.data}->", end="")
            temp = temp.next
    
        print("NULL")
    
    def getLength(self) -> int:
        length: int = 0

        temp: Node = self.head

        while (temp is not None):
            length += 1
            temp = temp.next
    
        return length

    def getMiddle(self) -> None:
        length: int = self.getLength()
        length = length // 2

        temp: Node = self.head

        while (length != 0):
            temp = temp.next
            length -= 1

        print(f"{temp.data}\n")
    
    def freeList(self) -> None:
        self.head = None


def main() -> int:
    list: LinkedList = LinkedList()
    list.betterAppend([1, 2, 3, 4, 5])
    list.printList()
    list.getMiddle()
    list.freeList()

    list.betterAppend([10, 20, 30, 40, 50, 50])
    list.printList()
    list.getMiddle()
    list.freeList()

if __name__ == "__main__":
    main()