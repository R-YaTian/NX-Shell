#pragma once

#include <string>
#include <switch.h>

typedef struct {
    int lang = 1;
    bool dev_options = false;
    bool image_filename = false;
    bool multi_lang = false;
    bool full_charset = false;
} config_t;

extern config_t cfg;
extern std::string cwd;
extern std::string device;

namespace Config {
    int Save(config_t &config);
    int Load(void);
}
