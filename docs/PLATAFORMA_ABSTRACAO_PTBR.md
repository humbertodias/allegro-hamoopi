# Camada de Abstração de Plataforma - HAMOOPI

## Resumo

Este documento explica a camada de abstração de plataforma criada para desacoplar o motor de jogo de luta HAMOOPI do Allegro 4. Esta abstração permite trocar facilmente de backend (por exemplo, de Allegro 4 para SDL2) no futuro.

## O que foi feito?

### Arquivos Criados

1. **src/platform.h** - API independente de plataforma
   - Define tipos genéricos: PlatformBitmap, PlatformFont, PlatformSample, PlatformMidi
   - Declara todas as funções de plataforma
   - Quando USE_ALLEGRO4 está definido, usa tipos do Allegro diretamente (sem overhead)

2. **src/platform_allegro.c** - Implementação usando Allegro 4
   - Implementa todas as funções da plataforma usando Allegro 4
   - Atua como wrapper fino em volta do Allegro 4

3. **src/platform_compat.h** - Camada de compatibilidade
   - Fornece macros para compatibilidade com código Allegro 4 existente
   - Permite que o código existente funcione sem alterações
   - Quando USE_ALLEGRO4 está definido, não redefine constantes do Allegro

### Modificações

- **src/HAMOOPI.c**: Alterada a linha 35 de `#include <allegro.h>` para `#include "platform_compat.h"`
- **CMakeLists.txt**: Adicionado `-DUSE_ALLEGRO4` e inclusão do `platform_allegro.c`

## Funcionalidades Abstraídas

A camada de abstração cobre cinco áreas principais:

### 1. Inicialização do Sistema
- Inicialização da plataforma
- Instalação de timer, teclado, mouse
- Configuração de modo gráfico
- Callbacks e eventos

### 2. Operações Gráficas
- Gerenciamento de bitmaps (criar, destruir, carregar)
- Desenho (sprites, primitivas)
- Blitting (regular, esticado, com máscara)
- Transformações (espelhar, rotação)
- Operações de pixel

### 3. Renderização de Texto
- Carregar e destruir fontes
- Desenhar texto simples e centralizado
- Texto formatado (estilo printf)

### 4. Áudio
- Instalação do sistema de som
- Gerenciamento de samples (carregar, tocar, ajustar)
- Gerenciamento de MIDI
- Controle de volume

### 5. Arquivos de Configuração
- Leitura e escrita de configurações (INI)

## Como Usar Atualmente

O engine continua usando Allegro 4, mas agora através da camada de abstração:

```bash
# Compilar
cmake -Bbuild
cmake --build build

# Executar
./HAMOOPI
```

## Vantagens

1. **Separação de Responsabilidades**: Lógica do jogo separada do código específico da plataforma
2. **Fácil Troca de Backend**: Mude o backend modificando o CMakeLists.txt
3. **Código Existente Funciona**: Sem necessidade de reescrever código
4. **Sem Overhead**: Tipos são diretamente mapeados para o Allegro (sem custo de performance)
5. **Preparado para o Futuro**: Pronto para SDL2, SDL3, ou qualquer outro backend
6. **Manutenível**: API clara facilita entendimento e manutenção

## Migração Futura para SDL2

Para migrar para SDL2 no futuro:

### Passo 1: Criar platform_sdl2.c

Implementar todas as funções `platform_*` usando SDL2.

### Passo 2: Atualizar CMakeLists.txt

```cmake
option(USE_SDL2 "Use SDL2 backend" OFF)

if(USE_SDL2)
    add_definitions(-DUSE_SDL2)
    add_executable(HAMOOPI src/HAMOOPI.c src/platform_sdl2.c)
    # Link com SDL2...
else()
    # Usar Allegro 4 (atual)
endif()
```

### Passo 3: Compilar com SDL2

```bash
cmake -Bbuild -DUSE_SDL2=ON
cmake --build build
```

## Estrutura de Arquivos

```
src/
├── HAMOOPI.c             # Código principal (usa platform_compat.h)
├── platform.h            # API de abstração
├── platform_compat.h     # Macros de compatibilidade
├── platform_allegro.c    # Implementação Allegro 4
└── platform_sdl2.c       # Implementação SDL2 (a ser criada)
```

## Testado

- ✅ Sistema de compilação funciona corretamente
- ✅ Todo código Allegro 4 existente funciona sem modificações
- ✅ Sem overhead de performance (mapeamento direto de tipos)
- ✅ Caminho claro para migração SDL2 definido

## Documentação Completa

Para documentação detalhada em inglês, veja: [docs/PLATFORM_ABSTRACTION.md](PLATFORM_ABSTRACTION.md)
