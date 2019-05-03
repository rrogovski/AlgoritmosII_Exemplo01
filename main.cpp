/*
*Uma empresa de cr�dito est� desenvolvendo um sistema para avalia��o de cr�dito
*para pessoas. Para isso ela quer fazer um cadastro de pessoas. Cada pessoa ter� um
*c�digo, nome, idade e sal�rio. Estes dados devem ser mantidos em arquivo para que n�o sejam
*perdidos e possam ser adicionados novos clientes no futuro.
*
*Fa�a um sistema, usando fun��es, que mostre um menu com as op��es de incluir, consultar, editar,
*excluir, relat�rio das pessoas cadastradas e relat�rio de limite suportado.
*
*O limite suportado � calculado pelas seguintes regras:
*   Pessoas com menos de 18 anos - Cr�dito 0;
*   Pessoas com sal�rio inferior a 800 - Cr�dito 0;
*   Pessoas com 18 a 55 anos e com sal�rio maior que 800 - Cr�dito de 50% do sal�rio;
*   Pessoas com mais de 55 anos e com sal�rio maior que 800 - Cr�dito de 30% do sal�rio;

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

///Fun��o para limpar a tela
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

    cout << "Endere�o: ";
    cin.getline(c.endereco, 100);
    fflush(stdin);

    cout << "Sal�rio: ";
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
            cout << "  Endere�o: " << clientes[i].endereco << endl;
            cout << "  Sal�rio: " << clientes[i].salario << endl;
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
        cout << "Digite uma op��o v�lida!" << endl;
        goto voltarConsulta;
    }

    if(printCadastro(id) == 0) {
        cout << "Registro n�o encontrado!" << endl;
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
        cout << "Digite uma op��o v�lida!" << endl;
        goto voltarEditar;
    }

    cout << "--------------------------------------" << endl;
    cout << "Informa��es atuais do cliente" << endl;

    if(printCadastro(id) == 0) {
        cout << "Registro n�o encontrado!" << endl;
        cout << "Realizar nova busca? S-Sim / N-N�o" << endl;
        voltarOpcao:;
        char op;
        if (scanf("%c", &op) != 1) {
            fflush(stdin);
            cout << "Digite uma op��o v�lida!" << endl;
            goto voltarOpcao;
        } else {
            if(op == 'S' || op == 's')
                goto voltarEditar;
            else
                return 0;
        }
    }
    cout << "--------------------------------------" << endl;
    cout << "Atualiza��o de cadastro!\n\n" << endl;

    cout << "Nome: ";
    cin.getline(clientes[id].nome,100);
    fflush(stdin);

    cout << "Idade: ";
    cin >> clientes[id].idade;
    fflush(stdin);

    cout << "Endere�o: ";
    cin.getline(clientes[id].endereco, 100);
    fflush(stdin);

    cout << "Sal�rio: ";
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

///Relat�rio de cadastros
void relatorio(){
    cout << "Relat�rio de cadastros!" << endl;
    cout << "-----------------------" << endl;

    for (int i=0; i<indice; i++) {
        cout << "Cadastro id - " << i+1 << ":" << endl;
        cout << "  Nome: " << clientes[i].nome << endl;
        cout << "  Idade: " << clientes[i].idade << endl;
        cout << "  Endere�o: " << clientes[i].endereco << endl;
        cout << "  Sal�rio: " << clientes[i].salario << endl;
        cout << "-----------------------" << endl;
        //cout << "Pr�ximo registro, tecle Enter! >>" << endl;
        //getch();
    }

    cout << "Fim dos registros. Pressione qualquer tecla para voltar ao menu inicial!" << endl;
    getch();
    limparTela();
    return;
}

///Relat�rio de empr�stimos
int relatorioEmprestimos(){
    cout << "Relat�rio de emprestimos!" << endl;
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
        cout << "Selecione a op��o desejada:" << endl;
        cout << "1 - Inserir" << endl;
        cout << "2 - Consultar" << endl;
        cout << "3 - Editar" << endl;
        cout << "4 - Excluir" << endl;
        cout << "5 - Relat�rio" << endl;
        cout << "6 - Relat�rio de emprestimos" << endl;
        cout << "0 - Sair" << endl;

        voltar:;

        if (scanf("%d", &opcao) != 1) {
            fflush(stdin);
            cout << "Digite uma op��o v�lida!" << endl;
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
                cout << "Digite uma op��o v�lida!" << endl;
                fflush(stdin);
                goto voltar;
            }
        }
    } while (opcao);
}

///Fun��o principal do programa
int main()
{
    clientes = (Cliente *) malloc(sizeof(Cliente)*capacidade);
    setlocale(LC_ALL, "");
    menu();
    return 0;
}
