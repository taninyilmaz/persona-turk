#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>

extern const char *male_names[];
extern const char *female_names[];
extern const char *surname_list[];

// Function prototypes
void generate_full_name(char *fullname, size_t max_len, char *name1, char *name2, char *surname, int *is_double_name);
void randomName(char *name, size_t max_len);
void randomSurname(char *surname, size_t max_len);
void generateEmailFromParts(char *email, size_t max_len, const char *name1, const char *name2, int is_double_name, const char *surname);
void generatePhoneNumber(char *phone, size_t max_len);
void transliterate_turkish(const char *src, char *dest, size_t max_len);
void generateCreditCardNumber(char *card_number, size_t max_len, char *card_type, size_t type_len);
void generateTCKN(char *tckn, size_t max_len);

#endif
