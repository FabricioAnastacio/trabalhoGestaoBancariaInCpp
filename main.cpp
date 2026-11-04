#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Conta
{
    public:
        string nomeCliente;
        string cpf;
        int numeroConta;
        int tipoConta;
        double saldo;
        bool contaAtiva;
    
    public:
        friend ostream& operator<<(ostream& os, const Conta& conta)
        {
            os << "Nome do cliente: " << conta.nomeCliente << endl;
            os << "CPF: " << conta.cpf << endl;
            os << "Número da conta: " << conta.numeroConta << endl;
            os << "Tipo da conta: " << (conta.tipoConta == 1 ? "Corrente" : "Poupança") << endl;
            os << "Saldo: R$" << conta.saldo << endl;
            os << "Conta ativa: " << (conta.contaAtiva ? "Sim" : "Não") << endl;
            return os;
        };
};

class Movimentacao
{
    public:
        int numeroConta;
        string tipoMovimentacao;
        double valor;
        string dataHora;
};

string getCurrentDateTime()
{
    time_t now = time(0);
    int ano = 1900 + localtime(&now)->tm_year;
    int mes = 1 + localtime(&now)->tm_mon;
    int dia = localtime(&now)->tm_mday;
    int hora = localtime(&now)->tm_hour;
    int minuto = localtime(&now)->tm_min;
    int segundo = localtime(&now)->tm_sec;
    
    string dataHr = to_string(dia) + "/" + to_string(mes) + "/" + to_string(ano)
        + " " + to_string(hora) + ":" + to_string(minuto) + ":" + to_string(segundo);

    return dataHr; 
}

void registrarMovimentação(int numeroConta, double valor, string tipo, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    movimentacoes[quantidadeMovimentacoes].numeroConta = numeroConta;
    movimentacoes[quantidadeMovimentacoes].tipoMovimentacao = tipo;
    movimentacoes[quantidadeMovimentacoes].valor = valor;
    movimentacoes[quantidadeMovimentacoes].dataHora = getCurrentDateTime();
    quantidadeMovimentacoes++;
    cout << "*MOVIMENTAÇÃO REGISTRADA*" << endl;
};

void cadastro(Conta clintes[], int& quantidadeContas)
{
    int inputContaAtiva;

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
    
    cout << "------- CONTA CADASTRADA COM SUCESSO -------" << endl;
    quantidadeContas++;
}

int consultaNumeroConta(Conta clintes[], int& quantidadeContas)
{
    int numeroConta;
    cout << "Digite o numero da conta: ";
    cin >> numeroConta;
    for (int i = 0; i < quantidadeContas; i++)
    {
        if (clintes[i].numeroConta == numeroConta) {
            return i; // Retorna o índice da conta encontrada
        }
    }
    return -1;
}

void deposito(Conta clintes[], int& quantidadeContas, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    double valorDeposito;
    cout << "Digite o valor do depósito: ";
    cin >> valorDeposito;
    int index = consultaNumeroConta(clintes, quantidadeContas);
    if (index == -1)
    {
        cout << "Conta não encontrada!" << endl;
    }
    else
    {
        clintes[index].saldo += valorDeposito;
        registrarMovimentação(clintes[index].numeroConta, valorDeposito, "D", movimentacoes, quantidadeMovimentacoes);
        
        cout << "------- DEPÓSITO REALIZADO COM SUCESSO -------" << endl;
    }

}

void saque(Conta clintes[], int& quantidadeContas, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    bool continuar = true;
    int index;
    double valorSaque;

    index = consultaNumeroConta(clintes, quantidadeContas);
    if (index == -1) 
    {
        cout << "Conta não encontrada!" << endl;
    }
    else
    {
        while (continuar)
        {
            cout << "Saldo atual: " << clintes[index].saldo << endl;
            cout << "Qual valor deseja retirar? ";
            cin >> valorSaque;

            if (clintes[index].saldo >= valorSaque)
            {
                clintes[index].saldo -= valorSaque;
                registrarMovimentação(clintes[index].numeroConta, valorSaque, "S", movimentacoes, quantidadeMovimentacoes);
                cout << "------- SAQUE REALIZADO COM SUCESSO -------" << endl;
            }
            else
            {
                cout << "Valor informado superior ao saldo da conta" << endl;
            }

            string resposta;
            cout << "Fazer novo saque? (s ou n) ";
            cin >> resposta;
            continuar = resposta == "s" || resposta == "S";
            cout << endl;
        }
    }
    
};

