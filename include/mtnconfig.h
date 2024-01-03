/**
 * @file mtnconfig.h
 * @brief Moltony's config library
 * @author moltony
*/

#ifndef MTNCONFIG_H_
#define MTNCONFIG_H_ 1

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Initialize config
 * @param configPath where config is located
*/
bool mtnconfigInit(const char *configPath);

/**
 * @brief Get value from config with the given key as a string
 * @param key entry key
*/
const char *mtnconfigGet(const char *key);

/**
 * @brief Get value from config with the given key as an integer
 * @param key entry key
*/
int mtnconfigGetInt(const char *key);

/**
 * @brief Get value from config with the given key as boolean (true/false)
 * @param key entry key
 */
bool mtnconfigGetBool(const char *key);

#ifdef __cplusplus
}
#endif

#endif
