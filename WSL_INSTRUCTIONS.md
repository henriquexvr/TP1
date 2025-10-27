# 🪟 Instruções para WSL (Windows Subsystem for Linux)

Guia específico para seu amigo compilar o projeto em **WSL com arquitetura x86-64**.

---

## 📋 Pré-requisitos no WSL

### 1. Ter WSL2 Instalado
```powershell
# No PowerShell (como administrador)
wsl --install
```

### 2. Abrir Terminal WSL
```powershell
# Abrir distribuição Linux (Ubuntu é padrão)
wsl
```

---

## ⚙️ Setup no WSL

Dentro do terminal WSL, execute:

```bash
# Atualizar pacotes
sudo apt update
sudo apt upgrade -y

# Instalar dependências
sudo apt install -y build-essential cmake git

# Verificar instalação
cmake --version
gcc --version
```

---

## 📥 Clonar/Acessar Projeto

```bash
# Ir para diretório (ou clonar se não tiver)
cd /mnt/c/Users/[seu_usuario]/[pasta_do_projeto]  # Ajustar caminho
# ou simplesmente
cd ~/TP1  # Se tiver clonado no home

# Ou clonar pela primeira vez
git clone https://github.com/henriquexvr/TP1.git
cd TP1
```

---

## 🚀 Compilar

```bash
# Opção 1: Script automático (Recomendado)
bash build.sh

# Opção 2: Manual
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
cd ..
```

---

## ✅ Verificar Compilação

Ao compilar, você deve ver:

```
-- Architecture: x86-64 (SSE)
-- SIMD Implementation: src/normalizeSse.c
```

✅ Se vir isso, perfeito! A compilação detectou corretamente a arquitetura x86-64.

---

## ▶️ Executar

```bash
# Teste básico
./build/normalize tests/sample_data.csv baseline
./build/normalize tests/sample_data.csv quake
./build/normalize tests/sample_data.csv sse

# Com dados maiores
./build/normalize tests/data_1000x10.csv sse
./build/normalize tests/data_1000x100.csv sse
```

---

## 📊 Saída Esperada

```
baseline,3,3,0.000002,0.000001,0.000002,1032192
quake,3,3,0.000001,0.000000,0.000001,1032192
sse,3,3,0.000002,0.000000,0.000001,1032192
```

---

## 🔄 Sincronizar com o Seu Projeto (macOS)

Vocês podem agora:

1. **Você testa em macOS com NEON:**
   ```bash
   bash build.sh
   ./build/normalize tests/data_1000x100.csv sse
   ```

2. **Seu amigo testa em WSL com SSE:**
   ```bash
   bash build.sh
   ./build/normalize tests/data_1000x100.csv sse
   ```

3. **Ambos compartilham os resultados em `results/metrics.csv`:**
   ```bash
   # Rodar experimentos
   bash scripts/runExperiments.sh
   
   # Comparar
   cat results/metrics.csv
   ```

---

## ⚠️ Problemas Comuns no WSL

### `cmake: command not found`
```bash
sudo apt install cmake
```

### `gcc: command not found`
```bash
sudo apt install build-essential
```

### `bash: build.sh: Permission denied`
```bash
chmod +x build.sh
bash build.sh
```

### Arquivo em Windows, problemas de linha
```bash
# Converter CRLF para LF (se necessário)
dos2unix build.sh  # ou: sed -i 's/\r$//' build.sh
```

---

## 🎯 Próximos Passos

1. ✅ Compilar com `bash build.sh`
2. ✅ Testar com `./build/normalize tests/sample_data.csv sse`
3. ✅ Rodar experimentos com `bash scripts/runExperiments.sh`
4. ✅ Compartilhar resultados com você

---

## 💬 Comparar Resultados

Após ambos rodarem os experimentos:

**Você (macOS ARM NEON):**
```
cat results/metrics.csv
```

**Seu amigo (WSL x86 SSE):**
```
cat results/metrics.csv
```

**Comparação esperada:**
- SSE deve ser mais rápido em dados grandes no WSL
- NEON deve ser comparável no macOS
- Versões baseline e quake servem como reference

---

**Status:** ✅ **Pronto para usar no WSL**
