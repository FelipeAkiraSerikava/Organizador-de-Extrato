#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Função para carregar o último saldo salvo no CSV
void carregarDados(double &total, double &GASTO_TOTAL, double &a, double &c, double &l, double &o) {
    // Ajuste o caminho abaixo conforme necessário (ex: "financas.csv" ou o caminho completo)
    ifstream arquivo("../financas.csv"); 
    string linha;

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            if (linha.empty()) continue;

            stringstream ss(linha);
            string tipo, categoria, valorStr, saldoStr;

            // Divide a linha pelas vírgulas: TIPO, CATEGORIA, VALOR, SALDO_ACUMULADO
            getline(ss, tipo, ',');
            getline(ss, categoria, ',');
            getline(ss, valorStr, ',');
            getline(ss, saldoStr, ',');

            try {
                double valor = stod(valorStr);
                total = stod(saldoStr); // O último total lido será o saldo atual

                if (tipo == "GASTO") {
                    GASTO_TOTAL += valor;
                    if (categoria == "Alimentacao") a += valor;
                    else if (categoria == "Carro") c += valor;
                    else if (categoria == "Lazer") l += valor;
                    else if (categoria == "Outros") o += valor;
                }
            } catch (...) {
                // Pula linhas que não estejam no formato correto
                continue;
            }
        }
        arquivo.close();
    } else {
        total = 0;
        GASTO_TOTAL = 0;
    }
}
void ADsaldo(double &total) {
    double saldo;
    cout << "\nDIGITE O GANHO: ";
    cin >> saldo;
    
    while (saldo < 0) {
        cout << "\nDIGITE UM GANHO POSITIVO: ";
        cin >> saldo;
    }
    
    total += saldo;

    ofstream arquivo("financas.csv", ios::app);
    if (arquivo.is_open()) {
        // Formato: TIPO,CATEGORIA,VALOR,SALDO_ACUMULADO
        arquivo << "GANHO,Entrada," << saldo << "," << total << endl;
        arquivo.close();
        cout << "\nSALVO COM SUCESSO!" << endl;
    } else {
        cout << "\nERRO AO SALVAR! Verifique se o arquivo esta aberto em outro programa." << endl;
    }

    cout << "SALDO ATUAL : " << fixed << setprecision(2) << total << endl;
}

void ADgasto(double &total, double &GASTO_TOTAL, double &a, double &c, double &l, double &o) {
    double valorGasto;
    string categoria;
    int opcao;

    cout << "\n1 - ALIMENTACAO\n2 - CARRO\n3 - LAZER\n4 - OUTROS\nEscolha: ";
    cin >> opcao;

    cout << "DIGITE O VALOR DO GASTO: ";
    cin >> valorGasto;

    switch (opcao) {
        case 1: a += valorGasto; categoria = "Alimentacao"; break;
        case 2: c += valorGasto; categoria = "Carro"; break;
        case 3: l += valorGasto; categoria = "Lazer"; break;
        case 4: o += valorGasto; categoria = "Outros"; break;
        default:
            cout << "Opcao invalida!" << endl;
            return;
    }

    total -= valorGasto;
    GASTO_TOTAL += valorGasto;

    ofstream arquivo("financas.csv", ios::app);
    if (arquivo.is_open()) {
        arquivo << "GASTO," << categoria << "," << valorGasto << "," << total << endl;
        arquivo.close();
        cout << "NOVO SALDO : " << fixed << setprecision(2) << total << endl;
    } else {
        cout << "ERRO AO GRAVAR NO ARQUIVO!" << endl;
    }
}

void Extrato(double total, double gasto, double a, double c, double l, double o) {
    cout << fixed << setprecision(2);
    cout << "\n==================================================================================" << endl;
    cout << "|| SALDO ATUAL:  R$ " << total << endl;
    cout << "|| GASTO TOTAL:  R$ " << gasto << endl;
    cout << "||------------------------------- GASTOS ---------------------------------------||" << endl;
    cout << "|| ALIMENTACAO:  R$ " << a << endl;
    cout << "|| CARRO:        R$ " << c << endl;
    cout << "|| LAZER:        R$ " << l << endl;
    cout << "|| OUTROS:       R$ " << o << endl;
    cout << "==================================================================================" << endl;
}

int main() {
    double TOTAL = 0, A = 0, C = 0, L = 0, O = 0, GASTO_TOTAL = 0;
    int n;

    // Carrega o saldo anterior assim que o programa inicia
carregarDados(TOTAL, GASTO_TOTAL, A, C, L, O);

    while (true) {
        cout << "\n1-ADICIONAR SALDO | 2-ADICIONAR GASTO | 3-EXTRATO | 4-SAIR: ";
        if (!(cin >> n)) break; // Previne erro se o usuário digitar letras

        if (n == 4) break;

        if (n == 1) ADsaldo(TOTAL);
        else if (n == 2) ADgasto(TOTAL, GASTO_TOTAL, A, C, L, O);
        else if (n == 3) Extrato(TOTAL, GASTO_TOTAL, A, C, L, O);
        else cout << "Opcao Invalida!" << endl;
    }

    return 0;
}
