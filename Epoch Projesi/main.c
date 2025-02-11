#include <stdio.h>
#include <time.h>

// Tarih ve saat bilgisini saklamak için struct kullanýyoruz
struct TarihSaat {
    int yil;
    int ay;
    int gun;
    int saat;
    int dakika;
    int saniye;
};

// Epoch deðerini hem integer hem de time_t türünde saklamak için union kullanýyoruz
union Epoch {
    time_t epoch_saniye;
    long int epoch_long;
};

// Kullanýcýdan tarih ve saat alýp struct içine kaydeden fonksiyon
void tarihSaatAl(struct TarihSaat *ts, int num) {
    printf("\n%d. Tarih ve Saat Giriniz (YYYY MM DD HH MM SS): ", num);
    scanf("%d %d %d %d %d %d", &ts->yil, &ts->ay, &ts->gun, &ts->saat, &ts->dakika, &ts->saniye);
}

// TarihSaat struct'ýný epoch zamanýna çeviren fonksiyon
time_t tarihSaatToEpoch(struct TarihSaat ts) {
    struct tm t;
    t.tm_year = ts.yil - 1900; // Yýl 1900'den itibaren sayýlýyor
    t.tm_mon = ts.ay - 1;      // Aylar 0'dan baþlar
    t.tm_mday = ts.gun;
    t.tm_hour = ts.saat;
    t.tm_min = ts.dakika;
    t.tm_sec = ts.saniye;
    t.tm_isdst = -1; // Gün ýþýðýndan yararlanma (DST) otomatik belirlenir
    
    return mktime(&t); // Epoch zamanýna çevir
}

int main() {
    struct TarihSaat ts1, ts2;
    union Epoch epoch1, epoch2;

    // Kullanýcýdan iki farklý tarih ve saat al
    tarihSaatAl(&ts1, 1);
    tarihSaatAl(&ts2, 2);

    // Tarihleri epoch zamanýna çevir
    epoch1.epoch_saniye = tarihSaatToEpoch(ts1);
    epoch2.epoch_saniye = tarihSaatToEpoch(ts2);

    // Zaman farkýný hesapla
    time_t fark = difftime(epoch2.epoch_saniye, epoch1.epoch_saniye);

    // Sonuçlarý ekrana yazdýr
    printf("\n1. Tarih için Epoch Zamaný: %ld saniye\n", epoch1.epoch_long);
    printf("2. Tarih için Epoch Zamaný: %ld saniye\n", epoch2.epoch_long);
    printf("Ýki tarih arasýndaki zaman farký: %ld saniye (%ld dakika, %ld saat, %ld gün)\n",
           fark, fark / 60, fark / 3600, fark / 86400);

    return 0;
}

