//Criando struct do podquest
typedef struct podquest {

  int idPodquest;
  char nomePodquest[64];

  struct podquest *previous;
  struct podquest *next;

} Podquest;

//Criando um ponteiro para auxiliar na criação de novos podcasts
typedef Podquest* newPodquest;