#include "bank.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void menu() {
    int opcao;
    printf("======================================================\n");
    printf("=====================BEM-VINDO(A)=====================\n");
    printf("======================================================\n");

    printf("Selecione uma opção do menu:\n");
    printf("[1] - Criar conta.\n");
    printf("[2] - Efetuar saque.\n");
    printf("[3] - Efetuar depósito.\n");
    printf("[4] - Efetuar Transferência.\n");
    printf("[5] - Listar contas.\n");
    printf("[0] - Sair do sistema.\n");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            criarConta();
            break;
        case 2:
            efeturarSaque();
            break;
        case 3:
            efeturarDeposito();
            break;
        case 4:
            efeturarTransferencia();
            break;
        case 5:
            listarContas();
            break; // Add break here
        case 0:
            printf("Saindo...\n");
            exit(0);
        default:
            printf("Opção inválida.\n");
            sleep(2);
            menu();
            break;
    }
}

void infoCliente(Cliente cliente) {
    printf("Código: %d\nNome: %s\nData de Nascimento: %s\nCadastro: %s\n", cliente.codigo, strtok(cliente.nome, "\n"), 
           strtok(cliente.dataNascimento, "\n"), strtok(cliente.dataCadastro, "\n"));
}

void infoConta(Conta conta) {
    printf("Número da conta: %d\nCliente: %s\nData Nascimento: %s\nData Cadastro: %s\nSaldo Total: %.2f R$\n", conta.numero, 
           strtok(conta.cliente.nome, "\n"), strtok(conta.cliente.dataNascimento, "\n"), strtok(conta.cliente.dataCadastro, "\n"), conta.saldoTotal);
}

void criarConta() {
    Cliente cliente;

    // Data de cadastro
    char dia[3], mes[3], ano[5], data_cadastro[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(dia, "%02d", tm.tm_mday);
    sprintf(mes, "%02d", tm.tm_mon + 1); // Corrigido aqui
    sprintf(ano, "%d", tm.tm_year + 1900);

    snprintf(data_cadastro, sizeof(data_cadastro), "%s/%s/%s", dia, mes, ano);
    strcpy(cliente.dataCadastro, data_cadastro);

    printf("Informe os dados do cliente:\n");
    cliente.codigo = contador_clientes + 1;

    printf("Nome do cliente: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    printf("Email do cliente: ");
    fgets(cliente.email, sizeof(cliente.email), stdin);
    printf("CPF do cliente: ");
    fgets(cliente.cpf, sizeof(cliente.cpf), stdin);
    printf("Data de nascimento do cliente: ");
    fgets(cliente.dataNascimento, sizeof(cliente.dataNascimento), stdin);

    contador_clientes++;

    // Criar a conta
    contas[contador_contas].numero = contador_contas + 1;
    contas[contador_contas].cliente = cliente;
    contas[contador_contas].saldo = 0.0;
    contas[contador_contas].limite = 0.0;
    contas[contador_contas].saldoTotal = atualizaSaldoTotal(contas[contador_contas]);

    printf("Conta criada com sucesso!\n\n");
    printf("Dados da conta criada:\n\n");
    infoConta(contas[contador_contas]);
    contador_contas++;
    
    sleep(4);
    menu();
}

void efeturarSaque() {
    if (contador_contas > 0) {
        int numero;
        printf("Informe o número da conta: ");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);
        if (conta.numero != -1) { // Verifica se a conta é válida
            float valor;
            printf("Informe o valor do saque: ");
            scanf("%f", &valor);
            if (valor <= 0) {
                printf("Valor de saque deve ser positivo.\n");
                sleep(1);
                menu();
                return;
            }
            sacar(conta, valor);
        } else {
            printf("Não foi encontrada uma conta com o número %d.\n", numero);
        }
    } else {
        printf("Ainda não existem contas no sistema...\n");
    }
    sleep(2);
    menu();
}

void efeturarDeposito() {
    if (contador_contas > 0) {
        int numero;
        printf("Informe o número da conta: ");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);
        if (conta.numero != -1) { // Verifica se a conta é válida
            float valor;
            printf("Informe o valor do depósito: ");
            scanf("%f", &valor);
            if (valor <= 0) {
                printf("Valor de depósito deve ser positivo.\n");
                sleep(1);
                menu();
                return;
            }
            depositar(conta, valor);
        } else {
            printf("Não foi encontrada uma conta com o número %d.\n", numero);
        }
    } else {
        printf("Ainda não existem contas no sistema...\n");
    }
    sleep(2);
    menu();
}

