# Trabalho de Estrutura de Dados 2

## 📌 Descrição Geral
Implementação em C de um sistema integrado que gerencia:
1. **Dados geográficos** (Estados, cidades, CEPs)  
2. **Dados pessoais** (Pessoas com CPF, CEPs de nascimento/moradia)  
3. **Gerenciamento de memória** (Simulação com blocos de 1MB)  

Usando as estruturas:
- Listas duplamente encadeadas  
- Árvores vermelho-pretas (Parte 1)  
- Árvores 2-3 (Parte 2)  
- Árvores 4-5 (Parte 3)  

---

## 🔍 Partes do Trabalho

### 1️⃣ Parte 1: Estruturas Básicas (Árvores Vermelho-Pretas)
- **Lista de Estados**: Ordenada por nome, com dados de capital e população.  
- **Árvore de Cidades**: Vinculada a cada estado (armazena nome e população).  
- **Árvore de CEPs**: Vinculada a cada cidade.  
- **Árvore de Pessoas**: Com CPF, nome, CEPs e data de nascimento.  

#### Funcionalidades:
- Cadastro/remoção de estados, cidades, CEPs e pessoas.  
- Consultas como:  
  - Estado mais populoso  
  - População da capital  
  - Pessoas que mudaram de cidade natal  

---

### 2️⃣ Parte 2: Adaptação para Árvores 2-3
- Mesma lógica da **Parte 1**, mas substituindo árvores vermelho-pretas por **árvores 2-3**.  
- Objetivo: Comparar eficiência entre as estruturas.  

---

### 3️⃣ Parte 3: Gerenciador de Memória (Árvore 4-5)
- Simula alocação/dealocação de blocos de memória de 1MB.  
- Cada nó da árvore 4-5 armazena:  
  - Status (Livre/Ocupado)  
  - Bloco inicial/final  
  - Endereços de memória  