void trasferencia(Conta clintes[], int& quantidadeContas, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    double valorTransferencia;
    bool continuar = true;
    int indexOrigem, indexDestino;
    string resposta = "s";

    while (continuar)
    {
        cout << "Conta de origem ";
        indexOrigem = consultaNumeroConta(clintes, quantidadeContas);

        if (indexOrigem == -1) {
            cout << "Conta de origem não encontrada!" << endl;
            cout << "Deseja tentar novamente? (s ou n) ";
            cin >> resposta; 
            continuar = resposta == "s" || resposta == "S";
        }
        else if (!clintes[indexOrigem].contaAtiva) {
            cout << "Conta de origem está inativa!" << endl;
            cout << "Deseja tentar outra conta? (s ou n) ";
            cin >> resposta;
            continuar = resposta == "s" || resposta == "S";
        }
        else
        {
            continuar = false;
        }
    }

    continuar = resposta == "s" || resposta == "S";
    while (continuar)
    {
        cout << "Conta de destino ";
        indexDestino = consultaNumeroConta(clintes, quantidadeContas);

        if (indexDestino == indexOrigem) {
            cout << "Conta de destino não pode ser a mesma que a conta de origem!" << endl;
        }
        else if (indexDestino == -1) {
            cout << "Conta de destino não encontrada!" << endl;
            cout << "Deseja tentar novamente? (s ou n) ";
            cin >> resposta;
            continuar = resposta == "s" || resposta == "S";
        }
        else if (!clintes[indexDestino].contaAtiva) {
            cout << "Conta de destino está inativa!" << endl;
            cout << "Deseja tentar outra conta? (s ou n) ";
            cin >> resposta;
            continuar = resposta == "s" || resposta == "S";
        }
        else
        {
            continuar = false;
        }
    }

    continuar = resposta == "s" || resposta == "S";
    while (continuar)
    {
        cout << "Qual valor deseja transferir? ";
        cin >> valorTransferencia;
    
        if (valorTransferencia <= 0)
        {
            cout << "Valor inválido!" << endl;
        }
        else if (clintes[indexOrigem].saldo >= valorTransferencia)
        {
            clintes[indexOrigem].saldo -= valorTransferencia;
            clintes[indexDestino].saldo += valorTransferencia;
    
            registrarMovimentação(clintes[indexOrigem].numeroConta, valorTransferencia, "T-S", movimentacoes, quantidadeMovimentacoes);
            registrarMovimentação(clintes[indexDestino].numeroConta, valorTransferencia, "T-D", movimentacoes, quantidadeMovimentacoes);
    
            cout << "------- TRANSFERÊNCIA REALIZADA COM SUCESSO -------" << endl;
        }
        else
        {
            cout << "Valor informado superior ao saldo da conta de origem" << endl;
        }

        cout << "Deseja tentar outro valor? (s ou n) ";
        cin >> resposta;
        continuar = resposta == "s" || resposta == "S";
        cout << endl;
    }
    
    cout << "Deseja tentar outra transferencia? (s ou n) ";
    cin >> resposta;
    continuar = resposta == "s" || resposta == "S";
    cout << endl;

    if (resposta != "s" && resposta != "S") {
        cout << "------- SAINDO DO MENU DE TRANSFERÊNCIAS -------" << endl;
    }
};

