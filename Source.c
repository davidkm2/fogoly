#include <stdio.h>
#define foglyokszama 10
#define T 5
#define NUM_COMMANDS 2

struct Fogoly {
	char dontes;
	int nyeremeny;
};

struct Kapcsolat {
	struct Fogoly fogoly1;
	struct Fogoly fogoly2;
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
	struct Fogoly foglyok[foglyokszama];
	struct Kapcsolat kapcsolatok[foglyokszama * foglyokszama - 1];
	char dontesek[2] = { 'C', 'D' };
	srand(time(0));
	//Inicializ�l�s, mindenkinek legyen valami d�nt�se kezdetben, nyerem�ny 0
	for (int i = 0; i < foglyokszama; i++) {
		struct Fogoly ujfogoly;
		ujfogoly.dontes = dontesek[rand() % 2];
		ujfogoly.nyeremeny = 0;
		foglyok[i] = ujfogoly;
		//printf("Fogoly: %d , d�nt�se: %c \n", i, foglyok[i].dontes);
	}

	//printf("Mindenki mindenkivel:");
	int kapcsolatokszama = 0;
	//1

	int iteracioszam = 0;
	
	double aranyok[foglyokszama];
	double iteraciok[foglyokszama];
	while (iteracioszam < foglyokszama)
	{
		printf("------------------------------------------------------\n\n\n");
		printf("%d . iteracio\n", iteracioszam);
		int mesteridx = rand() % foglyokszama;
		int tanitvanyidx;
		int egyuttmukodok = 0;
		do {
			tanitvanyidx = rand() % foglyokszama;
		} while (mesteridx == tanitvanyidx);
		printf("Mesteridx: %d , tanitvanyidx : %d\n", mesteridx, tanitvanyidx);
		if (foglyok[mesteridx].dontes != foglyok[tanitvanyidx].dontes) {
			//Mester j�tszik random 4 fogollyal
			for (int i = 0; i < 4; i++) {
				int randomfogolyidx;
				do {
					randomfogolyidx = rand() % foglyokszama;
				} while (mesteridx == randomfogolyidx || tanitvanyidx == randomfogolyidx);
				printf("Randomfogoly: %d\n", randomfogolyidx);
				printf("Mester dontese: %c, fogoly dontese: %c\n", foglyok[mesteridx].dontes, foglyok[randomfogolyidx].dontes);
				foglyok[mesteridx].nyeremeny = foglyok[mesteridx].nyeremeny + calcnyeremeny(foglyok[mesteridx].dontes, foglyok[randomfogolyidx].dontes);
				if (foglyok[randomfogolyidx].dontes == 'C') {
					egyuttmukodok++;
				}

			}
			printf("Mester nyeremenye 4 jatszma utan: %d\n", foglyok[mesteridx].nyeremeny);

			//Tan�tv�ny j�tszik random 4 fogollyal
			for (int i = 0; i < 4; i++) {
				int randomfogolyidx;
				do {
					randomfogolyidx = rand() % foglyokszama;
				} while (mesteridx == randomfogolyidx || tanitvanyidx == randomfogolyidx);
				printf("Randomfogoly: %d\n", randomfogolyidx);
				printf("Tanitvanyr dontese: %c, fogoly dontese: %c\n", foglyok[tanitvanyidx].dontes, foglyok[randomfogolyidx].dontes);
				foglyok[tanitvanyidx].nyeremeny = foglyok[tanitvanyidx].nyeremeny + calcnyeremeny(foglyok[tanitvanyidx].dontes, foglyok[randomfogolyidx].dontes);
				if (foglyok[randomfogolyidx].dontes == 'C') {
					egyuttmukodok++;
				}
			}
			printf("Tanitvany nyeremenye 4 jatszma utan: %d\n", foglyok[tanitvanyidx].nyeremeny);

			printf("Stategiai atveteli lehetoseg: %lf\n", w(foglyok[mesteridx].nyeremeny, foglyok[tanitvanyidx].nyeremeny));
			if (w(foglyok[mesteridx].nyeremeny, foglyok[tanitvanyidx].nyeremeny)*100 >= rand() % 101) {
				printf("A tanitvany atvette a mester strategiajat!\n");
				foglyok[tanitvanyidx].dontes = foglyok[mesteridx].dontes;
			}
			else {
				printf("A tanitvany nem vette at a mester strategiajat!\n");
			}
			printf("Egyuttmukodok szama: %d \n", egyuttmukodok);
		}
		else {
			printf("A mester es tanitvany dontese megegyezett!\n");
		}
		aranyok[iteracioszam] = (double)egyuttmukodok / (double)8;
		iteraciok[iteracioszam] = iteracioszam;
		iteracioszam++;
	}
	
	printf("Egy�ttm�k�d�sek iter�ci�sz�m szerint:\n");
	for (int i = 0; i < iteracioszam; i++) {
		printf("%d iteracio: %f\n", i, aranyok[i]);
	}

	char* commandsForGnuplot[] = { "set title \"TITLEEEEE\"", "plot 'data.temp'" };
	FILE* fp;
	//FILE* temp = fopen_s(&fp,"data.temp", "w");
	if (fopen_s(&fp, "data.temp", "w") != 0) {
		FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
		int i;
		for (int i = 0; i < foglyokszama; i++)
		{
			fprintf(fp, "%lf %lf \n", aranyok[i], iteraciok[i]); //Write the data to a temporary file
		}
	}
	else {
		printf("Failed");
	}
	fclose(fp);
	/*Opens an interface that one can use to send commands as if they were typing into the
	 *     gnuplot command line.  "The -persistent" keeps the plot open even after your
	 *     C program terminates.
	 */
	FILE* gnuplotPipe;
	gnuplotPipe = _popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persistent", "w");

	for (int i = 0; i < NUM_COMMANDS; i++)
	{
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
	}
	_pclose(gnuplotPipe);
	return 0;


}