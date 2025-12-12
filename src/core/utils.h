#ifndef HAMOOPI_UTILS_H
#define HAMOOPI_UTILS_H

/**
 * @file utils.h
 * @brief Funções utilitárias para o motor HAMOOPI
 * 
 * Este arquivo contém funções auxiliares reutilizáveis
 * que simplificam operações comuns no código.
 */

#include "backend/platform_compat.h"
#include "constants.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/**
 * Carrega um bitmap com fallback para imagem padrão
 * @param path Caminho do bitmap a carregar
 * @param fallback_path Caminho do bitmap alternativo se o primeiro falhar
 * @return Ponteiro para o bitmap carregado, ou NULL se ambos falharem
 */
static inline BITMAP* load_bitmap_with_fallback(const char* path, const char* fallback_path) {
    BITMAP* bmp = load_bitmap(path, NULL);
    if (!bmp && fallback_path) {
        bmp = load_bitmap(fallback_path, NULL);
    }
    return bmp;
}

/**
 * Carrega um bitmap de personagem com fallback automático
 * @param char_name Nome do personagem
 * @param sprite_file Nome do arquivo de sprite (ex: "000_01.png")
 * @return Ponteiro para o bitmap carregado
 */
static inline BITMAP* load_character_sprite(const char* char_name, const char* sprite_file) {
    char path[MAX_PATH_LENGTH];
    snprintf(path, sizeof(path), "data/chars/%s/%s", char_name, sprite_file);
    return load_bitmap_with_fallback(path, "data/system/000_01.png");
}

/**
 * Carrega um bitmap de cenário
 * @param stage_name Nome do cenário
 * @param sprite_file Nome do arquivo de sprite
 * @return Ponteiro para o bitmap carregado
 */
static inline BITMAP* load_stage_bitmap(const char* stage_name, const char* sprite_file) {
    char path[MAX_PATH_LENGTH];
    snprintf(path, sizeof(path), "data/backgrounds/%s/%s", stage_name, sprite_file);
    return load_bitmap(path, NULL);
}

/**
 * Verifica se uma string representa um nome de personagem válido
 * @param name Nome a verificar
 * @return 1 se válido, 0 caso contrário
 */
static inline int is_valid_character_name(const char* name) {
    return name && name[0] != '\0' && strlen(name) < MAX_NAME_LENGTH;
}

/**
 * Copia nome de forma segura, garantindo terminação null
 * @param dest Buffer de destino
 * @param src String fonte
 * @param max_size Tamanho máximo do buffer de destino
 */
static inline void safe_copy_name(char* dest, const char* src, size_t max_size) {
    if (dest && src && max_size > 0) {
        strncpy(dest, src, max_size - 1);
        dest[max_size - 1] = '\0';
    }
}

/**
 * Normaliza valor de volume para range válido
 * @param volume Valor de volume a normalizar
 * @return Volume normalizado entre MIN_VOLUME e MAX_VOLUME
 */
static inline int normalize_volume(int volume) {
    if (volume < MIN_VOLUME) return MIN_VOLUME;
    if (volume > MAX_VOLUME) return MAX_VOLUME;
    return volume;
}

/**
 * Normaliza valor de FPS para range válido
 * @param fps Valor de FPS a normalizar
 * @return FPS normalizado entre MIN_FPS e MAX_FPS
 */
static inline int normalize_fps(int fps) {
    if (fps < MIN_FPS) return MIN_FPS;
    if (fps > MAX_FPS) return MAX_FPS;
    return fps;
}

/**
 * Calcula o centro entre dois valores
 * @param a Primeiro valor
 * @param b Segundo valor
 * @return Centro entre a e b
 */
static inline int calculate_center(int a, int b) {
    return (a + b) / 2;
}

/**
 * Verifica se dois retângulos colidem (AABB)
 * @param x1 X do primeiro retângulo (canto superior esquerdo)
 * @param y1 Y do primeiro retângulo
 * @param w1 Largura do primeiro retângulo
 * @param h1 Altura do primeiro retângulo
 * @param x2 X do segundo retângulo
 * @param y2 Y do segundo retângulo
 * @param w2 Largura do segundo retângulo
 * @param h2 Altura do segundo retângulo
 * @return 1 se colidem, 0 caso contrário
 */
static inline int rectangles_collide(int x1, int y1, int w1, int h1,
                                     int x2, int y2, int w2, int h2) {
    return !(x1 + w1 < x2 || x2 + w2 < x1 || 
             y1 + h1 < y2 || y2 + h2 < y1);
}

