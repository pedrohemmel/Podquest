#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

//É utilizado # para separar tipo de funções
//É utilizado * para separar funções
//É utilizado #$ para separar objetos

/*#########################################################################################################*/
/*#########################################################################################################*/
/*########### STRUCTS ##########*/
/*#########################################################################################################*/
/*#########################################################################################################*/

//Criando struct do podquest
typedef struct podquest {

  int idPodquest;
  char nomePodquest[64];

  struct podquest *previous;
  struct podquest *next;

} Podquest;

//Criando um ponteiro para auxiliar na criação de novos podcasts
typedef Podquest* newPodquest;

/***********************************************************************************************************/
/***********************************************************************************************************/

//criando struct da playlist
typedef struct playlist {

  newPodquest first;
  newPodquest current;
  newPodquest last;

} Playlist;

//Alocando um espaço na memoria para new playlist
typedef Playlist *newPlaylist;

/***********************************************************************************************************/
/***********************************************************************************************************/

//criando struct de epidodios
typedef struct ep {

  int idPodquest;
  int idEp;
  char nomeEpisode[64];

  struct ep *previous;
  struct ep *next;

} Ep;

//Alocando um espaço na memória para struct ep

typedef Ep *newEp;

/***********************************************************************************************************/
/***********************************************************************************************************/

//Criando a lista que vai armazenar os episodios
typedef struct listEp {

  newEp first;
  newEp current;
  newEp last;

} ListEp;

typedef ListEp * newListEp;

/***********************************************************************************************************/
/***********************************************************************************************************/

//Criando uma struct para as palavras-chaves
typedef struct keyWord {

  int idEpisode;
  char nomePalavraChave[64];

  struct keyWord *previous;
  struct keyWord *next;

} KeyWord;

//Alocando um espaço na memória para a palavra-chave
typedef KeyWord *newKeyWord;

/***********************************************************************************************************/
/***********************************************************************************************************/

//Criando uma struct para lista de palavras chaves
typedef struct listKeyWord {

  newKeyWord first;
  newKeyWord current;
  newKeyWord last;

} ListKeyWord;

//Alocando um espaço na memória para a lista de palavra-chave
typedef ListKeyWord * newListKeyWord;


/*#########################################################################################################*/
/*#########################################################################################################*/
/*########### FUNCTIONS ##########*/
/*#########################################################################################################*/
/*#########################################################################################################*/

void remove_newline_ch(char* line) {
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}

/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$ PODCASTS #$#$#$#$#$#$*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/

