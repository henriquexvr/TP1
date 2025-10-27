# 📊 TP1 - Vector Normalization with SIMD Optimization

**Trabalho Prático 1** - Disciplina de Arquitetura de Computadores  
Comparação de desempenho de diferentes técnicas de normalização vetorial em C com otimizações SIMD.

---

## 📝 Descrição do Projeto

Este projeto implementa três versões diferentes do algoritmo de **normalização vetorial** (L2-norm), cada uma com diferentes níveis de otimização:

1. **Baseline**: Implementação pura em C com normalização padrão
2. **Quake**: Otimização com o famoso algoritmo "Fast Inverse Square Root" do Quake III
3. **SSE/NEON**: Otimização com instruções SIMD (SSE para x86-64, NEON para ARM)

O objetivo é medir e comparar o desempenho (tempo de execução, uso de CPU e memória) de cada versão em diferentes tamanhos de dataset.

---

## 🏗️ Arquitetura do Projeto

```
TP1/
├── src/                          # Código fonte C
│   ├── main.c                    # Programa principal (entrada e medição)
│   ├── csvReader.c               # Leitor de arquivos CSV
│   ├── normalizeBaseline.c       # Versão baseline
│   ├── normalizeQuake.c          # Versão Quake (Fast Inverse Sqrt)
│   ├── normalizeSse.c            # Versão SSE (x86-64)
│   └── normalizeSseArm.c         # Versão NEON (ARM) [opcional]
│
├── tests/                        # Dados de teste
│   ├── sample_data.csv           # Pequeno exemplo (3x3)
│   ├── data_1000x3.csv           # 1000 vetores de dimensão 3
│   ├── data_1000x10.csv          # 1000 vetores de dimensão 10
│   └── data_1000x100.csv         # 1000 vetores de dimensão 100
│
├── scripts/                      # Scripts de utilitários
│   ├── geracaoDeDados.py         # Gerador de datasets aleatórios
│   └── runExperiments.sh         # Script para rodar todos os experimentos
│
├── results/                      # Resultados dos experimentos
│   └── metrics.csv               # Métricas de desempenho
│
├── Makefile                      # Compilação (Unix-like)
├── CMakeLists.txt                # Build alternativo com CMake
└── README.md                     # Este arquivo
```

---

## 🚀 Como Compilar e Executar

### Opção 1: Makefile Simples (macOS/Linux)

```bash
# Compilar
make

# Executar uma versão específica
./normalize tests/sample_data.csv baseline
./normalize tests/sample_data.csv quake
./normalize tests/sample_data.csv sse

# Limpar binários
make clean
```

### Opção 2: CMake (Recomendado - Multiplataforma)

```bash
# Criar diretório de build
mkdir -p build && cd build

# Gerar arquivos de compilação (detecta arquitetura automaticamente)
cmake ..

# Compilar
cmake --build .

# Executar
./normalize ../tests/sample_data.csv baseline
```

### Opção 3: Compilação Manual

```bash
gcc -O3 -Wall -Wextra -o normalize src/main.c src/csvReader.c \
    src/normalizeBaseline.c src/normalizeQuake.c src/normalizeSse.c -lm
```

---

## 🔧 Parâmetros de Entrada

```
./normalize <arquivo.csv> <versao>

Argumentos:
  arquivo.csv    Caminho para arquivo CSV com dados (formato: valores separados por vírgula)
  versao         Uma de: baseline | quake | sse

Exemplo:
  ./normalize tests/data_1000x10.csv sse
```

---

## 📊 Formato de Saída

O programa exibe métricas de desempenho em formato CSV:

```
version,N,D,wall,user,sys,memoryKB
baseline,1000,3,0.001234,0.001200,0.000050,2048
quake,1000,3,0.000987,0.000950,0.000040,2048
sse,1000,3,0.000567,0.000540,0.000030,2048
```

**Campos:**
- `version`: Versão do algoritmo usado
- `N`: Número de vetores no dataset
- `D`: Dimensão de cada vetor
- `wall`: Tempo de parede (wall-clock time) em segundos
- `user`: Tempo de CPU em modo usuário (segundos)
- `sys`: Tempo de CPU em modo sistema (segundos)
- `memoryKB`: Uso máximo de memória em KB

---

## 🧪 Executar Experimentos Completos

O script `runExperiments.sh` executa todas as versões em diferentes datasets:

```bash
# Compilar primeiro
make

# Rodar todos os experimentos
bash scripts/runExperiments.sh

# Resultados serão salvos em results/metrics.csv
cat results/metrics.csv
```

---

## 📈 Gerar Dados de Teste

Use o script Python para gerar datasets customizados:

```bash
# Gerar 5000 vetores de dimensão 50
python3 scripts/geracaoDeDados.py 5000 50

# Isso cria: tests/data_5000x50.csv
```

**Requisitos:**
- Python 3
- NumPy

---

## ⚙️ Compatibilidade de Arquitetura

### ⚠️ Problema Atual

Este projeto tem **limitações de compatibilidade de arquitetura**:

- **SSE** (Streaming SIMD Extensions): ✅ Funciona apenas em **x86-64**
- **NEON** (Advanced SIMD): ❌ Necessário para **ARM64** (Apple Silicon, etc.)

| Arquitetura | Status | Arquivo |
|-------------|--------|---------|
| x86-64 (Intel/AMD) | ✅ Compilado | `normalizeSse.c` |
| ARM64 (Apple M1/M2) | ⚠️ Fallback | `normalizeQuake.c` apenas |
| WSL (Linux x86-64) | ✅ Compilado | `normalizeSse.c` |

### 🔧 Solução: Versão ARM com NEON

Se compilar em ARM (ex: macOS em Macbook Air M1/M2), use CMake que detecta a arquitetura automaticamente:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

O CMake detectará se é ARM ou x86-64 e compilará a versão otimizada apropriada.

---

## 📚 Descrição dos Algoritmos

### 1. Baseline
Implementação pura em C da normalização L2:
```c
norm = sqrt(sum of v[i]²)
v[i] = v[i] / norm
```

### 2. Quake Fast Inverse Square Root
Usa o famoso "hack" do Quake III para calcular a raiz quadrada inversa rapidamente:
```c
y = fastInvSqrt(sum)
v[i] = v[i] * y
```

### 3. SSE (x86-64) / NEON (ARM)
Otimização com instruções SIMD de ponto flutuante para cálculo paralelo:
- **SSE**: `_mm_rsqrt_ss()` - raiz quadrada inversa usando instrução SIMD
- **NEON**: `vrsqrte_f32()` - equivalente em ARM

---

## 💡 Notas Importantes

- ⚠️ **O flag `-march=native` foi removido** para compatibilidade entre x86 e ARM
- 📊 Use datasets grandes (como `data_1000x100.csv`) para observar diferenças de desempenho
- 🔬 As métricas refletem **operações puras de normalização** sem I/O de arquivo
- 🖥️ Os tempos variam significativamente entre máquinas diferentes

---

## 👥 Autores

Desenvolvido como trabalho prático para a disciplina de **Arquitetura de Computadores** na PUC.

---

## 📖 Referências

- [SIMD: SSE Intrinsics](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
- [ARM NEON Intrinsics](https://developer.arm.com/architectures/instruction-sets/intrinsics/)
- [Quake III Fast Inverse Square Root](https://en.wikipedia.org/wiki/Fast_inverse_square_root)
- [L2 Normalization](https://en.wikipedia.org/wiki/Norm_(mathematics)#Euclidean_norm)
