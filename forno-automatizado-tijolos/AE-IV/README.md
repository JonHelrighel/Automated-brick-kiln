# AE-IV — Automação e Redes / Supervisório (2026/2 — em andamento)

## O que foi feito nesta etapa

Com o controle de temperatura já validado na AE-III, a AE-IV foca em **automação de redes e supervisório**: dar visibilidade remota ao processo por meio de um sistema SCADA simplificado, com banco de dados para histórico e uma IHM web para operação/monitoramento.

Principais atividades (em andamento):

1. **Modelagem do banco de dados** do forno (MySQL Workbench), armazenando dados de processo (temperatura, estado do ciclo, eventos).
2. **Máquina de estados do supervisório**, definindo os modos de operação do sistema (parado, aquecendo, patamar, resfriando, alarme, etc.).
3. **Desenvolvimento das telas da IHM** em HTML/JS, para visualização e controle do forno via navegador.
4. Planejamento de atividades e rubrica de avaliação da etapa.

## Estrutura da pasta

| Pasta/arquivo | Conteúdo |
|---|---|
| `Atividades de Extensão V_1 2026.docx` | Rascunho do relatório da etapa (estrutura de conclusão, sugestões de melhoria e documentos complementares) |
| ` AE4 - Tijolos Apr. Inicial_.pptx` | Apresentação inicial do semestre |
| `2026-2 - AE4 - Rubrica para Avaliação AE.xlsx` | Rubrica de avaliação da atividade, fornecida pela coordenação do curso |
| `Maquina de estados Supervisório.drawio` (+ `.png`) | Diagrama da máquina de estados do sistema supervisório |
| `Banco de Dados/` | Modelo do banco de dados do forno em MySQL Workbench: `banco_forno.mwb` (modelo atual) e `.mwb.bak` (backup) |
| `Programas-Codigos/Codigos Telas/` | Telas HTML da IHM web (ex.: `1_parametros.html`, `Tela_IHM.html`) para visualização/ajuste de parâmetros do processo |
| `supervisorio_sql_tarefas_Validar com o grupo.xlsx` | Planilha de tarefas do supervisório/SQL, para validação com o grupo |
| `Planejamento de Atividades/` | Planejamento do semestre e cópia da rubrica de avaliação |

## Status

Etapa em andamento no semestre 2026/2 — a documentação final e o relatório completo ainda serão produzidos ao longo do semestre.
