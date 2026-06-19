# PersonaTurk

## English Description

**PersonaTurk** is a C project that generates realistic random Turkish personal data for testing, development, and educational purposes. It can create random Turkish names, surnames, email addresses, phone numbers, credit card numbers, and Turkish ID numbers (TCKN) with a single command-line interface.

### Features
- Random Turkish male and female names
- Random Turkish surnames
- Consistent full name and email generation
- Random Turkish phone numbers
- Random credit card numbers (Visa, MasterCard, Amex)
- Random Turkish ID numbers (TCKN)
- All data is generated in a realistic and format-correct way

### Usage

####  Compilation & Installation (Using Makefile)
You can easily compile and install the application globally:
1. **Compile:**
   ```sh
   make
   ```
2. **Install globally (Optional):**
   ```sh
   make install
   ```
   *Now you can run `persona_turk` from any directory.*
3. **Clean build files:**
   ```sh
   make clean
   ```

#### 🐳 Using Docker
If you don't have GCC or Make installed, you can build and run using Docker:
1. **Build image:**
   ```sh
   docker build -t persona_turk .
   ```
2. **Run container (Interactive):**
   ```sh
   docker run -it persona_turk
   ```

####  Running Modes
* **Interactive Menu (Default):**
  If you run it without any arguments, it will open the interactive menu:
  ```sh
  ./persona_turk
  ```
* **CLI Mode (Parameters):**
  You can generate specific data directly without entering the menu:
  ```sh
  ./persona_turk -n          # Generates a random name
  ./persona_turk --surname   # Generates a random surname
  ./persona_turk --fullname  # Generates a random full name
  ./persona_turk -e          # Generates a random email
  ./persona_turk -p          # Generates a random phone number
  ./persona_turk -c          # Generates a random credit card
  ./persona_turk -t          # Generates a random TCKN
  ./persona_turk -a          # Generates all information at once
  ./persona_turk -h          # Shows the help menu
  ```

---

## Türkçe Açıklama

**PersonaTurk**, test, geliştirme ve eğitim amaçlı gerçekçi rastgele Türk kişisel verileri üreten bir C projesidir. Komut satırı arayüzü ile rastgele Türkçe isim, soyisim, e-posta, telefon numarası, kredi kartı numarası ve TCKN üretebilir.

### Özellikler
- Rastgele Türkçe erkek ve kadın isimleri
- Rastgele Türkçe soyadları
- Tutarlı ad-soyad ve e-posta üretimi
- Rastgele Türkçe telefon numarası
- Rastgele kredi kartı numarası (Visa, MasterCard, Amex)
- Rastgele TCKN (Türkiye Cumhuriyeti Kimlik Numarası)
- Tüm veriler gerçekçi ve formatına uygun şekilde üretilir

### Kullanım

####  Derleme ve Kurulum (Makefile ile)
Uygulamayı kolayca derleyebilir ve sisteminize kurabilirsiniz:
1. **Derleyin:**
   ```sh
   make
   ```
2. **Sisteme Kurun (İsteğe Bağlı):**
   ```sh
   make install
   ```
   *Artık terminalin her yerinden sadece `persona_turk` yazarak programı çalıştırabilirsiniz.*
3. **Derleme Dosyalarını Temizleyin:**
   ```sh
   make clean
   ```

####  Docker ile Çalıştırma
Bilgisayarınızda GCC veya Make kurulu değilse, Docker kullanarak çalıştırabilirsiniz:
1. **İmajı Derleyin:**
   ```sh
   docker build -t persona_turk .
   ```
2. **Konteyneri Çalıştırın (İnteraktif):**
   ```sh
   docker run -it persona_turk
   ```

####  Çalıştırma Modları
* **Etkileşimli Menü (Varsayılan):**
  Hiçbir parametre vermeden çalıştırırsanız interaktif seçim menüsü açılır:
  ```sh
  ./persona_turk
  ```
* **Komut Satırı Parametreleri (CLI Modu):**
  Menüye girmeden doğrudan veri üretmek için aşağıdaki parametreleri kullanabilirsiniz:
  ```sh
  ./persona_turk -n          # Rastgele isim üretir
  ./persona_turk --surname   # Rastgele soyisim üretir
  ./persona_turk --fullname  # Rastgele ad soyad üretir
  ./persona_turk -e          # Rastgele e-posta üretir
  ./persona_turk -p          # Rastgele telefon numarası üretir
  ./persona_turk -c          # Rastgele kredi kartı üretir
  ./persona_turk -t          # Rastgele TCKN üretir
  ./persona_turk -a          # Tüm verileri tek seferde üretir
  ./persona_turk -h          # Yardım menüsünü gösterir
  ```

---

### Credits
- Developed by @taninyilmaz
- Inspired by Turkish data formats and real-life use cases

---
