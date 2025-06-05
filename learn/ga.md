### GENETIC ALGORYTHM SIMPLE EXPLANATION

#### STEPS
1. Start (Initialization)

2. Evaluation (Fitness)

3. Selection: choosing "parents" to create a new generation

4. Crossing (Crossover)

5. Mutation

6. New Population

7. Loop: going back to step 2 and doing the same process for the new population


### EXPLANATION IN POLISH

START
1. ZAINICJALIZUJ populację (stwórz losową grupę osobników)
   
2. POWTÓRZ (przez określoną liczbę pokoleń LUB dopóki nie znajdziesz rozwiązania LUB dopóki fitness się poprawia):
   
    a. OCEŃ fitness każdego osobnika w populacji.

    b. WYBIERZ rodziców na podstawie ich fitness.
   
    c. WYGENERUJ nową populację:
   
        i. Zastosuj KRZYŻOWANIE na wybranych parach rodziców, tworząc potomstwo.
        ii. Zastosuj MUTACJĘ do potomstwa z małym prawdopodobieństwem.
        iii. (Opcjonalnie) Dodaj najlepszych osobników ze starej populacji do nowej (ELITARYZM).
        iv. Uzupełnij nową populację nowo wygenerowanym potomstwem.
   
    d. ZASTĄP starą populację nową populacją.
   
5. ZAKOŃCZ (zwróć najlepszego osobnika znalezionego podczas działania algorytmu).
   
KONIEC


### INFORMATIONAL VIDEOS
https://www.youtube.com/watch?v=MwnRzXj8pJA [IN POLISH]

https://www.youtube.com/watch?v=yxWIjyCVM-s

https://www.youtube.com/watch?v=uQj5UNhCPuo&pp=ygUSZ2VuZXRpYyBhbGdvcml0aG0g

https://www.youtube.com/watch?v=1i8muvzZkPw&pp=ygUSZ2VuZXRpYyBhbGdvcml0aG0g
