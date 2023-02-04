// nome: estefanio miko engonga bindang
// matricula: 21.2.9997
//turma: 31

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
// declaracao de funcoes usadas no codigo
void table_printer();
void menu_printer();
void game_saver(char* filename, int);
void game_loader(char* filename, int * step);
void menu_manager(char* opx);
void menu_iterator();
void game_starter();
int **table_iniatializer();
int embaralhador(int level);
void player_iterator(int step);
void player();
int is_sorted();
int get_index(int played_num, int *row, int *col);
int mov_controller(int played_num);
void swaper(int row, int col, int row_goto, int col_goto);
void instruction();
char* split(char * word, char * );
void deslacorMemoria();

int **table;
int start_flag=0;
int step_counter=0;


int main(int argc, char const *argv[]){   
   

    
    menu_iterator();
    
    return 0;
}

// funcao para printar o tabuleiro e verificar 

void table_printer(){

   
    for(int i=0; i<3; i++){
        printf("-------------------\n");
        for(int j=0; j<3; j++){
            int temp = table[i][j];
            if(j==2){
                if(temp == 9)
                    printf("|   ");
                else
                    printf("|  %d", temp);
            }
            else{
                if(temp == 9)
                    printf("|     ");
                else
                    printf("|  %d  ", table[i][j]);
            }
        }
        printf("  |\n");
    }

    printf("-------------------\n");


}


// funcao para printar  as opcoes do menu do jogo

void menu_printer(){
    printf("Bem vindo ao Quebra-Cabeças\n\n");
    printf("0. Sair do Jogo\n");
    printf("1. Começar um novo jogo\n");
    printf("2. Continuar o jogo atual\n");
    printf("3. Continuar um jogo salvo\n");
    printf("4. Instruções do jogo\n");
}

// essa funcao é usada para controlar o movimento das fichas

int mov_controller(int played_num){

    int row, col;
    int success = get_index(played_num, &row, &col);

  
    if(!success){
        return 0;
    }

    int row_goto, col_goto;

    if(col +1 <= 2){
        if(table[row][col+1] == 9){
            row_goto = row;
            col_goto = col+1;
            swaper(row, col, row_goto, col_goto);
            return 1;
        }
    }
    
    if(col -1 >= 0){
        if(table[row][col-1] == 9){
            row_goto = row;
            col_goto = col-1;
            swaper(row, col, row_goto, col_goto);
            return 1;
        }

    }

    if(row +1 <= 2){
        if(table[row+1][col] == 9){
            row_goto = row+1;
            col_goto = col;
            swaper(row, col, row_goto, col_goto);
            return 1;
        }
    }
    
    if(row -1 >= 0){
        if(table[row-1][col] == 9){
            row_goto = row-1;
            col_goto = col;
            swaper(row, col, row_goto, col_goto);
            return 1;
        }

    }

    return 0;

}

// essa funcao foi usada par salvar o jogo num arquivo

void game_saver(char* filename, int step){

    FILE* game;
    game = fopen(filename, "w");
   
    fprintf(game,  "%d\n", step);
    if(game == NULL){
        printf("Houve um problema salvando jogo\n");
        exit(1);
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            int temp = table[i][j];
            fprintf(game, "%d ", temp);
            table[i][j] = temp;
        }
        fprintf(game, "\n");
    }
    fclose(game);


}

// funcao para obter o indice do num jogado

int get_index(int played_num, int *row, int *col){

    if(played_num > 8 || played_num <1)
        return 0;

    for(int i=0; i<3;i++){
        for(int j=0; j<3;j++){
            if (played_num == table[i][j]){
                *row = i;
                *col = j;
                return 1;
            }
        }

    }

    return 0;
}
// funcao para carregar o jogo

