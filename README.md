# AVL tree and a chained hash table

## Project Overview
This project involves the implementation of a phonebook system using two different data structures: an AVL tree and a chained hash table. The goal is to compare the performance and efficiency of these data structures when used to store and query name-phone number pairs. The project also includes a user-interactive component, where the user can query, update, and exit the program using commands in a console environment. Additionally, the project includes performance analysis through the creation of plots that compare the efficiency of the data structures for various input sizes and hash table configurations.

- The program takes input from a file and inserts all name-phone pairs into the selected structure. It then allows interactive operations:

  - g — get phone number by name.
  - u — update phone number for an existing name.
  - q — quit the program.

## Objectives
- Implement an AVL Tree:
  - Learn how to implement a self-balancing binary search tree (BST) and apply it to store and manage name-phone pairs.
  - Implement AVL tree operations such as insertion with balance checking, rotations, and height calculations.
- Implement a Chained Hash Table:
  - Implement a hash table that uses separate chaining for collision resolution.
  - Learn how to compute hash values based on the ASCII values of strings and how to handle collisions using linked lists.
- Performance Comparison:
  - Analyze the performance of the AVL tree and hash table by measuring the tree height (AVL) and maximum chain length (hash table).
  - Generate plots to compare the efficiency of both data structures in terms of query/update performance.
  - Experiment with different hash table sizes to see their effect on performance.
- User Interaction:
  - Implement a user-driven interactive system where the user can:
  - Get a phone number by entering a name.
  - Update the phone number for a given name.
  - Quit the program.
 
## Compilation Instructions:
Use the following command to compile the project:
```bash
g++ -std=c++17 -o main main.cpp 
```
Run Instructions:
- For AVL Tree:
```bash
./main phones/phones100.data avl
```
- For Hash Table:
```bash
./main phones/phones100.data hash 127
```
## Plots
- Hash Table Chain Length vs. Input Size Graph:
[Graph1](images/Graph_1_Sandu.pdf)
- AVL Tree Height vs. Input Size Graph:
