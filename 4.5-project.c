#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0


typedef struct {
    char city_name[50];
    int coord_x;
    int coord_y;
}City_Info;


typedef struct node {
    City_Info city;
    struct node *next;
}Node;


typedef struct {
    Node *init;
} LSE;


void clear_screen() {
    system("@cls||clear");
}

// CRIA LISTA
void create_list(LSE *list) {
    list->init = NULL;
    //  puts("Lista criada!");
}


//VERIFICA SE A LISTA ESTÁ VAZIA
int empty(LSE list) {
    return (list.init == NULL);
}

City_Info read_city() {
    City_Info city;
    printf("Nome da cidade: ");
    fgets(city.city_name, 50, stdin);
    printf("Coordenadas (x,y): ");
    scanf("%d%d", &city.coord_x, &city.coord_y);


    return city;
}

//VERIFICA A QUANTIDADE DE ELEMENTOS, E RETORNA UM INTEIRO
int number_of_elements(LSE list) {
    Node *curr;
    int amount = 0;

    for(curr = list.init; curr != NULL; curr = curr->next) {
        amount++;
    }
    return amount;
}

// ALOCA UM NOVO NÓ, E INSERE NA CABEÇA DA LISTA. 
// RETORNA FALSE CASO NÃO CONSIGA ALOCAR MEMÓRIA.
int insert_head(LSE *list) {
    Node *new_node;
    City_Info new_city = read_city();

    if((new_node = malloc(sizeof(Node))) == NULL ) return FALSE;
            
    new_node->city = new_city;
    new_node->next = list->init;
    list->init = new_node;

    return TRUE;
}

int insert_end(LSE *list) {
    //se a lista estiver vazia, insere na cabeça
    if(empty(*list)) {
        return insert_head(list);
    }

    Node *curr, *new_node;
    City_Info new_city = read_city();

    if((new_node = malloc(sizeof(Node))) == NULL ) return FALSE;

    //encontra a ultima posição
    curr = list->init;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_node;
    new_node->next = NULL;
    new_node->city = new_city;

    return TRUE;    

}

void print_cities(LSE list) {
    Node *curr;

    if(empty(list)) {
        return;
    }

    clear_screen();

    puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-\n");
    for (curr = list.init; curr != NULL; curr = curr->next) {
        printf("Nome: %s", curr->city.city_name);
        printf("Coordenadas: (%d,%d)\n\n", curr->city.coord_x, curr->city.coord_y);
    }
    puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-\n\n");
}

int remove_head(LSE *list, City_Info *city) {
    Node *curr;

    if(empty(*list)) return FALSE;

    curr = list->init;
    list->init = curr->next;
    *city = curr->city;

    free(curr);

    return TRUE;
}

int remove_tail(LSE *list, City_Info *city) {
    Node *curr, *prev = NULL;

    if(empty(*list)) return FALSE;

    curr = list->init;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    if(prev == NULL) {
        return remove_head(list, city);
    }

    *city = curr->city;
    prev->next = curr->next;

    free(curr);

    return TRUE;
}

int remove_element(LSE *list, char *name, City_Info *city) {
    Node *prev, *curr;

    if(empty(*list)) return FALSE;

    prev = NULL;
    curr = list->init;

    while (curr != NULL) {
        if(strcmp(curr->city.city_name, name) == 0) {
            if(prev == NULL) return remove_head(list, city);

            prev->next = curr->next;
            *city = curr->city;

            free(curr);
        }
        prev = curr;
        curr = curr->next;
    }

    return FALSE;
}

int remove_by_coordinate(LSE *list, int x, int y, City_Info *city) {
    Node *prev, *curr;

    if(empty(*list)) return FALSE;

    prev = NULL;
    curr = list->init;

    while (curr != NULL) {
        if(curr->city.coord_x == x && curr->city.coord_y == y) {
            if(prev == NULL) return remove_head(list, city);

            prev->next = curr->next;
            *city = curr->city;

            free(curr);
        }
        prev = curr;
        curr = curr->next;
    }
    return FALSE;
}

int search(LSE list, char *name) {
    Node *curr = list.init;
    while (curr != NULL) {
        if(strcmp(curr->city.city_name, name) == 0) return TRUE;

        curr = curr->next;
    } 
    return FALSE;
}

