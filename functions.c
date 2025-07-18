#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include <string.h>
#include <math.h> // for pow
#include <ctype.h> // for tolower

// Turkish to ASCII transliteration function
void transliterate_turkish(const char *src, char *dest, size_t max_len) {
    size_t j = 0;
    while (*src && j < max_len - 1) {
        // Check for UTF-8 encoded Turkish characters
        if ((unsigned char)src[0] == 0xc3) {
            switch ((unsigned char)src[1]) {
                case 0xbc: dest[j++] = 'u'; src += 2; continue; // ü
                case 0x9c: dest[j++] = 'U'; src += 2; continue; // Ü
                case 0xb6: dest[j++] = 'o'; src += 2; continue; // ö
                case 0x96: dest[j++] = 'O'; src += 2; continue; // Ö
                case 0xa7: dest[j++] = 'c'; src += 2; continue; // ç
                case 0x87: dest[j++] = 'C'; src += 2; continue; // Ç
                case 0x9f: dest[j++] = 's'; src += 2; continue; // ş
                case 0x98: dest[j++] = 'S'; src += 2; continue; // Ş
            }
        } else if ((unsigned char)src[0] == 0xc4) {
            switch ((unsigned char)src[1]) {
                case 0xb1: dest[j++] = 'i'; src += 2; continue; // ı
                case 0xb0: dest[j++] = 'I'; src += 2; continue; // İ
                case 0x9f: dest[j++] = 'g'; src += 2; continue; // ğ
                case 0x9e: dest[j++] = 'G'; src += 2; continue; // Ğ
            }
        }
        // If not a special character, just copy
        dest[j++] = *src++;
    }
    dest[j] = '\0';
}

// Male and female name lists
const char* male_names[] = {
    "Ahmet", "Mehmet", "Mustafa", "Ali", "Hüseyin", "Hasan", "İbrahim", "Yusuf", "Murat", "Ramazan",
    "Osman", "Halil", "Recep", "Enes", "Kerem", "Burak", "Emir", "Furkan", "Umut", "Can",
    "Tayfun", "Cem", "Ömer", "Bekir", "Eren", "Kaan", "Yunus", "Onur", "Taha", "Selim",
    "Yavuz", "Alper", "Baran", "Tolga", "Eray", "Fatih", "Arda", "Batuhan", "Samet", "Serkan",
    "Kenan", "Kadir", "Serhat", "Gökhan", "Emre", "Oğuz", "Egemen", "Volkan", "Sefa", "İsmail",
    "Berk", "Berat", "Talha", "Yigit", "Hakan", "Alp", "Çağrı", "Cihan", "Mert", "Ege",
    "Ayhan", "Harun", "Rıdvan", "Barış", "Adem", "Şahin", "Erkan", "Doğukan", "Görkem", "Rasim",
    "İlker", "Kutay", "Levent", "Uğur", "Deniz", "Atakan", "Sinan", "Nihat", "Şükrü", "Koray",
    "Bektaş", "Aykut", "Fikret", "Halit", "İdris", "Servet", "Veysel", "Hayati", "Nuri", "Tuncay",
    "Orhan", "Bahadır", "Salih", "Mahmut", "Vedat", "Talat", "Cemal", "Turan", "Yılmaz", "Coşkun",
    "Zafer", "Nazım", "Latif", "İhsan", "Sami", "Nevzat", "Refik", "Metin", "Zeki", "Durmuş",
    "Fazıl", "Fuat", "Cavit", "Hilmi", "Bedirhan", "Berkan", "Yiğitcan", "Kubilay", "Bülent", "Ergin",
    "Burhan", "Okan", "Kutlu", "Doğan", "Ufuk", "Taylan", "Melih", "Ergün", "Alpay", "Tamer",
    "Tunahan", "Barışcan", "Özgür", "Ferhat", "Rüstem", "Kıvanç", "Yekta", "Ulaş", "Arif", "Haluk",
    "Tuncer", "Ferdi", "İlyas", "Süleyman", "Ekrem", "Nail", "Sabri", "Şevket", "Mazhar", "Reşat",
    "Selahattin", "Gani", "Mevlüt", "İrfan", "Sadi", "Abdullah", "Zekeriya", "Mesut", "Yüksel", "Nevfel",
    "Ergül", "Cüneyt", "İkbal", "Hidayet", "Tuncel", "Ömer Faruk", "Abdurrahman", "Bedreddin", "Kâmil", "Kenan",
    "Şahin", "Tayyar", "Aziz", "Yücel", "Erkut", "Temel", "Orçun", "Rahmi", "İsmail Hakkı", "Abdülkadir",
    "Mustafa Kemal", "Muhammet", "Saffet", "Ferami","Fetullah", "Ramazan Ali", "Behçet", "Vefa", "Nejat", "Reha", "Şenol",
    "Ragıp", "Seyfettin", "Muzaffer", "Teoman", "Edip", "Kazım", "Muhittin", "Tarık", "Remzi", "Baki",
    "Sabahattin", "Lütfi", "Selçuk", "Ziver", "Bayram", "Suat", "Yaşar", "Seyit", "İshak", "Ercan",
    "Abdurrahim", "Mehmet Emin", "Münir", "Yalçın", "Engin", "Ahmet Can", "Aras", "Bartu", "Ozan", "Çağan",
    "Doruk", "Yiğit Alp", "Mert Ali", "Caner", "Murat Can", "Emre Can", "Burak Can", "Berke", "Yiğit Efe", "Ayberk",
    "Atilla", "Ersel", "Koral", "Barlas", "Demir", "Göktuğ", "Yamaç", "Tunç", "Atlas", "Oğuzhan",
    "Alparslan", "Efe", "Altan", "Tibet", "Arınç", "Mirkan", "Kayra", "Ilgaz", "Dorukan", "Çağatay",
    "Ulaşcan", "Durukan", "Orhun", "Yalın", "Berkehan", "Çağıl", "Özkan", "Rüzgar", "Ata", "Sencer",
    "Noyan", "Temir", "Demiralp", "Aybars", "Kürşat", "Kutalmış", "Erkam", "Arkut", "Yarkın", "Tan",
    "Yavuz Selim", "Boran", "Tardu", "Barın", "Timur", "Algan", "Süer", "Doğruer", "Taner", "Armağan",
    "Sarp", "Soykan", "Yüce", "Gökçen", "Berkay", "Uras", "Süha", "Mestan", "Sencer Alp", "Gökalp",
    "Baybars", "Batu", "Boğaç", "Yekhan", "Serdil", "Taşkın", "Bulut", "Oytun", "Savran", "Arel",
    "Burç", "Oruç", "Tayboğa"
};
#define MALE_NAME_COUNT (sizeof(male_names) / sizeof(male_names[0]))