/**
 * Verifica colisão entre dois boxes definidos por coordenadas
 * @param x1_min X mínimo do primeiro box
 * @param y1_min Y mínimo do primeiro box
 * @param x1_max X máximo do primeiro box
 * @param y1_max Y máximo do primeiro box
 * @param x2_min X mínimo do segundo box
 * @param y2_min Y mínimo do segundo box
 * @param x2_max X máximo do segundo box
 * @param y2_max Y máximo do segundo box
 * @return 1 se colidem, 0 caso contrário
 */
static inline int boxes_collide(int x1_min, int y1_min, int x1_max, int y1_max,
                                int x2_min, int y2_min, int x2_max, int y2_max) {
    return !(x1_max < x2_min || x2_max < x1_min || 
             y1_max < y2_min || y2_max < y1_min);
}

/**
 * Calcula distância entre dois pontos
 * @param x1 X do primeiro ponto
 * @param y1 Y do primeiro ponto
 * @param x2 X do segundo ponto
 * @param y2 Y do segundo ponto
 * @return Distância entre os pontos
 */
static inline float calculate_distance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrtf((float)(dx * dx + dy * dy));
}

/**
 * Interpola linearmente entre dois valores
 * @param start Valor inicial
 * @param end Valor final
 * @param t Fator de interpolação (0.0 a 1.0)
 * @return Valor interpolado
 */
static inline float lerp(float start, float end, float t) {
    return start + t * (end - start);
}

/**
 * Verifica se um ponto está dentro de um retângulo
 * @param px X do ponto
 * @param py Y do ponto
 * @param rx X do retângulo
 * @param ry Y do retângulo
 * @param rw Largura do retângulo
 * @param rh Altura do retângulo
 * @return 1 se o ponto está dentro, 0 caso contrário
 */
static inline int point_in_rectangle(int px, int py, int rx, int ry, int rw, int rh) {
    return px >= rx && px <= rx + rw && py >= ry && py <= ry + rh;
}

/**
 * Formata string de tempo em formato MM:SS
 * @param buffer Buffer para armazenar o resultado
 * @param buffer_size Tamanho do buffer
 * @param total_seconds Total de segundos a formatar
 */
static inline void format_time(char* buffer, size_t buffer_size, int total_seconds) {
    int minutes = total_seconds / SECONDS_PER_MINUTE;
    int seconds = total_seconds % SECONDS_PER_MINUTE;
    snprintf(buffer, buffer_size, "%02d:%02d", minutes, seconds);
}

/**
 * Retorna número de identificação da resolução
 * @param width Largura da resolução
 * @param height Altura da resolução
 * @return Número identificador da resolução (1-8), ou 0 se inválida
 */
static inline int get_resolution_number(int width, int height) {
    if (width == RES_320x240_WIDTH && height == RES_320x240_HEIGHT) return 1;
    if (width == RES_640x480_WIDTH && height == RES_640x480_HEIGHT) return 2;
    if (width == RES_720x480_WIDTH && height == RES_720x480_HEIGHT) return 3;
    if (width == RES_800x600_WIDTH && height == RES_800x600_HEIGHT) return 4;
    if (width == RES_960x640_WIDTH && height == RES_960x640_HEIGHT) return 5;
    if (width == RES_960x720_WIDTH && height == RES_960x720_HEIGHT) return 6;
    if (width == RES_1024x600_WIDTH && height == RES_1024x600_HEIGHT) return 7;
    if (width == RES_1280x720_WIDTH && height == RES_1280x720_HEIGHT) return 8;
    return 0;
}

/**
 * Aplica gravidade a uma velocidade vertical
 * @param vspeed Velocidade vertical atual
 * @param gravity Valor da gravidade
 * @return Nova velocidade vertical
 */
static inline float apply_gravity(float vspeed, float gravity) {
    return vspeed + gravity;
}

/**
 * Aplica fricção a uma velocidade horizontal
 * @param hspeed Velocidade horizontal atual
 * @param friction Valor da fricção
 * @return Nova velocidade horizontal
 */
static inline float apply_friction(float hspeed, float friction) {
    if (hspeed > 0) {
        hspeed -= friction;
        if (hspeed < 0) hspeed = 0;
    } else if (hspeed < 0) {
        hspeed += friction;
        if (hspeed > 0) hspeed = 0;
    }
    return hspeed;
}

#endif // HAMOOPI_UTILS_H
