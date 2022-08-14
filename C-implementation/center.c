#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"sort.c"


void mergeFiles(){
	FILE *fp1 = fopen("transSorted711.txt", "r");
   FILE *fp2 = fopen("transSorted713.txt", "r");
   FILE *fp3 = fopen("central.txt", "w");
   char c;
   while ((c = fgetc(fp1)) != EOF){
	   fputc(c, fp3);
   }
   while ((c = fgetc(fp2)) != EOF){
	   fputc(c, fp3);
   }
   fclose(fp1);
   fclose(fp2);
   fclose(fp3);
}

int main(){
	sort_transaction("trans711.txt", "transSorted711.txt");
	sort_transaction("trans713.txt", "transSorted713.txt");
	mergeFiles();
	sort_transaction("central.txt", "Final.txt");
	return 0;
}

