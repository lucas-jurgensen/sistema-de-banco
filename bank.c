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
    printf("[2] - Efeturar saque.\n");
    printf("[3] - Efetuar depósito.\n");
    printf("[4] - Efeturar Transferência.\n");
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
            efeturarTranferencia();
            break;

        case 5:
            listarContas();

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
    strtok(cliente.dataNascimento, "\n"),strtok(cliente.dataCadastro, "\n"));
}

void infoConta(Conta conta) {
    printf("Número da conta: %d\nCliente %s\nData Nascimento: %s\nData Cadastro: %s\nSaldo Total: %.2f\n", conta.numero, strtok(conta.cliente.nome, "\n"),
    strtok(conta.cliente.dataNascimento, "\n"), strtok(conta.cliente.dataCadastro, "\n"), conta.saldoTotal);
}

void criarConta() {
    Cliente cliente;
    
    //data de cadastro
    char dia[3], mes[3], ano[5], data_cadastro[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if(tm.tm_mday < 10) {
        sprintf(dia, "0%d", tm.tm_mday);
    } else {
        sprintf(dia, "%d", tm.tm_mday);
    }

    if(tm.tm_mon + 1 < 10) {
        sprintf(mes, "0%d", tm.tm_mon);
    } else {
        sprintf(mes, "%d", tm.tm_mon);
    }

    sprintf(ano, "%d", tm.tm_year + 1900);

    strcpy(data_cadastro, "");
    strcat(data_cadastro, dia);
    strcat(data_cadastro, "/");
    strcat(data_cadastro, mes);
    strcat(data_cadastro, "/");
    strcat(data_cadastro, ano);
    strcat(data_cadastro, "\0");
    strcpy(cliente.dataCadastro, data_cadastro);

    printf("Informe os dados do cliente:\n");
    cliente.codigo = contador_clientes + 1;

    printf("Nome do cliente: ");
    fgets(cliente.nome, 50, stdin);

    printf("Email do cliente: ");
    fgets(cliente.email, 50, stdin);

    printf("CPF do cliente: ");
    fgets(cliente.cpf, 20, stdin);

    printf("Data de nascimento do cliente: ");
    fgets(cliente.dataNascimento, 20, stdin);

    contador_clientes++;

    //criar a conta
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
    if(contador_contas > 0) {
        int numero;
        printf("Informe o número da conta: ");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);

        if(conta.numero == numero) {
            float valor;
            printf("Informe o valor do saque: ");
            scanf("%f", &valor);

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
    if(contador_contas > 0) {
        int numero;
        printf("Informe o número da conta: ");
        scanf("%d", &numero);

        Conta conta = buscarContaPorNumero(numero);

        if(conta.numero == numero) {
            float valor;
            printf("Informe o valor do depósito: ");
            scanf("%f", &valor);

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

void efeturarTranferencia() {
    if(contador_contas > 0) {
        int numero_o, numero_d;
        printf("Informe o número da sua conta: ");
        scanf("%d", &numero_o);
        
        Conta conta_o = buscarContaPorNumero(numero_o);
        if(conta_o.numero == numero_o) {
            printf("Informe o número da conta destino: ");
            scanf("%d", &numero_d);

            Conta conta_d = buscarContaPorNumero(numero_d);
            if(conta_d.numero == numero_d) {
                float valor;
                printf("Informe o valor da trasnferência: ");
                scanf("%f", &valor);
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
    if(contador_contas > 0) {
        for(int i = 0; i < contador_contas; i++) {
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
    Conta c;
    
    if(contador_contas > 0) {
        for(int i = 0; i < contador_contas; i++) {
            if(contas[i].numero == numero) {
                c = contas[i];
            }
        }
    } else {
        printf("Não existem contas veinculadas à este banco ainda.\n");
        sleep(1);
    }
    return c; 
}

void sacar(Conta conta, float valor) {
    if(valor > 0 && conta.saldoTotal >= valor) {
        for(int i = 0; i < contador_contas; i++) {
            if(contas[i].numero == conta.numero) {
                if(contas[i].saldo >= valor) {
                    contas[i].saldo = contas[i].saldo - valor;
                    contas[i].saldo = atualizaSaldoTotal(contas[i]);
                    printf("Saque efetuado com sucesso!\n");
                } else {
                    float restante = valor - contas[i].saldo;
                    contas[i].limite = contas[i].limite - restante;
                    contas[i].saldo = 0.0;
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                    printf("Saque efetuado com sucesso!\n");
                }
            }
        }

    } else {
        printf("Saque não realizado.\n");
        sleep(1);
    }
}

void depositar(Conta conta, float valor) {
    if(valor > 0) {
        for(int i = 0; i < contador_contas; i++) {
            if(contas[i].numero == conta.numero) {
                contas[i].saldo = contas[i].saldo + valor;
                contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                printf("Depósito efetuado com sucesso!\n");
            }
        }
    } else {
        printf("Erro ao efetuar o depósito.\n");
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