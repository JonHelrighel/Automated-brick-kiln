# AE-III — Instrumentação e Controle (2026/1)

## O que foi feito nesta etapa

Com o forno já construído fisicamente (AE-II), a AE-III foca em **instrumentar e controlar** a planta térmica: medir a temperatura de forma confiável, identificar o modelo dinâmico do forno e projetar/testar controladores automáticos (PI e PID) embarcados em um **ESP32**.

Principais atividades:

1. **Revisão do projeto informacional/conceitual** com foco em dinâmica de sistemas e controle.
2. **Instrumentação de temperatura**: termopar tipo K + placa de condicionamento de sinal (amplificação, filtro analógico passa-baixa) e conversão para leitura no ADC do ESP32.
3. **Identificação do sistema (Ensaios do forno)**: ensaios em malha aberta com diferentes níveis de potência (25%, 50%, 75%, 100%) para levantar a função de transferência do forno via MATLAB System Identification.
4. **Projeto de controladores PI e PID**, testados em malha fechada para diferentes referências de temperatura (150 °C, 300 °C, 600 °C) e perfis de rampa, com e sem filtro no sinal medido.
5. **Firmware do ESP32** (ESP-IDF, em C) implementando leitura do ADC, lógica de controle e acionamento das portas/motor.
6. **Peças mecânicas adicionais**: base/caixa e tampa do processador (impressas em 3D), sistema de fim de curso (chave/obstáculo) para detectar a posição da porta/carrinho.
7. **Projeto elétrico** completo no EPLAN (conjuntos "Controladora" e "Periféricos").
8. Relatório e apresentação da etapa, com sugestões de melhoria (filtro digital dedicado, isolação térmica melhor, alimentação trifásica para atingir a taxa de subida de 15 °C/min exigida).

## Estrutura da pasta

| Pasta/arquivo | Conteúdo |
|---|---|
| `AE3 Tijolos - Relatório.docx` / `AE3_Tijolos_VERSAO FINAL_.docx` | Relatório da etapa (versão de trabalho e versão final): introdução, objetivo geral, revisão de projeto, fundamentação teórica sobre sensores de temperatura, resultados dos ensaios de controle e sugestões de melhoria |
| `AE3 - Tijolos Apr. Inicial_.pptx` | Apresentação inicial do semestre |
| `código fim de curso.txt` | Anotações/código relacionado ao sistema de fim de curso (detecção de posição) |
| `divisor resistivo PI FORNO.psimsch` | Simulação PSIM do divisor resistivo usado no condicionamento do sinal do termopar |
| `Draw.IO (ESQUEMAS)/` | Diagramas: função global e desdobramentos da AE-III, e o **P&ID** completo do sistema (`P&ID AEIII` + PNG exportado) |
| `Projeto Elétrico/` | Projeto elétrico em EPLAN (`AE.eprj`), biblioteca de símbolos do ESP32 (`.elibz`) e PDFs dos conjuntos "Controladora" e "Periféricos" |
| `Projetos (PLANILHAS DOCS)/` | Checklist, projeto conceitual/informacional atualizados (`.xlsx`) e cronograma de prazos |
| `Impressões 3D (Arquivos STL)/` | Peça `ApoioIHM` (suporte da IHM), modelo nativo e STL para impressão |
| `Mecânica/` | Peças mecânicas da etapa: caixa/tampa/base do processador (com STL para impressão 3D e revisões), pontes H, e subpasta `Sistema do FimCurso/` (peça obstáculo + switch, usadas para detectar fim de curso da porta/carrinho) |
| `Programa de IOS ESP32/` | **Firmware do ESP32** — veja detalhamento abaixo |
| `ENSAIOS FORNO (25,50,75,100)/` | **Identificação do sistema**: ensaios em malha aberta a 25%, 50%, 75% e 100% de potência, com scripts MATLAB (`.m`), modelos identificados (`.mat`, `.slx`), gráficos e uma subpasta com o projeto de controlador PI/PID já filtrado |
| `ENSAIOS CONTROLE (TXT)/` | Dados brutos (`.txt`) dos ensaios em malha fechada: controle PI/PID para referências de 150 °C, 300 °C, 600 °C, com e sem filtro, além de rampa 50→150 °C e testes de termopar |
| `SUBIR PRO DRIVE ESSA PASTA/` | Projeto MATLAB do filtro digital do sinal do termopar (`Código Filtro Forno.m`) e workspace salvo (`.mat`), preparados para compartilhamento no Drive do grupo |

### `Programa de IOS ESP32/` — detalhamento do firmware

| Pasta | O que é |
|---|---|
| `main/` | **Código-fonte principal e mais atual** do firmware ESP-IDF: `main.c` + módulos `adc.c/h` (leitura do termopar), `controle.c/h` (lógica PI/PID), `controle_portas.c/h` (acionamento da porta/motor) e `temporizador.c/h` |
| `PROGRAMA ESP32AEIII/` | Cópia/versão paralela do mesmo firmware (mesma estrutura de `main/src`) |
| `testeESP/`, `Nova pasta/teste_forno/` | Projetos de teste do ESP-IDF — **as pastas `build/` geradas por esses projetos foram removidas** desta organização (artefatos de compilação, não código-fonte) |
| `sketch_mar27a/`, `ProgramaEsp_copy_20260320090435/` | Sketches Arduino (`.ino`) de testes pontuais/simulações |
| `Maquina de Estados Forno.drawio` | Diagrama da máquina de estados do firmware do forno |
| `DadosSimuladosEsp32.m` / `.txt`, `GraficoSimulado.jpg` | Dados e gráfico de uma simulação do comportamento do ESP32 |
| `Padronização de nomes.txt` | Convenção de nomes usada no código/projeto |
| `Untitled_0.CoolTermSettings`, `CurrentSession.CoolTermSession` | Configurações do terminal serial CoolTerm usado para monitorar a UART do ESP32 |

> ℹ️ **Nota:** os arquivos gerados por build do ESP-IDF (`build/`, `CMakeFiles/`, `esp-idf/`, bibliotecas `.a`, etc.) foram excluídos ao organizar este repositório — juntos ocupavam ~280 MB e podem ser 100% recriados a partir do código-fonte com `idf.py build`. Eles já estão listados no `.gitignore` da raiz.
