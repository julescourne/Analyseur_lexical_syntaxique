/**
 * \file lex.c
 * \brief analyseur lexical pour le langage JSON
 * \author NM
 * \version 0.1
 * \date 25/11/2015
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>


#define JSON_LEX_ERROR -1 /**< code d'erreur lexicale */
#define JSON_TRUE 1 /**< entite lexicale true */
#define JSON_FALSE 2 /**< entite lexicale false */
#define JSON_NULL 3 /**< entite lexicale null */
#define JSON_LCB 4 /**< entite lexicale { */
#define JSON_RCB 5 /**< entite lexicale } */
#define JSON_LB 6 /**< entite lexicale [ */
#define JSON_RB 7 /**< entite lexicale ] */
#define JSON_COMMA 8 /**< entite lexicale , */
#define JSON_COLON 9 /**< entite lexicale : */
#define JSON_STRING 10 /**<entite lexicale chaine de caracteres */
#define JSON_INT_NUMBER 11 /**< entite lexicale nombre entier */
#define JSON_REAL_NUMBER 12 /**< entite lexicale nombre reel */

/**
 * \union TSymbole
 * \brief union permettant de  manipuler un entier/reel/chaine pour la table
 * des symboles
 */
typedef struct {
	int type; /**< l'un des 3 types suivants : JSON_STRING/JSON_INT_NUMBER/JSON_REAL_NUMBER */
	union {
        int entier;
        float reel;
        char * chaine;
    } val; /**< valeur associer a un element de la table des symboles */
} TSymbole;

/**
 * \struct TLex
 * \brief structure contenant tous les parametres/donnees pour
 * l'analyse lexicale
 */
typedef struct{
	char * data; /**< chaine a parcourir */
	char * startPos; /**< position de depart pour la prochaine analyse */
	int nbLignes; /**< nb de lignes analysees */
	TSymbole * tableSymboles; /**< tableau des symboles : chaines/entier/reel */
	int nbSymboles; /**<  nb de symboles stockes dans tableSymboles */
	int tailleTableSymboles; /**< taille memoire du tableau tableSymboles */
} TLex;

/**
 * \fn int isSep(char _symb)
 * \brief fonction qui teste si un symbole fait partie des separateurs
 *
 * \param[in] _symb symbole a analyser
 * \return 1 (vrai) si _symb est un separateur, 0 (faux) sinon
 */
int isSep(const char _symb) {
	if (_symb == '{' || _symb == '}' || _symb == '[' || _symb == ']' || _symb == ':' || _symb == ','|| _symb == ';'||_symb == ' ' || _symb == '\0' || _symb == ' '|| _symb == '\t' || _symb == '\r' )
	{
		return 1;
	}	
	else 
	{
		return 0;
	}
}

/**
 * \fn TLex * initLexData(char * _data)
 * \brief fonction qui reserve la memoire et initialise les
 * donnees pour l'analyseur lexical
 *
 * \param[in] _data chaine a analyser
 * \return pointeur sur la structure de donnees creee
 */
TLex * initLexData(char * _data) {

	TLex *_tableau = (TLex*)malloc(sizeof(TLex)); // verifier que ça eu lieu

    	if (_tableau == NULL) // Si l'allocation a échoué
    	{
        	exit(0); // On arrête immédiatement le programme
    	}

	_tableau->data =_data; //pas besoin de faire une copie
	_tableau->startPos = &(_tableau->data[0]);
	_tableau->tailleTableSymboles = strlen(_data)+1;
	_tableau->nbLignes = 0;
	_tableau->tableSymboles =  malloc((_tableau->tailleTableSymboles)*sizeof(TSymbole));
	_tableau->nbSymboles = 0;
	return _tableau;


}

/**
 * \fn void deleteLexData(TLex ** _lexData)
 * \brief fonction qui supprime de la memoire les donnees pour
 * l'analyseur lexical
 *
 * \param[inout] _lexData donnees de l'analyseur lexical
 * \return neant
 */
void deleteLexData(TLex ** _lexData) {
	free((*_lexData)->tableSymboles);
	free(*_lexData);
}

/**
 * \fn void printLexData(TLex * _lexData)
 * \brief fonction qui affiche les donnees pour
 * l'analyseur lexical
 *
 * \param[in] _lexData donnï¿½es de l'analyseur lexical
 * \return neant
 */
void printLexData(TLex * _lexData) {
   	printf("Nombre de lignes analysées : %d\n", _lexData->nbLignes);
	printf("Chaine à analyser : %s\n", _lexData->data);
	printf("Nombre de valeurs stockées dans la table des symboles : %d\n", _lexData->nbSymboles);
	printf("Position de départ pour la prochaine analyse : %s\n", _lexData->startPos);
    for(int i = 1 ; i < _lexData->nbSymboles +1 ; i++){
        if(_lexData->tableSymboles[i].type == JSON_STRING){
            printf("Chaine numéro %d de la table des symboles : %s\n",i,_lexData->tableSymboles[i].val.chaine);
        }
        if(_lexData->tableSymboles[i].type == JSON_INT_NUMBER){
            printf("Entier numéro %d de la table des symboles : %d\n",i,_lexData->tableSymboles[i].val.entier);
        }
        if(_lexData->tableSymboles[i].type == JSON_REAL_NUMBER){
            printf("Reel numéro %d de la table des symboles : %f\n",i,_lexData->tableSymboles[i].val.reel);
        }
    }
}


