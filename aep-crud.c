#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int totUser = 0; // Total de usuarios comecando com 0
char nome[100][15]; // Array de 100 nomes, cada um com 15 caracteres no maximo
char senha[100][15]; // Array de 100 senhas, cada uma com 15 caracteres no maximo

void arquivo(int tp);
void entrarAdmin(char *userAdmin, char *senhaAdmin);
void menuAdmin();
void menuUsuario();
int verificaSenha(char *senha);
void criptografarSenha(char *senha);
char* descriptografarSenha(char *senha);
void addUsuario(char *nomeUsuario);
void listarUsuarios();
void listarUsuariosAdm();
void removeUsuario(char *usuarioARemover);
void editarUsuario(char *usuarioAEditar);

void entrarAdmin(char *userAdmin, char *senhaAdmin) {
    if (strcmp(userAdmin, "AdministradorAEP") == 0 && strcmp(senhaAdmin, "12345678") == 0) { // Se os dados informados baterem com os pre-definidos aqui entao ta liberado o acesso.
        menuAdmin(); // Exibe o menu para a visao do administrador
    } else {
        printf("Dados invalidos\n");
    }
}

void menuAdmin() { // Menu do administrador
    arquivo(0); // chama pra leitura

    int escolha;
    char nomeUsuario[15], usuarioAEditar[15], usuarioARemover[15];
    
    do { // loop do while vai fazer com que exiba o menu repetidamente até que o usuario escolha a opcao '5' para sair
        // system("clear"); // Limpa a tela no linux
        system("cls"); // Limpa a tela no windows
        printf("\n==============================\n");
        printf("** Painel Administrativo **\n");
        printf("==============================\n");
        printf("O que deseja fazer?\n");
        printf("==============================\n");
        printf("1. Adicionar usuario\n");
        printf("2. Editar usuario\n");
        printf("3. Remover usuario\n");
        printf("4. Listar usuarios\n");
        printf("5. Voltar para o menu principal\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar();
        
        switch (escolha) {
        case 1:
            printf("Nome do novo usuario: ");
            scanf("%s", nomeUsuario);
            addUsuario(nomeUsuario);
            break;
        case 2:
            printf("Digite o nome do usuario que deseja editar: ");
            scanf("%s", usuarioAEditar);
            editarUsuario(usuarioAEditar);
            break;
        case 3:
            printf("Digite o usuario a remover: ");
            scanf("%s", usuarioARemover);
            removeUsuario(usuarioARemover);
            break;
        case 4:
            listarUsuariosAdm();
            break;
        case 5:
            printf("\nVoltando para o menu principal...\n");
            break;
        default:
            printf("\n Opcao invalida! Tente novamente.\n");
            break;
        }

        if (escolha != 5) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while (escolha != 5); // Se nao for a opcao 5, volta para o menu
}

void menuUsuario() { // Menu do usuario comum
    arquivo(0);

    int escolha;
    char nomeUsuario[15], usuarioAEditar[15];
    
    do { // loop do while vai fazer com que exiba o menu repetidamente até que o usuario escolha a opcao '5' para sair
        // system("clear"); // Limpa a tela no linux
        system("cls"); // Limpa a tela no windows
        printf("\n==============================\n");
        printf(" *Sistema de Gerenciamento de Usuarios* \n");
        printf("==============================\n");
        printf("O que deseja fazer?\n");
        printf("==============================\n");
        printf("1. Adicionar usuario\n");
        printf("2. Editar usuario\n");
        printf("3. Listar usuarios\n");
        printf("4. ~~~ (Somente Administradores podem excluir usuarios) ~~~\n");
        printf("5. Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
        case 1:
            printf("Nome do novo usuario: ");
            scanf("%s", nomeUsuario);
            addUsuario(nomeUsuario);
            break;
        case 2: 
            printf("Digite o nome do usuario que deseja editar: ");
            scanf("%s", usuarioAEditar);
            editarUsuario(usuarioAEditar);
            break;
        case 3:
            listarUsuarios();
            break;
        case 4:
            printf("\n :( Acao nao permitida para usuarios comuns. Somente administradores podem excluir usuarios.\n");
            break;
        case 5:
            printf("\n Bye.\n");
            break;
        default:
            printf("\n Opcao invalida! Tente novamente. \n");
            break;
        } 

        if (escolha != 5) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
    } while (escolha != 5); // Se a opcao nao for '5', ele pede para o usuario apertar 'Enter' para continuar
}

int verificaSenha(char *senha) {
    int tamanho = strlen(senha);
    int temMaiusc = 0, temMinusc = 0, temNumero = 0, temEspecial = 0; // COMECAM TODOS FALSOS

    if (tamanho < 8) {
        return 0; // AQUI SE NaO FOR SATISFEITA A CONDICaO JA TA ERRADO.
    }

    for (int i = 0; i < tamanho; i++) {
        char c = senha[i]; // CARACTERE ATUAL
        if (c >= 'A' && c <= 'Z') { // Entre 'A' e 'Z' maiúsculo
            temMaiusc = 1;
        } else if (c >= 'a' && c <= 'z') { // Entre 'a' e 'z' minúsculo
            temMinusc = 1;
        } else if (c >= '0' && c <= '9') { // Entre '0' e '9' para numero
            temNumero = 1;
        } else if ((c >= 32 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126)) { // Intervalos de caracteres especiais usando a tabela ASCII
            temEspecial = 1;
        }
    }

    return temMaiusc && temMinusc && temNumero && temEspecial; // Retorna todas as verificacões
}

void criptografarSenha(char *senha) {
    for (int i = 0; senha[i] != '\0'; i++) {
        senha[i] += 7; // Vai sempre somar 7 posicões a frente do caractere atual na tabela ASCII e troca-lo
    }
}

char* descriptografarSenha(char *senha) { // Essa funcao vai retornar o próprio ponteiro 'senha', a string da senha descriptografada
    for (int i = 0; senha[i] != '\0'; i++) {
        senha[i] -= 7; // Vai agora subtrair as 7 posicões da criptografia
    }
    return senha;
}

void addUsuario(char *nomeUsuario) {
    char senhaUsuario[15], senhaConfirmada[15];
    while (1) {
        printf("Digite a senha do novo usuario: ");
        scanf("%s", senhaUsuario);

        printf("Confirme sua senha: ");
        scanf("%s", senhaConfirmada);

        if (strcmp(senhaUsuario, senhaConfirmada) != 0) { // '0' acontece quando sao iguais
            printf("\n !! As senhas nao coincidem. Tente novamente. !!\n");
            continue;
        }

        if (verificaSenha(senhaUsuario)) { // Se todas as condicões para senha valida retornadas pela funcao forem true, ele pula esse bloco
            break;
        } else {
            printf("\n !! Senha invalida. A senha deve conter pelo menos 8 caracteres, incluindo:\n");
            printf("   - 1 maiuscula\n   - 1 minuscula\n   - 1 numero\n   - 1 caractere especial\n");
        }
    }
    
    criptografarSenha(senhaUsuario); // Criptografa
    strcpy(nome[totUser], nomeUsuario); // Copia o nome do usuario para o array de nomes no índice 'totUser', no caso de um arquivo vazio vai comecar pelo 0
    strcpy(senha[totUser], senhaUsuario); // Copia a senha do usuario para o array de senhas no índice 'totUser'   ==     ==     ==    == 
    totUser++; // Incrementa o número de usuarios
    arquivo(1); // Salva as informacões no arquivo .txt (banco)
    printf("\n Usuario adicionado com sucesso! :)\n"); // Mensagem de sucesso
}

void listarUsuarios() {
    arquivo(0); // Chama a funcao 'arquivo' para a leitura do .txt
    printf("\n***************************\n");
    printf(";) Usuarios cadastrados: \n\n");
    for (int i = 0; i < totUser; i++) {
        printf("Usuario: %s | Senha Criptografada: %s\n", nome[i], senha[i]); // Exibe os usuarios de acordo com suas posicões nos arrays
    }
    printf("***************************\n");
}

void listarUsuariosAdm() {
    arquivo(0); // Chama a funcao 'arquivo' para a leitura do .txt
    printf("\n***************************\n");
    printf(";) Usuarios cadastrados: \n\n");
    for (int i = 0; i < totUser; i++) {
        printf("Usuario: %s | Senha Criptografada: %s | Senha descriptografada: %s\n", nome[i], senha[i], descriptografarSenha(strdup(senha[i]))); // Exibe os usuarios de acordo com suas posicões nos arrays
    }                                                                                                     // agora exibe a senha descriptografada também
    // Foi usado o 'strdup' para fazer uma cópia da senha e descriptografar a cópia, sem mudar o valor original da string da senha criptografada, 
    // desse modo é possível mostrar ambas as senhas, criptografadas e descriptografadas sem conflito nenhum.
    printf("***************************\n");
}

void removeUsuario(char *usuarioARemover) {
    arquivo(0); // Chama a funcao 'arquivo' para a leitura do .txt
    int encontrei = 0; // Inicializa como 0 --> false

    for (int i = 0; i < totUser; i++) {
        if (strcmp(nome[i], usuarioARemover) == 0) { // Percorre o array de nomes e se o nome corresponder ao informado pelo usuario 'usuarioARemover', encontrei se torna '1'
            encontrei = 1;
        } else {
            strcpy(nome[i - (encontrei ? 1 : 0)], nome[i]); // Copia o nome do usuario atual para a nova posicao. Se 'encontrei' for '1', move o índice para cima e remove a posicao do usuario encontrado
            strcpy(senha[i - (encontrei ? 1 : 0)], senha[i]); // Faz a mesma coisa pra senha, copia para a nova posicao e ajusta o índice
        }
    }
    
    if (encontrei) { // Se encontrou... 
        totUser--; // Decrementa o total de usuarios
        arquivo(1); // Chama a funcao 'arquivo' para a escrita no .txt
        printf("\n  Usuario removido com sucesso! :)\n"); // Mensagem de sucesso
    } else {
        printf("\n~~~ :( Usuario nao encontrado. ~~~\n"); // Mensagem se nao achar 
    }
}

void editarUsuario(char *usuarioAEditar) {
    char novaSenha[15], novaSenhaConfirmada[15];
    int usuarioEncontrado = 0; // Inicializa como '0' --> false

    for (int i = 0; i < totUser; i++) {
        if (strcmp(nome[i], usuarioAEditar) == 0) { // Percorre o array de nomes, se o nome informado 'usuarioAEditar' for igual ao nome na posicao atual, 
                                                    // 'usuarioEncontrado' se torna 1 e para a execucao do loop
            usuarioEncontrado = 1;
            break;
        }
    }

    if (!usuarioEncontrado) { // Se 'usuarioEncontrado' for '0', nao achou
        printf("\n~~~ :( Usuario nao encontrado. ~~~\n");
        return;
    }

    while (1) { // Loop infinito até que as condicões de senha sejam 'verdadeiras' e chegue no 'break'
        printf("Digite a nova senha: ");
        scanf("%s", novaSenha);

        printf("Confirme a nova senha: ");
        scanf("%s", novaSenhaConfirmada);

        if (strcmp(novaSenha, novaSenhaConfirmada) != 0) { // Se nao forem iguais
            printf("\n !! As senhas nao coincidem. Tente novamente. !!\n");
            continue; // O loop recomeca
        }

        if (verificaSenha(novaSenha)) { // Se as senhas coincidirem, 'verificaSenha' é chamada para a validacao
            break; // Se for valida, para o loop
        } else { // Se nao for valida, exibe a mensagem de erro e recomeca
            printf("\n !! Senha invalida. A senha deve conter pelo menos 8 caracteres, incluindo:\n");
            printf("   - 1 maiuscula\n   - 1 minuscula\n   - 1 numero\n   - 1 caractere especial\n");
        }
    }
    criptografarSenha(novaSenha); // Criptografa
    arquivo(0); // Chama a funcao 'arquivo' para a leitura do .txt
    for (int i = 0; i < totUser; i++) {
        if (strcmp(nome[i], usuarioAEditar) == 0) { // Percorre o vetor, e se o nome informado 'usuarioAEditar' for igual ao nome na posicao atual...
            strcpy(senha[i], novaSenha);            // A nova senha vai ser armazenada na posicao correspondente pelo nome
            break; // sai do loop
        }
    }
    arquivo(1); // chama a funcao 'arquivo' para a escrita no .txt
    printf("\n Usuario editado com sucesso! :)\n"); // Mensagem de sucesso
}

void arquivo(int tp) { // Procedimento passado pelo professor 'Alexandre Moreno' para escrita e leitura no arquivo '.txt'
    FILE *file;
    if (tp == 0) { // se o parâmetro for '0', vai ser para 'leitura'
        file = fopen("usuarios-crud.txt", "r"); // abre para 'read' --> leitura
        if (file != NULL) {
            totUser = 0;
            char linha[15];
            while (fgets(linha, sizeof(linha), file) != NULL) {
                linha[strcspn(linha, "\n")] = 0;
                strcpy(nome[totUser], linha);
                if (fgets(linha, sizeof(linha), file) != NULL) {
                    linha[strcspn(linha, "\n")] = 0;
                    strcpy(senha[totUser], linha);
                }
                totUser++;
            }
            fclose(file);
        } else {
            printf("Erro ao abrir arquivo para leitura\n");
        }
    } else {
        file = fopen("usuarios-crud.txt", "w");
        if (file != NULL) {
            for (int i = 0; i < totUser; i++) {
                fprintf(file, "%s\n%s\n", nome[i], senha[i]);
            }
            fclose(file);
        } else {
            printf("Erro ao abrir o arquivo para escrita\n");
        }
    } 
}

int main() {
    arquivo(0); // chama a funcao 'arquivo' para a leitura dos dados

    int escolha;
    char nomeUsuario[15], usuarioAEditar[15], usuarioARemover[15];
    char userAdmin[17], senhaAdmin[15];
    do { // loop do while vai fazer com que exiba o menu repetidamente até que o usuario escolha a opcao '3' pra sair
        //system("clear");  // limpa a tela no Linux
        system("cls"); // limpa a tela no Windows
        printf("\n==============================\n");
        printf(" *Sistema de Gerenciamento de Usuarios* \n");
        printf("==============================\n\n");
        printf("O que deseja fazer:\n");
        printf("==============================\n");
        printf("1. Entrar como Administrador\n");
        printf("2. Entrar como Usuario\n");
        printf("3. Creditos\n");
        printf("4. Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
        case 1:
            printf("Digite o nome do administrador: ");
            scanf("%s", userAdmin);
            printf("Digite a senha do administrador: ");
            scanf("%s", senhaAdmin);
            entrarAdmin(userAdmin, senhaAdmin); // chama a funcao 'entrarAdmin' para validar se o usuario é administrador
            break;
        case 2:
            menuUsuario(); // chama o menu para os usuarios comuns
            break;
        case 3:
            printf("\n\n+++++++++++++ CREDITOS +++++++++++++\n\n");
            printf("Desenvolvido pelos alunos:\n\nHeitor Henrique Scramim de Freitas\nRA: 24190382-2\n &\nAndre Perin Geraldo\nRA:24017529-2\n");
            printf("+++++++++++++ -------- +++++++++++++\n\n");
            getchar();
            getchar();
            break;
        case 4:
            printf("Saindo do sistema... Bye!\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }

    } while (escolha != 4); // fim do loop

    return 0;
}