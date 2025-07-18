#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

void generate_full_name(char *fullname, size_t max_len, char *name1, char *name2, char *surname, int *is_double_name);
void randomName(char *name, size_t max_len);
void randomSurname(char *surname, size_t max_len);
void generateEmail(char *email, size_t max_len);
void generatePhoneNumber(char *phone, size_t max_len);
void generateCreditCardNumber(char *card_number, size_t max_len, char *card_type, size_t type_len);
void generateTCKN(char *tckn, size_t max_len);
    void generateAll(char *fullname, char *name, char *surname, char *email, char *phone, char *tckn, char *card_number, char *card_type);

int main() {
    srand(time(NULL));

    int choice;
    char name[50];
    char surname[50];
    char fullname[100];
    char email[100];
    char phone[50];
    char card_number[20];
    char card_type[20];
    char tckn[20];
    char name1[50], name2[50];
    int is_double_name;
    size_t max_len = 100;

    do {
        printf("\n=== NEW LIFE GENERATOR ===\n");
        printf("Ne yapmak istediginizi seciniz\n");
        printf("1) Rastgele isim\n");
        printf("2) Rastgele soy isim\n");
        printf("3) Rastgele isim + soyisim\n");
        printf("4) Rastgele email adresi\n");
        printf("5) Rastgele telefon numarasi\n");
        printf("6) Rastgele kredi karti numarasi\n");
        printf("7) Rastgele TCKN\n");
        printf("8) Herseyi rastgele uret\n");
        printf("0) Programi kapat\n");
        printf("Seciminiz: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                randomName(name, max_len);
                printf("Rastgele isim: %s\n", name);
                break;
            case 2:
                randomSurname(surname, max_len);
                printf("Rastgele soyisim: %s\n", surname);
                break;
            case 3:
                generate_full_name(fullname, max_len, name1, name2, surname, &is_double_name);
                printf("Rastgele ad soyad: %s\n", fullname);
                break;
            case 4:
                generate_full_name(fullname, max_len, name1, name2, surname, &is_double_name);
                generateEmailFromParts(email, max_len, name1, name2, is_double_name, surname);
                printf("Rastgele e-posta: %s\n", email);
                break;
            case 5:
                generatePhoneNumber(phone, max_len);
                printf("Rastgele telefon numarasi: %s\n", phone);
                break;
            case 6: {
                generateCreditCardNumber(card_number, sizeof(card_number), card_type, sizeof(card_type));
                printf("Rastgele kredi karti numarasi: %s (%s)\n", card_number, card_type);
                break;
            }
            case 7:
                generateTCKN(tckn, sizeof(tckn));
                printf("Rastgele TCKN: %s\n", tckn);
                break;
            case 8:
                generate_full_name(fullname, max_len, name1, name2, surname, &is_double_name);
                generateEmailFromParts(email, max_len, name1, name2, is_double_name, surname);
                generatePhoneNumber(phone, max_len);
                generateCreditCardNumber(card_number, sizeof(card_number), card_type, sizeof(card_type));
                generateTCKN(tckn, sizeof(tckn));
                printf("Rastgele ad soyad: %s\n", fullname);
                printf("Rastgele e-posta: %s\n", email);
                printf("Rastgele telefon numarasi: %s\n", phone);
                printf("Rastgele kredi karti numarasi: %s (%s)\n", card_number, card_type);
                printf("Rastgele TCKN: %s\n", tckn);
                break;
            case 0:
                printf("Program sonlandirildi.\n");
                break;
            default:
                printf("Hatali secim yaptiniz.\n");
        }

    } while (choice != 0);

    return 0;
}
