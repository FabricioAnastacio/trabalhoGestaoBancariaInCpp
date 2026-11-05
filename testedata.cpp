#include <iostream>
#include <string>
#include <typeinfo>
#include <ctime>

using namespace std;

int main() {
    time_t now = time(0);
    int ano = 1900 + localtime(&now)->tm_year;
    int mes = 1 + localtime(&now)->tm_mon;
    int dia = localtime(&now)->tm_mday;
    int hora = localtime(&now)->tm_hour;
    int minuto = localtime(&now)->tm_min;
    int segundo = localtime(&now)->tm_sec;
    
    cout << "Data e hora atual: " << dia << "/" << mes << "/" << ano << " " << hora << ":" << minuto << ":" << segundo << endl;


    string cpf;
    cout << "Digite seu CPF (No formato 123.456.789-00): ";
    getline(cin, cpf);

    for (int i = 0; i < cpf.length(); i++) {
        if (!isdigit(cpf[i]) && cpf[i] != '.' && cpf[i] != '-') {
            cout << "CPF inválido. Por favor, digite apenas números e os caracteres '.' e '-'." << endl;
            cpf = "";
            break;
        }
        else if (i == 3 || i == 7 || i == 11) {
            if (cpf[i] != '.' && cpf[i] != '-') {
                cout << "CPF inválido. Por favor, digite no formato correto (123.456.789-00)." << endl;
                cpf = "";
                break;
            }
        }
    }

    return 0;
}