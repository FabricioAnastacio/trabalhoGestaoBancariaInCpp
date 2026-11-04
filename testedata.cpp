#include <iostream>
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

    return 0;
}