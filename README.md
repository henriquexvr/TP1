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

### ⚡ Quick Start (Recomendado)

#### macOS / Linux
```bash
# Clonar ou entrar no diretório do projeto
cd TP1

# Compilar usando script
bash build.sh

# Executar
./build/normalize tests/sample_data.csv baseline
./build/normalize tests/data_1000x10.csv sse
```

#### Windows (PowerShell ou CMD)
```cmd
# Compilar usando script
build.bat

# Executar
build\Release\normalize.exe tests\sample_data.csv baseline
build\Release\normalize.exe tests\data_1000x10.csv sse
```

---

### Opção 1: Makefile Wrapper (Unix-like)

O projeto inclui um Makefile que funciona como wrapper para o CMake:

```bash
# Compilar
make build

# Limpar
make clean

# Ver opções
make help
```

---

### Opção 2: CMake Manual (Todas as Plataformas)

#### Setup inicial (qualquer SO)
```bash
# Criar diretório de build
mkdir build
cd build

# Configurar o projeto (detecta arquitetura automaticamente!)
cmake -DCMAKE_BUILD_TYPE=Release ..
```

#### Compilar

**Linux/macOS:**
```bash
cmake --build . --config Release
```

**Windows (Visual Studio):**
```cmd
cmake --build . --config Release
```

#### Executar
```bash
# Linux/macOS
./normalize ../tests/sample_data.csv baseline

# Windows
Release\normalize.exe ..\tests\sample_data.csv baseline
```

---

### Opção 3: Compilação Manual com GCC (Apenas x86-64)

```bash
gcc -O3 -Wall -Wextra -o normalize src/main.c src/csvReader.c \
    src/normalizeBaseline.c src/normalizeQuake.c src/normalizeSse.c -lm
```

---

## 📊 Exemplos de Uso Completo

### Exemplo 1: Testar uma versão em dados pequenos

```bash
# Compilar
bash build.sh

# Rodar baseline
./build/normalize tests/sample_data.csv baseline
# Output: baseline,3,3,0.000001,0.000001,0.000000,2048

# Rodar Quake
./build/normalize tests/sample_data.csv quake
# Output: quake,3,3,0.000001,0.000001,0.000000,2048

# Rodar SIMD (SSE em x86, NEON em ARM)
./build/normalize tests/sample_data.csv sse
# Output: sse,3,3,0.000001,0.000001,0.000000,2048
```

### Exemplo 2: Comparar desempenho com dados maiores

```bash
bash build.sh

# Executar com 1000 vetores de 100 dimensões
./build/normalize tests/data_1000x100.csv baseline
./build/normalize tests/data_1000x100.csv quake
./build/normalize tests/data_1000x100.csv sse
```

### Exemplo 3: Rodar experimentos automaticamente

```bash
bash build.sh

# Gerar dados de teste (opcional)
python3 scripts/geracaoDeDados.py 1000 50

# Rodar experimentos (Linux/macOS)
bash scripts/runExperiments.sh
```

---

## 🧪 Gerar Dados Customizados

Use o script Python para criar datasets de teste com tamanhos diferentes:

```bash
# Gerar 5000 vetores de dimensão 50
python3 scripts/geracaoDeDados.py 5000 50

# Resultado: tests/data_5000x50.csv
```

**Requisitos:**
```bash
pip install numpy
# ou
apt install python3-numpy  # Linux
brew install numpy         # macOS
```

---

## 🏗️ Como o CMake Detecta Arquitetura

O CMake detecta automaticamente a arquitetura do seu processador e compila a versão otimizada apropriada:

### x86-64 (Intel/AMD)
```
CMake detects: x86_64
Compiles: src/normalizeSse.c (SSE intrinsics)
Flags: -msse -O3
```

### ARM (Apple M1/M2, Raspberry Pi)
```
CMake detects: aarch64 / arm
Compiles: src/normalizeSseArm.c (NEON intrinsics)
Flags: -march=armv8-a+simd -O3
```

### Arquitetura Desconhecida
```
Falls back to: normalizeQuake.c (sem SIMD)
Warning: "Unknown architecture"
```

---

## 🔧 Troubleshooting

### ❌ "cmake: command not found"

**Solução:** Instalar CMake

```bash
# macOS
brew install cmake

# Ubuntu/Debian
sudo apt install cmake

# Fedora/RHEL
sudo yum install cmake

# Windows
# Baixar de: https://cmake.org/download/
```

### ❌ "No compiler found"

**Linux/macOS:**
```bash
# Instalar GCC/Clang
# macOS
xcode-select --install

# Ubuntu
sudo apt install build-essential

# Fedora
sudo yum install gcc
```

**Windows:**
- Instalar Visual Studio Community Edition
- Ou: `choco install mingw` (se usar Chocolatey)

### ❌ NEON não disponível (ARM)

Se receber erro compilando em ARM:
```bash
# Certificar-se que está compilando com flags NEON
cmake -DCMAKE_BUILD_TYPE=Release ..

# Ou manualmente
gcc -march=armv8-a+simd -O3 ...
```

### ❌ Aviso "CRLF will be replaced by LF"

Isso é normal no Windows. Apenas gitignore.

```bash
git config core.safecrlf false
```

---

## 📋 Checklist de Compilação Bem-Sucedida

- [x] Projeto clonado/acessado
- [ ] CMake instalado (`cmake --version`)
- [ ] Compilador instalado (`gcc --version` ou `clang --version`)
- [ ] `bash build.sh` ou `build.bat` executado sem erros
- [ ] Arquivo `build/normalize` ou `build\Release\normalize.exe` existe
- [ ] `./build/normalize tests/sample_data.csv baseline` funciona

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
