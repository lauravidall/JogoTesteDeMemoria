#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node {
 int numero;
 struct node *next;
};

struct Jogador {
  char Nome[4];
  int pont;
};

struct Highscore {
  struct Jogador jogador;
  struct Highscore *next;
};

void addnode(struct node **head, int numero);
void OrdenarLista(struct Highscore **head, struct Jogador nick);
void EscreverLista(struct Highscore *head, FILE *fptr);
void PrintarLista(struct Highscore *head);
void FreeLista(struct Highscore **head);

int main(void) {

 struct node *head = NULL;
 struct node *novo = NULL;

  FILE *fptr;
  struct Jogador player;
  printf("O jogo começará 3 segundos depois que digitar seu nick!\n");
  printf("Digite sua sigla de 3 letras: ");
  scanf("%s", player.Nome);

 int quantidade;
 quantidade = 0;
  
 printf("Você quer tentar o jogo da memória com quantos números?");
 scanf("%d", &quantidade);
 sleep(1);

 int numero;
 int listarandom[quantidade];

 for (int i = 0; i < quantidade; i++) {

 int numero_aleatorio = rand() % quantidade;
 printf("%d\n", numero_aleatorio);

 listarandom[i] = numero_aleatorio;
 sleep(1);
 system("clear");
 }

 int resposta = 0;

 for (int j = 0; j < quantidade; j++) {

 printf("Digite o número %d da sequência: ", j + 1);
 scanf("%d", &numero);
 addnode(&head, numero);

 if (listarandom[j] == numero) {
 resposta = resposta + 1;
 } else {
 printf("Você perdeu!");
 break;
 }

 }

 if (resposta == quantidade) {
   printf("PARABÉNS, você venceu!\n");
   player.pont = quantidade;
   fptr = (fopen("placar.txt", "a"));
   fwrite(&player, sizeof(struct Jogador), 1, fptr);
   fclose(fptr);
   struct Highscore *lista = NULL;
   fptr = (fopen("placar.txt", "r"));
   while (fread(&player, sizeof(struct Jogador), 1, fptr) == 1) {
     OrdenarLista(&lista, player);
   }
   fclose(fptr);
   fptr = (fopen("placar.txt", "w"));
   EscreverLista(lista, fptr);
   fclose(fptr);
   PrintarLista(lista);
   FreeLista(&lista); 
 
 }

 return 0;

}

void addnode(struct node **head, int numero) {

 struct node *n = *head;
 struct node *novo = (struct node *)malloc(sizeof(struct node));

 novo->numero = numero;

 if (*head == NULL) {
  *head = novo;
  novo->next = NULL;

 } else {
  while (n->next != NULL) {
    n = n->next;
  }
  novo->next = NULL;
  n->next = novo;
 }

}

void OrdenarLista(struct Highscore **head, struct Jogador nick) {
  if (*head == NULL) {
    *head = (struct Highscore *)malloc(sizeof(struct Highscore));
    (*head)->jogador = nick;
    (*head)->next = NULL;
  } else {
    struct Highscore *n = *head;
    struct Highscore *novo = (struct Highscore *)malloc(sizeof(struct Highscore));
    novo->jogador = nick;
    while (n->next != NULL && nick.pont < n->next->jogador.pont) {
      n = n->next;
    }
    if (nick.pont > (*head)->jogador.pont) {
      novo->next = *head;
      *head = novo;
    } else if (n->next == NULL) {
      novo->next = NULL;
      n->next = novo;
    } else {
      novo->next = n->next;
      n->next = novo;
    }
  }
}

void EscreverLista(struct Highscore *head, FILE *fptr) {
  struct Highscore *n = head;
  struct Jogador Ojogador;
  while (n != NULL) {
    Ojogador = n->jogador;
    if (fwrite(&Ojogador, sizeof(struct Jogador), 1, fptr) != 1) {
      break;
    }
    n = n->next;
  }
}

void PrintarLista(struct Highscore *head) {
  struct Highscore *n = head;
  struct Jogador Ojogador;
  int i = 1;
  while (n != NULL && (i < 4)) {
    printf("\n%d colocado:\n", i);
    printf("Nome: %s\n", n->jogador.Nome);
    printf("Pontuação: %d\n", n->jogador.pont);
    n = n->next;
    i++;
  }
}

void FreeLista(struct Highscore **head) {
  struct Highscore *n = *head;
  while (n != NULL) {
    struct Highscore *temp = n;
    n = n->next;
    free(temp);
  }
}
