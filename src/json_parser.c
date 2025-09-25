#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int skip_value(void);
char *json; // pointer to current position in JSON text
int life_saver = 0; // helper counter tracking nesting of braces

// Skip over any whitespace characters.
void skip_space(char **json) {
    *json += strspn(*json, " \t\n\r"); 
}

// Skip a number. Returns 0 on success, 1 on failure (invalid number).
int skip_number(void) {
    int r = 0;
    double dummy;

    if (sscanf(json, "%lf%n", &dummy, &r) == 1) { 
        json += r;
        if (*json == '.') 
            return 1; // reject if a stray '.' follows (incomplete fractional part)
        return 0; // valid number
    }
    return 1;
}

// Skip a JSON string. Returns 0 on success, 1 on failure.
int skip_string(void) {
    if (*json != '"') return 1; 
    json++; 
    while (*json != '\0') {
        if (*json == '"') { 
            json++;
            return 0; // closing quote found
        }
        if (*json == '\\') { 
            json++; 
            if (*json == '\0') return 1; 
            if (!strchr("\"\\/bfnrtu", *json)) return 1; 
            if (*json == 'u') { // expect 4 hex digits
                for (int i = 0; i < 4; i++) {
                    json++; 
                    if (!isxdigit(*json)) return 1;  
                }
            }
        } else if ((unsigned char)*json <= 0x1F) { 
            return 1; // control characters not allowed inside a JSON string
        }
        json++;
    }
    return 1; // unterminated string
}

// Skip true / false / null. Returns 0 on success, 1 on failure.
int skip_boolnul(void) {
    if (strncmp(json, "true", 4) == 0) { json += 4; return 0; }
    if (strncmp(json, "false", 5) == 0) { json += 5; return 0; }
    if (strncmp(json, "null", 4) == 0) { json += 4; return 0; }
    return 1;
}

// Skip an object. Returns 0 if valid, 1 otherwise.
int skip_object(void) {
    skip_space(&json); 
    if (*json != '{') return 1; 
    json++;  

    skip_space(&json); 
    if (*json == '}') { // empty object
        json++;  
        return 0;
    }

    // Iterate over key / value pairs
    while (1) { 
        skip_space(&json);
        if (skip_string() != 0) return 1; // key must be a string

        skip_space(&json);
        if (*json != ':') return 1; // missing ':' after key
        json++; // skip ':'

        skip_space(&json);
        if (skip_value() != 0) return 1; // invalid value
        skip_space(&json);
        if (*json == '}') { // object closes
            json++; 
            return 0;
        }

        if (*json == ',') { // more pairs follow
            json++; 
            skip_space(&json);
            continue;  
        }

        return 1; // invalid character in object
    }
}

// Skip an array. Returns 0 if valid, 1 otherwise.
int skip_array(void) {
    if (*json != '[') return 1; // must start with '['
    json++; // skip '['
    skip_space(&json);
    if (*json == ']') { // empty array
        json++;
        return 0;
    }
    // Iterate over elements
    while (1) {
        skip_space(&json);
        if (skip_value() != 0) return 1; // element invalid
        skip_space(&json);
        if (*json == ']') { // end of array
            json++;
            return 0;
        }
        if (*json == ',') { // next element
            json++;
            skip_space(&json);
            continue;
        }
        return 1; // invalid delimiter
    }
}

// Skip any JSON value (object, array, number, string, bool, null). 0 success, 1 failure.
int skip_value(void) {     
    if (*json == '{') return skip_object();
    if (*json == '[') return skip_array();
    if (skip_number() == 0 || skip_boolnul() == 0 || skip_string() == 0) return 0; // string last because it advances pointer char-by-char
    return 1;
}

// Search for a specific literal string and advance pointer to just after it.
// Updates life_saver counter for '{' and '}'. Returns 0 if found, 1 if not.
int find_string(const char *str) {
    size_t len = strlen(str);
    while (*json) { 
        if (strncmp(json, str, len) == 0) { 
            json += len; 
            return 0;
        }
        if (*json == '{') {
            life_saver++;
        }
        if (*json == '}') {
            life_saver--;
        }
        json++; 
    }
    return 1;
}

// Validate the whole JSON text. Returns 0 if valid, 1 otherwise.
int parse_json(void) {
    skip_space(&json);
    if (*json == '{') {
        if (skip_object() != 0) return 1; 
    } else if (*json == '[') {
        if (skip_array() != 0) return 1;
    } else {
        return 1; // must start with object or array
    }
    skip_space(&json);
    return !(*json == '\0'); // success only if we've consumed entire string
}

//Checks if the json file is valid. Returns 0 if valid, 1 otherwise.
int json_parser(char *buffer) {

    json = buffer;

    // Validate JSON first
    if (parse_json()) return 1;

    return 0;
    
}