# Genetic-Algorithm-Sudoku
sudoku for the 3rd time, god help me &lt;3

note: i added getchar(); after each print of generation because when running the app it either:
    - freezes completely, only says generation 0 and its fitness
    - it crashes; 
so i added getchar to manually check the program and all the generations... if they even show up...

<pre>
MAIN STEPS
        1. For each generation:
            - Generate offspring from selected parents
            - Apply crossover and mutation
            - Evaluate fitness
            - Track best individual so far
            - Exit early if perfect solution is found
        2. After loop: Print best solution overall
</pre>

### BUILDING THE APP:
```
gcc main.c sudoku.c ga.c util.c -o ga_solvedsudoku
```
run either the .exe app in the folder or by cmd