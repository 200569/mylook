#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int pierwsza(long int);

int main(int argc, char *argv[]) {
    int lproc;
    int lzakresow = atoi(argv[1]); //liczba potomnych
    printf("Liczba potomnych: %d\n",lzakresow);

    int tab[lzakresow][2]; //tablica 2 wymiarowa
    int lpierwszych = 0;
    long int pocz = atoi(argv[2]);
    long int koniec = atoi(argv[3]);
    printf("Poczatek = %ld, Koniec = %ld.\n",pocz,koniec);
    int tpocz = time(NULL);
    if (argc < 3) {printf("Za malo argumentow");exit(1);}
    long int malyzakres = (koniec-pocz)/lzakresow;
    for (lproc = 0; lproc<lzakresow;lproc++){
        tab[lproc][0] = lproc * malyzakres;
        tab[lproc][1] = (lproc+1) * malyzakres - 1;
    }

    int pid,status,i;
    for (lproc = 0; lproc<lzakresow;lproc++){
        if((pid = fork()) == 0) {
            /* Proces potomny ---*/
            int lpierwszych = 0;
            //printf("PID procesu potomnego %d: %d \n", lproc,getpid());
            long int pocz = tab[lproc][0];
            long int koniec = tab[lproc][1];
            printf("Poczatek = %ld, Koniec = %ld\n", pocz, koniec);
                for(i=pocz;i<koniec;i++) {
                        if (pierwsza(i)){
                        lpierwszych++;
                    }
            }
          exit(lpierwszych);
        }
        /* Proces macierzysty */
        //printf("Macierzysty = %d \n",getpid());

    }
   for (lproc = 0; lproc<lzakresow;lproc++){
        pid = wait(&status);
        int exitstat = WEXITSTATUS(status);
        printf("Proces %d zakoñczony status: %d\n",pid,exitstat);
        lpierwszych=lpierwszych+exitstat;
   }
    int czas = tpocz - time(NULL);
    printf("Liczba liczb pierwszych: %d\n, znaleziono w czasie: %d\n",lpierwszych, czas);
   return 0;
}


int pierwsza(long int n){
    // Funkcja zwraca 1 gdy n jest liczb¹ pierwsza 0 gdy nie
    long int i;
    for(i=2;i*i<=n;i++) {
            if(n%i == 0) return(0) ;
    }
    return(1);
}