const char* female_names[] = {
    "Ayşe", "Fatma", "Emine", "Elif", "Zeynep", "Hatice", "Meryem", "Hümeyra", "Şeyma", "Kübra",
    "Rabia", "Nisa", "Zehra", "İlayda", "Büşra", "Sümeyye", "Beyza", "Melisa", "Damla", "Ceyda",
    "Derya", "Eda", "Nazlı", "Sena", "Gamze", "Ayşegül", "Tuğba", "Sevgi", "Gül", "Nur",
    "Yasemin", "Aylin", "İrem", "Esra", "Melike", "Betül", "Merve", "Gözde", "Gülşah", "Canan",
    "Zeliha", "Nurgül", "Sibel", "Selin", "Necla", "Fadime", "Perihan", "Dilara", "Azra", "Sude",
    "Nehir", "Aleyna", "Aslı", "Hande", "Hilal", "Melek", "Nermin", "Sevda", "Lale", "Elvan",
    "Bahar", "Yıldız", "Serap", "Belgin", "Gülçin", "Feride", "Berrin", "Aysun", "Esma", "Mihriban",
    "Gülizar", "Nevin", "Gönül", "Nazan", "Arzu", "Gülsüm", "Selma", "Naciye", "Hülya", "Cansu",
    "Gülay", "Çiğdem", "Figen", "Reyhan", "Funda", "Rukiye", "Pınar", "Seher", "Şule", "Nihan",
    "Demet", "Sevil", "Saliha", "Şirin", "Gülben", "Ceylan", "Sevim", "Leman", "Tülay", "Arife",
    "Nursel", "Gülseren", "Elçin", "Binnur", "Gülperi", "Hayriye", "Aysel", "Suna", "Hicran", "Suzan",
    "Aybike", "Hanzade", "Kevser", "Cemile", "Meltem", "Nihal", "Eylül", "Hazal", "Hira", "Rüya",
    "Beste", "İdil", "Alara", "Çağla", "Lal", "Arven", "Bade", "Şevval", "Ecrin", "Afra",
    "İklim", "Neva", "Mina", "Dila", "Serra", "Tülin", "Seray", "Berfin", "Tuana", "Berna",
    "Gülin", "Meral", "İkbal", "İlknur", "Duygu", "Gülru", "Nazife", "Medine", "Bedia", "Şükran",
    "Zahide", "Tuba", "Saliha", "Vildan", "Güner", "Gülten", "Şermin", "İmran", "Nadire", "Sadiye",
    "Cemre", "İnci", "Banu", "Ayla", "Seval", "Zülal", "Birgül", "Nurcan", "Günay", "Esin",
    "Melda", "Huriye", "Sebahat", "Dilek", "Hayal", "Bedriye", "Nefise", "Nazire", "Hilmiye", "Macide",
    "Ayten", "Nursima", "Aycan", "Güliz", "Rengin", "Rezzan", "Naz", "Gülbeyaz", "Gülsena", "Hicret",
    "Mehtap", "Halime", "Fatmanur", "Nursena", "Feryal", "Melis", "Derya", "Şahika", "Remziye", "Sıla",
    "Asuman", "Yelda", "Burcu", "Dilan", "Sezen", "Sibel", "İlknaz", "Tenzile", "Nisa Nur", "Ayşenur",
    "Emel", "Munise", "Munira", "Tansel", "Zehra Nur", "Hasibe", "Aynur", "Şahide", "Dilber", "Gülgün",
    "Nuran", "Münevver", "Nigar", "Hediye", "Aynişah", "Halide", "Cennet", "Songül", "Elvan", "Gülnihal",
    "Müzeyyen", "Sadiye", "Nuray", "Gülse", "İlayda", "Süreyya", "Gülce", "Yağmur", "Kardelen", "Aydan",
    "Bihter", "Gülhan", "Rana", "Umay", "Gülsu", "Duygu", "Ayda", "Bengisu", "Selda", "Elifnaz",
    "Kevser", "Şura", "Zeynepnur", "Sînan", "Nuriye", "Firuze", "Munise", "Medine", "Azize", "Nezahat",
    "Nezire", "Mislina", "Yaren", "İlay", "Yasemin Nur", "Bedia", "Nagehan", "Nihan", "Hüsniye", "Hanife",
    "Hafize", "Lütfiye", "Naime", "Pakize", "Türkan", "Neval", "Zeynep Su", "Nil", "Nisan", "Nilsu",
    "Armina", "Cansel", "Miray", "Almina", "Melodi", "Elifnaz", "Cemile Nur", "Eylül Su", "Beste Nur", "Asiye",
    "Ceylin", "Gülnaz", "Hilal Nur", "Betigül", "Sultan", "Güler", "Zerrin", "Gülendam", "İffet", "Gülkız"
};
#define FEMALE_NAME_COUNT (sizeof(female_names) / sizeof(female_names[0]))

