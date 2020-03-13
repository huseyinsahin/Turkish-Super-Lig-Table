/*
#Ad-Soyad = Huseyin Sahin
#E-posta = huseyin.sahin@ceng.ktu.edu.tr
#Proje = Turkish Super Lig Table
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct takim takim;
typedef struct lig lig;

struct takim{
    char isim[12];
    char k_isim;
    int oynanan_mac;
    int galibiyet;
    int beraberlik;
    int maglubiyet;
    int atilan_gol;
    int yenilen_gol;
    int averaj;
    int puan;
};

struct lig{
    takim *takimlar;
    int takim_sayisi;
    int max_takim_sayisi;
    int **skor_matrisi;
    int **oyun_matrisi;
    int g_puan;
    int b_puan;
    int m_puan;
};


void takim_goster(takim*);
void takimlari_listele(lig*);
lig* lig_olustur();
void takim_oku(lig*,const char*);
void skor_oku(lig*,const char*);
void skor_oku_klavyeden(lig*);
void ayar_oku(lig*,const char*);
void oyna(lig*,char,int,char,int);
void takim_ekle(lig*,const char*);
void matrisi_ciz(lig*);
void b_skor_tablosu_ciz(lig*);
void k_skor_tablosu_ciz(lig*);
void sirala_puan(lig*);
void sirala_k_isim(lig*);
void sirala_isim(lig*);
void takas(takim*,takim*);
char* kucult(const char*);
char* buyult(const char*);

int main(){
    int x = 1,y = 2, z = 0;
    char c;//sirf hata duzelsin diye eklendi
    lig *l = lig_olustur();
    ayar_oku(l,"ayarlar.txt");
    takim_oku(l,"takimlar.txt");
    //takimlari_listele(l);
    b_skor_tablosu_ciz(l);
    printf("Sonuclari nerden okumak istersiniz? Dosya icin 0, klavye icin 1 = ");
    scanf("%d",&z);
    if(z == 0)
    {
        skor_oku(l,"maclar1.txt");
    }
    else if(z == 1)
    {
        scanf("%c",&c);
        while(x != 2){
            skor_oku_klavyeden(l);
            printf("Mac eklemeye devam icin 1, tamam icin 2 =");
            scanf("%d",&x);
            scanf("%c",&c);
        }
    }
    printf("Tabloyu nasil siralayalim, isme gore 0, puana gore 1 = ");
    scanf("%d",&x);
    scanf("%c",&c);
    printf("Takim adlarini nasil yazdiralim, buyuk harf icin 0, kucuk harf icin 1 = ");
    scanf("%d",&y);
    scanf("%c",&c);
    if(x == 1 && y == 1){
        sirala_puan(l);
        k_skor_tablosu_ciz(l);
    }
    if(x == 0 && y == 1){
        sirala_isim(l);
        k_skor_tablosu_ciz(l);
    }
    if(x == 1 && y == 0){
        sirala_puan(l);
        b_skor_tablosu_ciz(l);
    }
    if(x == 0 && y == 0){
        sirala_isim(l);
        b_skor_tablosu_ciz(l);
    }
    return 0;
}

void takim_goster(takim *t){
    printf("Takim adi : %s\n",t->isim);
    printf("Takim kisa adi : %c\n",t->k_isim);
    printf("Oynanan mac : %d\n",t->oynanan_mac);
    printf("Galibiyet : %d\n",t->galibiyet);
    printf("Beraberlik : %d\n",t->beraberlik);
    printf("Maglubiyet : %d\n",t->maglubiyet);
    printf("Atilan gol : %d\n",t->atilan_gol);
    printf("Yenilen gol : %d\n",t->yenilen_gol);
    printf("Averaj : %d\n",t->averaj);
    printf("Puan : %d\n",t->puan);
}

void takimlari_listele(lig *l){
    for(int i = 0;i < l->takim_sayisi;i++){
        takim_goster(&l->takimlar[i]);
    }
}

lig* lig_olustur(){
    lig *l = (lig*)calloc(1,sizeof(lig));
    l->g_puan = 2;
    l->b_puan = 1;
    l->m_puan = -1;
    return l;
}

void takim_oku(lig *l,const char *dosya_adi){
    FILE *fp = fopen(dosya_adi,"r");
    char isim[12];
    if(fp){
        while(fscanf(fp,"%s",isim) == 1){
        takim_ekle(l,isim);
        }
    }
}

void skor_oku(lig *l,const char *dosya_adi){
    FILE *fp = fopen(dosya_adi,"r");
    char t1,t2;
    int s1,s2;
    if(fp){
    //dosyadan satir okuyabildigi surece dongude kal (tum dosyayı okuyabilmek icin)
        while(fscanf(fp,"%c %d %c %d ",&t1,&s1,&t2,&s2) == 4){
            oyna(l,t1,s1,t2,s2);
        }
    }
}

void skor_oku_klavyeden(
    lig *l){
    char t1,t2;
    int s1,s2;
    if(scanf("%c %d %c %d",&t1,&s1,&t2,&s2)){
        printf("%c %d %c %d\n",t1,s1,t2,s2);
        oyna(l,t1,s1,t2,s2);
    }
}

void ayar_oku(lig *l,const char *dosya_adi){
    FILE *fp = fopen(dosya_adi,"r");
    int x1,x2,x3,x4;
    if(fp){
        fscanf(fp,"%d %d %d %d",&x1,&x2,&x3,&x4);
        l->max_takim_sayisi = x1;
        l->g_puan = x2;
        l->b_puan = x3;
        l->m_puan = x4;
    }
}

//takimin takma adi 'A' ise ('A' - 65 = 0.indis)
//takimin takma adi 'B' ise ('B' - 65 = 1.indis)
void oyna(lig *l,char t1,int s1,char t2,int s2){
    if(l->oyun_matrisi[t1 - 65][t2 - 65]){
        printf("Daha once oynandi!!!!\n");
    }
    else{
        l->skor_matrisi[t1 - 65][t2 - 65] = s1;
        l->skor_matrisi[t2 - 65][t1 - 65] = s2;
        l->takimlar[t1 - 65].atilan_gol += s1;
        l->takimlar[t2 - 65].atilan_gol += s2;
        l->takimlar[t1 - 65].yenilen_gol += s2;
        l->takimlar[t2 - 65].yenilen_gol += s1;
        l->takimlar[t1 - 65].oynanan_mac++;
        l->takimlar[t2 - 65].oynanan_mac++;
        l->takimlar[t1 - 65].averaj += s1 - s2;
        l->takimlar[t2 - 65].averaj += s2 - s1;
        l->oyun_matrisi[t1 - 65][t2 - 65] = 1;
        //l->oyun_matrisi[t2 - 65][t1 - 65] = 1;
    }
    if(s1 > s2){
        l->takimlar[t1 - 65].galibiyet++;
        l->takimlar[t1 - 65].puan += l->g_puan;
        l->takimlar[t2 - 65].maglubiyet++;
        l->takimlar[t2 - 65].puan += l->m_puan;
    }
    if(s1 == s2){
        l->takimlar[t1 - 65].beraberlik++;
        l->takimlar[t1 - 65].puan += l->b_puan;
        l->takimlar[t2 - 65].beraberlik++;
        l->takimlar[t2 - 65].puan += l->b_puan;
    }
    if(s1 < s2){
        l->takimlar[t1 - 65].maglubiyet++;
        l->takimlar[t1 - 65].puan += l->m_puan;
        l->takimlar[t2 - 65].galibiyet++;
        l->takimlar[t2 - 65].puan += l->g_puan;
    }       
}
void takim_ekle(lig *l,const char *isim){
    if(l->takim_sayisi < l->max_takim_sayisi){
        l->takim_sayisi++;
        //skor matrisinin boyutlarini 1 arttir
        l->skor_matrisi = (int**)realloc(l->skor_matrisi,sizeof(int*) * l->takim_sayisi);
        for(int i = 0;i < l->takim_sayisi - 1;i++){
            l->skor_matrisi[i] = (int*)realloc(l->skor_matrisi[i],sizeof(int) * l->takim_sayisi);
            l->skor_matrisi[i][l->takim_sayisi - 1] = 0;
        }

        l->skor_matrisi[l->takim_sayisi - 1] = (int*)calloc(l->takim_sayisi,sizeof(int));
        //oyun matrisinin boyutlarini 1 arttir
        l->oyun_matrisi = (int**)realloc(l->oyun_matrisi,sizeof(int*) * l->takim_sayisi);
        for(int i = 0;i < l->takim_sayisi - 1;i++){
            l->oyun_matrisi[i] = (int*)realloc(l->oyun_matrisi[i],sizeof(int) * l->takim_sayisi);
            l->oyun_matrisi[i][l->takim_sayisi - 1] = 0;
        }

        l->oyun_matrisi[l->takim_sayisi - 1] = (int*)calloc(l->takim_sayisi,sizeof(int));
        //takimlar dizisinin boyutlarini 1 arttirir
        l->takimlar = (takim*)realloc(l->takimlar,sizeof(takim) * l->takim_sayisi);
        //takimlar dizisinin son elemanıni hazirlar
        strcpy(l->takimlar[l->takim_sayisi - 1].isim,isim);
        l->takimlar[l->takim_sayisi - 1].k_isim = 64 + l->takim_sayisi;
        l->takimlar[l->takim_sayisi - 1].oynanan_mac = 0;
        l->takimlar[l->takim_sayisi - 1].galibiyet = 0;
        l->takimlar[l->takim_sayisi - 1].beraberlik = 0;
        l->takimlar[l->takim_sayisi - 1].maglubiyet = 0;
        l->takimlar[l->takim_sayisi - 1].atilan_gol = 0;
        l->takimlar[l->takim_sayisi - 1].yenilen_gol = 0;
        l->takimlar[l->takim_sayisi - 1].averaj= 0;
        l->takimlar[l->takim_sayisi - 1].puan = 0;
    }
    else{
        printf("Daha fazla takim eklenemez!\n");
    }
}

void matrisi_ciz(lig *l){
    for(int i = 0;i < l->takim_sayisi;i++){
        for(int j = 0;j < l->takim_sayisi;j++){
            printf("%d ",l->skor_matrisi[i][j]);
        }
        printf("\n");
    }
}

void b_skor_tablosu_ciz(lig *l){
    printf("\t\tSPOR\tTOTO\tSUPER\tLIG\tPUAN\tCETVELI\t\t\n--------------------------------------------------------------------------------\n%15s%5s%5s%5s%5s%5s%5s%5s%5s%5s\n--------------------------------------------------------------------------------\n","Takim","Harf","O.M","G","B","M","A.G","Y.G","Avg","P");
    for(int i = 0;i < l->takim_sayisi;i++){
        int x1,x2,x3,x4,x5,x6,x7,x8;
        x1 = l->takimlar[i].oynanan_mac;
        x2 = l->takimlar[i].galibiyet;
        x3 = l->takimlar[i].beraberlik;
        x4 = l->takimlar[i].maglubiyet;
        x5 = l->takimlar[i].atilan_gol;
        x6 = l->takimlar[i].yenilen_gol;
        x7 = l->takimlar[i].averaj;
        x8 = l->takimlar[i].puan;
        printf("%15s%5c%5d%5d%5d%5d%5d%5d%5d%5d\n",buyult(l->takimlar[i].isim),l->takimlar[i].k_isim,x1,x2,x3,x4,x5,x6,x7,x8);
    }
}

void k_skor_tablosu_ciz(lig *l){
    printf("\t\tSPOR\tTOTO\tSUPER\tLIG\tPUAN\tCETVELI\t\t\n--------------------------------------------------------------------------------\n%15s%5s%5s%5s%5s%5s%5s%5s%5s%5s\n--------------------------------------------------------------------------------\n","Takim","Harf","O.M","G","B","M","A.G","Y.G","Avg","P");
    for(int i = 0;i < l->takim_sayisi;i++){
        int x1,x2,x3,x4,x5,x6,x7,x8;
        x1 = l->takimlar[i].oynanan_mac;
        x2 = l->takimlar[i].galibiyet;
        x3 = l->takimlar[i].beraberlik;
        x4 = l->takimlar[i].maglubiyet;
        x5 = l->takimlar[i].atilan_gol;
        x6 = l->takimlar[i].yenilen_gol;
        x7 = l->takimlar[i].averaj;
        x8 = l->takimlar[i].puan;
        printf("%15s%5c%5d%5d%5d%5d%5d%5d%5d%5d\n",kucult(l->takimlar[i].isim),l->takimlar[i].k_isim,x1,x2,x3,x4,x5,x6,x7,x8);
    }
}

void sirala_puan(lig *l){
    for(int i = 0;i < l->takim_sayisi - 1;i++){
        for(int j = 0;j < l->takim_sayisi - i - 1;j++){
            if(l->takimlar[j].puan < l->takimlar[j + 1].puan){
                takas(&l->takimlar[j],&l->takimlar[j + 1]);
            }
        }
    }
}

void sirala_k_isim(lig *l){
    for(int i = 0;i < l->takim_sayisi - 1;i++){
        for(int j = 0;j < l->takim_sayisi - i - 1;j++){
            if(l->takimlar[j].k_isim > l->takimlar[j + 1].k_isim){
                takas(&l->takimlar[j],&l->takimlar[j + 1]);
            }
        }
    }
}

void sirala_isim(lig *l){
    for(int i = 0;i < l->takim_sayisi - 1;i++){
        for(int j = 0;j < l->takim_sayisi - i - 1;j++){
            if(strcmp((char*)&l->takimlar[j].isim,(char*)&l->takimlar[j + 1].isim) > 0){
                takas(&l->takimlar[j],&l->takimlar[j + 1]);
            }
        }
    }
}

void takas(takim *t1,takim *t2){
    takim tmp = *t1;
    *t1 = *t2;
    *t2 = tmp;
}

char* kucult(const char *isim){
    char *isim2 = (char*)malloc(sizeof(char) * strlen(isim));
    strcpy(isim2,isim);
    char *ptr = isim2;
    while(*ptr != '\0'){
        //97 = 'a^ , harfin sayisal degeri 97'den kucukse buyuk harftir
        *ptr = (*ptr < 97)? *ptr + 32 : *ptr;
        ptr++;
    }
    return isim2;
}

char* buyult(const char *isim){
    char *isim2 = (char*)malloc(sizeof(char) * strlen(isim));
    strcpy(isim2,isim);
    char *ptr = isim2;
    while(*ptr != '\0'){
        //90 = 'Z^ , harfin sayisal degeri 90'dan buyukse kucuk harftir
        *ptr = (*ptr > 90)? *ptr - 32 : *ptr;
        ptr++;
    }
    return isim2;
}
