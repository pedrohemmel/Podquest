#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*#$#$#$#$#$#$ PALAVRA CHAVE #$#$#$#$#$#$*/

//Cria uma nova lista de episodios e seta todos atributos como nulo para não ocorrer problema de memória
newListKeyWord createNewListKeyWord() {

	newListKeyWord novaListKeyWord = (newListKeyWord)malloc(sizeof(ListKeyWord));

	novaListKeyWord->first = NULL;
	novaListKeyWord->current = NULL;
	novaListKeyWord->last = NULL;
	
	return novaListKeyWord;
}

newKeyWord createNewKeyWord(int idEpisode) {

  //Reservando um valor na memória para o podcast
  newKeyWord newKey = (newKeyWord)malloc(sizeof(KeyWord));

  //Variavel para controlar a quantide de palavras chaves
  int controlKeyWord;

  newKey->idEpisode = idEpisode;

  printf("\nDigite a palavra chave:\n");
  fgets(newKey->nomePalavraChave, 64, stdin);
  remove_newline_ch(newKey->nomePalavraChave);

  newKey->next = NULL;
  newKey->previous = NULL;
  
  
  return newKey;
}

//Adicionando podcast a playlist
void addNewKeyWordOrderByEpId(newListKeyWord newLstKeyWord, int idEpisode) {

  newKeyWord novaPalavraChave = createNewKeyWord(idEpisode);

  //Se não houver podcasts na playlist, é adicionado um novo podcast representando o inicial, atual e final
  if(newLstKeyWord->first == NULL) {
    
    newLstKeyWord->first = novaPalavraChave;
    newLstKeyWord->current = newLstKeyWord->first;
    newLstKeyWord->last = novaPalavraChave;

    return;

    //Se o id do podcast for menor que os ids que tem
  } else if(novaPalavraChave->idEpisode <= newLstKeyWord->last->idEpisode) {
    
    novaPalavraChave->next = newLstKeyWord->first->next;
    newLstKeyWord->first->next = novaPalavraChave;
    novaPalavraChave->previous = newLstKeyWord->first;
    newLstKeyWord->current = newLstKeyWord->first;

    return;

    //Se o id do podcast for maior que o id do final, ele adiciona um no proximo
  } else {
    newLstKeyWord->last->next = novaPalavraChave;
    novaPalavraChave->previous = newLstKeyWord->last;
    newLstKeyWord->last = novaPalavraChave;
    newLstKeyWord->current = newLstKeyWord->first;

    return;
  }
} 