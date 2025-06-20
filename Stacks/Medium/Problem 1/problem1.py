"""
You are given an integer n. Return all well-formed parentheses strings that you can generate with n pairs of parentheses.

Example 1:

Input: n = 1

Output: ["()"]
Example 2:

Input: n = 3

Output: ["((()))","(()())","(())()","()(())","()()()"]
You may return the answer in any order.
"""
import random

def validateParenthesis(parenthesisArray: str) -> bool: # This function works in O(n) time

    stack: list[str] = []

    for symbol in parenthesisArray:
        if (symbol == '('): stack.append(symbol)
        if (symbol == ')'): 
            if (len(stack) == 0): 
                return False
            
            if (stack[-1] == '('): stack.pop()            

    if (len(stack) == 0): return True
    else: return False    



def generateParenthesis(n: int) -> list[str]:
    def generate_A():
        if random.choice([True, False]):  # Choose whether to go '(' A B or just B
            return '(' + generate_A() + generate_B()
        else:
            return generate_B()

    def generate_B():
        if random.choice([True, False]):  # Choose whether to emit ')' B or epsilon
            return ')' + generate_B()
        else:
            return ''  # epsilon
    
    while (len(generate_A()) != 6):
        

def main():
    generateParenthesis(3)

if __name__ == "__main__":
    main()