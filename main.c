#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


const char matrix_bigram_strings[10][3] = { "th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te" };

const char matrix_trigram_strings[10][4] = { "the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die" };

const char languages[2][8] = { "english", "german" };

//Ýngilizce dilinin frekans deðerleri
const float frequency_eng[20] = { 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
//Almanca dilinin frekans deðerleri
const float frequency_germ[20] = { 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };


float calculated_frequencies[20];
float distances[2] = { 0,0 };


void filter_str(char str[]) {
	char temp = ' '; //istenmeyen karakterler yerine bosluk koymak icin
	int i, j;
	for (i = 0; i < strlen(str); i++) { //dizinin her karakterini geziyor
		if (!(str[i] > 64 && str[i] < 91 || str[i]>96 && str[i] < 123)) { //ASCII olarak bosluk koymak istedigimiz alani belirledik
			if (str[i] == 32) { // bosluk varsa bir daha bosluk konmamasý icin
				continue;
			}
			str[i] = temp; //istenmeyen karakteri boslukla degistirdik
		}
	}

	}

float calculate_percent(float strlength, float counter) { //frekans hesaplarken yüzde olarak hesaplanacagindan yardimci olmasi icin bu fonksiyonu ekledik
	float percent = counter * 100 / strlength;
	return percent;
}

void calculate_frequencies_bi(char str[]) {
	int i, j;
	int k = 0;
	int counter; //bir bigramin kac kere bulundugunu saymak icin bir degisken
	for (i= 0;i<10; i++) //on adet bigrami tek tek kac adet var saymak icin bigram sayisi kadarlik bir dongu
	{
		counter = 0; //her yeni dongude yeni bigram icin sayacagimiz icin her dongu oncesi sifirlanmasi gerek
		for (j = 0; j < strlen(str); j++) { //metinin her karakterini gezmek icin bir dongu
		if (matrix_bigram_strings[i][k] == str[j]) { //sirasiyla bigramlarin ilk harfi ayniysa
			if (matrix_bigram_strings[i][k+1] == str[j + 1]) { //ve ikinci harfi de ayniysa
				counter++; //o bigramin tekrar sayisini arttiririz
				calculated_frequencies[i] = calculate_percent(strlen(str),counter); //hesapladigimiz tekrar sayisini yukarida yazdigimiz yuzde hesaplama fonksiyonuyla hesaplayip hesaplanan frekanslara ekledik
			}
		}
		}
		printf(matrix_bigram_strings[i]);//frekans matrisini gostermek icin
		printf(" %d", counter);
		printf("\n");
	}
	printf("----------------------------------------\n");
}
void calculate_frequencies_tri(char str[]) { //yukaridaki islemin aynisini yaptik sadece trigram oldugu icin bir if kontrolu daha ekledik
	int i, j;
	int k = 0;
	int counter;
	for (i = 0; i < 10; i++)
	{
		counter = 0;
		for (j = 0; j < strlen(str); j++) {
			if (matrix_trigram_strings[i][k] == str[j]) {
				if (matrix_trigram_strings[i][k + 1] == str[j + 1]) {
					if (matrix_trigram_strings[i][k + 2] == str[j + 2]) {
						counter++;
						calculated_frequencies[i+10] = calculate_percent(strlen(str), counter);
					}
				}
			}
		}
		printf(matrix_trigram_strings[i]);//frekans matrisini gostermek icin
		printf(" %d", counter);
		printf("\n");
	}
	printf("----------------------------------------\n");
}
void calculate_distances() { //uzakligi hesaplamak icin oklid kullandik
	float engresult = 0;
	float germresult = 0;
	for (int i = 0; i < 20; i++)
	{
		engresult += pow(calculated_frequencies[i] - frequency_eng[i], 2); //pow fonksiyonuyla karelerini alip donguyle kendi kendine toplattik
	}
	for (int i = 0; i < 20; i++)
	{
		germresult += pow(calculated_frequencies[i] - frequency_germ[i], 2);
	}
	distances[0] = sqrt(engresult); //oklid icin birbirinden cikarip karelerini aldigimiz degerlerin sqrt fonksiyonu ile kokunu aldik ve distancese sirayla atadik
	distances[1] = sqrt(germresult);

}
void detect_lang() {                   //hangisi 0a daha yakinsa tahminimizin o dil olacagi sorgulama sistemi
	if (distances[0] < distances[1]) {
		printf("Guess: English");
	}
	else if (distances[1] < distances[0]) {
		printf("Guess: German");
	}
	else {
		printf("both of them?:D");
	}
}

int main()
{
    char text[1000];
    printf("lutfen bir text giriniz:");
    gets(text);
	printf("Sample Text: %s\n",text);
	filter_str(text);
	printf("Filtered Version: ");
	printf(text);
	printf("\n----------------------------------------\n");
	calculate_frequencies_bi(text);
	calculate_frequencies_tri(text);
	calculate_distances();
	detect_lang();

	return 0;
}
