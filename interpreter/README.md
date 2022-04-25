# Interpreter

Interpreter for model language:

  * 1 - 0: Conditional operator: if (E) S else S

  * 2 - 2: For loops: for ([E];[E];[E]) S

  * 3 - 2: Transfer operator (for and while loops): continue

  * 4 - 2: Data types: int, real, string

  * 5 - 2: Additional operation: unary plus, unary minus

  * 6 - 2: Evaluation strategy: eager evaluation

## Build Interpreter

Build scrypt for fast compilation Interpreter  

    $ chmod +x ./make.sh

Build Interpreter

    $ ./make.sh

Run Interpreter:

    $ ./inter program_name