void game_loader(char* filename, int * step){
    table = table_iniatializer();
    


    char newFilename[50];

    if(filename[strlen(filename)-1] == '\n'){
        strncat(newFilename, filename, strlen(filename)-1);
    }else{
        strcpy(newFilename, filename);
    }

    if(*step >=1){
        printf("Arquivo “%s” Carregado. Vamos começar o jogo!\n", newFilename);
        sleep(1);
    }
    FILE* game;
    printf("Nome do fic %s\n", newFilename);
    game = fopen(newFilename, "r");
    
    if(game == NULL){
        printf("Houve um problema carregando jogo\n");
        exit(1);
    }
    int temp;
    fscanf(game, "%d", &temp);
    fscanf(game, "\n");
    *step = temp;
    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            fscanf(game, "%d", &table[i][j]);
        }
        fscanf(game, "\n");
    }

    fclose(game);

    table_printer(table, 3);

}
//funcao para gerenciar o menu do jogo

void menu_manager(char* opx){

    printf("\n%s", opx);
}

void menu_iterator(){

    char opx[50];
    int op;
    int dif, step;

    while(1){

        menu_printer();
        menu_manager("Escolha a opção (digite “sair” em qualquer lugar para sair do jogo):");
        fgets(opx, 50, stdin);
       
        char filename[50], newfilename[50];
        if(strlen(opx) == 2){
            char c = opx[0];
            if(isdigit(c))
                op = atoi(opx);
            else
                op =-1;
        }else{

        }

        switch (op){
            case 0:
                printf("Saindo do jogo.....\n");
                sleep(1);
                system("clear");
                deslacorMemoria();
                exit(1);
                break;

            case 1:
                table_iniatializer();
                game_starter();
                start_flag=1;
                break;
            

            case 2:
                if(start_flag>=1){
                    table_printer();
                    player_iterator(0);
                }else{

                    menu_manager("Inicie o jogo primeiro\n");
                    getchar();
                }
                break;


            case 3:
                printf("Digite o nome do arquivo: ");
                fgets(filename, 50, stdin);
                game_loader(filename, &step);
                player_iterator(step);
                break;



            case 4:
                    instruction();
                    getchar();
            break;

            default:
                printf("entre com opxao correta\n");
                sleep(2);
            break;
        }

        system("clear");
    }

}

// funcao para iniciar o jogo

void game_starter(){
    
    int dif;
    table = table_iniatializer();
    table_printer(table, 3);
    menu_manager("Tabuleiro ordenado!");
   
    menu_manager("Digite o nı́vel de dificuldade para embaralhar, fácil (1), médio (2) ou difı́cil (3):");
    scanf("%d", &dif);


    switch (dif){

    case 1:
        embaralhador(1);
       
        menu_manager("Tabuleiro embaralhado. Vamos começar o jogo!\n");
        table_printer(table,3);
        getchar();
        player_iterator(0);
        break;
    
    case 2:
        embaralhador(2);
        table_printer(table,3);
        getchar();
        menu_manager("Tabuleiro embaralhado. Vamos começar o jogo!\n");
        player_iterator(0);

        break;
    
    case 3:
        embaralhador(3);
        table_printer(table,3);
        getchar();
        menu_manager("Tabuleiro embaralhado. Vamos começar o jogo!\n");
        player_iterator(0);

        break;

    default:
        break;
    }
}
// funcao para iniciar o tabuleiro
int **table_iniatializer(){
    int DEFAULT = 1 ;
    int **table;

    table = (int**)malloc(sizeof(int*) * 3);

    for(int i=0; i<3;i++){
        table[i] =  malloc(sizeof(int)*3);
        for(int j=0; j < 3; j++){
            table[i][j] = DEFAULT;
            DEFAULT++;
        }
    }

    return table;
}

