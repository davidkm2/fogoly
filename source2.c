// gcc source2.c -o source2 -lm
#include <stdio.h>
#define foglyokszama 10
#define T 5
#define L 5
#define NUM_COMMANDS 3
struct Fogoly {
	char dontes;
	int nyeremeny;
};

int calcnyeremeny(char mester, char fogoly) {
	double nyeremeny = 0;
	if (mester == 'C' && fogoly == 'C') {
		nyeremeny = 1;
	}
	if (mester == 'C' && fogoly == 'D') {
		nyeremeny = 0;
	}
	if (mester == 'D' && fogoly == 'C') {
		nyeremeny = T;
	}
	if (mester == 'D' && fogoly == 'D') {
		nyeremeny = 0;
	}
	return nyeremeny;
}

double w(P_m, P_t) {
	return (1 / (1 + (double)exp(-(P_m - P_t) / (double)0.1)));
}

int main() {
	struct Fogoly foglyok[L][L];
	char dontesek[2] = { 'C', 'D' };
	srand(time(0));
	//Inicializálás, mindenkinek legyen valami döntése kezdetben, nyeremény 0
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			struct Fogoly ujfogoly;
			ujfogoly.dontes = dontesek[rand() % 2];
			ujfogoly.nyeremeny = 0;
			foglyok[i][j] = ujfogoly;
			//printf("Fogoly: %d , döntése: %c \n", i, foglyok[i].dontes);
		}
	}
	int iteracioszam = 0;
	double aranyok[L * L];
	double iteraciok[L * L];
	while (iteracioszam < L * L) {
		printf("------------------------------------------------------\n\n\n");
		printf("%d . iteracio\n", iteracioszam);
		int tanitvanyxidx, tanitvanyyidx;
		int egyuttmukodok = 0;
		do {
			tanitvanyxidx = rand() % L;
			tanitvanyyidx = rand() % L;
		} while (tanitvanyxidx <= 1 || tanitvanyyidx <= 1 || tanitvanyxidx >= L-1 || tanitvanyyidx >= L-1);
		printf("Tanitvany indexei: [%d][%d]\n", tanitvanyxidx, tanitvanyyidx);

		int szomszedirany = rand() % 4; 
		int mesterxidx, mesteryidx;
		if (szomszedirany == 0) {
			mesterxidx = tanitvanyxidx;
			mesteryidx = tanitvanyyidx + 1;
		}
		if (szomszedirany == 1) {
			mesterxidx = tanitvanyxidx + 1;
			mesteryidx = tanitvanyyidx;
		}
		if (szomszedirany == 2) {
			mesterxidx = tanitvanyxidx;
			mesteryidx = tanitvanyyidx - 1;
		}
		if (szomszedirany == 3) {
			mesterxidx = tanitvanyxidx - 1;
			mesteryidx = tanitvanyyidx;
		}
		printf("Mester indexei: [%d][%d]\n", mesterxidx, mesteryidx);

		for (int i = 0; i < 4; i++) {
			int randomirany = rand() % 4;
			int randomfogolyxidx, randomfogolyyidx;
			if (randomirany == 0) {
				randomfogolyxidx = mesterxidx;
				randomfogolyyidx = mesteryidx + 1;
			}
			if (randomirany == 1) {
				randomfogolyxidx = mesterxidx + 1;
				randomfogolyyidx = mesteryidx;
			}
			if (randomirany == 2) {
				randomfogolyxidx = mesterxidx;
				randomfogolyyidx = mesteryidx - 1;
			}
			if (randomirany == 3) {
				randomfogolyxidx = mesterxidx - 1;
				randomfogolyyidx = mesteryidx;
			}
			printf("Mester dontese: %c Fogoly dontese: %c\n", foglyok[mesterxidx][mesteryidx].dontes, foglyok[randomfogolyxidx][randomfogolyyidx].dontes);
			foglyok[mesterxidx][mesteryidx].nyeremeny += calcnyeremeny(foglyok[mesterxidx][mesteryidx].dontes, foglyok[randomfogolyxidx][randomfogolyyidx].dontes);
			if (foglyok[randomfogolyxidx][randomfogolyyidx].dontes == 'C') {
				egyuttmukodok++;
			}
		}
		printf("A mester nyeremenye 4 jatszma utan: %d\n", foglyok[mesterxidx][mesteryidx].nyeremeny);

		for (int i = 0; i < 4; i++) {
			int randomirany = rand() % 4;
			int randomfogolyxidx, randomfogolyyidx;
			if (randomirany == 0) {
				randomfogolyxidx = tanitvanyxidx;
				randomfogolyyidx = tanitvanyyidx + 1;
			}
			if (randomirany == 1) {
				randomfogolyxidx = tanitvanyxidx + 1;
				randomfogolyyidx = tanitvanyyidx;
			}
			if (randomirany == 2) {
				randomfogolyxidx = tanitvanyxidx;
				randomfogolyyidx = tanitvanyyidx - 1;
			}
			if (randomirany == 3) {
				randomfogolyxidx = tanitvanyxidx - 1;
				randomfogolyyidx = tanitvanyyidx;
			}
			printf("tanitvany dontese: %c Fogoly dontese: %c\n", foglyok[tanitvanyxidx][tanitvanyyidx].dontes, foglyok[randomfogolyxidx][randomfogolyyidx].dontes);
			foglyok[tanitvanyxidx][tanitvanyyidx].nyeremeny += calcnyeremeny(foglyok[tanitvanyxidx][tanitvanyyidx].dontes, foglyok[randomfogolyxidx][randomfogolyyidx].dontes);
			if (foglyok[randomfogolyxidx][randomfogolyyidx].dontes == 'C') {
				egyuttmukodok++;
			}
		}
		printf("A tanitvany nyeremenye 4 jatszma utan: %d\n", foglyok[tanitvanyxidx][tanitvanyyidx].nyeremeny);
		if (w(foglyok[mesterxidx][mesteryidx].nyeremeny, foglyok[tanitvanyxidx][tanitvanyyidx].nyeremeny) > rand() % 101) {
			foglyok[tanitvanyxidx][tanitvanyyidx].dontes = foglyok[mesterxidx][mesteryidx].dontes;
			printf("A tanitvany atvette a mester strategiajat!\n");
		}
		else {
			printf("A tanitvany nem vette at a mester strategiajat!\n");
		}
		aranyok[iteracioszam] = (double)egyuttmukodok / (double)8;
		iteraciok[iteracioszam] = iteracioszam;
		iteracioszam++;
	}
	printf("Együttmûködések iterációszám szerint:\n");
	for (int i = 0; i < iteracioszam; i++) {
		printf("%d iteracio: %f\n", i, aranyok[i]);
	}

	char * commandsForGnuplot[] = {"set title \"TITLEEEEE\"", "set style data lines","plot 'data.temp'"};
    FILE * temp = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int i;
    for (i=0; i < L*L; i++)
    {
    fprintf(temp, "%lf %lf \n", iteraciok[i], aranyok[i]); //Write the data to a temporary file
    }

    for (i=0; i < NUM_COMMANDS; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
	return 0;
}
