# Otimização Multiobjetiva para o Problema de Distritamento Capacitado

Este repositório contém a implementação de uma variante do algoritmo NSGA-II (Non-dominated Sorting Genetic Algorithm II) combinada com um Algoritmo Genético (GA) de um único objetivo para resolver o **Problema de Distritamento Capacitado (CDP)**. 

## 📚 Contexto Acadêmico

Este projeto foi desenvolvido para a disciplina **Otimização Multiobjetiva 2024-2** do Programa de Pós-Graduação em Ciência da Computação (PGC-UFF) sob a orientação do Prof. Dr. Igor Machado Coelho.

## 🔍 Objetivos

- Implementar uma variante do NSGA-II com uma população hierarquicamente estruturada.
- Integrar um GA de um único objetivo para melhorar a geração e evolução das soluções iniciais.
- Aplicar a abordagem combinada para resolver o Problema de Distritamento Capacitado, otimizando compacidade e homogeneidade dos distritos.

## 📁 Estrutura do Repositório

- `src/`: Código-fonte do algoritmo.
- `data/`: Conjuntos de dados utilizados nas instâncias T1, T4 e T7.
- `results/`: Resultados dos experimentos, incluindo gráficos de Pareto e visualizações geográficas.
- `docs/`: Documentação adicional e relatórios.

## 🛠️ Instalação

1. **Clone o repositório:**
    ```bash
    git clone https://github.com/augustompm/PACGAMP.git
    ```

## 🚀 Como Usar

**Preparação dos Dados:**
    - Coloque as instâncias de teste (T1, T4, T7) ou gere instâncias similares na pasta `data/`.

**Visualização dos Resultados:**
    - Os gráficos de Pareto e visualizações geográficas serão salvos na pasta `results/` correspondente a cada instância.

## 📈 Resultados

Os resultados incluem:

- **Curvas de Pareto:** Representam as fronteiras de Pareto para cada instância, destacando as soluções não dominadas.
- **Visualizações Geográficas:** Mostram a distribuição espacial dos distritos definidos para cada instância.

## 📝 Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests para melhorias e sugestões.

## 📧 Contato

- **Aluno:** Augusto Magalhães Pinto de Mendonça  
  Email: [augustompm@id.uff.br](mailto:augustompm@id.uff.br)

- **Orientador:** Prof. Dr. Igor Machado Coelho  

## 📜 Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

