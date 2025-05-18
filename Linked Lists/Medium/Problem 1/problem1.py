class Node:
    def __init__(self, data: int):
        self.data: int = data
        self.next: 'Node' = None  # Use forward reference for type hint


class LinkedList:
    def __init__(self):
        self.head: 'Node' = None

    def append(self, data: int) -> None:
        newNode: Node = Node(data)

        if self.head is None:
            self.head = newNode
            return

        temp: Node = self.head
        while temp.next is not None:
            temp = temp.next
        temp.next = newNode

    def betterAppend(self, nums: list[int]) -> None:
        for i in nums:
            self.append(i)

    def printList(self) -> None:
        temp: Node = self.head
        while temp is not None:
            print(f"{temp.data}->", end="")
            temp = temp.next
        print("NULL")

    def solution(self) -> None:
        if self.head is None:
            print("EMPTY LIST")
            return

        if self.head.next is None:
            print("ONLY ONE NODE")
            return

        # Swap the first pair and update head
        prev: Node = None
        current: Node = self.head
        self.head = current.next  # New head will be second node

        while current and current.next:
            first: Node = current
            second: Node = current.next
            following: Node = second.next

            # Swap
            second.next = first
            first.next = following

            # Link previous pair's tail to current swapped head
            if prev:
                prev.next = second

            # Move pointers forward
            prev = first
            current = following

    def free(self) -> None:
        self.head = None


def main() -> int:
    listOne: LinkedList = LinkedList()

    # Case 1: Even number of nodes
    listOne.betterAppend([1, 2, 3, 4, 5, 6])
    listOne.printList()
    listOne.solution()
    listOne.printList()
    listOne.free()

    # Case 2: Odd number of nodes
    listOne.betterAppend([1, 2, 3, 4, 5])
    listOne.solution()
    listOne.printList()
    listOne.free()

    # Case 3: Single node
    listOne.betterAppend([42])
    listOne.solution()
    listOne.printList()
    listOne.free()

    # Case 4: Empty list
    listOne.solution()

    return 0


if __name__ == "__main__":
    main()
