# AE-I — Projeto de Produto (5º semestre – 2025/1)

## O que foi feito nesta etapa

A AE-I é a fase inicial do projeto, focada na **concepção e documentação técnica** do forno automatizado, antes de qualquer construção física. Seguindo a metodologia de *Projeto Integrado de Produtos* (BACK et al.), o grupo percorreu:

1. **Carta de demanda** — levantamento da necessidade real da Olaria Modesto (RS): dificuldade no carregamento/descarregamento manual de tijolos e ausência de controle preciso de temperatura em fornos a carvão.
2. **Projeto informacional** — fundamentação teórica (histórico do tijolo, processo de fabricação cerâmica, estudo de caso da Cerâmica Pallotti) e definição dos requisitos do produto.
3. **Projeto conceitual** — geração e seleção de concepções para a solução (estrutura do forno, sistema de movimentação, IHM, painel elétrico).
4. **Projeto preliminar (1 e 2)** — primeiras modelagens 3D e dimensionamentos (corrente, motor, tijolos) para validar as concepções escolhidas.
5. Apresentações intermediária e final do semestre.

## Estrutura da pasta

| Pasta/arquivo | Conteúdo |
|---|---|
| `AE1 Tijolos - Carta de demanda/` | PDF com a carta de demanda de soluções tecnológicas da Olaria Modesto |
| `AE1 Tijolos - MPP.docx` | Relatório principal (Metodologia de Projeto de Produto): introdução, demanda, fundamentação teórica, projeto informacional/conceitual e referências |
| `AE1 Tijolos - Rascunho Manual.docx` | Rascunho/anotações manuscritas digitalizadas do desenvolvimento do relatório |
| `AE1 Tijolos - Projeto Informacional.xlsx` | Planilha com requisitos e especificações do produto |
| `AE1 Tijolos - Projeto Concentual.xlsx` | Planilha de geração/avaliação de concepções (matriz de decisão) |
| `AE1 Tijolos - Funcao Global e Desdobramentos.drawio` | Diagrama da função global do sistema e seus desdobramentos (entradas/saídas/subsistemas) |
| `AE1 Tijolos - Dimensionamentos/` | Cálculos de dimensionamento em SMath (`.sm`): corrente de transmissão, motor e tijolos |
| `AE1 Tijolos- Projeto Preliminar 1/` | Primeira rodada de modelagem 3D preliminar, organizada por subsistema: `CARRINHO`, `FORNO`, `IHM`, `MESA DE APOIO PRO FORNO`, `MOTOR`, `MOVIMENTAÇÃO DO CARRINHO`, `OUTRAS...` (catálogos de peças comerciais), `PAINEL ELÉTRICO`, `PORTA FORNO`, `TRILHO` |
| `AE1 Tijolos - Projeto Preliminar 2/` | Segunda rodada de projeto preliminar, refinando a modelagem anterior |
| `Montagens/` | Conjuntos montados em SolidWorks (`.SLDASM`) com desenhos técnicos (`.SLDDRW`) e PDFs exportados (ex.: `CT-00-00-XX`, `ESP_00_00_XX`) |
| `Peças/` | Peças individuais modeladas em SolidWorks (`.SLDPRT`), com desenho técnico e PDF de cada peça (nomenclatura por conjunto: `CSS`, `CT`, `ENG`, `ESP`, `ETI`, `MC`, `SPM`) |
| `AE1 Tijolos - Apr. Inicial (30-04).pptx` | Apresentação de meio de semestre |
| `AE1 Tijolos - Apr.  Festa Junina.pptx` | Apresentação em evento intermediário (Festa Junina) |
| `AE1 Tijolos - Apr. Final (16-07).pptx` | Apresentação final da AE-I |

## Convenção de nomenclatura das peças

As peças/conjuntos seguem códigos por subsistema, por exemplo:
- `CT` — Carrinho
- `ESP` — Espelho / estrutura
- `CSS`, `ENG`, `ETI`, `MC`, `SPM` — demais componentes e subconjuntos mecânicos

Cada código de peça possui até 3 arquivos irmãos: `.SLDPRT`/`.SLDASM` (modelo nativo do SolidWorks), `.SLDDRW` (desenho técnico) e `.PDF` (exportação para consulta sem precisar do SolidWorks instalado).