const char* surname_list[] = {
    "Yılmaz", "Kaya", "Demir", "Şahin", "Çelik", "Yıldız", "Aydın", "Arslan", "Doğan", "Kurt",
    "Koç", "Öztürk", "Özdemir", "Polat", "Kılıç", "Aksoy", "Erdoğan", "Ergin", "Avcı", "Aslan",
    "Özkan", "Taş", "Güneş", "Yalçın", "Çetin", "Uçar", "Turan", "Bozkurt", "Karataş", "Erden",
    "Eren", "Karaca", "Toprak", "Bayraktar", "Gökçe", "Keskin", "Uzun", "Sarı", "Karaman", "Yüce",
    "Önal", "Albayrak", "Dinçer", "Başar", "Bulut", "Tuna", "Acar", "Gür", "Gündüz", "Sezer",
    "Özgür", "Köksal", "Türkmen", "Erbaş", "Güler", "Özer", "İnce", "Yavuz", "Köroğlu", "Işık",
    "Can", "Kaplan", "Baran", "Yalvaç", "Altun", "Ersoy", "Sert", "Bilgin", "Baykal", "Bozkaya",
    "Yıldırım", "Kurtuluş", "Özçelik", "Şentürk", "Çakır", "Aktaş", "Uysal", "Bal", "Karakaya", "Ateş",
    "Gürbüz", "Balcı", "Tekin", "Dağ", "Köse", "Yurtseven", "Doğru", "Tan", "Kavak", "Şimşek",
    "Altıntaş", "Yazıcı", "Durmaz", "Tetik", "Boz", "Koyuncu", "Elmas", "Öcalan", "Ermiş", "Özbey", "Kaleli",
    "Öztuna", "Durukan", "Solmaz", "Ekinci", "Taşçı", "İlhan", "Baş", "Gül", "Yaman", "Bayındır",
    "Karakuş", "Kural", "Yardımcı", "Ertaş", "Demirtaş", "İpek", "Eroğlu", "Gökmen", "Gültekin", "Karabulut",
    "Tanrıkulu", "Türkmenoğlu", "Deniz", "Çevik", "Kara", "İnanç", "Yurt", "Savaş", "Özkanlı", "Özpolat",
    "Barış", "Aydoğdu", "Tok", "Deliktaş", "Tokgöz", "Oymak", "Uz", "Sağlam", "Türkmenler", "Bilge",
    "Kalaycı", "Özbilen", "Karataşlı", "Soylu", "Özkaya", "Gümüş", "Şanlı", "Bektaş", "Göçmen", "Poyraz",
    "Ünal", "Sarıoğlu", "Akar", "Beyaz", "Bozdoğan", "Demirel", "Köprücü", "Canpolat", "Başaran", "Çalışkan",
    "Altay", "Özbay", "Yeşil", "Çoban", "Gürkan", "İlter", "Bayraktaroğlu", "Sevgi", "Gönül", "Ece", "Bingöl",
    "Koçoğlu", "Göçer", "Fırtına", "Sağır", "Bayındıroğlu", "Balkan", "Tunç", "Aydemir", "Mutlu", "Sancak",
    "Güleç", "Orhan", "Ergün", "Kocabaş", "Alkan", "Tanış", "Ergül", "Özkurt", "Yurdakul", "Ağaç",
    "Bozkurtlar", "Çam", "Demirtaşoğlu", "Esen", "İlker", "Yörük", "Ulusoy", "Yürek", "Bayram", "Sönmez",
    "Ayhan", "Yıldıztekin", "Alp", "Altındağ", "Kanal", "Özçınar", "Sertel", "Karakurt", "İlboğa", "Kızıl",
    "Bozok", "Üstün", "Tetikçi", "Güven", "Ertem", "Arı", "Teker", "Saygı", "Öztoprak", "Erkek", "Akıncı",
    "Yorgancı", "Uzuntaş", "Özdemiroğlu", "Türkmenli", "Gezer", "Erkut", "Gülmez", "Tetiktaş", "Karakoç", "Delibaş",
    "Konak", "Güzel", "Kurtoğlu", "Özata", "Yurttaş", "Balta", "Erbay", "Bilmez", "Çınar", "Yumuşak",
    "Aydınlık", "Bozkuş", "Altın", "Göksu", "Güllü", "Karacaoğlu", "Özen", "Kızılkaya", "Üstüner", "Candan",
    "Bora", "Karan", "Demirci", "Durdu", "Uğurlu", "Karamanlı", "Yeşiltaş","Gülen", "Doğaner", "Türkdoğan", "Alagöz",
    "Yalın", "İlboz", "Ertekin", "Kalem", "Aytaç", "Oğuz", "Yücesoy", "Kösemen", "Çakıroğlu", "Güvenç",
    "Alpsoy", "Kocatürk", "Yavuzoğlu", "Çelikkan", "Yolaç", "Karabacak", "Görkem", "Baytekin", "Akça", "Taşkın",
    "Turaç", "Çağlar", "Alpdoğan", "Türkmenbaş", "Akçay", "Soykan", "Soydan", "Soydaş", "Soysal", "Soydemir",
    "Soykurt", "Soysalan", "Soyboğa", "Soytekin", "Soybaş", "Soyarslan", "Soykut", "Soyel", "Soyöz", "Soygül",
    "Soybulut", "Soygüven", "Soyerdem"
};
#define SURNAME_COUNT (sizeof(surname_list) / sizeof(surname_list[0]))


