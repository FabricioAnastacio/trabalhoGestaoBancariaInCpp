#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Estrutura de dados para armazenar informações da conta
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

// Estrutura de dados para armazenar informações da movimentação
class Movimentacao
{
    public:
        int numeroConta;
        string tipoMovimentacao;
        double valor;
        string dataHora;
};

// Função para obter a data e hora atual formatada
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

    return dataHr; // Retorna a data e hora atual formatada como string formato "dd/mm/yyyy hh:mm:ss"
}

// Função para registrar uma movimentação
void registrarMovimentação(int numeroConta, double valor, string tipo, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    movimentacoes[quantidadeMovimentacoes].numeroConta = numeroConta;
    movimentacoes[quantidadeMovimentacoes].tipoMovimentacao = tipo;
    movimentacoes[quantidadeMovimentacoes].valor = valor;
    movimentacoes[quantidadeMovimentacoes].dataHora = getCurrentDateTime();
    quantidadeMovimentacoes++;
    cout << "*MOVIMENTAÇÃO REGISTRADA*" << endl;
};

// Função para validar e obter o CPF do usuário
string getCpf(string cpf)
{
    while (cpf.length() != 14)
    {
        cout << "Digite o CPF (No formato 123.456.789-00): ";
        getline(cin, cpf);
        if (cpf.length() != 14)
        {
            cout << "CPF inválido. Por favor, o cpf deve possuir 14 digitos (123.456.789-00)." << endl;
            cpf = "";
        }
        for (int i = 0; i < cpf.length(); i++) {
            if (!isdigit(cpf[i]) && cpf[i] != '.' && cpf[i] != '-') {
                cout << "CPF inválido. Por favor, digite apenas números e os caracteres '.' e '-'." << endl;
                cpf = "";
                break;
            }
            else if (i == 3 || i == 7) {
                if (cpf[i] != '.') {
                    cout << "CPF inválido. Por favor, digite no formato correto (123.456.789-00)." << endl;
                    cpf = "";
                    break;
                }
            }
            else if (i == 11) {
                if (cpf[i] != '-') {
                    cout << "CPF inválido. Por favor, digite no formato correto (123.456.789-00)." << endl;
                    cpf = "";
                    break;
                }
            }
        }
    }
    return cpf;
}

// Função para validar e obter o número da conta do usuário
int getNumeroConta(Conta clintes[], int& quantidadeContas)
{
    string numeroConta = "0";
    while (numeroConta.length() != 5)
    {
        cout << "Digite o número da conta (Deve possuir 5 numeros): ";
        getline(cin, numeroConta);
        for (char c : numeroConta) {
            if (!isdigit(c)) {
                cout << "Número de conta inválido. Por favor, digite apenas números." << endl;
                numeroConta = "0";
                break;
            }
        }
        if (numeroConta.length() != 5)
        {
            cout << "Número de conta inválido. Por favor, digite um número com 5 dígitos." << endl;
            numeroConta = "0";
        }
        for (int i = 0; i < quantidadeContas; i++)
        {
            if (clintes[i].numeroConta == stoi(numeroConta))
            {
                cout << "Número de conta já existente. Por favor, digite outro número." << endl;
                numeroConta = "0";
                break;
            }
        }
    }
    return stoi(numeroConta);
}

// Função para validar e obter o tipo da conta do usuário
int getTipoConta(Conta clintes[], int& quantidadeContas)
{
    string tipoContaStr = "";
    while (tipoContaStr != "1" && tipoContaStr != "2")
    {
        cout << "1 para Corrente\n2 para Poupança\nDigite o tipo da conta : ";
        cin >> tipoContaStr;
        for (char c : tipoContaStr) {
            if (!isdigit(c)) {
                cout << "Caracter inválido. Por favor, digite apenas número." << endl;
                clintes[quantidadeContas].tipoConta = 0;
                break;
            }
        }
        if (tipoContaStr != "1" && tipoContaStr != "2")
        {
            cout << "----- Tipo de conta inválido. Por favor, digite 1 para Corrente ou 2 para Poupança. -----" << endl;
            clintes[quantidadeContas].tipoConta = 0;
        }
    }
    return stoi(tipoContaStr);
}

// Função para validar e obter o saldo inicial da conta do usuário
double getSaldo()
{
    string saldo = "0";
    while (stod(saldo) <= 0)
    {
        cout << "Digite o saldo (A conta precisa ter um saldo inicial): ";
        cin >> saldo;
        for (char c : saldo) {
            if (!isdigit(c) && c != '.') {
                cout << "Caracter inválido. Por favor, digite apenas número." << endl;
                saldo = "0";
                break;
            }
        }
        if (stod(saldo) <= 0)
        {
            cout << "----- Saldo inválido. Por favor, digite um valor maior que zero. -----" << endl;
            saldo = "0";
        }
    }
    return stod(saldo);
}

