# Sistema Automatizado de Cozimento de Tijolos 🧱🔥

Repositório com o desenvolvimento completo do projeto de extensão do curso de **Engenharia de Controle e Automação**, cujo objetivo é projetar e construir um **forno elétrico automatizado** para a queima de tijolos cerâmicos, atendendo à demanda real da **Olaria Modesto** (Rio Grande do Sul).

O projeto é dividido em Atividades de Extensão (AE) semestrais — cada uma corresponde a uma fase do desenvolvimento do produto, seguindo a metodologia do livro *Projeto Integrado de Produtos* (BACK et al.): projeto informacional → conceitual → preliminar → detalhado → automação → retrofit.

> Este repositório é uma organização/documentação pessoal do meu projeto --> **[@JonHelrighel](https://github.com/JonHelrighel)**. O projeto é resultado de trabalho em grupo (autores abaixo) e também existe uma versão mantida por um dos colegas em [EduardoPaz01/AE-Tijolos](https://github.com/EduardoPaz01/AE-Tijolos).

## 👥 Equipe

- Eduardo Paz Putti
- João Emiliano Helrighel Freitas
- Gabriel Dettenborn
- Raian Lobato

**Curso:** Engenharia de Controle e Automação — Chapecó, SC, Brasil

## 🎯 Objetivo geral

Desenvolver e implementar um forno elétrico automatizado, capaz de atingir **até 1100 °C**, com:
- Controle automático de temperatura (malha fechada PI/PID);
- Carregamento e descarregamento automático dos tijolos (carrinho motorizado + porta guilhotina);
- Instrumentação com termopar tipo K e condicionamento de sinal;
- Supervisório (SCADA) com banco de dados e IHM para monitoramento remoto.

## 🗺️ Linha do tempo do projeto (visão geral por AE)

| Etapa | Semestre | Foco | Principais entregas |
|---|---|---|---|
| **[AE-I](./AE-I)** | 5º sem. – 2025/1 | Projeto de Produto (informacional, conceitual, preliminar) | Carta de demanda, fundamentação teórica, dimensionamentos iniciais, modelagem 3D preliminar (CAD) |
| **[AE-II](./AE-II)** | 6º sem. – 2025/2 | Mecânica e Elétrica (construção física) | Projeto mecânico detalhado, fabricação/montagem real do forno, painel elétrico, primeiros ensaios térmicos (dez/2025) |
| **[AE-III](./AE-III)** | 2026/1 | Instrumentação e Controle | Condicionamento de sinal do termopar, identificação do sistema, controladores PI/PID, firmware ESP32, ensaios de malha fechada |
| **[AE-IV](./AE-IV)** | 2026/2 (em andamento) | Automação e Redes / Supervisório | Banco de dados (MySQL), telas de IHM web (HTML), máquina de estados do supervisório |
| **AE-V** | Próximo semestre | Retrofit | Ainda não iniciado |

Cada pasta `AE-*` tem seu próprio `README.md` detalhando o que foi feito naquela etapa e explicando os arquivos/subpastas.

## 🧱 Contexto do problema

A Olaria Modesto fabrica tijolos maciços e furados em fornos a carvão com controle térmico manual e limitado, o que gera perda de peças por queima irregular, baixa agilidade no carregamento/descarregamento e alto consumo de combustível. A proposta do grupo é substituir esse processo por um **forno elétrico automatizado**, com controle preciso de temperatura e movimentação automática das peças — reduzindo perdas e padronizando a qualidade da queima.

## 🛠️ Stack / ferramentas utilizadas ao longo do projeto

- **CAD / Modelagem 3D:** SolidWorks (`.SLDPRT`, `.SLDASM`, `.SLDDRW`), exportações em `.STL` para impressão 3D
- **Simulação de circuitos:** PSIM (`.psimsch`)
- **Simulação de sistemas de controle:** MATLAB/Simulink (`.m`, `.mat`, `.slx`)
- **Diagramas (P&ID, função global, máquina de estados):** draw.io (`.drawio`)
- **Firmware:** ESP32 com ESP-IDF (C) e Arduino (`.ino`)
- **Elétrica:** EPLAN Electric P8 (`.eprj`)
- **Banco de dados:** MySQL Workbench (`.mwb`)
- **Supervisório / IHM:** HTML/JS
- **Documentação:** relatórios em `.docx`, planilhas de projeto em `.xlsx`, apresentações em `.pptx`

## 📁 Estrutura do repositório

```
.
├── AE-I/     → Projeto de produto (informacional, conceitual, preliminar)
├── AE-II/    → Projeto mecânico/elétrico detalhado + construção física
├── AE-III/   → Instrumentação, controle e firmware
├── AE-IV/    → Supervisório, banco de dados e automação de redes
├── AE-V/     → Retrofit (ainda não iniciado)
└── Referências/ → Material de apoio de disciplinas anteriores
```

## ⚠️ Nota sobre arquivos grandes

Este repositório contém arquivos de CAD (`.SLDPRT`, `.SLDASM`, `.STL`), imagens e relatórios que juntos somam algumas centenas de MB. Nenhum arquivo individual ultrapassa o limite de 100 MB do GitHub, mas para repositórios que crescerão mais (novos ensaios, mais fotos, etc.) utilizou-se **Git LFS** para os arquivos de CAD/binários. 