// Updated full name generator: outputs selected names and surname
void generate_full_name(char *fullname, size_t max_len, char *name1, char *name2, char *surname, int *is_double_name) {
    int gender = rand() % 2; // 0: male, 1: female
    int two_names = rand() % 2; // 0: one name, 1: two names
    *is_double_name = two_names;
    if (gender == 0) {
        strcpy(name1, male_names[rand() % MALE_NAME_COUNT]);
        if (two_names) {
            do {
                strcpy(name2, male_names[rand() % MALE_NAME_COUNT]);
            } while (strcmp(name1, name2) == 0);
        } else {
            name2[0] = '\0';
        }
    } else {
        strcpy(name1, female_names[rand() % FEMALE_NAME_COUNT]);
        if (two_names) {
            do {
                strcpy(name2, female_names[rand() % FEMALE_NAME_COUNT]);
            } while (strcmp(name1, name2) == 0);
        } else {
            name2[0] = '\0';
        }
    }
    strcpy(surname, surname_list[rand() % SURNAME_COUNT]);
    if (two_names) {
        snprintf(fullname, max_len, "%s %s %s", name1, name2, surname);
    } else {
        snprintf(fullname, max_len, "%s %s", name1, surname);
    }
}

// New: generate email from given name(s) and surname
void generateEmailFromParts(char *email, size_t max_len, const char *name1, const char *name2, int is_double_name, const char *surname) {
    const char* emailDomains[] = {
        "gmail.com", "hotmail.com", "yahoo.com", "mail.com", "icloud.com", "outlook.com"
    };
    #define DOMAIN_COUNT (sizeof(emailDomains) / sizeof(emailDomains[0]))
    char ascii_name1[64], ascii_name2[64], ascii_surname[64], email_raw[256];
    transliterate_turkish(name1, ascii_name1, sizeof(ascii_name1));
    if (is_double_name && name2 && name2[0] != '\0') {
        transliterate_turkish(name2, ascii_name2, sizeof(ascii_name2));
    } else {
        ascii_name2[0] = '\0';
    }
    transliterate_turkish(surname, ascii_surname, sizeof(ascii_surname));
    int domain_index = rand() % DOMAIN_COUNT;
    // Random number (2-4 digits)
    int rand_num = rand() % 10000; // 0-9999
    int num_digits = 2 + rand() % 3; // 2, 3, or 4 digits
    char rand_num_str[5];
    snprintf(rand_num_str, sizeof(rand_num_str), "%0*d", num_digits, rand_num % (int)pow(10, num_digits));
    if (is_double_name && ascii_name2[0] != '\0') {
        snprintf(email_raw, sizeof(email_raw), "%s.%s%s.%s@%s", ascii_name1, ascii_name2, rand_num_str, ascii_surname, emailDomains[domain_index]);
    } else {
        snprintf(email_raw, sizeof(email_raw), "%s%s.%s@%s", ascii_name1, rand_num_str, ascii_surname, emailDomains[domain_index]);
    }
    // Convert to lowercase
    size_t i;
    for (i = 0; email_raw[i] && i < max_len - 1; ++i) {
        email[i] = (char)tolower((unsigned char)email_raw[i]);
    }
    email[i] = '\0';
}

