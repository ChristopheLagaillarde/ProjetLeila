/*/////////////////En tête////////////////////////////
 * Programme : Cryptage avec XOR
 *
 * Description : Ce programme permet au choix de chiffrer
 *               ou de déchiffrer un texte avec une clé
 *               de chiffrement, le texte est dans un
 *               fichier, et permet d'afficher le texte.
 *
 *
 * Auteur : Christophe LAGAILLARDE
 *
 * Date : 23/01/2021
 *
 * Version 1.0 :
 *
 *///////////////////////////////////////////////////

// Déclaration des bibliotheques de fonctions...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mem.h>

void ecrireDansLeFichier(char texte[], char adresse[]){
	FILE* fichier = NULL;
	fichier = fopen(adresse,"w");
	if(fichier == NULL){                    // Si le fichier ne s'est pas ouvert
		printf("Erreur fichier inexistant");
		fclose(fichier);
	}
	else{
		fprintf(fichier,"%s",texte);           // écrit dans le fichier la variable texte d'entré
		fclose(fichier);
	}
}

char* lireLeFichier(char adresse[]){

	static char texteARecuperer[500];
	FILE *fichier=fopen(adresse, "r");
	int i=0;
	char caractere;


	if(fichier == NULL){
			printf("Erreur fichier inexistant");
			fclose(fichier);
		}
		else{
			while(fscanf(fichier,"%c",&caractere) != EOF){  // Tant que le pointeur de fgets ne parcours pas tout le fichier
				texteARecuperer[i++] =caractere;
			}
			fclose(fichier);
		}

	return texteARecuperer;
}

char* encrypter(char texteInitial[500],int decalage){
	int AsciiDuCryptage;
	int i = 0;
	char static texteCrypte[500];
	while(texteInitial[i] != *"\0"){   // Tant que le texte n'est pas fini
		if(((int)texteInitial[i] >= (int)*"A" && (int)texteInitial[i] <= (int)*"z") && ((int)texteInitial[i] <= (int)*"Z" || (int)texteInitial[i] >= (int)*"a")){ // Si c'est une lettre de l'alphabet
			if(((int)texteInitial[i] + decalage > (int)*"z") || (((((int)*"A" <= (int)texteInitial[i]) && (int)texteInitial[i] <=(int)*"Z")) && ((int)texteInitial[i] + decalage > (int)*"Z"))){ // Si le décalage est trop grand par rapport au rang de la lettre crypté
				AsciiDuCryptage = ((int)texteInitial[i] + decalage) - 26; // Retour au début de l'alphabet
			}
			else{
				AsciiDuCryptage = (int)texteInitial[i] + decalage;  // Ajout du décalage au niveau du code ASCII
			}
		}
		else{
			AsciiDuCryptage = (int)texteInitial[i];             // Si ce n'est pas une lettre alors il n y a aucun décalage
		}

		texteCrypte[i] = (char)AsciiDuCryptage;                      // conversion du code ASCII en caractère
		i++;
	}
	return texteCrypte;
}

char* decrypter(int decalage, char nomFichier[]){
	int asciiDuDecryptage;
	int i = 0;
	char static texteDecrypte[500];
	char caractere;
	char static format[5] = ".cryp";
	char static adresse[100] ="C:/Users/Lagaillarde/eclipse-workspace/Projet_LeilaV2/";
    FILE* fichier = NULL;

	strcat(nomFichier,format);                 // On fait la concaténation pour avoir l'adresse
	strcat(adresse,nomFichier);
	fichier = fopen(adresse,"r");
	if(fichier == NULL){                       // Si le fichier ne s'est pas ouvert
		printf("Erreur fichier inexistant");
		fclose(fichier);
	}
	else{
		printf("Le texte décrypté est : \n");
	}
	while(fscanf(fichier,"%c",&caractere) != EOF){   // Tant que le fichier n'est pas parcouru entièrement
		if(((int)caractere >= (int)*"A" && (int)caractere <= (int)*"z") && ((int)caractere <= (int)*"Z" ||  (int)caractere >= (int)*"a")){  // Si c'est une lettre de l'alphabet
			if(((caractere == *"A" || caractere ==*"B" || caractere ==*"C"|| caractere ==*"D"|| caractere ==*"E" || caractere ==*"F" || caractere ==*"G" || caractere ==*"H"|| caractere ==*"I"|| caractere ==*"J"|| caractere ==*"K"|| caractere ==*"L"|| caractere ==*"M"|| caractere ==*"N"|| caractere ==*"O"|| caractere ==*"P"|| caractere ==*"Q"|| caractere ==*"R"|| caractere ==*"S"|| caractere ==*"T"|| caractere ==*"U" || caractere ==*"V"|| caractere ==*"W"|| caractere ==*"X"|| caractere ==*"Y" || caractere ==*"Z")  && ((int)caractere - decalage) < (int)*"A") || ((caractere == *"a" || caractere ==*"b" || caractere ==*"c"|| caractere ==*"d"|| caractere ==*"e" || caractere ==*"f" || caractere ==*"g" || caractere ==*"h"|| caractere ==*"i"|| caractere ==*"j"|| caractere ==*"k"|| caractere ==*"l"|| caractere ==*"m"|| caractere ==*"n"|| caractere ==*"o"|| caractere ==*"p"|| caractere ==*"q"|| caractere ==*"r"|| caractere ==*"s"|| caractere ==*"t"|| caractere ==*"u" || caractere ==*"v"|| caractere ==*"w"|| caractere ==*"x"|| caractere ==*"y" || caractere ==*"z") && ((int)caractere - decalage) < (int)*"a")){
				asciiDuDecryptage = ((int)caractere - decalage) + 26;  // Retour au début de l'alphabet
    		}
			else{
				asciiDuDecryptage = (int)caractere - decalage; // Enlèvement du décalage au niveau du code ASCII
				}
		}
		else{
			asciiDuDecryptage = (int)caractere;         // Si ce n'est pas une lettre alors il n y a aucun décalage
			}
		texteDecrypte[i] = (char)asciiDuDecryptage; // conversion du code ASCII en caractère
    	i++;
    }
	fclose(fichier);
	return texteDecrypte;
}