/**
 * \fn void addIntSymbolToLexData(TLex * _lexData, const int _val)
 * \brief fonction qui ajoute un symbole entier a la table des symboles
 *
 * \param[inout] _lexData donnees de l'analyseur lexical
 * \param[in] _val valeur entiere e ajouter
 * \return neant
 */
void addIntSymbolToLexData(TLex * _lexData, const int _val) {
	_lexData->nbSymboles++;
	if(_lexData->nbSymboles > _lexData->tailleTableSymboles)
	{
		_lexData->tableSymboles = realloc(_lexData->tableSymboles, sizeof(_lexData->tableSymboles)+5);
		_lexData->tailleTableSymboles = _lexData->tailleTableSymboles+5;
	}
	_lexData->tableSymboles[_lexData->nbSymboles].type = JSON_INT_NUMBER;
	_lexData->tableSymboles[_lexData->nbSymboles].val.entier = _val;
}

/**
 * \fn void addRealSymbolToLexData(TLex * _lexData, const float _val)
 * \brief fonction qui ajoute un symbole reel a la table des symboles
 *
 * \param[inout] _lexData donnees de l'analyseur lexical
 * \param[in] _val valeur reelle a ajouter
 */
void addRealSymbolToLexData(TLex * _lexData, const float _val) {
	_lexData->nbSymboles++;
	
	_lexData->tableSymboles[_lexData->nbSymboles].val.reel = _val;
	_lexData->tableSymboles[_lexData->nbSymboles].type = JSON_REAL_NUMBER;
}

 /**
 * \fn void addStringSymbolToLexData(TLex * _lexData, char * _val)
 * \brief fonction qui ajoute une chaine de caracteres a la table des symboles
 *
 * \param[inout] _lexData donnees de l'analyseur lexical
 * \param[in] _val chaine a ajouter
 */
void addStringSymbolToLexData(TLex * _lexData, char * _val) {
	
	_lexData->tableSymboles[_lexData->nbSymboles].val.chaine = _val;
	_lexData->tableSymboles[_lexData->nbSymboles].type = JSON_STRING;
	_lexData->nbSymboles++;
	
	
}