void efeturarTransferencia() {
    if (contador_contas > 0) {
        int numero_o, numero_d;
        printf("Informe o número da sua conta: ");
        scanf("%d", &numero_o);
        
        Conta conta_o = buscarContaPorNumero(numero_o);
        if (conta_o.numero != -1) { // Verifica se a conta origem é válida
            printf("Informe o número da conta destino: ");
            scanf("%d", &numero_d);

            Conta conta_d = buscarContaPorNumero(numero_d);
            if (conta_d.numero != -1) { // Verifica se a conta destino é válida
                float valor;
                printf("Informe o valor da transferência: ");
                scanf("%f", &valor);
                if (valor <= 0) {
                    printf("Valor da transferência deve ser positivo.\n");
                    sleep(1);
                    menu();
                    return;
                }
                transferir(conta_o, conta_d, valor);
            } else {
                printf("A conta destino com número %d não foi encontrada.\n", numero_d);
            }
        } else {
            printf("A conta origem com número %d não foi encontrada.\n", numero_o);
        }
    } else {
        printf("Ainda não existem contas no sistema...\n");
    }
    sleep(2);
    menu();
}

void listarContas() {
    if (contador_contas > 0) {
        for (int i = 0; i < contador_contas; i++) {
            infoConta(contas[i]);
            printf("\n");
            sleep(1);
        }
    } else {
        printf("Ainda não existem contas no sistema...\n");
    }
    sleep(2);
    menu();
}

float atualizaSaldoTotal(Conta conta) {
    return conta.saldo + conta.limite; 
}

Conta buscarContaPorNumero(int numero) {
    for (int i = 0; i < contador_contas; i++) {
        if (contas[i].numero == numero) {
            return contas[i];
        }
    }
    // Retorna uma conta inválida
    Conta invalid;
    invalid.numero = -1; // Indica uma conta inválida
    return invalid; 
}

void sacar(Conta conta, float valor) {
    if (valor > 0 && conta.saldoTotal >= valor) {
        for (int i = 0; i < contador_contas; i++) {
            if (contas[i].numero == conta.numero) {
                if (contas[i].saldo >= valor) {
                    contas[i].saldo -= valor;
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                    printf("Saque efetuado com sucesso!\n");
                } else {
                    float restante = valor - contas[i].saldo;
                    contas[i].limite -= restante;
                    contas[i].saldo = 0.0;
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                    printf("Saque efetuado com sucesso!\n");
                }
            }
        }
    } else {
        printf("Saque não realizado. Verifique o valor.\n");
        sleep(1);
    }
}

void depositar(Conta conta, float valor) {
    if (valor > 0) {
        for (int i = 0; i < contador_contas; i++) {
            if (contas[i].numero == conta.numero) {
                contas[i].saldo += valor;
                contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                printf("Depósito efetuado com sucesso!\n");
            }
        }
    } else {
        printf("Erro ao efetuar o depósito. Valor inválido.\n");
        sleep(1);
    }
}

void transferir(Conta conta_origem, Conta conta_destino, float valor) {
    if(valor > 0 && conta_origem.saldoTotal >= valor) {
        for(int co = 0; co < contador_contas; co++) {
            if(contas[co].numero == conta_origem.numero) {
                for(int cd = 0; cd < contador_contas; cd++) {
                    if(contas[cd].numero == conta_destino.numero) {
                        if(contas[co].saldo >= valor) {
                            contas[co].saldo = contas[co].saldo - valor;
                            contas[cd].saldo = contas[cd].saldo + valor;
                            contas[co].saldoTotal = atualizaSaldoTotal(contas[co]);
                            contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]);
                            printf("Transferência realizada com sucesso!\n");
                        } else {
                            float restante = valor - contas[co].saldo;
                            contas[co].limite = contas[co].limite - restante;
                            contas[co].saldo = 0.0;
                            contas[cd].saldo = contas[cd].saldo + valor;
                            contas[co].saldoTotal = atualizaSaldoTotal(contas[co]);
                            contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]);
                            printf("Transferência realizada com sucesso!\n"); 
                        }
                    }
                }
            }
        }
    } else {
        printf("Transferência não realizada.\n");
        sleep(1);
    }
}