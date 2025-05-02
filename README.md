# Sistema Bancário em C

Um sistema bancário fictício desenvolvido em C que permite a criação e gestão de contas bancárias com operações financeiras básicas.

## Funcionalidades

- **Criação de contas**
  - Cadastro de novas contas com nome do titular e saldo inicial
  - Gerenciamento de múltiplas contas no sistema

- **Operações financeiras**
  - Depósitos (adicionar fundos à conta)
  - Saques (retirar fundos com validação de saldo)
  - Transferências entre contas (com verificação de saldo disponível)

- **Validações de segurança**
  - Impede transações com saldo insuficiente
  - Verifica a existência das contas antes das operações

## Pré-requisitos

- Compilador GCC instalado
- Sistema operacional Linux (recomendado)
- Terminal bash

## Compilação e Execução

1. Clone ou baixe o repositório
```bash
git clone https://github.com/lucas-jurgensen/sistema-de-banco.git
```

2. Acesse o diretório da página
```bash
cd sistema-de-banco
```

3. Se necessário, compile o programa
```bash
gcc banco.c -o banco
```

4. Execute o programa
```bash
./banco
```
## Aprendizados

Este projeto foi desenvolvido como ferramenta de estudo para:

- Praticar lógica de programação em C
- Implementar estruturas de dados básicas
- Desenvolver sistemas de gestão simples
- Aprender validações e tratamentos básicos