/**
 * \fn int lex(Lex * _lexData)
 * \brief fonction qui effectue l'analyse lexicale (contient le code l'automate fini)
 *
 * \param[inout] _lexData donnees de suivi de l'analyse lexicale
 * \return code d'identification de l'entite lexicale trouvee
*/
int lex(TLex * _lexData) {
	int etat = 0;
	int fini = 0;
	char symbole ;
	int cpt = 0;
	while(!fini){
		symbole = *_lexData->startPos;
		switch(etat){
			case 0:
				switch(symbole){
					case '\n':
						_lexData->nbLignes++;
						etat = etat;
						break;
					case 't':
						etat = 1;
						break;
					case '{':
						etat = 17;
						fini = JSON_LCB;
						break;
					case '}':
						etat = 18;
						fini = JSON_RCB;
						break;
					case '[':
						etat = 19;
						fini = JSON_LB;
						break;
					case ']':
						etat = 20;
						fini = JSON_RB;
						break;
					case ':':
						etat = 21;
						fini = JSON_COLON;
						break;
					case ',':
						etat = 22;
						fini = JSON_COMMA;
						break;
					case 'f':
						etat = 6;
						break;
					case 'n':
						etat = 12;
						break;
					case '"':
						etat = 23;
						break;
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						etat = 29;
						break;
					case '-':
						etat = 27;
						break;
					case '0':
						etat = 28;
						break;
					default:
						fini = JSON_LEX_ERROR;
						break;
				}
				break;
			case 1:
				switch(symbole){
					case 'r':
						etat = 2;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 2:
				switch(symbole){
					case 'u':
						etat = 3;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 3:
				switch(symbole){
					case 'e':
						etat = 4;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 4:
				if(isSep(symbole)){
					etat = 5;
					fini = JSON_TRUE;
					break;
				}
				else{
					fini = JSON_LEX_ERROR;
				}
				break;
			case 6:
				switch(symbole){
					case 'a':
						etat=7;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 7:
				switch(symbole){
					case 'l':
						etat=8;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 8:
				switch(symbole){
					case 's':
						etat=9;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 9:
				switch(symbole){
					case 'e':
						etat=10;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 10:
				if(isSep(symbole)){
					etat = 11;
					fini = JSON_FALSE;
					break;
				}
				else{
					fini = JSON_LEX_ERROR;
				}  
				break;            
			case 12:
				switch(symbole){
					case 'u':
						etat=13;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 13:
				switch(symbole){
					case 'l':
						etat=14;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 14:
				switch(symbole){
					case 'l':
						etat=15;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;
			case 15:
				if(isSep(symbole)){
					etat = 16;
					fini = JSON_NULL;
				}
				else{
					fini = JSON_LEX_ERROR;
				}
				break;
			case 23: //cas pour un string
				if(symbole == '\\')
				{
					etat = 25;
				}
				else if(symbole == '"')
				{
					etat = 26;
					fini = JSON_STRING;
				}
				else{
					etat = 23;

				}
				break;
			case 25:
				etat = 23;
				break;
			case 27://cas pour un nombre ENTIER negatif
				switch(symbole)
				{
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						etat = 29;
						break;
					case '0':
						etat = 28;
						break;
					default:
						fini = JSON_LEX_ERROR;	
				}
				break;

			case 28:
				if(isSep(symbole)){
					etat = 31;
					fini = JSON_INT_NUMBER;
					_lexData->startPos--;
					cpt--;
				}
				else if(symbole == '.'){
					etat = 30;
				}
				else if(symbole == 'e' || symbole == 'E'){
					etat = 32;
				}
				else{
					fini = JSON_LEX_ERROR;
				}
				break;
			case 29://cas pour un nombre ENTIER 
				if(isSep(symbole)){
					etat = 31;
					fini = JSON_INT_NUMBER;
					_lexData->startPos--;
					cpt--;

				}
				else if(symbole == 'e' || symbole == 'E'){
						etat = 32;
				}
				else if(symbole == '0' || symbole == '1' || symbole == '2' || symbole == '3' || symbole == '4' || symbole == '5' || symbole == '6' || symbole == '7' || symbole == '8' || symbole == '9'){
						etat = 29;
				}
				else if (symbole == '.') {
					etat = 30;
				}
				else{
					fini = JSON_LEX_ERROR;
				}
				break;


			case 30:
				switch(symbole){
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						etat = 33;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;

			case 32:
				switch(symbole){
					case '+':
					case '-':
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						etat = 35;
						break;
					default:
						fini = JSON_LEX_ERROR;
				}
				break;

			case 33:
				if(isSep(symbole)){
					etat = 34;
					fini = JSON_REAL_NUMBER;
					_lexData->startPos--;
					cpt--;

				}
				else if(symbole == 'e' || symbole == 'E'){
					etat = 32;
				}
				else if(symbole == '0' || symbole == '1' || symbole == '2' || symbole == '3' || symbole == '4' || symbole == '5' || symbole == '6' || symbole == '7' || symbole == '8' || symbole == '9'){
						etat = 33;
				}
				else{
					fini = JSON_LEX_ERROR;
				}
				break;

			case 35:
				if(isSep(symbole)){
					etat = 36;
					fini = JSON_REAL_NUMBER;
					_lexData->startPos--;
					cpt--;

				}
				else if(symbole == '0' || symbole == '1' || symbole == '2' || symbole == '3' || symbole == '4' || symbole == '5' || symbole == '6' || symbole == '7' || symbole == '8' || symbole == '9'){
					etat = 35;
				}
				else{
					fini = JSON_LEX_ERROR;
				}
				break;
				

			default:
				fini = JSON_LEX_ERROR;
		}
		
		if(fini == 0){
			cpt++;
			_lexData->startPos++;
		}
		else if (fini == JSON_STRING || fini == JSON_INT_NUMBER ||fini == JSON_REAL_NUMBER)
		{
			char* temp = (char*)malloc((cpt+2)*sizeof(char));
			int i;
			for (i = 0; i < cpt+1; i++){
				temp[i] = *(_lexData->startPos-cpt+i);
			}
			temp[i] = '\0';
			switch (fini)
			{
			case JSON_STRING:
				addStringSymbolToLexData(_lexData, temp);
				break;
			case JSON_INT_NUMBER:
				addIntSymbolToLexData(_lexData, atoi(temp));
				break;
			case JSON_REAL_NUMBER:
				addRealSymbolToLexData(_lexData, atof(temp));
				break;	
			default:
				
				break;
			}
			free(temp);
		}
		else if(fini == JSON_LEX_ERROR && ( symbole == ' ' || symbole == '\t' )){
				fini = 0;
				_lexData->startPos++;
		}
	}
	_lexData->startPos++;
	return fini;
}
			
/**
 * \fn int main()
 * \brief fonction principale
 */
/*int main() {
	char * test ;
	int i;
	TLex * lex_data;

	test = strdup("{\"obj1\": [ {\"obj2\": 12, \"obj3\":\"text1 \\\"and\\\" text2\"},\n {\"obj4\":314.32} ], \"obj5\": true }");

	printf("%s",test);
	printf("\n");

	lex_data = initLexData(test);
	i = lex(lex_data);
	while (i!=JSON_LEX_ERROR) {
		printf("lex()=%d\n",i);
		i = lex(lex_data);
	}
  printLexData(lex_data);
	deleteLexData(&lex_data);
	free(test);


	return 0;
}*/


