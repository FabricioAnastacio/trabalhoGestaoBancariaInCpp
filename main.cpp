#include <iostream>
#include <string>

using namespace std;

class Conta {
    public:
        string nomeCliente;
        string cpf;
        int numeroConta;
        int tipoConta;
        double saldo;
        bool contaAtiva;
    
    public:
        friend ostream& operator<<(ostream& os, const Conta& conta) {
            os << "Nome do cliente: " << conta.nomeCliente << endl;
            os << "CPF: " << conta.cpf << endl;
            os << "Número da conta: " << conta.numeroConta << endl;
            os << "Tipo da conta: " << (conta.tipoConta == 1 ? "Corrente" : "Poupança") << endl;
            os << "Saldo: R$" << conta.saldo << endl;
            os << "Conta ativa: " << (conta.contaAtiva ? "Sim" : "Não") << endl;
            return os;
        }
};

int cadastro(Conta clintes[], int& quantidadeContas) {
    int inputContaAtiva;

    cout << string(6, '*') << " Cadastro de conta " << string(6, '*') << endl;
    cout << "Digite o nome: ";
    getline(cin, clintes[quantidadeContas].nomeCliente);
    
    cout << "Digite o CPF: ";
    getline(cin, clintes[quantidadeContas].cpf);

    while (clintes[quantidadeContas].numeroConta <= 0)
    {
        cout << "Digite o número da conta: ";
        cin >> clintes[quantidadeContas].numeroConta;
        if (clintes[quantidadeContas].numeroConta <= 0)
        {
            cout << "Número de conta inválido. Por favor, digite um número maior que zero." << endl;
        }
    }

    while (clintes[quantidadeContas].tipoConta != 1 && clintes[quantidadeContas].tipoConta != 2)
    {
        cout << "Digite o tipo da conta\n 1 para Corrente\n 2 para Poupança\nOpção: ";
        cin >> clintes[quantidadeContas].tipoConta;
        if (clintes[quantidadeContas].tipoConta != 1 && clintes[quantidadeContas].tipoConta != 2)
        {
            cout << "Tipo de conta inválido. Por favor, digite 1 para Corrente ou 2 para Poupança." << endl;
        }
    }

    while (clintes[quantidadeContas].saldo <= 0)
    {
        cout << "Digite o saldo: ";
        cin >> clintes[quantidadeContas].saldo;
        if (clintes[quantidadeContas].saldo <= 0)
        {
            cout << "Saldo inválido. Por favor, digite um valor maior que zero." << endl;
        }
    }

    while (true)
    {
        cout << "Digite se a conta está ativa (1 para sim, 0 para não): ";
        cin >> inputContaAtiva;
        if (inputContaAtiva == 1 || inputContaAtiva == 0) {
            clintes[quantidadeContas].contaAtiva = inputContaAtiva == 1 ? true : false;
            break;
        } else {
            cout << "Entrada inválida." << endl;
        }
    }
    
    cout << "Conta cadastrada com sucesso!" << endl;
    quantidadeContas++;
    return 0;
}

int main()
{
    // Declaração de variáveis
    const int MAX_CONTAS = 100;
    Conta clintes[MAX_CONTAS];
    int quantidadeContas = 0;
    int opcao;

    // Titulo do programa
    cout << string(32, '*') << endl;
    cout << "*" << string(8, ' ') << "BANCOMASTER3.0" << string(8, ' ') << "*" << endl;
    cout << string(32, '*') << endl;

    do {
        cout << "Por favor, selecione uma das opções abaixo" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Listar as contas cadastradas" << endl; 
        cout << "3 - Consultar uma conta pelo número." << endl;
        cout << "4 - Realizar depósitos." << endl;
        cout << "5 - Realizar saques, verificando saldo suficiente." << endl;
        cout << "6 - Realizar transferências entre duas contas." << endl;
        cout << "7 - Exibir o extrato de uma conta." << endl;
        cout << "8 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcao;
        cout << endl;
        cin.ignore();

        switch (opcao)
        {
        case 1:
            cadastro(clintes, quantidadeContas);
            break;
        default:
            cout << "Opção invalida! Por favor, escolha corretamente." << endl;
            break;
        }
    } while (opcao != 8);

    cout << quantidadeContas << " conta(s) cadastrada(s):" << endl;
    return 0;
};
