# libmtnconfig

`libmtnconfig` is a simple config file library originally created for [ds-craft](https://github.com/IAmMoltony/ds-craft).

## Config syntax

Here's an example config that covers everyting:

```
# comment

userName moltony
numberValue 4352
```

Keys can be any string of characters except for space. Spaces are used to separate the key and value. The value can be anything, even if it has spaces.

## API

```c
void mtnconfigInit(const char *configPath);
```

Initializes config system and reads the config from `configPath`.

```c
const char *mtnconfigGet(const char *key);
```

Gets a string value with the given key.

```c
int mtnconfigGetInt(const char *key);
```

Gets a number value with the given key. If the value is not a valid number, then this might crash or return some garbage value.

## Using

Paste the header and source of the library into your project.
