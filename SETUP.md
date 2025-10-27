# 🚀 Guia Rápido de Setup

## Pré-requisitos

### macOS
```bash
# Instalar Xcode Command Line Tools (se não tiver)
xcode-select --install

# Instalar CMake
brew install cmake
```

### Linux (Ubuntu/Debian)
```bash
# Atualizar pacotes
sudo apt update

# Instalar dependências
sudo apt install -y build-essential cmake
```

### Linux (Fedora/RHEL)
```bash
# Instalar dependências
sudo yum install -y gcc cmake
```

### Windows
1. Instalar [Visual Studio Community Edition](https://visualstudio.microsoft.com/community/) ou:
2. `choco install cmake` (se usar Chocolatey)

---

## 📥 Passo a Passo: Compilação

### ⚡ Opção Mais Rápida (Recomendado)

#### macOS / Linux
```bash
cd TP1
bash build.sh
```

#### Windows (PowerShell/CMD)
```cmd
cd TP1
build.bat
```

---

### Opção Manual (Qualquer SO)

```bash
# Entrar no diretório
cd TP1

# Criar pasta de build
mkdir build
cd build

# Configurar (detecta arquitetura automaticamente!)
cmake -DCMAKE_BUILD_TYPE=Release ..

# Compilar
cmake --build . --config Release

# Voltar para raiz
cd ..
```

---

## ▶️ Executando o Programa

### macOS / Linux

```bash
# Versão baseline
./build/normalize tests/sample_data.csv baseline

# Versão Quake
./build/normalize tests/sample_data.csv quake

# Versão SIMD (SSE em x86, NEON em ARM)
./build/normalize tests/sample_data.csv sse

# Com dataset maior
./build/normalize tests/data_1000x10.csv sse
./build/normalize tests/data_1000x100.csv sse
```

### Windows

```cmd
# Versão baseline
build\Release\normalize.exe tests\sample_data.csv baseline

# Versão Quake
build\Release\normalize.exe tests\sample_data.csv quake

# Versão SIMD
build\Release\normalize.exe tests\sample_data.csv sse

# Com dataset maior
build\Release\normalize.exe tests\data_1000x10.csv sse
build\Release\normalize.exe tests\data_1000x100.csv sse
```

---

## 🧪 Rodar Todos os Experimentos

### macOS / Linux

```bash
bash build.sh
bash scripts/runExperiments.sh

# Ver resultados
cat results/metrics.csv
```

---

## 🔍 O CMake Detectou Corretamente?

Ao compilar, procure por uma mensagem assim:

```
-- Architecture: ARM (NEON)
-- SIMD Implementation: src/normalizeSseArm.c
```

Ou para x86-64:

```
-- Architecture: x86-64 (SSE)
-- SIMD Implementation: src/normalizeSse.c
```

---

## ❌ Troubleshooting Rápido

| Problema | Solução |
|----------|---------|
| `cmake: command not found` | `brew install cmake` (macOS) ou `sudo apt install cmake` (Linux) |
| `gcc: command not found` | Instalar compilador (xcode-select --install no macOS) |
| `build/normalize: not found` | Verifique se compilou: `cmake --build .` |
| NEON error (ARM) | Usar CMake: `mkdir build && cd build && cmake ..` |

---

## 📊 Saída Esperada

```
version,N,D,wall,user,sys,memoryKB
baseline,3,3,0.000002,0.000001,0.000002,1032192
quake,3,3,0.000001,0.000000,0.000001,1032192
sse,3,3,0.000002,0.000000,0.000001,1032192
```

✅ Se vir isso, está funcionando!

---

## 📞 Mais Informações

Ver `README.md` para documentação completa.
