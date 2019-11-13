#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#define typeof(var) _Generic( (var),\
char: "Char",\
int: "Integer",\
float: "Float",\
char *: "String",\
void *: "Pointer",\
default: "Undefined")

/*

Criar uma agenda que grave jogos em 2 arquivos(binario e texto), no modo facil, medio ou dificil.
Para jogar o usuario carrega o jogo em um dos modos, preenche e salva. O programa
deve informar caso o usuario vença.

O programa deve:

- INSERIR JOGOS OK,
- LISTAR OS JOGOS EXISTENTES OK,
- REMOVER JOGOS OK,
- ALTERAR JOGOS EXISTENTES OK,
- BUSCAR JOGOS EXISTENTES EM ARQUIVOS,
- VERIFICAR CONDIÇÃO DE VITORIA.

Deve:

- Usar struct,
- função,
- malloc e free,
- gravação e leitura de arquivos.

NOME: Joao Gabriel de Sousa Assis
RA: 22218026-7

*/

void adicionar(){
    system("cls");
    puts("Menu - Adicionar");
    puts("Qual sera o nome do jogo?");

    char txt[30];
    char entrada[10];

    sprintf(txt, "%s", "jogos/");
    scanf("%s", &entrada);                              // nome do arquivo
    strcat(entrada, "Texto");                           // adiciona "Texto" ao nome do arquivo
    strcat(txt, entrada);
    //printf("%s", txt);

    puts("\nQual sera o modo do jogo?");
    puts("***1 - Facil!");
    puts("***2 - Medio!");
    puts("***3 - Dificil!");

    int modo;
    scanf("%d", &modo);                                 // salva em modo a dificuldade do jogo

    srand(time(NULL));
    char str[20];

    switch(modo){
        case 1:{                                        // modo facil
            int aleatorio = 1 + (rand() % 3);           // cria numero aletorio de 1 a 3
            sprintf(str, "modos/%d", aleatorio);        // transforma aleatorio em string
            //printf("%s", str);
        } break;

        case 2:{                                        // modo medio
            int aleatorio = 4 + (rand() % 6);           // cria numero aletorio de 4 a 6
            sprintf(str, "modos/%d", aleatorio);        // transforma aleatorio em string
        } break;

        case 3:{                                        // modo dificil
            int aleatorio = 7 + (rand() % 9);           // cria numero aletorio de 7 a 9
            sprintf(str, "modos/%d", aleatorio);        // transforma aleatorio em string
        } break;

        default:{                                       // caso o modo seja invalido
            system("clear");
            printf("\nModo invalido!\n");
        } break;
    }

    FILE *origem = fopen(str, "r");                     // abre um dos 3 sudokus no modo
    FILE *arquivo = fopen(txt, "w");                    // cria o arquivo de texto com nome dado

    char ler[10];
    while(fgets(ler, 10, origem) != NULL){              // le todas as linhas do arquivo
            fputs(ler, arquivo);                        // escreve no arquivo de texto criado
    }

    system("clear");                                    // limpa o console
    printf("\nArquivo criado!\n");                      // notifica

    fclose(origem);                                     // fecha o arquivo de exemplo
    fclose(arquivo);                                    // fecha o arquivo texto criado
}

void remover(){
    system("cls");
    puts("Menu - Remover");
    char entrada[30];
    char copia[30];

    puts("Qual jogo voce deseja excluir?");

    sprintf(copia, "%s", "jogos/");                     // adiciona o caminho da pasta em copia
    scanf("%s", &entrada);                              // atribui nome do jogo a entrada
    strcat(entrada, "Texto");                           // contatena "Texto" em entrada
    strcat(copia, entrada);                             // concatena a entrada em copia
    //printf("%s", copia);
    remove(copia);                                      // apaga o arquivo (jogos/fulanoTexto)

    system("cls");                                    // limpa o console
    printf("Removido o jogo!\n");                       // notifica
}

void lista(){
    system("cls");
    puts("Menu - Lista de jogos");
    puts("Jogos salvos:\n");
    printf("%s\n", system("ls jogos"));                 // exibe todos os jogos na pasta jogos/...
    puts("NULL = fim dos arquivos!");
}

void edita(){
    system("cls");
    puts("Editar jogos");
    puts("\nQual o nome do jogo?");

    char entrada[50];
    char copia[50];
    char nome[50];
    scanf("%s", &copia);

    sprintf(entrada, "%s", "jogos/");               // adiciona o caminho da pasta em entrada
    strcat(nome, copia);
    strcat(copia, "Texto");                         // concatena "Texto" em copia (fulanoTexto)
    strcat(entrada, copia);                         // concatena copia em entrada (jogos/fulanoTexto)
    //printf("%s\n", entrada);

    FILE *arquivo;

    if((arquivo = fopen(entrada, "r")) == NULL){    // caso não exista o arquivo
        printf("\nErro na abertura do arquivo\n");  // exibe erro
    }

    else{

      system("cls");
      arquivo = fopen(entrada, "r");              // abre o arquivo no modo leitura
      char sudoku[4][4];

      char exemplo[4][4] = {"abc", "def", "ghi"};

      int i, j;                                   // contador de linha e coluna
      printf("\nJogo: %s\n\n", nome);             // nome do jogo

      for ( i=0; i<4; i++ ){                      // le o arquivo
          for ( j=0; j<4; j++ ){
              fscanf(arquivo, "%c", &sudoku[i][j]);
          }
      }

      for ( i=0; i<4; i++ ){                      // exibe o jogo
          for ( j=0; j<4; j++ ){
              printf ("%c", sudoku[i][j]);        // sudoku do arquivo

              if(sudoku[i][j] != '0'){
                exemplo[i][j] = 'x';
              }
          }
      }

      fclose(arquivo);                            // fecha o arquivo

      puts("\nAs posicoes disponiveis sao as letras:\n");

      for ( i=0; i<3; i++ ){
          for ( j=0; j<3; j++ ){
            printf ("%c", exemplo[i][j]);         // exibe posicoes disponiveis
          }
      printf("\n");
      }

      puts("\nOnde quer jogar?");
      char jogada[3];
      scanf("%s", &jogada);

      puts("\nQual numero:");
      char numero[3];
      scanf("%s", &numero);

      for ( i=0; i<4; i++ ){
          for ( j=0; j<4; j++ ){
            if(exemplo[i][j] == jogada[0]){
              sudoku[i][j] = numero[0];
            }
          }
      printf("\n");
      }
      vitoria();                                  // funcao que verifica vitoria a cada rodada(INCOMPLETA)
    } // else
} // fim da funcao

void vitoria(){
    system("cls");
    puts("Chamada da funcao que verifica vitoria a cada rodada(INCOMPLETA)!\n");
}

int main(){
    printf("Bem vindo a agenda de sudoku!\n");

    int entrada;

    while(1){                                           // repetição em loop infinito

        puts("\nMenu:");
        puts("1 Adicionar jogo");
        puts("2 Remover jogo");
        puts("3 Listar jogos salvos");
        puts("4 Editar jogos");

        puts("\nDigite o numero:");
        scanf("%d", &entrada);

        switch(entrada){
            case 1:
                adicionar();                            // função que cria novo jogo
                break;

            case 2:
                remover();                              // função que remove jogo existente
                break;

            case 3:
                lista();                                // função que lista jogos salvos
                break;

            case 4:
                edita();                                // função que edita jogos criados ou salvos
                break;

            default:                                    // caso a entrada nao exista
                printf("\nEntrada invalida!\n");
        }
    }
    return 0;                                           // fim do programa
}
