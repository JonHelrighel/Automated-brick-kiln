# AE-II — Mecânica e Elétrica (6º semestre – 2025/2)

## O que foi feito nesta etapa

A AE-II é a fase de **construção física** do protótipo: o grupo saiu da modelagem 3D e partiu para a fabricação e montagem real do forno, do carrinho, da porta e do painel elétrico, além de revisar o projeto mecânico com base nas dificuldades encontradas na oficina.

Principais atividades:

1. **Revisão do projeto mecânico** (pasta `REVISAO`), incorporando ajustes descobertos durante a fabricação (ex.: adição de um novo subsistema `TAMBOR`, não previsto na AE-I).
2. **Dimensionamento das resistências elétricas** e do circuito de acionamento (simulação em PSIM).
3. **Fabricação e montagem física**, documentada dia a dia em fotos (pasta `AE2 - imagens relatório`, com uma subpasta por data de setembro a dezembro de 2025): corte e soldagem das chapas, montagem da caixa do forno, instalação da porta e isolamento térmico, montagem do painel elétrico, etc.
4. **Primeiros ensaios térmicos do protótipo montado**, em dezembro de 2025. No primeiro acionamento (17/12/2025) a temperatura atingida foi de aproximadamente 170 °C, evidenciando vazamentos térmicos que motivaram melhorias no isolamento.
5. **Descrição do P&ID** (diagrama de tubulação e instrumentação) do sistema.
6. Checklist de entregas e relatório final da etapa.

## Estrutura da pasta

| Pasta/arquivo | Conteúdo |
|---|---|
| `AE2 Tijolos - Relatório final.docx` | Relatório completo da etapa: introdução, demanda, justificativa, fundamentação teórica (termopar tipo K, transmissor HT-010, ponte H, etc.), resultados dos primeiros ensaios térmicos e conclusão |
| `AE2 - Tijlos Checklist.xlsx` | Checklist de itens/entregas da atividade |
| `AE2 - Tijolos Apr. Inicial (14-08).pptx` | Apresentação inicial do semestre |
| `P&ID descrição.xlsx` | Descrição textual do diagrama P&ID do sistema (instrumentos, malhas de controle, tubulação/fiação) |
| `AE2 - Tijolos Dimensionamentos/` | `AE2 - Esquema elétrico.psimsch` (simulação PSIM do circuito de acionamento das resistências) e `dimensionamento resistencias.sm` (cálculo de potência/dimensionamento das resistências de aquecimento) |
| `AE2 - Tijolos Projeto mecânico/` | Modelagem mecânica "como projetado" antes das correções de fabricação, organizada por subsistema: `CARRINHO`, `FORNO`, `IHM`, `MESA DE APOIO PRO FORNO`, `MOTOR`, `MOVIMENTAÇÃO DO CARRINHO`, `PAINEL ELÉTRICO`, `PORTA FORNO`, `TRILHO` |
| `REVISAO - AE2 - Tijolos Projeto mecânico/` | Versão **revisada** do projeto mecânico após ajustes de fabricação — mesmos subsistemas da pasta anterior, mais o novo subsistema `TAMBOR` |
| `AE2 - imagens relatório/` | **Diário fotográfico da montagem**, com uma pasta por data (de `set - 25 de setembro` até `dez - 18 de dezembro`), registrando cada etapa da fabricação: corte/solda das chapas, montagem da caixa e da porta, isolamento térmico, fabricação de eixos, montagem do painel elétrico e testes iniciais do forno já carregado |

## Linha do tempo da construção (pelas fotos)

- **Set/2025:** corte de chapas, soldagem da caixa do forno, isolamento das portas
- **Out/2025:** furação dos trilhos, montagem dos suportes da porta, fabricação de eixos, montagem da caixa do painel elétrico
- **Nov/2025:** porta soldada com dobradiça, corte de tijolos para teste, recepção dos tijolos de teste
- **Dez/2025:** apresentação do forno montado, forno carregado no carrinho, painel com fonte e contactora, ajustes finais e reposicionamento de suportes — **primeiros ensaios térmicos**