// funcao criada para interar com jogo
void player_iterator(int other){

    char opt[50];
    char *prev;
    char filename[50]; 
    char final_file_name[50] ="";
    printf("\n");
    char cleaner;
    int isContinuation=0;
    if(step_counter >= 1){
        isContinuation=1;
        printf("Quantidade de jogadas até agora: %d\n", step_counter);
    }

    int opx;
     int control;

    while(1){
        menu_manager("Digite um comando ou número da peça que quer mover: ");
        fgets(opt, 50, stdin);
        printf("texto %s", opt);
        if(strlen(opt) >=4 && strlen(opt) <= 5){
            opx = -1;
        }else if (strlen(opt) >= 6 ) {
            opx = 0;
        }else{
            opx = atoi(opt);
        }

        switch (opx)
        {
        case 1 ... 8:
            control = mov_controller(opx); 
            table_printer(table, 3);
            printf("Quantidade de jogadas até agora: %d\n", step_counter+1);
            
            if(!control){
                printf("Não é possı́vel mover a peça %d\n", opx);
            }
            step_counter++;

            if(is_sorted()){
                printf("Parabéns! Você completou com quebra-cabeças com %d movimentos.", step_counter);
                sleep(1);
            }
            break;
        
        case -1:
            printf("saindo do jogo ....\n");
            sleep(2);
            return;
            break;

        case 0:
            printf("salvando ... \n");
            
            char* token = strtok(opt, " ");
            
            while (token != NULL) {
                printf("%s", token);
                prev = token;
                token = strtok(NULL, " ");
            }
            strncat(final_file_name, prev, strlen(prev)-1);
            game_saver(final_file_name, step_counter);
            printf("Arquivo “%s” salvo com sucesso!\n", final_file_name);
            sleep(1);
            break;

        
        default:
            printf("Por favor, digite a opxao correta");
            sleep(2);
            break;
        }

    }
}

// funcao para saber se o jogador ganhou
int is_sorted(){
    int table_vetored [9];
    int temp;
    int index=0;
    for(int i=0; i<3;i++){
        for(int j=0; j<3;j++){
            table_vetored[index] = table[i][j];
            index++;
        }
    }
    int swap=0;
    for(int i = 0; i < 9 - 1; i++){       

        for(int j = 0; j < 9 - i - 1; j++){          

            if(table_vetored[j] > table_vetored[j + 1]){               
                swap++;
                temp = table_vetored[j];

                table_vetored[j] = table_vetored[j + 1];

                table_vetored[j + 1] = temp;
            }
        }
    }

    return swap >= 1 ? 0 : 1;
}

// funcao usada para mov o peão
void swaper(int row, int col, int row_goto, int col_goto){
    
    int temp = table[row][col];
    table[row][col] =9;
    table[row_goto][col_goto] = temp;
}

// embaralhar o jogo por nivel escolhido pelo jogador
int embaralhador(int level){

    int counter;
    srand(time(0));

    int times;
    if(level== 1)
        times = 20;
    else if(level == 2)
        times = 40;
    else
        times = 80;

    while(1){

        if(mov_controller(rand()%9)) // controlar o mov das fichas a serem movidas
            times--;

        if(times == 0)
            break;
    }

    return 1;
}

// funcao auxiliar pára separar o texto
char* split(char * word, char * filename){

    int i=0, flag=0;
    int size = strlen(word)-4;
    char novo[size];
    int index=0;

    char c = word[0];
    while( c != '\n'){


        if(flag){
            novo[index] = c;
            index++;
        }   
      
        
        if(c == ' ')
            flag=1;
        
        i++;
        c = word[i];
    }

   
    strcpy(filename, novo);
}

// funcao criada para mostrar as instrucoes do jogo
void instruction(){

    system("clear");
    
    menu_manager("1 - embaralhe o tabuleir0\n");
    menu_manager("2 - move as fichas no quadro vazio para ordenar o tabuleiro\n");
    menu_manager("3 - complete de maneira crescente as fichas\n");
    menu_manager("4 - deixe vazio o ultimo quadro da tabela com as fichas ordenadas para ganhar a partida\n");
    


}


// desalocar memoria

void deslacorMemoria(){
    
    for(int i=0; i<3;i++){
        free(table[i]);
    }
}