// Rastgele isim secen fonksiyon
// Random name generator function
void randomName(char *name, size_t max_len) {

    int gender = rand() % 2;
    if (gender == 0) {
        int idx = rand() % MALE_NAME_COUNT;
        snprintf(name, max_len, "%s", male_names[idx]);
    } else {
        int idx = rand() % FEMALE_NAME_COUNT;
        snprintf(name, max_len, "%s", female_names[idx]);
    }
}



// Rastgele soy isim veren fonksiyon
// Random surname generator function
void randomSurname(char *surname, size_t max_len) {

    int surname_index = rand() % SURNAME_COUNT;

    snprintf(surname, max_len, "%s", surname_list[surname_index]);
}


// Rastgele mail adresi olusturan fonksiyon
// Random email address generator function
void generateEmail(char *email, size_t max_len) {
    const char* emailDomains[] = {
        "gmail.com", "hotmail.com", "yahoo.com", "mail.com", "icloud.com", "outlook.com"
    };
    #define DOMAIN_COUNT (sizeof(emailDomains) / sizeof(emailDomains[0]))
    int gender = rand() % 2;
    const char *name, *surname;
    char ascii_name[64], ascii_surname[64];
    if (gender == 0) {
        name = male_names[rand() % MALE_NAME_COUNT];
    } else {
        name = female_names[rand() % FEMALE_NAME_COUNT];
    }
    surname = surname_list[rand() % SURNAME_COUNT];
    transliterate_turkish(name, ascii_name, sizeof(ascii_name));
    transliterate_turkish(surname, ascii_surname, sizeof(ascii_surname));
    int domain_index = rand() % DOMAIN_COUNT;
    snprintf(email, max_len, "%s.%s@%s", ascii_name, ascii_surname, emailDomains[domain_index]);
}


