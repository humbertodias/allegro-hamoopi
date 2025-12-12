#ifndef HAMOOPI_MACROS_H
#define HAMOOPI_MACROS_H

/**
 * @file macros.h
 * @brief Macros úteis para o motor HAMOOPI
 * 
 * Este arquivo contém macros auxiliares para operações comuns,
 * simplificando o código e evitando erros.
 */

#include "constants.h"

// ============================================================================
// MACROS DE VERIFICAÇÃO DE MEMÓRIA
// ============================================================================

/**
 * Verifica se um ponteiro é NULL e retorna erro se for
 * Uso: CHECK_NULL(ptr);
 */
#define CHECK_NULL(ptr) \
    do { \
        if (!(ptr)) { \
            return -1; \
        } \
    } while(0)

/**
 * Verifica se um ponteiro é NULL com mensagem de erro
 * Uso: CHECK_NULL_MSG(ptr, "Failed to allocate");
 */
#define CHECK_NULL_MSG(ptr, msg) \
    do { \
        if (!(ptr)) { \
            fprintf(stderr, "Error: %s\n", msg); \
            return -1; \
        } \
    } while(0)

/**
 * Cria um bitmap e verifica se foi criado com sucesso
 * Uso: CREATE_BITMAP_CHECKED(my_bitmap, 640, 480);
 */
#define CREATE_BITMAP_CHECKED(bmp, w, h) \
    do { \
        (bmp) = create_bitmap((w), (h)); \
        if (!(bmp)) { \
            return -1; \
        } \
    } while(0)

// ============================================================================
// MACROS DE RANGE/CLAMP
// ============================================================================

/**
 * Limita um valor entre min e max
 */
#define CLAMP(value, min, max) \
    (((value) < (min)) ? (min) : (((value) > (max)) ? (max) : (value)))

/**
 * Retorna o mínimo entre dois valores
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/**
 * Retorna o máximo entre dois valores
 */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/**
 * Verifica se um valor está dentro de um range (inclusivo)
 */
#define IN_RANGE(value, min, max) \
    ((value) >= (min) && (value) <= (max))

// ============================================================================
// MACROS DE ARRAY
// ============================================================================

/**
 * Retorna o número de elementos em um array estático
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/**
 * Itera sobre todos os elementos de um array estático
 * Uso: ARRAY_FOREACH(i, my_array) { ... }
 */
#define ARRAY_FOREACH(index, array) \
    for (size_t index = 0; index < ARRAY_SIZE(array); index++)

// ============================================================================
// MACROS DE STRING
// ============================================================================

/**
 * Copia string de forma segura com verificação de tamanho
 * Uso: SAFE_STRCPY(dest, src, sizeof(dest));
 */
#define SAFE_STRCPY(dest, src, size) \
    do { \
        strncpy((dest), (src), (size) - 1); \
        (dest)[(size) - 1] = '\0'; \
    } while(0)

/**
 * Verifica se duas strings são iguais
 */
#define STR_EQUALS(str1, str2) (strcmp((str1), (str2)) == 0)

/**
 * Verifica se uma string está vazia
 */
#define STR_EMPTY(str) ((str)[0] == '\0')

// ============================================================================
// MACROS DE DEBUG
// ============================================================================

/**
 * Imprime mensagem de debug quando DEBUG está definido
 */
#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d: " fmt "\n", \
                __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) ((void)0)
#endif

/**
 * Imprime mensagem de log com nível
 */
#define LOG_INFO(fmt, ...) \
    fprintf(stdout, "[INFO] " fmt "\n", ##__VA_ARGS__)

#define LOG_WARNING(fmt, ...) \
    fprintf(stderr, "[WARNING] " fmt "\n", ##__VA_ARGS__)

#define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[ERROR] " fmt "\n", ##__VA_ARGS__)

// ============================================================================
// MACROS DE PERFORMANCE
// ============================================================================

/**
 * Marca função como inline (hint para o compilador)
 */
#ifdef __GNUC__
    #define INLINE __attribute__((always_inline)) inline
#else
    #define INLINE inline
#endif

/**
 * Marca função ou variável como não usada (suprime warning)
 */
#ifdef __GNUC__
    #define UNUSED __attribute__((unused))
#else
    #define UNUSED
#endif

// ============================================================================
// MACROS DE CORES
// ============================================================================

/**
 * Cria cor RGB de forma mais legível
 */
#define RGB(r, g, b) makecol((r), (g), (b))

/**
 * Cores comuns predefinidas
 */
#define COLOR_TRANSPARENT RGB(COLOR_MAGENTA_R, COLOR_MAGENTA_G, COLOR_MAGENTA_B)
#define COLOR_BLACK       RGB(0, 0, 0)
#define COLOR_WHITE       RGB(255, 255, 255)
#define COLOR_RED         RGB(255, 0, 0)
#define COLOR_GREEN       RGB(0, 255, 0)
#define COLOR_BLUE        RGB(0, 0, 255)

// ============================================================================
// MACROS DE CONVERSÃO
// ============================================================================

/**
 * Converte segundos para frames (60 FPS)
 */
#define SECONDS_TO_FRAMES(seconds) ((seconds) * DEFAULT_FPS)

/**
 * Converte frames para segundos (60 FPS)
 */
#define FRAMES_TO_SECONDS(frames) ((frames) / (float)DEFAULT_FPS)

/**
 * Converte graus para radianos
 */
#define DEG_TO_RAD(deg) ((deg) * 3.14159265358979323846 / 180.0)

/**
 * Converte radianos para graus
 */
#define RAD_TO_DEG(rad) ((rad) * 180.0 / 3.14159265358979323846)

// ============================================================================
// MACROS DE VALIDAÇÃO
// ============================================================================

/**
 * Verifica se um índice de jogador é válido (1 ou 2)
 */
#define VALID_PLAYER_INDEX(idx) ((idx) >= 1 && (idx) <= MAX_PLAYERS)

/**
 * Verifica se um ID de personagem é válido
 */
#define VALID_CHARACTER_ID(id) ((id) >= 1 && (id) <= MAX_CHARACTERS)

/**
 * Verifica se um ID de stage é válido
 */
#define VALID_STAGE_ID(id) ((id) >= 1 && (id) <= MAX_STAGES)

// ============================================================================
// MACROS ESPECÍFICAS DO JOGO (Requerem variáveis globais definidas)
// ============================================================================

// As macros abaixo dependem de variáveis globais e devem ser usadas
// somente após a inicialização do jogo

/**
 * Verifica se o jogador está no chão
 * Requer: AlturaPiso definido
 */
// #define IS_GROUNDED(player) ((player).y >= AlturaPiso)

/**
 * Verifica se o jogador está no ar
 * Requer: AlturaPiso definido
 */
// #define IS_AIRBORNE(player) ((player).y < AlturaPiso)

/**
 * Verifica se o estado é de pulo
 * Requer: STATE_* constantes definidas
 */
// #define IS_JUMPING(state) \
//     ((state) == STATE_JUMP || \
//      (state) == STATE_JUMP_FORWARD || \
//      (state) == STATE_JUMP_BACKWARD)

#endif // HAMOOPI_MACROS_H
