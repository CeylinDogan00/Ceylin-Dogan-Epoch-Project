#include <stdio.h>
#include <time.h>

// Tarih ve saat bilgisini saklamak i�in struct kullan�yoruz
struct TarihSaat {
    int yil;
    int ay;
    int gun;
    int saat;
    int dakika;
    int saniye;
};

// Epoch de�erini hem integer hem de time_t t�r�nde saklamak i�in union kullan�yoruz
union Epoch {
    time_t epoch_saniye;
    long int epoch_long;
};

// Kullan�c�dan tarih ve saat al�p struct i�ine kaydeden fonksiyon
void tarihSaatAl(struct TarihSaat *ts, int num) {
    printf("\n%d. Tarih ve Saat Giriniz (YYYY MM DD HH MM SS): ", num);
    scanf("%d %d %d %d %d %d", &ts->yil, &ts->ay, &ts->gun, &ts->saat, &ts->dakika, &ts->saniye);
}

// TarihSaat struct'�n� epoch zaman�na �eviren fonksiyon
time_t tarihSaatToEpoch(struct TarihSaat ts) {
    struct tm t;
    t.tm_year = ts.yil - 1900; // Y�l 1900'den itibaren say�l�yor
    t.tm_mon = ts.ay - 1;      // Aylar 0'dan ba�lar
    t.tm_mday = ts.gun;
    t.tm_hour = ts.saat;
    t.tm_min = ts.dakika;
    t.tm_sec = ts.saniye;
    t.tm_isdst = -1; // G�n �����ndan yararlanma (DST) otomatik belirlenir
    
    return mktime(&t); // Epoch zaman�na �evir
}

int main() {
    struct TarihSaat ts1, ts2;
    union Epoch epoch1, epoch2;

    // Kullan�c�dan iki farkl� tarih ve saat al
    tarihSaatAl(&ts1, 1);
    tarihSaatAl(&ts2, 2);

    // Tarihleri epoch zaman�na �evir
    epoch1.epoch_saniye = tarihSaatToEpoch(ts1);
    epoch2.epoch_saniye = tarihSaatToEpoch(ts2);

    // Zaman fark�n� hesapla
    time_t fark = difftime(epoch2.epoch_saniye, epoch1.epoch_saniye);

    // Sonu�lar� ekrana yazd�r
    printf("\n1. Tarih i�in Epoch Zaman�: %ld saniye\n", epoch1.epoch_long);
    printf("2. Tarih i�in Epoch Zaman�: %ld saniye\n", epoch2.epoch_long);
    printf("�ki tarih aras�ndaki zaman fark�: %ld saniye (%ld dakika, %ld saat, %ld g�n)\n",
           fark, fark / 60, fark / 3600, fark / 86400);

    return 0;
}

