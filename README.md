# Genetic-Algorithm-Sudoku
sudoku for the 3rd time, god help me &lt;3

---
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

---
### FITNESS EXPLANATION

- each row, column, and box can contribute up to 9 unique digits
- there are 9 rows + 9 columns + 9 boxes = 27 groups
- maximum fitness = 27 × 9 = 243
  
which means a fully valid Sudoku with no repeats anywhere

## EXAMPLES WHEN RUNNING THE PROGRAM

![image](https://github.com/user-attachments/assets/81bcd57b-6134-4d7f-8041-b35b310c9045)

### BUILDING THE APP:
```
gcc main.c sudoku.c ga.c util.c -o ga_solvedsudoku
```
run either the .exe app in the folder or by cmd

![image](https://github.com/user-attachments/assets/8327e11b-b4c0-46f0-a2f7-715659e8fe00)
