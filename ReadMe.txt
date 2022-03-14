1. Au fost folositi 5 algoritmi de sortare: MergeSort, ShellSort, RadixSort, TimSort, CountigSort + algoritmul de sortare nativ functiei
sort() (Introsort).

2. Pentru ShellSort au fost folosite 2 metode de alegere a gap-urilor: secventa lui Knuth (algoritm denumit ShellSortKnuth in Time.txt) si
secventa lenght / 2^k (algoritm denumit ShellSort2k in Time.txt).

3. Pentru RadixSort au fost alese baza 10 (algoritm denumit RadixSortBase10 in Time.txt) si baza 2^16 cu operatii pe biti (algoritm denumit
RadixSortBinary in Time.txt)

4. In fisierul "date.in" se afla 15 teste.

5. In cazul in care, dintr-un motiv, testele nu se gasesc in "date.in" acestea se gasesc si mai jos.

6. CountingSort nu a fost folosit pentru ultimele 3 teste (unde valMax este de 10^12).

7. Afisarea se face in consola si nu in fisier. 

8. Pentru fiecare din cele 15 teste a fost generata o serie de numere care apoi este sortata folosind toate sortarile precizate mai sus, cu
exceptia countingSort-ului unde este generata o alta serie de numere pentru aceeasi parametri (acelasi N si Max). Acest lucru se intampla 
deoarece testele pentru countingSort sunt facute la finalul programului. Am ales aceasta solutie deoarece deoarece exista posibilitatea
ca din cauza valorii Max countingSort-ul sa faca programul sa dea crash, iar countingSortul fiind pus la final nu afecteaza si testele pentru
restul algoritmilor, in caz ca exista un crash (pentru testele introduse in "date.in" nu ar trebui sa exista astfel de probleme). Oricum
faptul ca ca sirurile generate pentru countingSort sunt diferite nu ar trebui sa afecteze intr-un mod considerabil timpii de rulare, acestia
fiind oricum foarte diferiti fata de timpii celorlati algoritmi (mai multe detalii in Sortari.pptx).

9. O lista cu concluzii in urma testelor se gaseste in Sortari.pptx.


Teste:


15
1000
1000
1000000
1000
100000000
1000
1000
1000000
1000000
1000000
100000000
1000000
1000
1000000000
1000000
1000000000
100000000
1000000000
1000
3000000000
1000000
3000000000
100000000
3000000000
1000
1000000000000
1000000
1000000000000
100000000
1000000000000

