# Trabalho de Otimização (LP Solve)

Projeto em C para montar automaticamente um modelo de Programação Linear no formato `.lp`, compatível com `lp_solve`.

## Objetivo

Gerar um arquivo `saida.lp` a partir de dados de entrada sobre:

- componentes nutricionais;
- tipos de comprimidos;
- preços dos comprimidos;
- limites opcionais de alguns componentes.

O modelo gerado tenta minimizar o custo total dos comprimidos respeitando as restrições.

---

## Estrutura do projeto

- `trab.c`: código-fonte principal.
- `trab`: executável (quando compilado).
- `saida.lp`: modelo LP gerado na execução.
- `codigo.html`: documentação visual do formato LP + simulador didático.
- `readme.md`: este arquivo.

---

## Como compilar

Use GCC:

```bash
gcc trab.c -o trab
```

---

## Como executar

```bash
./trab
```

O programa lê os dados via entrada padrão (`stdin`) e gera o arquivo `saida.lp`.

---

## Formato esperado de entrada (resumo)

1. `c p`
   - `c`: quantidade de componentes
   - `p`: quantidade de tipos de comprimidos

2. `c` inteiros com as necessidades diárias de cada componente:
   - `q1 q2 ... qc`

3. Dados dos comprimidos:
   - total de `p * (c + 1)` inteiros
   - para cada comprimido: `c` valores de componentes + `1` valor de preço

4. `k` (quantidade de restrições de limite)

5. Pares `<componente, limite>` para os limites informados.

> Observação: o código está em desenvolvimento e pode exigir ajustes em indexação/leitura para alguns casos.

---

## Saída gerada

O arquivo `saida.lp` contém:

- função objetivo (`min:`);
- restrições de necessidade diária de componentes (`>=`);
- restrições de limite de componentes (`<=`);
- declaração de variáveis inteiras (`int x1, x2, ...`).

---

## Exemplo rápido de fluxo

1. Compilar:

```bash
gcc trab.c -o trab
```

2. Executar e informar os dados quando solicitado.

3. Abrir o `saida.lp` gerado e validar no `lp_solve`.

---

## Referência

Para regras detalhadas do formato LP (`lp_solve`), consulte a documentação resumida e formatada em `codigo.html`.