void search_coordinate(LSE list, int x, int y) {
    Node *curr = list.init;

    while (curr != NULL) {
        if(curr->city.coord_x == x && curr->city.coord_y == y) {
            puts("\n-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=--=-=-");
            puts("A cidade está no banco!");
            printf("Nome: %s", curr->city.city_name);
            printf("Coordenadas: (%d,%d)\n", curr->city.coord_x, curr->city.coord_y);
            puts("-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=--=-=-\n\n");

            return;
        }

        curr = curr->next;
    }
    return;
}

double calculate_distance(int x1, int x2, int y1, int y2) {
    double ans = sqrt(pow((x2 - x1), 2) + (pow((y2 - y1), 2)));
    return ans;
}

int search_by_distance(LSE list, int x, int y, int radius) {
    Node *curr = list.init;
    double dist;

    puts("\n-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=--=-=-");
    while (curr != NULL) {
        dist = calculate_distance(curr->city.coord_x, x, curr->city.coord_y, y);
        if(dist <= (double) radius && dist > 0) {
            // puts("A cidade está no banco!");
            printf("Nome: %s", curr->city.city_name);
            printf("Coordenadas: (%d,%d)\n", curr->city.coord_x, curr->city.coord_y);
            printf("Distância: %.2lf\n\n", dist);
        }
        curr = curr->next;
    }
    puts("-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=--=-=-\n\n");
    
    return FALSE;
}

int menu() {
    int choice;

    puts("****************************************************");
    puts("\n-----------------------MENU-------------------------\n");
    puts("[1] Limpar tela");
    puts("[2] Adicionar nova cidade");
    puts("[3] Pesquisar cidade");
    puts("[4] Remover cidade");
    puts("[5] Imprimir lista de cidades");
    puts("[6] Pesquisar cidades num raio");
    puts("[7] Verificar quantidade de cidades\n\n");
    puts("****************************************************");
    printf("Opção: ");
    scanf("%d", &choice);
    getchar();

    return choice;
}


int main() {
    int option = 0, choice, x, y, dist;
    char pesquisa[50];

    City_Info cidade;
    LSE list;


    create_list(&list);
    

    while (option != -1)
    {
        option = menu();
    
        switch (option) {
            case 7: // QUANTIDADE DE ITEMS
                clear_screen();
                printf("Quantidade atual de cidades: %d\n", number_of_elements(list));
                break;
            
            case 2: //INSERIR NA LISTA
                clear_screen();
                if (!insert_end(&list)) {
                    puts("Memória isuficiente!");
                } else {
                    puts("Adicionada com sucesso!");
                }
                break;
            
            case 5: // IMPRIMIR LISTA
                print_cities(list);
                break;

            case 3: // PESQUISAR CIDADE
                clear_screen();
                //puts("")
                puts("[1] Pesquisa por coordenada");
                puts("[2] Pesquisa por nome");
                printf("Digite a opção: ");
                scanf("%d", &choice);
                getchar();
                switch(choice) {
                    case 1:
                        printf("Digite as coordenadas: ");
                        scanf("%d%d", &x, &y);
                        getchar();
                        search_coordinate(list, x, y);
                        break;
                    case 2:
                        printf("Digite o nome da cidade: ");
                        fgets(pesquisa, 50, stdin);
                        search(list, pesquisa) ? puts("A cidade está na lista") : puts("A cidade não está na lista");
                        break;
                    default:
                        break;
                }

                
                break;

            case 4: // REMOVER DA LISTA
                clear_screen();
                puts("[1] Remover por coordenada");
                puts("[2] Remover por nome");
                printf("Digite a opção: ");
                scanf("%d", &choice);
                getchar();
                switch(choice) {
                    case 1:
                        printf("Digite as coordenadas: ");
                        scanf("%d%d", &x, &y);
                        getchar();
                        if(remove_by_coordinate(&list, x, y, &cidade)) puts("\nRemovido!\n");
                        break;
                    case 2:
                        printf("Digite o nome da cidade: ");
                        fgets(pesquisa, 50, stdin);
                        if(remove_element(&list, pesquisa, &cidade)) puts("Removido!");
                        break;

                    default:
                        break;
                }
                break;
            
            case 6:
                clear_screen();
                printf("Digite as coordenadas de um ponto: ");
                scanf("%d%d", &x, &y);
                printf("Digite a distancia do raio de pesquisa: ");
                scanf("%d", &dist);

                if(!search_by_distance(list, x, y, dist)){
                    puts("Nenhuma cidade encontrada dentro do raio!");
                }
                break;

            case 1:
                clear_screen();
                break;
            default:
                break;
        }
    }
    
    return 0;
}
