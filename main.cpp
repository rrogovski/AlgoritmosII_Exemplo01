/*
*Uma empresa de crédito está desenvolvendo um sistema para avaliação de crédito
*para pessoas. Para isso ela quer fazer um cadastro de pessoas. Cada pessoa terá um
*código, nome, idade e salário. Estes dados devem ser mantidos em arquivo para que não sejam
*perdidos e possam ser adicionados novos clientes no futuro.
*
*Faça um sistema, usando funções, que mostre um menu com as opções de incluir, consultar, editar,
*excluir, relatório das pessoas cadastradas e relatório de limite suportado.
*
*O limite suportado é calculado pelas seguintes regras:
*   Pessoas com menos de 18 anos - Crédito 0;
*   Pessoas com salário inferior a 800 - Crédito 0;
*   Pessoas com 18 a 55 anos e com salário maior que 800 - Crédito de 50% do salário;
*   Pessoas com mais de 55 anos e com salário maior que 800 - Crédito de 30% do salário;

*O sistema deve carregar os dados do arquivo do disco ao abrir e salvar os dados ao sair do sistema.
*/

#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

typedef struct Cliente{
    char nome[100], endereco[100];
    int id, idade;
    float limiteCredito, salario;
};

FILE *arq;
int indice = 0;
int capacidade = 5;
Cliente *clientes = NULL;

///Função para limpar a tela
void limparTela()
{
	system("cls || clear");
}

///Sair do programa
void sair()
{
	limparTela();
	cout << "Hasta la vista, Baby!!!\n\nFechando o programa em...\n\n";

	for (int i = 5; i > 0; i--)
	{
		printf("%d\n", i);
		Sleep(500);
	}
}


///Inserir registro
int inserir(){
    Cliente c;

    cout << "Inserir novo registro - Cadastro de cliente!" << endl;
    cout << "--------------------------------------------" << endl;

    cout << "Id: ";
    cin >> c.id;
    fflush(stdin);

    cout << "Nome: ";
    cin.getline(c.nome,100);
    fflush(stdin);

    cout << "Idade: ";
    cin >> c.idade;
    fflush(stdin);

    cout << "Endereço: ";
    cin.getline(c.endereco, 100);
    fflush(stdin);

    cout << "Salário: ";
    cin >> c.salario;
    fflush(stdin);

    clientes[indice] = c;
    indice++;
    if (indice>=capacidade) {
        capacidade*=2;
        clientes = (Cliente *) realloc(clientes, sizeof(Cliente)*capacidade);
    }

    getch();
    limparTela();
    return 0;
}

int printCadastro(int id) {
    for(int i=0; i<indice; i++) {
        if(clientes[i].id == id){
            cout << "Cadastro id - " << clientes[i].id << ":" << endl;
            cout << "  Nome: " << clientes[i].nome << endl;
            cout << "  Idade: " << clientes[i].idade << endl;
            cout << "  Endereço: " << clientes[i].endereco << endl;
            cout << "  Salário: " << clientes[i].salario << endl;
            cout << "-----------------------" << endl;

            return 1;
        } else {
            return 0;
        }
    }
}

///Consultar registro
int consultar(){
    int id;
    cout << "Consultar registro!" << endl;
    cout << "-------------------" << endl;
    cout << "Informe o id do cliente: ";
    voltarConsulta:;

    if (scanf("%d", &id) != 1) {
        fflush(stdin);
        cout << "Digite uma opção válida!" << endl;
        goto voltarConsulta;
    }

    if(printCadastro(id) == 0) {
        cout << "Registro não encontrado!" << endl;
        //goto voltarConsulta;
    }

    getch();
    limparTela();
    return 0;
}