int verificarIdPodquest(newPlaylist newPlay, int id, newPlaylist novaPlay) {

  novaPlay->first = NULL;
  novaPlay->current = NULL;
  novaPlay->last = NULL;

  for(newPodquest aux = newPlay->first; aux != NULL; aux = aux->next) {
    if(novaPlay->first == NULL) {
      novaPlay->first = aux;
      novaPlay->current = aux;
      novaPlay->last = aux;
    }
    else {
      novaPlay->current->next = aux;
      novaPlay->current = novaPlay->current->next;
    }
  }

  novaPlay->current = novaPlay->first;


  
  //Percorrendo os itens da lista de episodios e verificando se há um id igual na lista
  while(novaPlay->current != NULL) {
    if(novaPlay->current->idPodquest == id) {
      return 1;
    }
    novaPlay->current = novaPlay->current->next;
  }

  return 0;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

newPodquest createNewPodquest(newPlaylist newPlay, newPlaylist novaPlay) {

  //Reservando um valor na memória para o podcast
  newPodquest newPodcast = (newPodquest)malloc(sizeof(Podquest));

  printf("\nDigite o id do podcast:\n");
  scanf("%d", &newPodcast->idPodquest);
  getchar();

  int verificarId = verificarIdPodquest(newPlay, newPodcast->idPodquest, novaPlay);

  while(verificarId == 1) {
    printf("\nJá existe um podcast com esse id no sistema, digite outro id:\n");
    scanf("%d", &newPodcast->idPodquest);
    getchar();
    verificarId = verificarIdPodquest(newPlay, newPodcast->idPodquest, novaPlay);
  }

  printf("\nDigite o nome do podcast:\n");
  fgets(newPodcast->nomePodquest, 64, stdin);
  remove_newline_ch(newPodcast->nomePodquest);

  newPodcast->next = NULL;
  newPodcast->previous = NULL;
  
  
  return newPodcast;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

//Adicionando podcast a playlist
void addNewPodquestOrderById(Playlist* playlist, newPlaylist novaPlay) {

  newPodquest newPodcast = createNewPodquest(playlist, novaPlay);

  //Se não houver podcasts na playlist, é adicionado um novo podcast representando o inicial, atual e final
  if(playlist->first == NULL) {
    
    playlist->first = newPodcast;
    playlist->current = playlist->first;
    playlist->last = newPodcast;

    return;

    //Se o id do podcast for menor que os ids que tem
  } else if(newPodcast->idPodquest <= playlist->last->idPodquest) {
    
    newPodcast->next = playlist->first->next;
    playlist->first->next = newPodcast;
    newPodcast->previous = playlist->first;
    playlist->current = playlist->first;

    return;

    //Se o id do podcast for maior que o id do final, ele adiciona um no proximo
  } else {
    playlist->last->next = newPodcast;
    newPodcast->previous = playlist->last;
    playlist->last = newPodcast;
    playlist->current = playlist->first;

    return;
  }
} 

/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$ PLAYLIST #$#$#$#$#$#$*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/

//função que cria a playlist setando seus apontamentos como nulos
newPlaylist createNewPlaylist() {

	newPlaylist novaPlaylist = (newPlaylist)malloc(sizeof(Playlist));

	novaPlaylist->first = NULL;
	novaPlaylist->current = NULL;
	novaPlaylist->last = NULL;
	
	return novaPlaylist;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

//Função que mostra todos os podcasts da playlist
void viewPodcastsInPlaylist(newPlaylist novaPlaylist) {
  
  newPlaylist novaPlay = createNewPlaylist(); 
  for(newPodquest aux = novaPlaylist->first; aux != NULL; aux = aux->next) {
    if(novaPlay->first == NULL) {
      novaPlay->first = aux;
      novaPlay->current = aux;
      novaPlay->last = aux;
    }
    else {
      novaPlay->current->next = aux;
      novaPlay->current = novaPlay->current->next;
    }
  }

  novaPlay->current = novaPlay->first;

  int qtdPodcasts = 0;
  
  printf("\n");
  //Percorrendo os itens da playlist
  while(novaPlay->current != NULL) {
    printf("%d - %s", novaPlay->current->idPodquest, novaPlay->current->nomePodquest);
    printf("\n");
    novaPlay->current = novaPlay->current->next;
    qtdPodcasts++;
  }

  printf("\nSua playlist tem %d podcast(s) no total\n", qtdPodcasts);

}

/***********************************************************************************************************/
/***********************************************************************************************************/

newPodquest verifyNamePodcastById(newPlaylist novaPlaylist, int id) {
  newPlaylist novaPlay = createNewPlaylist(); 
  for(newPodquest aux = novaPlaylist->first; aux != NULL; aux = aux->next) {
    if(novaPlay->first == NULL) {
      novaPlay->first = aux;
      novaPlay->current = aux;
      novaPlay->last = aux;
    }
    else {
      novaPlay->current->next = aux;
      novaPlay->current = novaPlay->current->next;
    }
  }

  novaPlay->current = novaPlay->first;

  //Percorrendo os itens da playlist
  while(novaPlay->current != NULL) {
    if(novaPlay->current->idPodquest == id) {
      return novaPlay->current;
    }
    novaPlay->current = novaPlay->current->next;
  }
  return NULL;
}

/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$ PALAVRA CHAVE #$#$#$#$#$#$*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/

//Cria uma nova lista de episodios e seta todos atributos como nulo para não ocorrer problema de memória
newListKeyWord createNewListKeyWord() {

	newListKeyWord novaListKeyWord = (newListKeyWord)malloc(sizeof(ListKeyWord));

	novaListKeyWord->first = NULL;
	novaListKeyWord->current = NULL;
	novaListKeyWord->last = NULL;
	
	return novaListKeyWord;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

//Adicionando podcast a playlist
void addNewKeyWordOrderByEpId(newListKeyWord newLstKeyWord, newKeyWord newKey) {

  newKeyWord novaPalavraChave = newKey;

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

/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$ EPISODIOS #$#$#$#$#$#$*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/
/*#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#$#*/

//Cria uma nova lista de episodios e seta todos atributos como nulo para não ocorrer problema de memória
newListEp createNewListEp() {

	newListEp novaListEp = (newListEp)malloc(sizeof(ListEp));

	novaListEp->first = NULL;
	novaListEp->current = NULL;
	novaListEp->last = NULL;
	
	return novaListEp;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

//Função que irá printar todos itens da lista de episódios
void viewAllEps(newPlaylist newPlay, newListEp newLstEp) {
  
  newListEp novoEp = createNewListEp();
  for(newEp aux = newLstEp->first; aux != NULL; aux = aux->next) {
    if(novoEp->first == NULL) {
      novoEp->first = aux;
      novoEp->current = aux;
      novoEp->last = aux;
    }
    else {
      novoEp->current->next = aux;
      novoEp->current = novoEp->current->next;
    }
  }

  novoEp->current = novoEp->first;

  printf("\n");

  int qtdEps = 0;
  
  //Percorrendo os itens da lista de episodios e printando os mesmos
  while(novoEp->current != NULL) {
    newPodquest newPod = verifyNamePodcastById(newPlay, novoEp->current->idPodquest);
    printf("%s | %d - %s", newPod->nomePodquest, novoEp->current->idEp, novoEp->current->nomeEpisode);
    printf("\n");
    novoEp->current = novoEp->current->next;
    qtdEps++;
  }

  printf("\nSua playlist tem %d episódio(s) no total\n", qtdEps);
}

/***********************************************************************************************************/
/***********************************************************************************************************/

//Função para verificar ja existe o id na lista de episódios
int verificarIdEpisodio(newListEp newLstEp, int id) {
  
  newListEp novoEp = createNewListEp();
  for(newEp aux = newLstEp->first; aux != NULL; aux = aux->next) {
    if(novoEp->first == NULL) {
      novoEp->first = aux;
      novoEp->current = aux;
      novoEp->last = aux;
    }
    else {
      novoEp->current->next = aux;
      novoEp->current = novoEp->current->next;
    }
  }

  novoEp->current = novoEp->first;
  
  //Percorrendo os itens da lista de episodios e verificando se há um id igual na lista
  while(novoEp->current != NULL) {
    if(novoEp->current->idEp == id) {
      return 1;
    }
    novoEp->current = novoEp->current->next;
  }

  return 0;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

newEp createNewEp(newListKeyWord newListKeyWord, newListEp newLstEp, newPlaylist newPlay) {

  //Reservando um valor na memória para o podcast
  newEp newEpisode = (newEp)malloc(sizeof(Ep));

  //Variavel para controlar a quantide de palavras chaves
  int controlKeyWord;
  int controlIdEpisode;

  printf("\nDigite o id do podcast que lançou o episódio:\n");
  scanf("%d", &newEpisode->idPodquest);
  getchar();

  newPodquest newPod = verifyNamePodcastById(newPlay, newEpisode->idPodquest);

  while(newPod == NULL) {
    printf("\nNão existe um podcast com esse id, digite outro id: \n");
    scanf("%d", &newEpisode->idPodquest);
    getchar();
    newPod = verifyNamePodcastById(newPlay, newEpisode->idPodquest);
  }

  printf("\nDigite o id do episodio:\n");
  scanf("%d", &newEpisode->idEp);
  getchar();

  controlIdEpisode = verificarIdEpisodio(newLstEp, newEpisode->idEp);

  while(controlIdEpisode == 1) {
    printf("\nJá existe outro episódio com esse id.\n\nDigite um id diferente: \n");
    scanf("%d", &newEpisode->idEp);
    getchar();

    controlIdEpisode = verificarIdEpisodio(newLstEp, newEpisode->idEp);
  }

  printf("\nDigite o nome do episódio:\n");
  fgets(newEpisode->nomeEpisode, 64, stdin);
  remove_newline_ch(newEpisode->nomeEpisode);

  printf("\nDeseja adicionar uma palavra chave a esse episódio? Se sim, digite <1>, se não, digite qualquer outro número: \n");
    scanf("%d", &controlKeyWord);

  while(controlKeyWord == 1)  {
    
    if(controlKeyWord == 1) {
      //Reservando um valor na memória para o podcast
      newKeyWord newKey = (newKeyWord)malloc(sizeof(KeyWord));
    
      //Variavel para controlar a quantide de palavras chaves
      newKey->idEpisode = newEpisode->idEp;
    
      printf("\nDigite uma palavra chave:\n");
      scanf("%s", newKey->nomePalavraChave);
    
      newKey->next = NULL;
      newKey->previous = NULL;
    
      addNewKeyWordOrderByEpId(newListKeyWord, newKey);
      
      printf("\nDigite 1 se quiser inserir mais uma palavra chave e qualquer outro número se quiser parar: \n");
      scanf("%d", &controlKeyWord);
    } 
  }
  
  newEpisode->next = NULL;
  newEpisode->previous = NULL;

  printf("\nEPISÓDIO CADASTRADO COM SUCESSO!\n");
  
  return newEpisode;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

//Adicionando podcast a playlist
void addNewEpisodeOrderById(newListEp newLstEp, newListKeyWord newListKeyWord, newPlaylist newPlay) {

  printf("\nPodcasts disponíveis na playlist: \n");
  viewPodcastsInPlaylist(newPlay);
    
  
  newEp newEpisode = createNewEp(newListKeyWord, newLstEp, newPlay);

  //Se não houver podcasts na playlist, é adicionado um novo podcast representando o inicial, atual e final
  if(newLstEp->first == NULL) {
    
    newLstEp->first = newEpisode;
    newLstEp->current = newEpisode;
    newLstEp->last = newEpisode;

    return;

    //Se o id do podcast for menor que os ids que tem
  } else {

    
    while(newLstEp->last->next != NULL) {
      newLstEp->last = newLstEp->last->next;
    }
    if(newLstEp->last->next == NULL) {
      newLstEp->last->next = newEpisode;
    }
    
   
    
    return;

    //Se o id do podcast for maior que o id do final, ele adiciona um no proximo
  }
} 

/***********************************************************************************************************/
/***********************************************************************************************************/

//Função que busca todos episódios por um certo id
int selectEpsById(newPlaylist newPlay, newListEp newLstEp, int id) {

  newListEp novaListEp = createNewListEp();

  for(newEp aux = newLstEp->first; aux != NULL; aux = aux->next) {
    if(novaListEp->first == NULL) {
      novaListEp->first = aux;
      novaListEp->current = aux;
      novaListEp->last = aux;
    } else {
      novaListEp->current->next = aux;
      novaListEp->current = novaListEp->current->next;
    }
  }

  novaListEp->current = novaListEp->first;

  int verificaPodcast = 0;
  
  while(novaListEp->current != NULL) {
    if(novaListEp->current->idPodquest == id) {

      newPodquest newPod = verifyNamePodcastById(newPlay, novaListEp->current->idPodquest);
      
      printf("\n%s | %d - %s\n", newPod->nomePodquest, novaListEp->current->idEp, novaListEp->current->nomeEpisode);

      verificaPodcast = 1;
      
    }
    novaListEp->current = novaListEp->current->next;
  }
  
  return verificaPodcast;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

//Função que removerá os episódios de um podcast específico

void removeEpisode(newListEp newLstEp, newPlaylist newPlay) {
  if(newLstEp->first != NULL && newLstEp->current != NULL && newLstEp->last != NULL) {
    
    int idEpisodio, idPodcast, verificaPodcast;
    newEp removido;

    printf("\nPodcasts disponíveis: \n");

    viewPodcastsInPlaylist(newPlay);
    
    printf("\nDigite o id do podcast: \n");
    scanf("%d", &idPodcast);
    getchar();

    //chamando função que verifica se tem podcast com o id digitado
    verificaPodcast = selectEpsById(newPlay, newLstEp, idPodcast);

    while(verificaPodcast == 0) {
      printf("\nO id digitado não pertence a nenhum podcast, digite novamente: \n");
      scanf("%d", &idPodcast);
      getchar();
      verificaPodcast = selectEpsById(newPlay, newLstEp, idPodcast);
    }
    
    printf("\nDigite o número do episódio: \n");
    scanf("%d", &idEpisodio);
    getchar();
    
      if(newLstEp->first->next == NULL) {
        if(newLstEp->first->idEp == idEpisodio && newLstEp->first->idPodquest == idPodcast) {
          removido = newLstEp->first;

          //resetando a lista
          newLstEp->first = NULL;
          newLstEp->current = NULL;
          newLstEp->last = NULL;
          
          printf("\nEpisódio %d - %s removido com sucesso!\n", removido->idEp, removido->nomeEpisode);
          return;
        }
      }

      else {
        for(newEp aux = newLstEp->first; aux != NULL; aux = aux->next){
          if(newLstEp->first->idEp == idEpisodio && newLstEp->first->idPodquest == idPodcast) {
              removido = newLstEp->first;
              newLstEp->first = newLstEp->first->next;
            if(newLstEp->current->idEp == idEpisodio && newLstEp->current->idPodquest == idPodcast ) {
              newLstEp->current = newLstEp->current->next;
              }
              printf("\nEpisódio %d - %s removido com sucesso!\n", removido->idEp, removido->nomeEpisode);
              //resetando o episodio
              removido->previous = NULL;
              removido->next = NULL;
      
            }
            
          else if(aux->next->idEp == idEpisodio && aux->next->idPodquest == idPodcast) {
            removido = aux->next;
            aux->next = aux->next->next;
            
            //resetando o episodio
            removido->previous = NULL;
            removido->next = NULL;
            
            if(newLstEp->current->idEp == idEpisodio && newLstEp->current->idPodquest == idPodcast ) {
              newLstEp->current = newLstEp->current->next;
            }
            printf("\nEPISÓDIO %d - %s REMOVIDO COM SUCESSO!\n", removido->idEp, removido->nomeEpisode);

            //resetando o episodio
            removido->previous = NULL;
            removido->next = NULL;
            return;
          }
        }
      }
    }
  else {
    printf("\nNÃO EXISTE EPISÓDIOS PARA APAGAR OU O ID DIGITADO ESTÁ INCORRETO!\n");
  }
  
}

/***********************************************************************************************************/
/***********************************************************************************************************/

newEp selectEpById(newListEp newLstEp, int id) {
  
  newListEp novaListEp = createNewListEp();

  for(newEp aux = newLstEp->first; aux != NULL; aux = aux->next) {
    if(novaListEp->first == NULL) {
      novaListEp->first = aux;
      novaListEp->current = aux;
      novaListEp->last = aux;
    } else {
      novaListEp->current->next = aux;
      novaListEp->current = novaListEp->current->next;
    }
  }

  novaListEp->current = novaListEp->first;

  while(novaListEp->current != NULL) {
    if(novaListEp->current->idEp == id) {
      return novaListEp->current;
    }
    novaListEp->current = novaListEp->current->next;
  }

  return NULL;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

newEp proxEp(newListEp newLstEp, int id) {
  
  newListEp novaListEp = createNewListEp();

  for(newEp aux = newLstEp->first; aux != NULL; aux = aux->next) {
    if(novaListEp->first == NULL) {
      novaListEp->first = aux;
      novaListEp->current = aux;
      novaListEp->last = aux;
    } else {
      novaListEp->current->next = aux;
      novaListEp->current = novaListEp->current->next;
    }
  }

  novaListEp->current = novaListEp->first;

  while(novaListEp->current != NULL) {
    if(novaListEp->current->idEp == id) {
      if(novaListEp->current->next != NULL) {
        return novaListEp->current->next;
      } else {
        return NULL;
      }
    }
    novaListEp->current = novaListEp->current->next;
  }

  return NULL;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

void tocarEp(newListEp newLstEp, newPlaylist newPlay, newEp novoEp) {
  if(newLstEp->first != NULL && newLstEp->current != NULL && newLstEp->last != NULL) {

      int continuarTocando = 1;
      int idEpisodio, idPodcast, verificaPodcast;
      newEp removido;
  
      printf("\nPodcasts disponíveis: \n");
  
      viewPodcastsInPlaylist(newPlay);
      
      printf("\nDigite o id do podcast para selecionar o episódio: \n");
      scanf("%d", &idPodcast);
      getchar();
  
      verificaPodcast = selectEpsById(newPlay, newLstEp, idPodcast);
  
      while(verificaPodcast == 0) {
        printf("\nO id digitado não pertence a nenhum podcast, digite novamente: \n");
        scanf("%d", &idPodcast);
        getchar();
        verificaPodcast = selectEpsById(newPlay, newLstEp, idPodcast);
      }
      
      printf("\nDigite o número do episódio: \n");
      scanf("%d", &idEpisodio);
      getchar();
  
      novoEp = selectEpById(newLstEp, idEpisodio);
  
      printf("\nTocando: %s\n\nDeseja passar para o próximo episódio? Se sim, digite <1>, se não, qualquer outro número:\n", novoEp->nomeEpisode);

      scanf("%d", &continuarTocando);

      while(continuarTocando == 1) {
        novoEp = proxEp(newLstEp, idEpisodio);

        if(novoEp == NULL) {
          printf("\nVocê não tem mais episódios na sua playlist.\n");
          return;
        } else {
          idEpisodio = novoEp->idEp;
        }

        printf("\nTocando: %s\n\nDeseja passar para o próximo episódio? Se sim, digite <1>, se não, qualquer outro número:\n", novoEp->nomeEpisode);

        scanf("%d", &continuarTocando);
        
      }
    
  } else {
    printf("\nNão tem nenhum episódio no sistema para ser tocado.\n");
  }
  
}

/***********************************************************************************************************/
/***********************************************************************************************************/

//Função que consta quantos elementos tem na lista de episódios
int countLstEp(newListEp newLstEp) {
  newListEp novaListEp = createNewListEp();

  for(newEp aux = newLstEp->first; aux != NULL; aux = aux->next) {
    if(novaListEp->first == NULL) {
      novaListEp->first = aux;
      novaListEp->current = aux;
      novaListEp->last = aux;
    } else {
      novaListEp->current->next = aux;
      novaListEp->current = novaListEp->current->next;
    }
  }

  int count = 0;
  
  novaListEp->current = novaListEp->first;

  while(novaListEp->current != NULL) {
    count++;
    novaListEp->current = novaListEp->current->next;
  }

  return count;
}

/***********************************************************************************************************/
/***********************************************************************************************************/

void tocarShuffle(newListEp newLstEp, newEp novoEp) {

  if(newLstEp->first != NULL && newLstEp->current != NULL && newLstEp->last != NULL) {
  

    srand(time(NULL));
    int randomNum = rand() % countLstEp(newLstEp) + 1;
  
    printf("%d", randomNum);
  
    newListEp novaListEp = createNewListEp();
  
    for(newEp aux = newLstEp->first; aux != NULL; aux = aux->next) {
      if(novaListEp->first == NULL) {
        novaListEp->first = aux;
        novaListEp->current = aux;
        novaListEp->last = aux;
      } else {
        novaListEp->current->next = aux;
        novaListEp->current = novaListEp->current->next;
      }
    }
  
      novaListEp->current = novaListEp->first;

    //Enquanto o numero randomico for maior que 0, ele continua decrementando até chegar no um e ver qual é o objeto que está no 1
      while(randomNum > 0) {

          //Se tiver somente um indicador anterior
          if(novoEp == novaListEp->current && novoEp->next == NULL && novoEp->previous != NULL) {
            novoEp = novoEp->previous;

          //Se tiver apenas um indicador proximo
          } else if(novoEp == novaListEp->current && novoEp->next != NULL && novoEp->previous == NULL) {
            novoEp = novoEp->next;

          //Se tiver um indicador proximo e anterior
          } else if(novoEp == novaListEp->current && novoEp->next != NULL && novoEp->previous != NULL) {
            novoEp = novoEp->next;
            
          } else {   
            novoEp = novaListEp->current;
          }
          
          printf("\nTocando: %s\n", novoEp->nomeEpisode);
        }
        novaListEp->current = novaListEp->current->next;
        randomNum--;
      }

}

int main(void) {

  newPlaylist newPlay = createNewPlaylist();
  newPlaylist playlistAux = createNewPlaylist();
  newListEp newLstEp = createNewListEp();
  newListKeyWord newLstKeyWord = createNewListKeyWord();

  newEp tocando;
  
  int count = 1;
  int escolha;
  while(count == 1) {
    newPlaylist playlist = newPlay;
    
    if(newPlay->current == NULL) {
      
      printf("Sua lista está vazia, adicione um novo podcast a ela:\n");
      addNewPodquestOrderById(newPlay, playlistAux);

      printf("\n\nPODCAST ADICIONADO COM SUCESSO!\n");
      
      printf("\n\nDigite 1 para continuar e qualquer outra coisa para parar: \n");
      scanf("%d", &count);
      getchar();
      
    } else {
      printf("\nDeseja tocar algum episódio? <1>: \n"); 

      printf("\nDeseja ativar o shuffle para tocar um episódio aleatório? <2>\n");
      
      printf("\nDeseja visualizar os podcasts disponiveis? <3>: \n");
      
      printf("\nDeseja visualizar os episódios disponíveis? <4>: \n");

      printf("\nDeseja apagar algum episódio disponível? <5>: \n");
      
      printf("\nDeseja adicionar um novo episódio a playlist? <6>\n");
      
      printf("\nDeseja adicionar um novo podcast na sua playlist? <7>: \n");
      
      scanf("%d", &escolha);

      switch(escolha) {
        case 1:
          tocarEp(newLstEp, newPlay, tocando);  
        break;
        case 2: 
          tocarShuffle(newLstEp, tocando);
        break;
        case 3: 
          viewPodcastsInPlaylist(playlist);
        break;
        case 4:
          viewAllEps(newPlay, newLstEp);
        break;
        case 5:
          removeEpisode(newLstEp, newPlay);
        break;
        case 6:
          addNewEpisodeOrderById(newLstEp, newLstKeyWord, newPlay);
        break;
        case 7:
          addNewPodquestOrderById(newPlay, playlistAux);
          printf("\n\nPODCAST ADICIONADO COM SUCESSO!\n");
        break;
      }

      printf("\nDigite 1 para continuar e qualquer outra coisa para parar: \n\n");
      scanf("%d", &count);
      getchar();
    }
    
    
    
  }

  
  return 0;
}