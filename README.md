<svg xmlns="http://w3.org" viewBox="0 0 1000 800" width="100%" height="100%">
  <defs>
    <style>
      .title { font-family: sans-serif; font-size: 18px; font-weight: bold; fill: #111; text-anchor: middle; }
      .node-text { font-family: sans-serif; font-size: 11px; font-weight: bold; fill: #222; text-anchor: middle; }
      .label-text { font-family: sans-serif; font-size: 10px; fill: #ff0000; font-weight: bold; }
      .arrow { stroke: #333; stroke-width: 2; fill: none; }
    </style>
    <marker id="arrow" viewBox="0 0 10 10" refX="5" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M 0 1 L 10 5 L 0 9 z" fill="#333"/>
    </marker>
  </defs>

  <text x="500" y="35" class="title">3. FLUXOGRAMA GERAL DE EXECUÇÃO (LÓGICA DO CÓDIGO)</text>

  <!-- Início -->
  <ellipse cx="500" cy="80" rx="60" ry="25" fill="#d9e1f2" stroke="#418ab3" stroke-width="2"/>
  <text x="500" y="84" class="node-text">INÍCIO (main)</text>
  <path d="M 500 105 L 500 140" class="arrow" marker-end="url(#arrow)"/>

  <!-- Parse Options -->
  <rect x="400" y="140" width="200" height="40" fill="#fff2cc" stroke="#d6b656" stroke-width="2"/>
  <text x="500" y="164" class="node-text">Analisar Opções (parse_options)</text>
  <path d="M 500 180 L 500 210" class="arrow" marker-end="url(#arrow)"/>

  <!-- Decisão: Opção Válida? -->
  <polygon points="500,210 580,245 500,280 420,245" fill="#fce4d6" stroke="#c65911" stroke-width="2"/>
  <text x="500" y="249" class="node-text">Opção Válida?</text>
  
  <!-- Ramificação Não (Erro) -->
  <path d="M 420 245 L 300 245 L 300 290" class="arrow" marker-end="url(#arrow)"/>
  <text x="340" y="240" class="label-text">NÃO</text>
  <rect x="220" y="290" width="160" height="40" fill="#f8cecc" stroke="#b85450" stroke-width="2"/>
  <text x="300" y="314" class="node-text" fill="#b85450">Exibir "Error" e Encerra</text>

  <!-- Ramificação Sim (Segue fluxo) -->
  <path d="M 580 245 L 700 245 L 700 290" class="arrow" marker-end="url(#arrow)"/>
  <text x="630" y="240" class="label-text" fill="#385723">SIM</text>
  
  <!-- Validar Argumentos -->
  <rect x="600" y="290" width="200" height="40" fill="#fff2cc" stroke="#d6b656" stroke-width="2"/>
  <text x="700" y="314" class="node-text">ft_parse_args (Validar)</text>
  <path d="M 700 330 L 700 360 L 500 360 L 500 390" class="arrow" marker-end="url(#arrow)"/>

  <!-- Inicializar Pilha e Medir Desordem -->
  <rect x="400" y="390" width="200" height="40" fill="#e2f0d9" stroke="#385723" stroke-width="2"/>
  <text x="500" y="414" class="node-text">Criar Pilha A + Calcular Desordem</text>
  <path d="M 500 430 L 500 460" class="arrow" marker-end="url(#arrow)"/>

  <!-- Decisão de Algoritmo Baseado no tamanho de N (Estratégia) -->
  <rect x="350" y="460" width="300" height="40" fill="#deebf7" stroke="#2f5597" stroke-width="2"/>
  <text x="500" y="484" class="node-text">Escolher Estratégia e Ordenar (select_and_sort)</text>

  <!-- Linha de Distribuição dos Algoritmos -->
  <path d="M 500 500 L 500 530" class="arrow"/>
  <line x1="150" y1="530" x2="850" y2="530" stroke="#333" stroke-width="2"/>

  <!-- Setas apontando para as 3 Estratégias -->
  <path d="M 150 530 L 150 560" class="arrow" marker-end="url(#arrow)"/>
  <path d="M 500 530 L 500 560" class="arrow" marker-end="url(#arrow)"/>
  <path d="M 850 530 L 850 560" class="arrow" marker-end="url(#arrow)"/>

  <!-- 1. MODO SIMPLE -->
  <rect x="50" y="560" width="200" height="60" rx="4" fill="#f5f5f5" stroke="#7f7f7f" stroke-width="2"/>
  <text x="150" y="585" class="node-text" fill="#c00000">MODO SIMPLE (N &lt;= 5)</text>
  <text x="150" y="600" font-family="sans-serif" font-size: 10px; text-anchor: middle;">Algoritmo: sort_n2()</text>

  <!-- 2. MODO MEDIUM -->
  <rect x="400" y="560" width="200" height="60" rx="4" fill="#f5f5f5" stroke="#7f7f7f" stroke-width="2"/>
  <text x="500" y="585" class="node-text" fill="#ed7d31">MODO MEDIUM (N &lt;= 100)</text>
  <text x="500" y="600" font-family="sans-serif" font-size: 10px; text-anchor: middle;">Algoritmo: sort_chunk()</text>

  <!-- 3. MODO COMPLEX -->
  <rect x="750" y="560" width="200" height="60" rx="4" fill="#f5f5f5" stroke="#7f7f7f" stroke-width="2"/>
  <text x="850" y="585" class="node-text" fill="#0070c0">MODO COMPLEX (N &gt; 100)</text>
  <text x="850" y="600" font-family="sans-serif" font-size: 10px; text-anchor: middle;">Algoritmo: sort_radix()</text>

  <!-- FIM convergência -->
  <path d="M 150 620 L 150 670 L 500 670" class="arrow"/>
  <path d="M 500 620 L 500 670" class="arrow"/>
  <path d="M 850 620 L 850 670 L 500 670" class="arrow" marker-end="url(#arrow)"/>

  <ellipse cx="500" cy="710" rx="60" ry="25" fill="#d9e1f2" stroke="#418ab3" stroke-width="2"/>
  <text x="500" y="714" class="node-text">FIM (Limpar e Sair)</text>
</svg>
