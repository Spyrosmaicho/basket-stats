#ifndef JSON_PARSER_H
#define JSON_PARSER_H

//Checks if the json file is valid. Returns 0 if valid, 1 otherwise.
int json_parser(char *buffer);
// Skip over any whitespace characters.
void skip_space(char **json);

#endif // JASON_H