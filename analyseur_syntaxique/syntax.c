/*
 * \file syntax.c
 * \brief programme qui renvoie 1 si la chaine passée en argument suit bien la grammaire JSon et 0 sinon.
 *        Nous n'avons pas réussi à analyser la chaine "#######..." L'analyseur syntaxique considère
 *        cette chaine comme une source d'erreur.    
 * 
 *
 * \author Courné - Dargent
 *
 * \version 1.0
 * \date 13/01/2021
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pile.h"
#include "json_tree.h"
#include "pile.c"
#include "lex.c"

#define ACCEPTATION 1
#define ERREUR -1
#define DEPLACEMENT 2
#define REDUCTION 3





/**
  * \fn TableAction(int _lexeme, int _etat)
  * \brief Fonction permettant de fournir une des quatres actions : Acceptation, reduction,
  *        déplacement et erreur.
  *
  * 
  * \param[in] lexeme. Symbole reconnu par l'analyseur lexical.
  * \param[in] _etat.  L’état en sommet de pile.
  *
  * \return action
  *
 **/

int TableAction(int _lexeme, int _etat){
	int action;
	switch(_etat){
		case 0:
			switch(_lexeme){
				case JSON_LCB:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 1:
			switch(_lexeme){
				case JSON_LEX_ERROR:
					action = ACCEPTATION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 2:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_STRING:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 3:
			switch(_lexeme){
				case JSON_RCB:	
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 4:
			switch(_lexeme){
				case JSON_RCB:
					action = REDUCTION;
					break;
				case JSON_COMMA:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 5:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
				case JSON_LEX_ERROR:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 6:
			switch(_lexeme){
				case JSON_COLON:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 7:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
				case JSON_LEX_ERROR:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;	
		case 8 :
			switch(_lexeme){
				case JSON_STRING:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;	
		case 9 :
			switch(_lexeme){
				case JSON_STRING:
				case JSON_LCB:
				case JSON_LB:
				case JSON_NULL:
				case JSON_TRUE:
				case JSON_FALSE:
				case JSON_INT_NUMBER:
				case JSON_REAL_NUMBER:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;				
		case 10 :
			switch(_lexeme){
				case JSON_RCB:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 11 :	
			switch(_lexeme){
					case JSON_RCB:
					case JSON_RB:
					case JSON_COMMA:
						action = REDUCTION;
						break;
					default:
						action = ERREUR;
						break;
			}
			break;		
		case 13 :
			switch(_lexeme){
				case JSON_RCB:
				case JSON_COMMA:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;			
		case 14 :
			switch(_lexeme){
				case JSON_STRING:
				case JSON_LCB:
				case JSON_LB:
				case JSON_RB:
				case JSON_NULL:
				case JSON_TRUE:
				case JSON_FALSE:
				case JSON_INT_NUMBER:
				case JSON_REAL_NUMBER:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;		
		case 12 :	
			switch(_lexeme){
					case JSON_RCB:
					case JSON_RB:
					case JSON_COMMA:
						action = REDUCTION;
						break;
					default:
						action = ERREUR;
						break;
			}
			break;	
		case 16 :	
			switch(_lexeme){
					case JSON_RCB:
					case JSON_RB:
					case JSON_COMMA:
						action = REDUCTION;
						break;
					default:
						action = ERREUR;
						break;
			}
			break;	
		case 15 :
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;				
		case 17 :	
			switch(_lexeme){
					case JSON_RCB:
					case JSON_RB:
					case JSON_COMMA:
						action = REDUCTION;
						break;
					default:
						action = ERREUR;
						break;
			}
			break;		
		case 18 :	
			switch(_lexeme){
					case JSON_RCB:
					case JSON_RB:
					case JSON_COMMA:
						action = REDUCTION;
						break;
					default:
						action = ERREUR;
						break;
			}
			break;		
		case 19 :
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;	
		case 20 :
			switch(_lexeme){
				case JSON_RB:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;	
		case 21:
			switch(_lexeme){
				case JSON_RB:
					action = REDUCTION;
					break;
				case JSON_COMMA:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;	
		case 22:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;
		case 23 :
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;	
		case 24 :
			switch(_lexeme){
				case JSON_STRING:
				case JSON_LCB:
				case JSON_LB:
				case JSON_NULL:
				case JSON_TRUE:
				case JSON_FALSE:
				case JSON_INT_NUMBER:
				case JSON_REAL_NUMBER:
					action = DEPLACEMENT;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;		
		case 25 :
			switch(_lexeme){
				case JSON_RB:
					action = REDUCTION;
					break;
				default:
					action = ERREUR;
					break;
			}
			break;	
		default :
			action = ERREUR;
			break;
	
	}
	return action;
}





/**
  * \fn TableGoto(int _lexeme, int _etat)
  * \brief Fonction permettant de fournir un nouvel état.
  *
  * 
  * \param[in] _lexeme. Symbole reconnu par l'analyseur lexical.
  * \param[in] _etat.  L’état en sommet de pile.
  *
  * \return deplace
  *
 **/
int TableGoto(int _lexeme, int _etat){
	int deplace = 0;
	switch(_etat){
		case 0 :
			switch(_lexeme){
				case JSON_LCB:
					deplace = 2;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 2 :
			switch(_lexeme){
				case JSON_RCB:
					deplace = 5;
					break;
				case JSON_STRING:
					deplace = 6;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 3 :
			switch(_lexeme){
				case JSON_RCB:
					deplace = 7;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 4 :
			switch(_lexeme){
				case JSON_COMMA:
					deplace = 8;
					break;
				default:
					deplace = -1;
					break;
			}
			break;	
		case 6 :
			switch(_lexeme){
				case JSON_COLON:
					deplace = 9;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 8 :
			switch(_lexeme){
				case JSON_STRING:
					deplace = 6;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 14 :
			switch(_lexeme){
				case JSON_LCB:
					deplace = 2;
					break;
				case JSON_LB:
					deplace = 14;
					break;
				case JSON_STRING:
					deplace = 15;
					break;
				case JSON_NULL:
					deplace = 19;
					break;
				case JSON_TRUE:
					deplace = 17;
					break;
				case JSON_FALSE:
					deplace = 18;
					break;
				case JSON_INT_NUMBER:
					deplace = 16;
					break;
				case JSON_REAL_NUMBER:
					deplace = 16;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 24 :
			switch(_lexeme){
				case JSON_LCB:
					deplace = 2;
					break;
				case JSON_LB:
					deplace = 14;
					break;
				case JSON_STRING:
					deplace = 15;
					break;
				case JSON_NULL:
					deplace = 19;
					break;
				case JSON_TRUE:
					deplace = 17;
					break;
				case JSON_FALSE:
					deplace = 18;
					break;
				case JSON_INT_NUMBER:
				case JSON_REAL_NUMBER:
					deplace = 16;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 9 :
			switch(_lexeme){
				case JSON_LCB:
					deplace = 2;
					break;
				case JSON_LB:
					deplace = 14;
					break;
				case JSON_STRING:
					deplace = 15;
					break;
				case JSON_NULL:
					deplace = 19;
					break;
				case JSON_TRUE:
					deplace = 17;
					break;
				case JSON_FALSE:
					deplace = 18;
					break;
				case JSON_INT_NUMBER:
				case JSON_REAL_NUMBER:
					deplace = 16;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 20 :
			switch(_lexeme){
				case JSON_RB:
					deplace = 23;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		case 21 :
			switch(_lexeme){
				case JSON_COMMA:
					deplace = 24;
					break;
				default:
					deplace = -1;
					break;
			}
			break;
		default :
			deplace = -1;
			break;
	}
	return deplace;
}






/**
  * \fn RegleReduction(int _lexeme, int _etat)
  * \brief Fonction qui donne le numéro de la règle à laquelle se reférer lors d'une réduction.
  *
  * 
  * \param[in] _lexeme. Symbole reconnu par l'analyseur lexical.
  * \param[in] _etat.  L’état en sommet de pile.
  *
  * \return retourne regle Le numéro de la règle.
  *
 **/
int RegleReduction(int _lexeme, int _etat){
	int regle = 0;
	switch(_etat){
		case 4: 
			switch(_lexeme){
				case JSON_RCB:
					regle = 3;
					break;
				default:
					regle = -1;
			}
			break;
		case 5:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
				case JSON_LEX_ERROR:
					regle = 1;
					break;
				default:
					regle = -1;
			}
			break;
		case 7:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
				case JSON_LEX_ERROR:
					regle = 2;
					break;
				default:
					regle = -1;
			}
			break;	
		case 10:
			switch(_lexeme){
				case JSON_RCB:
					regle = 4;
					break;
				default:
					regle = -1;
			}
			break;	
		case 11:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 12;
					break;
				default:
					regle = -1;
			}
			break;	
		case 12:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 13;
					break;
				default:
					regle = -1;
			}
			break;	
		case 13:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_COMMA:
					regle = 5;
					break;
				default:
					regle = -1;
			}
			break;	
		case 15:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 10;
					break;
				default:
					regle = -1;
			}
			break;	
		case 16:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 11;
					break;
				default:
					regle = -1;
			}
			break;	
		case 17:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 14;
					break;
				default:
					regle = -1;
			}
			break;	
		case 18:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 15;
					break;
				default:
					regle = -1;
			}
			break;	
		case 19:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 16;
					break;
				default:
					regle = -1;
			}
			break;	
		case 21:
			switch(_lexeme){
				case JSON_RB:
					regle = 8;
					break;
				default:
					regle = -1;
			}
			break;
		case 22:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 6;
					break;
				default:
					regle = -1;
			}
			break;
		case 23:
			switch(_lexeme){
				case JSON_RCB:
				case JSON_RB:
				case JSON_COMMA:
					regle = 7;
					break;
				default:
					regle = -1;
			}
			break;
		case 25:
			switch(_lexeme){
				case JSON_RB:
					regle = 9;
					break;
				default:
					regle = -1;
			}
			break;
		default:
			regle = -1;
		
	}
	return regle;
}





/**
  * \fn DestReduction(char *_auxiliaire, int _etat)
  * \brief Fonction qui identifie l'état qui intervient après une réduction
  *
  * 
  * \param[in] _etat. Etat en sommet de pile.
  * \param[in] _auxiliaire. Auxiliaire gauche des règles de la grammaire.
  * 
  *
  * \return resultat au nouvel état de sommet de pile.
  *
 **/
int DestReduction(char *_auxiliaire, int _etat){
	int resultat = 0;
	switch(*_auxiliaire){
		case 'O':
			switch(_etat){
				case 0:
					resultat = 1;
					break;
				case 9:
				case 14:
				case 24:
					resultat = 11;
					break;
				default:
					resultat = -1;
			}
			break;
		case 'M':
			switch(_etat){
				case 2:
					resultat = 3;
					break;
				case 8:
					resultat = 10;
					break;
				default:
					resultat = -1;
			}
			break;
		case 'P':
			switch(_etat){
				case 2:
				case 8:
					resultat = 4;
					break;
				default:
					resultat = -1;
			}
			break;
		case 'A':
			switch(_etat){
				case 9:
				case 14:
				case 24:
					resultat = 12;
					break;
				default:
					resultat = -1;
			}
			break;
		case 'E':
			switch(_etat){
				case 14:
					resultat = 20;
					break;
				case 24:
					resultat = 25;
					break;
				default:
					resultat = -1;
			}
			break;
		case 'V':
			switch(_etat){
				case 9:
					resultat = 13;
					break;
				case 14:
				case 24:
					resultat = 21;
					break;
				default:
					resultat = -1;
			}
			break;
		default:
			resultat = -1;
	}
	return resultat;
}





/**
  * \fn AuxiliaireGauche(int _numRegle)
  * \brief Fonction determine l'auxiliaire gauche d'une règle.
  *
  * 
  * \param[in] _numRegle. Le numéro de la règle.
  * 
  *
  * \return auxiliaire L'auxiliaire gauche d'une regle.
  *
 **/
char *AuxiliaireGauche(int _numRegle){
	char *auxiliaire;
	switch(_numRegle){
		case 0:
			auxiliaire = "S";
			break;
		case 1:
		case 2:
			auxiliaire = "O";
			break;
		case 3:
		case 4:
			auxiliaire = "M";
			break;
		case 5:
			auxiliaire = "P";
			break;
		case 6:
		case 7:
			auxiliaire = "A";
			break;
		case 8:
		case 9:
			auxiliaire = "E";
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			auxiliaire = "V";
			break;
		default:
			auxiliaire = NULL;
	}
	return auxiliaire;
}
		



/**
  * \fn TailleRegle(int _numRegle)
  * \brief Fonction qui retourne la taille de la partie droite de chaque règles
  *
  * 
  * \param[in] _numRegle. Le numéro de la règle.
  * 
  *
  * \return un int correspondant à la taille de la partie droite de la règle _numRegle.
  *
 **/
int TailleRegle(int _numRegle){
	int taille = 0;
	switch(_numRegle){
		case 0:
		case 3:
		case 8:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
			taille = 1;
			break;
		case 1:
		case 6:
			taille = 2;
			break;
		case 2:
		case 4:
		case 5:
		case 7:
		case 9:
			taille = 3;
			break;
		default:
			taille = -1;
	}
	return taille;
}



/**
  * \fn OpenFile(char *_file)
  * \brief Fonction permettant d'ouvrir un fichier et de mettre son contenu dans un tableau.
  *
  * \param[in] _file Le nom du fichier à appeler.
  * \param[out] chaine Une chaine contenant le contenu du fichier.
  * 
  * \return chaine
  *
 **/
char * OpenFile(char *_file){

	FILE* fichier = NULL; 
	fichier = fopen(_file, "r"); // On ouvre le fichier en mode lecture
	size_t size = 0;
	/*si l'ouverture a reussi*/    
	if(fichier){
        
		fseek(fichier, 0, SEEK_END);// place le curseur à a fin du fichier
		size = ftell(fichier)+1;// ftell donne la position courante du curseur
		printf("Nombre d'éléments du fichier : %ld\n",size);
		rewind(fichier);// remet le curseur au début du fichier
	 
		char *chaine = malloc(size*sizeof(char));//j'alloue une chaine de taille "size" de char
	    
		size_t elemLu = fread(chaine, sizeof(char), size, fichier);
		printf("Nombre d'éléments  lu : %ld\n", elemLu);
		
		chaine[elemLu] = '\0';
		return chaine;
		free(chaine);
	}
	else{
		printf("erreur d'ouverture du fichier\n");
		exit(1);
	}
	fclose(fichier);
	return NULL;
}



/**
  * \fn AnalyseurLR(char *_file)
  * \brief Fonction qui execute l'algorithme LR sur une chaine de caractère.
  *
  * \param[in] _file Le nom du fichier à appeler.
  *
  * \param[out] fini Une variable qui prend la valeur 1 lorsque l'analyseur a reconnu une grammaire Json,
  *		-1 lorsqu'il y a une erreur.
  *
  * \return fini
  *
 **/
int AnalyseurLR(char *_file){

	int fini = 0;
	int etat = 0;
	int action = 0;

	TIntPile *pile = initIntPile(); // On initialise une pile d'entier vide
	TVoidPile *pileJson = initVoidPile(); //On initialise une pile de void vide
	
	char *data = OpenFile(_file); // On insère le contenur du fichier dans data

	TLex *lex_Data = initLexData(data); // On initialise les données pour l'analyseur lexical
	
	empilerInt(pile, etat);// On empile l'état 0 sur le pile d'entier
	
	int lexeme = lex(lex_Data); // lexeme est le résultat de l'analyseur lexical
	
	/*tant que l'on a pas un etat d'acceptation ou une erreur, on fait tourner l'analyseur syntaxique*/
	while(!fini){
		action = TableAction(lexeme,sommetInt(pile));
		
		if(action == ACCEPTATION){
			
			depilerVoid(pileJson);
			fini = 1;
		}
		else if(action == ERREUR){
			printf("Grammaire non reconnu\n");
			fini = -1;
		}
		else if(action == DEPLACEMENT){
			etat = TableGoto(lexeme,sommetInt(pile));

			empilerInt(pile, etat);

			lexeme = lex(lex_Data);
		}
		else if(action == REDUCTION){
			int i = 0;
			int regle = RegleReduction(lexeme, sommetInt(pile));
			char *auxiliaire = AuxiliaireGauche(regle);

			/* On dépile pile autant de fois que la taille de la partie droite de la regle*/
			while( i < TailleRegle(regle)){
				depilerInt(pile);
				i++; 
			}
			switch(regle){
				case 0:
					etat = DestReduction(auxiliaire , sommetInt(pile));
					empilerInt(pile, etat);
					break;
				case 1:
				case 2:
					etat = DestReduction(auxiliaire , sommetInt(pile));
					empilerInt(pile, etat);
					break;
				case 3:
				case 4:
					etat = DestReduction(auxiliaire , sommetInt(pile));
					empilerInt(pile, etat);
					break;
				case 5:
					etat = DestReduction(auxiliaire , sommetInt(pile));
					empilerInt(pile, etat);
					break;
				case 6:
				case 7:
					etat = DestReduction(auxiliaire , sommetInt(pile));
					empilerInt(pile, etat);
					break;
				case 8:
				case 9:
					etat = DestReduction(auxiliaire , sommetInt(pile));
					empilerInt(pile, etat);
					break;
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
					etat = DestReduction( auxiliaire , sommetInt(pile));
					empilerInt(pile, etat);
					break;
				default:
					printf("Erreur de reduction");
					break;
				
			}
		}
	
			/*arbre Json*/
			/*switch(regle){	
				case 1: // O ->	{ }	
					JsonObject *object = CreateJsonObject();
					empilerVoid(pileJson, object);
					break;

				case 2: // O -> { M }
					break;

				case 3: // M -> P
					int i = 0;
					JsonPair *paire = depilerVoid(pileJson);
					JsonObject *object = CreateJsonObject();
					i = InsertJsonObject(object, paire);
					empilerVoid(pileJson, object);
					break;

				case 4: // M -> P, M
					int i = 0;
					JsonObject *object = depilerVoid(pileJson);
					JsonPair *paire = depilerVoid(pileJson);
					i = InsertJsonObject(object, paire);
					empilerVoid(pileJson, object);
					break;

				case 5:// P -> s : V
					JsonPair *paire = CreateJsonPair();
					JsonValueContainer *conteneur = depilerVoid(pileJson);
					char *string = lexData->tableSymboles[lexData->nbSymboles-1].val.chaine;
					UpdateJsonPair(paire, string, conteneur);
					empilerVoid(pileJson, paire);
					free(string);
					break;

				case 6: // A -> []
					JsonArray *array = CreateJsonArray();
					empilerVoid(pileJson, array);
					break;

				case 7: // A -> [ E ]
					break;

				case 8: // E -> V
					int i =0;
					JsonArray *array = CreateJsonArray();
					JsonValueContainer *value = depilerVoid(pileJson);
					i = InsertJsonArray(array, value, 0);
					break;

				case 9: // E -> V, E
					int i = 0;
					JsonArray *array = depilerVoid(pileJson);
					JsonValueContainer *value = depilerVoid(pileJson);
					i = InsertJsonArray(array, value, 0);
					empiler(pileJson, array);
					break;	
		}*/
	
	}
    	deleteIntPile(&pile);
	deleteLexData(&lex_Data);
	deleteVoidPile(&pileJson);
	free(data);
	return fini;
}	


int main(int argc, char *argv[]){

	(void)argc;// pour enlever l'erreur "unused parameter argc"

	if(AnalyseurLR(argv[1]) == 1)
		printf("Grammaire reconnu\n");


	return 0;
}
 


	  
		
