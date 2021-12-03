#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    scanf("%[^\n]", city.city_name);
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
        puts("A listá está vazia!");
        return;
    }

    clear_screen();

    puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-");
    for (curr = list.init; curr != NULL; curr = curr->next) {
        printf("Nome: %s\n", curr->city.city_name);
        printf("Coordenadas: (%d,%d)\n\n", curr->city.coord_x, curr->city.coord_y);
    }
    puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-");
}


int search(LSE list, char *name) {
    Node *curr = list.init;
    while (curr != NULL) {
        if(strcmp(curr->city.city_name, name) == 0) return TRUE;

        curr = curr->next;
    } 
    return FALSE;
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


int menu() {
    int choice;

    puts("****************************************************");
    puts("\n-----------------------MENU-------------------------\n");
    puts("[1] Limpar tela");
    puts("[2] Verificar se a lista está vazia");
    puts("[3] Verificar quantidade de elementos");
    puts("[4] Inserir nova cidade no início da lista");
    puts("[5] Inserir nova cidade no fim da lista");
    puts("[6] Imprimir lista");
    puts("[7] Pesquisar elemento");
    puts("[8] Remover cabeça");
    puts("[9] Remover cauda");
    puts("[10] Remover elemento\n");
    puts("****************************************************");
    printf("Opção: ");
    scanf("%d", &choice);

    return choice;
}


int main() {
    int option = 0;
    char pesquisa[50];

    City_Info cidade;
    LSE list;


    create_list(&list);
    

    while (option != -1)
    {
        option = menu();
    
        switch (option) {
        case 2:
            if(empty(list)) {
                printf("A lista está vazia!\n");
            } else {
                printf("A lista contém elementos!\n");
            }
            break;
        case 3:
            printf("%d\n", number_of_elements(list));
            break;
        
        case 4:           
            if (!insert_head(&list)) puts("Memória isuficiente!");            
            break;
        
        case 5:
            if (!insert_end(&list)) puts("Memória isuficiente!");
            break;
        
        case 6:
            print_cities(list);
            break;

        case 7:
            printf("Digite o nome da cidade: ");
            scanf("%50[^\n]", pesquisa);
            search(list, pesquisa) ? puts("O cidade está na lista") : puts("O cidade não está na lista");
            break;
        case 8:
            remove_head(&list, &cidade) ? puts("Removido!") : puts("Ops.. Algo deu errado!");
            break;
        
        case 9:
            remove_tail(&list, &cidade) ? puts("Removido!") : puts("Ops.. Algo deu errado!");
            break;

        case 10:
            printf("Digite o nome da cidade: ");
            scanf("%50[^\n]", pesquisa);
            printf("\n%d\n\n", remove_element(&list, pesquisa, &cidade)); 
            remove_element(&list, pesquisa, &cidade) == 1 ? puts("Removido!") : puts("Ops.. Algo deu errado!");
            break;
        
        case 1:
            clear_screen();

        default:
            break;
        }
    }
    
    return 0;
}
