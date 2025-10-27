# 🚀 Quick Start - TP1 Normalize

## Seu Projeto Agora é Multi-Arquitetura! ✨

### macOS (Apple M1/M2)
```bash
bash build.sh
./build/normalize tests/data_1000x100.csv sse
```

### WSL / Linux (x86-64)
```bash
bash build.sh
./build/normalize tests/data_1000x100.csv sse
```

### Windows (Visual Studio)
```cmd
build.bat
build\Release\normalize.exe tests\data_1000x100.csv sse
```

---

## 📖 Documentação Completa

1. **`SETUP.md`** - Guia de instalação por plataforma
2. **`README.md`** - Documentação detalhada do projeto
3. **`MIGRATION_SUMMARY.md`** - O que mudou
4. **`WSL_INSTRUCTIONS.md`** - Para seu amigo no WSL

---

## ✅ Verificação Rápida

```bash
# Seu Mac detectará:
-- Architecture: ARM (NEON)
-- SIMD Implementation: src/normalizeSseArm.c

# WSL do seu amigo detectará:
-- Architecture: x86-64 (SSE)
-- SIMD Implementation: src/normalizeSse.c
```

---

## 🎯 Resumo das Mudanças

| Antes | Depois |
|-------|--------|
| ❌ Você não conseguia compilar | ✅ Compila automático em ARM |
| ✅ Seu amigo conseguia compilar | ✅ Continua funcionando em x86-64 |
| ❌ Makefile não-portável | ✅ CMake multi-plataforma |
| ⚠️ SSE não funcionava em ARM | ✅ NEON agora disponível |

---

**Status:** Ready to use! 🎉
