#include "mtnconfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MTNCONFIG_MAX_LINE_LEN
#define MTNCONFIG_MAX_LINE_LEN 128
#endif

typedef struct cfgdict
{
	char *key;
	char *value;
	struct cfgdict *next;
} ConfigDict;

static ConfigDict *_cfgDict = NULL;

bool mtnconfigInit(const char *configPath)
{
	FILE *configFile = fopen(configPath, "r");
	if (!configFile)
		return false;

	char buf[MTNCONFIG_MAX_LINE_LEN];
	char keyBuf[MTNCONFIG_MAX_LINE_LEN];
	char valueBuf[MTNCONFIG_MAX_LINE_LEN];
	while (fgets(buf, MTNCONFIG_MAX_LINE_LEN, configFile))
	{
		if (buf[0] == '#' || buf[0] == '\n')
			continue; // comment or empty line

		// extract key
		int i;
		int keyLen = 0;
		int valueLen = 0;
		for (i = 0; buf[i] != ' '; i++)
			keyBuf[i] = buf[i];
		keyBuf[i++] = 0;
		keyLen = i;

		// extract value
		int j;
		for (j = 0; buf[i] != '\n'; i++, j++)
			valueBuf[j] = buf[i];

		// crlf support
		if (valueBuf[j - 1] == '\r')
			valueBuf[j - 1] = 0;

		valueBuf[j] = 0;
		valueLen = i;

		if (_cfgDict == NULL)
		{
			// create 1st entry
			_cfgDict = malloc(sizeof(ConfigDict));
			_cfgDict->key = malloc(keyLen * sizeof(char));
			_cfgDict->value = malloc(valueLen * sizeof(char));
			_cfgDict->next = NULL;

			// copy values
			memcpy(_cfgDict->key, keyBuf, keyLen);
			memcpy(_cfgDict->value, valueBuf, valueLen);
		}
		else
		{
			// find last entry
			ConfigDict *current = _cfgDict;
			for (; current->next; current = current->next)
				;

			// allocate next entry
			current->next = malloc(sizeof(ConfigDict));
			current = current->next;

			// allocate key and value
			current->key = malloc(keyLen * sizeof(char));
			current->value = malloc(valueLen * sizeof(char));
			current->next = NULL; // last entry (next is null)

			// copy values
			memcpy(current->key, keyBuf, keyLen);
			memcpy(current->value, valueBuf, valueLen);
		}
	}

	fclose(configFile);

	return true;
}

const char *mtnconfigGet(const char *key)
{
	for (ConfigDict *d = _cfgDict;; d = d->next)
	{
		if (!d)
			break;

		if (strcmp(key, d->key) == 0)
			return d->value;
	}
	return "";
}

int mtnconfigGetInt(const char *key)
{
	const char *strValue = mtnconfigGet(key);

	// return 0 if key not found
	if (strlen(strValue) == 0)
		return 0;

	return atoi(strValue);
}

bool mtnconfigGetBool(const char *key)
{
    const char *strValue = mtnconfigGet(key);

    // return false if key not found
    if (strlen(strValue) == 0)
        return 0;

    return strcmp(strValue, "true") == 0;
}