// Rastgele telefon numarasi
// Random turkish phone number generator function
void generatePhoneNumber(char *phone, size_t max_len) {

    int prefix[] = {530, 531, 532, 533, 534, 535, 536, 537, 538, 539};
    int p = prefix[rand() % 10];
    int r1 = rand() % 1000;
    int r2 = rand() % 10000;

    snprintf(phone, max_len, "0%d %03d %04d", p, r1, r2);

}

// Rastgele kredi karti numarasi ve tipi ureten fonksiyon
// Random credit card number and type generator function
void generateCreditCardNumber(char *card_number, size_t max_len, char *card_type, size_t type_len) {
    int card = rand() % 3; // 0: Visa, 1: MasterCard, 2: Amex
    if (card == 0) { // Visa
        strncpy(card_type, "Visa", type_len);
        int prefix[] = {4000, 4001, 4002, 4003, 4004, 4005, 4006, 4007, 4008, 4009};
        int p = prefix[rand() % 10];
        int n2 = rand() % 10000;
        int n3 = rand() % 10000;
        int n4 = rand() % 10000;
        snprintf(card_number, max_len, "%04d %04d %04d %04d", p, n2, n3, n4);
    } else if (card == 1) { // MasterCard
        strncpy(card_type, "MasterCard", type_len);
        int prefix[] = {5100, 5200, 5300, 5400, 5500};
        int p = prefix[rand() % 5];
        int n2 = rand() % 10000;
        int n3 = rand() % 10000;
        int n4 = rand() % 10000;
        snprintf(card_number, max_len, "%04d %04d %04d %04d", p, n2, n3, n4);
    } else { // Amex
        strncpy(card_type, "Amex", type_len);
        int prefix[] = {3400, 3700};
        int p = prefix[rand() % 2];
        int n2 = rand() % 1000000; // 6 digits
        int n3 = rand() % 100000;  // 5 digits
        snprintf(card_number, max_len, "%04d %06d %05d", p, n2, n3);
    }
}
// Rastgele TCKN ureten fonksiyon  
// Random TCKN(Turkish Identity Number) generator function
void generateTCKN(char *tckn, size_t max_len) {
    // 11 haneli rastgele TCKN üret (gerçek algoritma değil, örnek)
    if (max_len < 12) { tckn[0] = '\0'; return; }
    tckn[0] = '1' + rand() % 9; // ilk hane 1-9
    for (int i = 1; i < 11; i++) {
        tckn[i] = '0' + rand() % 10;
    }
    tckn[11] = '\0';
}

// Rastgele tüm bilgileri ureten fonksiyon
// Random all information generator function
void generateAll(char *fullname, char *name, char *surname, char *email, char *phone, char *tckn, char *card_number, char *card_type){
    char name1[50], name2[50], local_surname[50];
    int is_double_name;
    generate_full_name(fullname, 100, name1, name2, local_surname, &is_double_name);
    if (is_double_name) {
        snprintf(name, 50, "%s %s", name1, name2);
    } else {
        snprintf(name, 50, "%s", name1);
    }
    snprintf(surname, 50, "%s", local_surname);
    generateEmailFromParts(email, 100, name1, name2, is_double_name, local_surname);
    generatePhoneNumber(phone, 50);
    generateTCKN(tckn, 50);
    generateCreditCardNumber(card_number, 20, card_type, 20);
}