///Editar registro
int editar(){
    int id;
    cout << "Editar registro!" << endl;
    cout << "-----------------" << endl;
    cout << "Informe o id do cliente: ";
    voltarEditar:;

    if (scanf("%d", &id) != 1) {
        fflush(stdin);
        cout << "Digite uma opção válida!" << endl;
        goto voltarEditar;
    }

    cout << "--------------------------------------" << endl;
    cout << "Informações atuais do cliente" << endl;

    if(printCadastro(id) == 0) {
        cout << "Registro não encontrado!" << endl;
        cout << "Realizar nova busca? S-Sim / N-Não" << endl;
        voltarOpcao:;
        char op;
        if (scanf("%c", &op) != 1) {
            fflush(stdin);
            cout << "Digite uma opção válida!" << endl;
            goto voltarOpcao;
        } else {
            if(op == 'S' || op == 's')
                goto voltarEditar;
            else
                return 0;
        }
    }
    cout << "--------------------------------------" << endl;
    cout << "Atualização de cadastro!\n\n" << endl;

    cout << "Nome: ";
    cin.getline(clientes[id].nome,100);
    fflush(stdin);

    cout << "Idade: ";
    cin >> clientes[id].idade;
    fflush(stdin);

    cout << "Endereço: ";
    cin.getline(clientes[id].endereco, 100);
    fflush(stdin);

    cout << "Salário: ";
    cin >> clientes[id].salario;
    fflush(stdin);

    getch();
    limparTela();
    return 0;
}

///Excluir registro
int excluir(){
    cout << "Excluir registro!" << endl;
    cout << "-----------------" << endl;
    getch();
    limparTela();
    return 0;
}

///Relatório de cadastros
void relatorio(){
    cout << "Relatório de cadastros!" << endl;
    cout << "-----------------------" << endl;

    for (int i=0; i<indice; i++) {
        cout << "Cadastro id - " << i+1 << ":" << endl;
        cout << "  Nome: " << clientes[i].nome << endl;
        cout << "  Idade: " << clientes[i].idade << endl;
        cout << "  Endereço: " << clientes[i].endereco << endl;
        cout << "  Salário: " << clientes[i].salario << endl;
        cout << "-----------------------" << endl;
        //cout << "Próximo registro, tecle Enter! >>" << endl;
        //getch();
    }

    cout << "Fim dos registros. Pressione qualquer tecla para voltar ao menu inicial!" << endl;
    getch();
    limparTela();
    return;
}

///Relatório de empréstimos
int relatorioEmprestimos(){
    cout << "Relatório de emprestimos!" << endl;
    cout << "-------------------------" << endl;
    getch();
    limparTela();
    return 0;
}

///Menu do sistema
void menu(){
    int opcao;

    do{
        cout << "Exemplo de CRUD!" << endl;
        cout << "-----------------" << endl;
        cout << "Selecione a opção desejada:" << endl;
        cout << "1 - Inserir" << endl;
        cout << "2 - Consultar" << endl;
        cout << "3 - Editar" << endl;
        cout << "4 - Excluir" << endl;
        cout << "5 - Relatório" << endl;
        cout << "6 - Relatório de emprestimos" << endl;
        cout << "0 - Sair" << endl;

        voltar:;

        if (scanf("%d", &opcao) != 1) {
            fflush(stdin);
            cout << "Digite uma opção válida!" << endl;
            goto voltar;
        } else {
            switch (opcao)
            {
            case 1:
                limparTela();
                fflush(stdin);
                inserir();
                break;

            case 2:
                limparTela();
                fflush(stdin);
                consultar();
                break;

            case 3:
                limparTela();
                fflush(stdin);
                editar();
                break;

            case 4:
                limparTela();
                fflush(stdin);
                excluir();
                break;

            case 5:
                limparTela();
                fflush(stdin);
                relatorio();
                break;

            case 6:
                limparTela();
                fflush(stdin);
                relatorioEmprestimos();
                break;

            case 0:
                limparTela();
                fflush(stdin);
                sair();
                break;

            default:
                cout << "Digite uma opção válida!" << endl;
                fflush(stdin);
                goto voltar;
            }
        }
    } while (opcao);
}

///Função principal do programa
int main()
{
    clientes = (Cliente *) malloc(sizeof(Cliente)*capacidade);
    setlocale(LC_ALL, "");
    menu();
    return 0;
}