// Função para validar e obter se a conta está ativa ou não
bool getContaAtiva()
{
    string inputContaAtiva;
    while (true)
    {
        cout << "Digite se a conta está ativa (1 para sim, 0 para não): ";
        cin >> inputContaAtiva;
        for (char c : inputContaAtiva) {
            if (!isdigit(c)) {
                cout << "----- Caracter inválido. Por favor, digite apenas número. -----" << endl;
                inputContaAtiva = "2"; // Valor inválido para forçar a repetição do loop
                break;
            }
        }
        if (inputContaAtiva == "1" || inputContaAtiva == "0") {
            cout << "----- " << (inputContaAtiva == "1" ? "Conta ativa." : "Conta inativa.") << " -----" << endl;
            return inputContaAtiva == "1" ? true : false;
        } else {
            cout << "Entrada inválida." << endl;
        }
    }
}

// Função para cadastrar uma nova conta
void cadastro(Conta clintes[], int& quantidadeContas)
{
    string cpf = "";

    cout << "Digite o nome: ";
    getline(cin, clintes[quantidadeContas].nomeCliente);
    clintes[quantidadeContas].cpf = getCpf(cpf);
    clintes[quantidadeContas].numeroConta = getNumeroConta(clintes, quantidadeContas);
    clintes[quantidadeContas].tipoConta = getTipoConta(clintes, quantidadeContas);
    clintes[quantidadeContas].saldo = getSaldo();
    clintes[quantidadeContas].contaAtiva = getContaAtiva();
    
    cout << "------- CONTA CADASTRADA COM SUCESSO -------" << endl;
    quantidadeContas++;
}

// Função para consultar uma conta pelo número
int consultaNumeroConta(Conta clintes[], int& quantidadeContas)
{
    string numeroConta = "0";
    while (stoi(numeroConta) <= 0)
    {
        cout << "Digite o numero da conta: ";
        cin >> numeroConta;
        for (char c : numeroConta) {
            if (!isdigit(c)) {
                cout << "Número de conta inválido. Por favor, digite apenas números maior que 0." << endl;
                numeroConta = "0";
                break;
            }
        }
    }
    for (int i = 0; i < quantidadeContas; i++)
    {
        if (clintes[i].numeroConta == stoi(numeroConta)) {
            return i; // Retorna o índice da conta encontrada
        }
    }
    return -1;
}

// Função para realizar um depósito
void deposito(Conta clintes[], int& quantidadeContas, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    double valorDeposito;
    cout << "Digite o valor do depósito: ";
    cin >> valorDeposito;
    int index = consultaNumeroConta(clintes, quantidadeContas);
    if (index == -1)
    {
        cout << "----- Conta não encontrada! -----" << endl;
    }
    else
    {
        clintes[index].saldo += valorDeposito;
        registrarMovimentação(clintes[index].numeroConta, valorDeposito, "D", movimentacoes, quantidadeMovimentacoes);
        
        cout << "------- DEPÓSITO REALIZADO COM SUCESSO -------" << endl;
    }

}

// Função para realizar um saque
void  saque(Conta clintes[], int& quantidadeContas, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    bool continuar = true;
    int index;
    double valorSaque;

    index = consultaNumeroConta(clintes, quantidadeContas);
    if (index == -1) 
    {
        cout << "----- Conta não encontrada! -----" << endl;
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
                cout << "----- Valor informado superior ao saldo da conta -----" << endl;
            }

            string resposta;
            cout << "Fazer novo saque? (s ou n) ";
            cin >> resposta;
            continuar = resposta == "s" || resposta == "S";
            cout << endl;
        }
    }
    
};

