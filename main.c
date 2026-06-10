#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_full_name(char *fullname, size_t max_len, char *name1,
                        char *name2, char *surname, int *is_double_name);
void randomName(char *name, size_t max_len);
void randomSurname(char *surname, size_t max_len);
void generateEmail(char *email, size_t max_len);
void generatePhoneNumber(char *phone, size_t max_len);
void generateCreditCardNumber(char *card_number, size_t max_len,
                              char *card_type, size_t type_len);
void generateTCKN(char *tckn, size_t max_len);
void generateAll(char *fullname, char *name, char *surname, char *email,
                 char *phone, char *tckn, char *card_number, char *card_type);

void print_usage(const char *prog_name) {
  printf("Kullanim: %s [PARAMETRE]\n\n", prog_name);
  printf("Parametreler:\n");
  printf("  -h, --help       Yardim menusunu gosterir\n");
  printf("  -n, --name       Rastgele isim uretir\n");
  printf("  -s, --surname    Rastgele soyisim uretir\n");
  printf("  -f, --fullname   Rastgele ad soyad uretir\n");
  printf("  -e, --email      Rastgele e-posta uretir\n");
  printf("  -p, --phone      Rastgele telefon numarasi uretir\n");
  printf("  -c, --card       Rastgele kredi karti uretir\n");
  printf("  -t, --tckn       Rastgele TCKN uretir\n");
  printf("  -a, --all        Tum verileri tek seferde uretir\n\n");
  printf("Parametresiz calistirilirsa interaktif menu acilir.\n");
}

int main(int argc, char *argv[]) {
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

  if (argc > 1) {
    char *arg = argv[1];

    if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
      print_usage(argv[0]);
      return 0;
    }
    else if (strcmp(arg, "-n") == 0 || strcmp(arg, "--name") == 0) {
      randomName(name, max_len);
      printf("%s\n", name);
      return 0;
    }
    else if (strcmp(arg, "-s") == 0 || strcmp(arg, "--surname") == 0) {
      randomSurname(surname, max_len);
      printf("%s\n", surname);
      return 0;
    }
    else if (strcmp(arg, "-f") == 0 || strcmp(arg, "--fullname") == 0) {
      generate_full_name(fullname, max_len, name1, name2, surname, &is_double_name);
      printf("%s\n", fullname);
      return 0;
    }
    else if (strcmp(arg, "-e") == 0 || strcmp(arg, "--email") == 0) {
      generate_full_name(fullname, max_len, name1, name2, surname, &is_double_name);
      generateEmailFromParts(email, max_len, name1, name2, is_double_name, surname);
      printf("%s\n", email);
      return 0;
    }
    else if (strcmp(arg, "-p") == 0 || strcmp(arg, "--phone") == 0) {
      generatePhoneNumber(phone, max_len);
      printf("%s\n", phone);
      return 0;
    }
    else if (strcmp(arg, "-c") == 0 || strcmp(arg, "--card") == 0) {
      generateCreditCardNumber(card_number, sizeof(card_number), card_type, sizeof(card_type));
      printf("%s (%s)\n", card_number, card_type);
      return 0;
    }
    else if (strcmp(arg, "-t") == 0 || strcmp(arg, "--tckn") == 0) {
      generateTCKN(tckn, sizeof(tckn));
      printf("%s\n", tckn);
      return 0;
    }
    else if (strcmp(arg, "-a") == 0 || strcmp(arg, "--all") == 0) {
      generate_full_name(fullname, max_len, name1, name2, surname, &is_double_name);
      generateEmailFromParts(email, max_len, name1, name2, is_double_name, surname);
      generatePhoneNumber(phone, max_len);
      generateCreditCardNumber(card_number, sizeof(card_number), card_type, sizeof(card_type));
      generateTCKN(tckn, sizeof(tckn));
      printf("Ad Soyad: %s\n", fullname);
      printf("E-posta: %s\n", email);
      printf("Telefon: %s\n", phone);
      printf("Kredi Karti: %s (%s)\n", card_number, card_type);
      printf("TCKN: %s\n", tckn);
      return 0;
    }
    else {
      printf("Hata: Bilinmeyen parametre '%s'\n\n", arg);
      print_usage(argv[0]);
      return 1;
    }
  }

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
      generate_full_name(fullname, max_len, name1, name2, surname,
                         &is_double_name);
      printf("Rastgele ad soyad: %s\n", fullname);
      break;
    case 4:
      generate_full_name(fullname, max_len, name1, name2, surname,
                         &is_double_name);
      generateEmailFromParts(email, max_len, name1, name2, is_double_name,
                             surname);
      printf("Rastgele e-posta: %s\n", email);
      break;
    case 5:
      generatePhoneNumber(phone, max_len);
      printf("Rastgele telefon numarasi: %s\n", phone);
      break;
    case 6: {
      generateCreditCardNumber(card_number, sizeof(card_number), card_type,
                               sizeof(card_type));
      printf("Rastgele kredi karti numarasi: %s (%s)\n", card_number,
             card_type);
      break;
    }
    case 7:
      generateTCKN(tckn, sizeof(tckn));
      printf("Rastgele TCKN: %s\n", tckn);
      break;
    case 8:
      generate_full_name(fullname, max_len, name1, name2, surname,
                         &is_double_name);
      generateEmailFromParts(email, max_len, name1, name2, is_double_name,
                             surname);
      generatePhoneNumber(phone, max_len);
      generateCreditCardNumber(card_number, sizeof(card_number), card_type,
                               sizeof(card_type));
      generateTCKN(tckn, sizeof(tckn));
      printf("Rastgele ad soyad: %s\n", fullname);
      printf("Rastgele e-posta: %s\n", email);
      printf("Rastgele telefon numarasi: %s\n", phone);
      printf("Rastgele kredi karti numarasi: %s (%s)\n", card_number,
             card_type);
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
