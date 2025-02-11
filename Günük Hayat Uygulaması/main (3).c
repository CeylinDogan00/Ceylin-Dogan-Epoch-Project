#include <stdio.h>
#include <time.h>


struct TarihSaat {
    int yil;
    int ay;
    int gun;
    int saat;
    int dakika;
    int saniye;
};


union Epoch {
    time_t epoch_saniye;
    long int epoch_long;
};


void tarihSaatAl(struct TarihSaat *ts, const char *mesaj) {
    printf("%s (YYYY MM DD HH MM SS): ", mesaj);
    scanf("%d %d %d %d %d %d", &ts->yil, &ts->ay, &ts->gun, &ts->saat, &ts->dakika, &ts->saniye);
}


time_t tarihSaatToEpoch(struct TarihSaat ts) {
    struct tm t;
    t.tm_year = ts.yil - 1900;
    t.tm_mon = ts.ay - 1;
    t.tm_mday = ts.gun;
    t.tm_hour = ts.saat;
    t.tm_min = ts.dakika;
    t.tm_sec = ts.saniye;
    t.tm_isdst = -1;
    
    return mktime(&t);
}

int main() {
    struct TarihSaat varis, kalkis;
    union Epoch epoch_varis, epoch_kalkis;

   
    tarihSaatAl(&varis, "Ilk ucusun varis saatini giriniz");
    tarihSaatAl(&kalkis, "Ikinci ucusun kalkýs saatini giriniz");

  
    epoch_varis.epoch_saniye = tarihSaatToEpoch(varis);
    epoch_kalkis.epoch_saniye = tarihSaatToEpoch(kalkis);

    
    time_t fark = difftime(epoch_kalkis.epoch_saniye, epoch_varis.epoch_saniye);

    
    printf("\nIlk ucusun inis epoch zamani: %ld saniye\n", epoch_varis.epoch_long);
    printf("Ikinci ucusun kalkýs epoch zamani: %ld saniye\n", epoch_kalkis.epoch_long);
    printf("\nAktarma suresi: %ld saniye (%ld dakika, %ld saat, %ld gün)\n",
           fark, fark / 60, fark / 3600, fark / 86400);

    return 0;
}