// Função para realizar uma transferência entre duas contas
void transferencia(Conta clintes[], int& quantidadeContas, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
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
            cout << "----- Conta de origem não encontrada! -----" << endl;
            cout << "Deseja tentar novamente? (s ou n) ";
            cin >> resposta; 
            continuar = resposta == "s" || resposta == "S";
        }
        else if (!clintes[indexOrigem].contaAtiva) {
            cout << "----- Conta de origem está inativa! -----" << endl;
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
            cout << "----- Conta de destino não pode ser a mesma que a conta de origem! -----" << endl;
        }
        else if (indexDestino == -1) {
            cout << "----- Conta de destino não encontrada! -----" << endl;
            cout << "Deseja tentar novamente? (s ou n) ";
            cin >> resposta;
            continuar = resposta == "s" || resposta == "S";
        }
        else if (!clintes[indexDestino].contaAtiva) {
            cout << "----- Conta de destino está inativa! -----" << endl;
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
            cout << "----- Valor informado superior ao saldo da conta de origem -----" << endl;
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

// Função para exibir o extrato de uma conta
void exibirExtrato(Conta clintes[], int& quantidadeContas, Movimentacao movimentacoes[], int& quantidadeMovimentacoes)
{
    int index = consultaNumeroConta(clintes, quantidadeContas);
    if (index == -1) {
        cout << "----- Conta não encontrada! -----" << endl;
    } else {
        cout << "------- EXTRATO DA CONTA -------" << endl;
        cout << clintes[index] << endl;
        cout << "Movimentações:" << endl;
        for (int i = 0; i < quantidadeMovimentacoes; i++) {
            if (movimentacoes[i].numeroConta == clintes[index].numeroConta) {
                string tipoMovimentacao;
                if (movimentacoes[i].tipoMovimentacao == "D") {
                    tipoMovimentacao = "Depósito";
                } else if (movimentacoes[i].tipoMovimentacao == "S") {
                    tipoMovimentacao = "Saque";
                } else if (movimentacoes[i].tipoMovimentacao == "T-S") {
                    tipoMovimentacao = "Transferência Saída";
                } else if (movimentacoes[i].tipoMovimentacao == "T-D") {
                    tipoMovimentacao = "Transferência Entrada";
                }
                cout << "Conta: " << movimentacoes[i].numeroConta
                     << ", Tipo: " << tipoMovimentacao
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
    
    char opcao = '0';

    // Titulo do programa
    cout << string(32, '*') << endl;
    cout << "*" << string(8, ' ') << "BANCOMASTER3.0" << string(8, ' ') << "*" << endl;
    cout << string(32, '*') << endl;
    
    do {
        // Menu de opções
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
        case '1':
            // Cadastrar conta
            cout << string(6, '*') << " Cadastro de conta " << string(6, '*') << endl;
            if (quantidadeContas == 100)
            {
                cout << "Limite de contas atingido." << endl;
            }
            else
            {
                cadastro(clintes, quantidadeContas);
            }
            cout << endl;
            break;
        case '2':
            // Listar contas cadastradas
            cout << string(6, '*') << " Listagem de contas " << string(6, '*') << endl;
            for (int i = 0; i < quantidadeContas; i++) {
                cout << string(6, '-') << " Conta " << i + 1 << string(6, '-') << endl;
                cout << clintes[i] << endl;
            }
            cout << endl;
            break;
        case '3':
            // Consultar conta pelo número
            cout << string(6, '*') << " Consultar conta por numero " << string(6, '*') << endl;
            int index;
            index = consultaNumeroConta(clintes, quantidadeContas);
            if (index == -1) {
                cout << "----- Conta não encontrada! -----" << endl;
            } else {
                cout << clintes[index] << endl;
            }
            cout << endl;
            break;
        case '4':
            // Realizar depósito
            cout << string(6, '*') << " Realizar depósito " << string(6, '*') << endl;
            deposito(clintes, quantidadeContas, movimentacoes, quantidadeMovimentacoes);
            cout << endl;
            break;
        case '5':
            // Realizar saque
            cout << string(6, '*') << " Realizar saque " << string(6, '*') << endl;
            saque(clintes, quantidadeContas, movimentacoes, quantidadeMovimentacoes);
            cout << endl;
            break;
        case '6':
            // Realizar transferência
            cout << string(6, '*') << " Realizar transferência " << string(6, '*') << endl;
            transferencia(clintes, quantidadeContas, movimentacoes, quantidadeMovimentacoes);
            cout << endl;
            break;
        case '7':
            // Exibir extrato
            cout << string(6, '*') << " Exibir extrato " << string(6, '*') << endl;
            exibirExtrato(clintes, quantidadeContas, movimentacoes, quantidadeMovimentacoes);
            cout << endl;
            break;
        case '8':
            // Sair do programa
            cout << "------- SAINDO DO PROGRAMA -------" << endl;
            break;
        default:
            cout << "Opção invalida! Por favor, escolha um numero corretamente." << endl;
            break;
        }
    } while (opcao != '8');

    cout << "------- " << quantidadeContas << " conta(s) cadastrada(s): -------" << endl;
    cout << "------- " << quantidadeMovimentacoes << " movimentação(ões) registrada(s): -------" << endl;
    return 0;
};