void exibirExtrato(Conta clintes[], int& quantidadeContas, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    int index = consultaNumeroConta(clintes, quantidadeContas);
    if (index == -1) {
        cout << "Conta não encontrada!" << endl;
    } else {
        cout << "------- EXTRATO DA CONTA -------" << endl;
        cout << clintes[index] << endl;
        cout << "Movimentações:" << endl;
        for (int i = 0; i < quantidadeMovimentacoes; i++) {
            if (movimentacoes[i].numeroConta == clintes[index].numeroConta) {
                cout << "Conta: " << movimentacoes[i].numeroConta
                     << ", Tipo: " << movimentacoes[i].tipoMovimentacao
                     << ", Valor: R$" << movimentacoes[i].valor
                     << ", Data e hora: " << movimentacoes[i].dataHora << endl;
            }
        }
    }
}

int main()
{
    // Declaração de variáveis principais
    const int MAX_CONTAS = 100;
    const int MAX_MOVIMENTACOES = 500;

    Conta clintes[MAX_CONTAS];
    int quantidadeContas = 0;
    Movimentacao movimentacoes[MAX_MOVIMENTACOES];
    int quantidadeMovimentacoes = 0;
    
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
            cout << string(6, '*') << " Cadastro de conta " << string(6, '*') << endl;
            cadastro(clintes, quantidadeContas);
            cout << endl;
            break;
        case 2:
            cout << string(6, '*') << " Listagem de contas " << string(6, '*') << endl;
            for (int i = 0; i < quantidadeContas; i++) {
                cout << string(6, '-') << " Conta " << i + 1 << string(6, '-') << endl;
                cout << clintes[i] << endl;
            }
            cout << endl;
            break;
        case 3:
            cout << string(6, '*') << " Consultar conta por numero " << string(6, '*') << endl;
            int index;
            index = consultaNumeroConta(clintes, quantidadeContas);
            if (index == -1) {
                cout << "Conta não encontrada!" << endl;
            } else {
                cout << clintes[index] << endl;
            }
            cout << endl;
            break;
        case 4:
            cout << string(6, '*') << " Realizar depósito " << string(6, '*') << endl;
            deposito(clintes, quantidadeContas, movimentacoes, quantidadeMovimentacoes);
            cout << endl;
            break;
        case 5:
            cout << string(6, '*') << " Realizar saque " << string(6, '*') << endl;
            saque(clintes, quantidadeContas, movimentacoes, quantidadeMovimentacoes);
            cout << endl;
            break;
        case 6:
            cout << string(6, '*') << " Realizar transferência " << string(6, '*') << endl;
            trasferencia(clintes, quantidadeContas, movimentacoes, quantidadeMovimentacoes);
            cout << endl;
            break;
        case 7:
            cout << string(6, '*') << " Exibir extrato " << string(6, '*') << endl;
            exibirExtrato(clintes, quantidadeContas, movimentacoes, quantidadeMovimentacoes);
            cout << endl;
            break;
        case 8:
            cout << "------- SAINDO DO PROGRAMA -------" << endl;
            break;
        case 9:
            cout << string(6, '*') << " Ambiente de testes " << string(6, '*') << endl;
            cout << "Data e hora atual: " << getCurrentDateTime() << endl;
            clintes[0].nomeCliente = "Fabricio";
            clintes[0].cpf = "123.456.789-00";
            clintes[0].numeroConta = 12345;
            clintes[0].tipoConta = 1;
            clintes[0].saldo = 1000.00;
            clintes[0].contaAtiva = true;
            quantidadeContas++;
            cout << "------- 1° Conta de teste cadastrada -------" << endl;
            cout << clintes[0] << endl;
            clintes[1].nomeCliente = "Maria";
            clintes[1].cpf = "987.654.321-00";
            clintes[1].numeroConta = 54321;
            clintes[1].tipoConta = 2;
            clintes[1].saldo = 500.00;
            clintes[1].contaAtiva = true;
            quantidadeContas++;
            cout << "------- 2° Conta de teste cadastrada -------" << endl;
            cout << clintes[1] << endl;
            cout << endl;
            break;
        default:
            cout << "Opção invalida! Por favor, escolha corretamente." << endl;
            break;
        }
    } while (opcao != 8);

    cout << "------- " << quantidadeContas << " conta(s) cadastrada(s): -------" << endl;
    cout << "------- " << quantidadeMovimentacoes << " movimentação(ões) registrada(s): -------" << endl;
    return 0;
};
