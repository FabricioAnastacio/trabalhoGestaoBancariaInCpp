#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Declaração de variáveis
    string nomeCliente;
    string cpf;
    int numeroConta = 0;
    int tipoConta = 3;
    double saldo = 0;
    bool contaAtiva = false;
    int opcao;
    int contaAtivaInput; // Variável temporária para armazenar a entrada do usuário

    // Titulo do programa
    cout << string(32, '*') << endl;
    cout << "*" << string(8, ' ') << "BANCOMASTER2.0" << string(8, ' ') << "*" << endl;
    cout << string(32, '*') << endl;

    // Iniciando o loop principal do programa
    bool repete = true;
    while (repete)
    {
        // Menu de opções
        cout << "Por favor, selecione uma das opções abaixo" << endl;
        cout << "1 - Cadastrar conta" << endl;
        cout << "2 - Consultar conta" << endl; 
        cout << "3 - Verificar saldo" << endl;
        cout << "4 - Alterar tipo da conta" << endl;
        cout << "5 - Ativar/Desativar conta" << endl;
        cout << "6 - Sair" << endl;
        cout << "Digite a opção desejada: ";
        cin >> opcao;
        cout << endl;
        cin.ignore();

        contaAtivaInput = 3; // Resetando a variável temporária para cada iteração
        // Processando a opção selecionada pelo usuário
        switch (opcao)
        {
        case 1:
            cout << string(6, '*') << " Cadastro de conta " << string(6, '*') << endl;
            cout << "Digite o nome: ";
            getline(cin, nomeCliente);
            
            cout << "Digite o CPF: ";
            getline(cin, cpf);

            while (numeroConta <= 0)
            {
                cout << "Digite o número da conta: ";
                cin >> numeroConta;
                if (numeroConta <= 0)
                {
                    cout << "Número de conta inválido. Por favor, digite um número maior que zero." << endl;
                }
            }

            while (tipoConta != 1 && tipoConta != 2)
            {
                cout << "Digite o tipo da conta\n 1 para Corrente\n 2 para Poupança\nOpção: ";
                cin >> tipoConta;
                if (tipoConta != 1 && tipoConta != 2)
                {
                    cout << "Tipo de conta inválido. Por favor, digite 1 para Corrente ou 2 para Poupança." << endl;
                }
            }
    
            while (saldo <= 0)
            {
                cout << "Digite o saldo: ";
                cin >> saldo;
                if (saldo <= 0)
                {
                    cout << "Saldo inválido. Por favor, digite um valor maior que zero." << endl;
                }
            }
            
            while (contaAtivaInput != 1 && contaAtivaInput != 0) {
                cout << "Digite se a conta está ativa (1 para sim, 0 para não): ";
                cin >> contaAtivaInput;
                if (contaAtivaInput == 1 || contaAtivaInput == 0) {
                    break;
                } else {
                    cout << "Entrada inválida. Por favor, digite 1 para sim ou 0 para não." << endl;
                }
            }
    
            contaAtiva = contaAtivaInput == 1 ? true : false;

            cout << "Conta cadastrada com sucesso!" << endl;
            break;
        case 2:
            cout << string(6, '*') << " Consulta de conta " << string(6, '*') << endl;
            if (numeroConta == 0) {
                cout << "Nenhuma conta cadastrada." << endl;
                break;
            }
            cout << (contaAtiva ? "Conta ativa" : "Conta inativa") << endl;
            cout << "Nome do cliente: " << nomeCliente << endl;
            cout << "CPF: " << cpf << endl;
            cout << "Número da conta: " << numeroConta << endl;
            cout << "Tipo da conta: " << (tipoConta == 1 ? "Corrente" : "Poupança") << endl;
            cout << "Saldo: " << saldo << endl;
            break;
        case 3:
            cout << string(5, '*') << " Verificação de saldo " << string(5, '*') << endl;
            if (numeroConta == 0) {
                cout << "Nenhuma conta cadastrada." << endl;
                break;
            }
            cout << "Saldo: " << saldo << endl;
            break;
        case 4:
            cout << string(2, '*') << " Alteração de tipo de conta " << string(2, '*') << endl;
            if (numeroConta == 0) {
                cout << "Nenhuma conta cadastrada." << endl;
                break;
            } else if (!contaAtiva) {
                cout << "A conta está atualmente inativa." << endl;
                break;
            }

            cout << "Digite o novo tipo da conta\n 1 para Corrente\n 2 para Poupança\nOpção: ";
            cin >> tipoConta;
    
            cout << "Tipo de conta alterado com sucesso!" << endl;
            break;
        case 5:
            cout << "* Ativação/Desativação de conta *" << endl;
            if (numeroConta == 0) {
                cout << "Nenhuma conta cadastrada." << endl;
                break;
            }
            while (contaAtivaInput != 1 && contaAtivaInput != 0) {
                cout << "Digite se a conta está ativa (1 para sim, 0 para não): ";
                cin >> contaAtivaInput;
                if (contaAtivaInput == 1 || contaAtivaInput == 0) {
                    break;
                } else {
                    cout << "Entrada inválida. Por favor, digite 1 para sim ou 0 para não." << endl;
                }
            }

            contaAtiva = contaAtivaInput == 1 ? true : false;
    
            if (contaAtiva) {
                cout << "Conta ativada com sucesso!" << endl;
            } else {
                cout << "Conta desativada com sucesso!" << endl;
            }
            break;
        case 6:
            cout << "Saindo..." << endl;
            repete = false;
            break;
        default:
            cout << "Opção inválida" << endl;
            break;
        }
        cout << "\nDeseja realizar outra operação? (1 para sim, 0 para não): ";
        cin >> repete;
        repete = repete == 1 ? true : false;
    }
    

    return 0;
};
