# Sistema de Cadastro de Relatos de Catástrofes Naturais

Este projeto é uma aplicação de linha de comando desenvolvida em **linguagem C**, que permite o **cadastro, listagem e filtragem de relatos sobre desastres naturais** ocorridos em um raio de até 10 km a partir de uma localização informada. O sistema também armazena os dados em um arquivo `.txt` para persistência entre execuções.


Alunos: 
- João Vitor Lima Caldeira  RM: 566541

- Giovanna Fernandes Pereira  RM: 565434
---

##  Funcionalidades

-  Cadastro de relatos com dados completos da pessoa que registrou.
-  Validação básica de entradas.
-  Cálculo da distância geográfica entre pontos (fórmula de Haversine).
-  Filtro de relatos dentro de um raio de 10 km.
-  Listagem completa dos relatos.
-  Ordenação por data dos relatos.
-  Salvamento e carregamento automático dos relatos em arquivo `.txt`.

---

##  Tecnologias e conceitos aplicados

- `struct`: Representação de entidades como `Pessoa` e `Relato`.
- `vetores`: Armazenamento dinâmico dos relatos em memória.
- `algoritmos de busca e ordenação`: Implementado com `qsort` por data.
- `validação`: Verificação básica de campos com `fgets`, `strcspn`.
- `cálculo de distância`: Utilização da fórmula de Haversine.
- `persistência`: Gravação e leitura de dados em arquivo `.txt`.
  
---

##  Exemplo de uso

### Menu principal:

```
=== MENU ===
1. Cadastrar relato
2. Listar relatos
3. Filtrar por distância (10 km)
4. Ordenar por data
5. Salvar e sair
Escolha:
```

### Cadastro de relato:

```
Nome: João da Silva
CPF: 12345678900
Telefone: (11)99999-9999
Email: joao@gmail.com
Tipo de desastre: Enchente
Data (DD/MM/AAAA): 24/05/2025
Latitude: -23.5505
Longitude: -46.6333
Relato cadastrado com sucesso!
```

### Filtrar relatos por distância:

```
Digite sua latitude: -23.5500
Digite sua longitude: -46.6300

Relatos num raio de 10 km:

Nome: João da Silva
Tipo: Enchente
Distância: 0.40 km
```

---

##  Estrutura do arquivo `relatos.txt`

Cada linha do arquivo contém os dados de um relato, no seguinte formato:

```txt
João da Silva|12345678900|(11)99999-9999|joao@gmail.com|Enchente|24/05/2025|-23.5505|-46.6333
```

---

##  Limitações e melhorias possíveis

- Validação de CPF, email e data pode ser mais robusta.
- Adicionar ordenações por nome ou tipo de desastre.
- Interface gráfica ou Web futura (ex: em Python ou JavaScript).
- Internacionalização de mensagens.

