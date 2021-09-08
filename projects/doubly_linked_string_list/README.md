# Doubly Linked String List

> "Give thanks to the LORD because He is good and His love is eternal" - Psalm 118: 1

The doubly-linked-list of strings is an array of strings kept on the heap as opposed to the stack.

## Why Linked Lists

Storing variables on the heap enables the reallocation of memory to the array as the list shrinks or expands at runtime. It however is complicated for the engineer as he/she has to handle the allocation and freeing of memory themselves.

Imagine you created a list (array) on the heap with a given size using the normal `<type> variable[num];` syntax or something. Then you need to add more items that make it bigger than `num`. What do you do?

You could copy the entire array, save it in a bigger array and destroy the old instance.

Or you could just keep track of the next item of a given element on each element such that all you need to do is
to go to the last element of the array and update its next element to be the address of the new items you want to add.

Thus the linked list is created. This makes it possible to move from lower indices to higher indices.

What if then you need to access the element before the current element?

If only you also had the address of the previous element saved on each element. Good thing doubly-linked lists exist!

## Dependencies

- [gcc 7.5](https://gcc.gnu.org/install/index.html)
- [CMake](https://cmake.org/download/)

## Development Environment

- Operating system: [Ubuntu 18.04](https://releases.ubuntu.com/18.04.5/)
- IDE: [Visual Studio Code](https://code.visualstudio.com/)
- Compiler: [gcc 7.5](https://gcc.gnu.org/install/index.html)
- Testing Framework: [Check](https://libcheck.github.io/check/)
- Building Framework: [CMake](https://cmake.org/download/)

## VS Code Extensions

- [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

## How to Run

- Install [gcc 7.5](https://gcc.gnu.org/install/index.html)
- Install [CMake](https://cmake.org/download/)
- Clone the repository and enter the 'doubly_linked_string_list' directory

  ```sh
  git clone https://github.com/learn-along/learn-c && cd learn-c/projects/doubly_linked_string_list
  ```

- Make the build script executable

  ```sh
  sudo chmod +x build.sh
  ```

- Run the build script

  ```sh
  ./build.sh
  ```

- Run the `main` app

  ```sh
  build/src/main
  ```

- Find the artefact `main` in the `build/src` folder

  ```sh
  cd build/src
  ```

## How to Test

- Install [gcc 7.5](https://gcc.gnu.org/install/index.html)
- Install [CMake](https://cmake.org/download/)
- Clone the repository and enter the 'doubly_linked_string_list' directory

  ```sh
  git clone https://github.com/learn-along/learn-c && cd learn-c/projects/doubly_linked_string_list
  ```

- Make the test script executable

  ```sh
  sudo chmod +x test.sh
  ```

- Run the test script

  ```sh
  ./test.sh
  ```

## Acknowledgment

This assignment was picked from [the challenges in "Crafting Interpreters" Introduction chapter](https://craftinginterpreters.com/introduction.html)

## License

Copyright (c) 2021 [Martin Ahindura](https://github.com/Tinitto) Licensed under the [MIT License](./LICENSE)