void procedure_choix_1(){
	char texte[7] = "";
	char pwd[15] = "";
	int decalage = 0;
	char* texteDuFichier;
	char* texteEncrypte;
	char* texteDuFichierCrypte;

	printf("Veillez entrer un décalage : \n");
	scanf("%d",&decalage);

	printf("Veillez entrer le mot de passe : \n");
	scanf("%s",pwd);

	printf("Le mot de passe est : %s\n",pwd);
	printf("Le décalage est : %d\n",decalage);

	if(strcmp(pwd,"08re4VqZCbGhA7YZ") == 0){  //strvmp est une fonction qui compare 2 chaine et retourne 0 si elle sont identique
		printf("écrivez le message que vous souhaitez crypter : \n");
		scanf("%[^>]s",texte);
		ecrireDansLeFichier(texte,"C:/Users/Lagaillarde/eclipse-workspace/Projet_LeilaV2/chemisette.txt");
		texteDuFichier = lireLeFichier("C:/Users/Lagaillarde/eclipse-workspace/Projet_LeilaV2/chemisette.txt");
		texteEncrypte = encrypter(texteDuFichier,decalage);
		printf("%s",texteDuFichier);
		ecrireDansLeFichier(texteEncrypte,"C:/Users/Lagaillarde/eclipse-workspace/Projet_LeilaV2/chemisette.cryp");
		texteDuFichierCrypte = lireLeFichier("C:/Users/Lagaillarde/eclipse-workspace/Projet_LeilaV2/chemisette.cryp");
		printf("%s",texteDuFichierCrypte);
	}
	else {
		printf("Mot de passe incorrecte !");
	}

}

void procedure_choix_2(){
	char nomFichier[20];
	char pwd[15] = "";
	int decalage = 0;
	char* texteDecrypte;

	printf("Veillez entrer un décalage : \n");
	scanf("%d",&decalage);

	printf("Veillez entrer le mot de passe : \n");
	scanf("%s",pwd);

	if(strcmp(pwd,"08re4VqZCbGhA7YZ") == 0){
		printf("Veillez entrer le nom du fichier à décrypter : \n");
		scanf("%s",nomFichier);
		texteDecrypte = decrypter(decalage, nomFichier);
		printf("%s",texteDecrypte);
		ecrireDansLeFichier(texteDecrypte,"C:/Users/Lagaillarde/eclipse-workspace/Projet_LeilaV2/chemisetteDecrypte.txt");

	}
	else {
		printf("Mot de passe incorrecte !");
	}
}

void procedure_choix_3(){
	printf("\n Au revoir \n");
}

//////////////////Le Programme principal/////////////

//////////////////Début//////////////////////////////
int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);  //Résout le bug du système
	setvbuf(stderr, NULL, _IONBF, 0);

	int choix = 0;

	printf("Entrer 1 si vous souhaitez chiffrer le fichier à envoyer (chemisette.txt) \n");
	printf("Entrer 2 si vous souhaitez déchiffrer un fichier qui a été reçu \n");
	printf("Entrer 3 si vous souhaitez quitter le programme \n");

	scanf("%d",&choix);


	if(choix == 1){
		procedure_choix_1();
	}
	if(choix == 2){
		procedure_choix_2();
	}

	if(choix == 3){
		procedure_choix_3();
	}

}
