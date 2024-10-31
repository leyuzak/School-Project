//Leyuza Koksoken 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //tolower bunun icinde diye ekledim.

typedef struct Node {
    char kelime[256];
    int sayi;
    struct Node* prev;
    struct Node* next; //cift yonlu bagli liste icin pointerdan yardim aldim.
} Node;

Node* head = NULL;

void turkceKarakterleriCevir(char *kelime) { //girdigimiz turkce karakterleri ingilizceye cevirip okumasini sagliyoruz.
    for (int i = 0; kelime[i] != '\0'; i++) {
        switch (kelime[i]) {
            case 'ç': kelime[i] = 'c'; break;
            case 'Ç': kelime[i] = 'C'; break;
            case 'ð': kelime[i] = 'g'; break;
            case 'Ð': kelime[i] = 'G'; break;
            case 'ý': kelime[i] = 'i'; break;
            case 'Ý': kelime[i] = 'I'; break;
            case 'ö': kelime[i] = 'o'; break;
            case 'Ö': kelime[i] = 'O'; break;
            case 'þ': kelime[i] = 's'; break;
            case 'Þ': kelime[i] = 'S'; break;
            case 'ü': kelime[i] = 'u'; break;
            case 'Ü': kelime[i] = 'U'; break;
            default: break;
        }
    }
}

void kelimeEkle(char* kelime) {
    //kelimeleri turkce karsiligiyla eklesin.
    turkceKarakterleriCevir(kelime);
    //yeni node icin bellek ayirdim.
    Node* yeniNode = (Node*)malloc(sizeof(Node));
    strcpy(yeniNode->kelime, kelime); //kopyaladim yeniyi
    yeniNode->sayi = 1;

    if (head == NULL) {
        head = yeniNode;
        head->next = head;
        head->prev = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
         // eger kelime varsa sayi arttirip yeni nodeu serbest biraktim
         if (strcmp(temp->kelime, kelime) == 0) {
                temp->sayi++;
                free(yeniNode);
                return;
            }
            temp = temp->next;
        }
        if (strcmp(temp->kelime, kelime) == 0) {
            temp->sayi++;
            free(yeniNode);
            return;
        }
        Node* son = head->prev;// eger kelime yeniyse, sona ekledim.
        //yeni nodeun next ve prev pointerlarini ayarladim.
        yeniNode->next = head;
        head->prev = yeniNode;
        yeniNode->prev = son;
        son->next = yeniNode;
    }
}

void dosyadanKelimeOku(char* dosyaAdi) {
    FILE* dosya = fopen(dosyaAdi, "r"); //dosyayi sadece okumak icin r
    if (!dosya) {
        printf("Dosya Acilamadi.\n");
        return;
    }

    char kelime[100];
    char tempKelime[100];


    while (fscanf(dosya, "%s", kelime) != EOF) {
        turkceKarakterleriCevir(kelime);


        int j = 0;
        for (int i = 0; i < strlen(kelime); i++) {
            if (isalnum(kelime[i]) || kelime[i] == '-') {
                tempKelime[j++] = tolower(kelime[i]); // kucuk harfe çevirdim karismasin diye
            }
        }
        tempKelime[j] = '\0';

        if (j > 0) {
            kelimeEkle(tempKelime); // gecerli kelimeleri bagli listeye ekledim
        }
    }

    fclose(dosya);
}


void kelimeleriAlfabetikSirala() {
    if (head == NULL) return;

    for (Node* i = head; i->next != head; i = i->next) { // tum elemanlari gezmek icin
        for (Node* j = i->next; j != head; j = j->next) { //i elemaninin sonrasindaki tum elemanlarla karsilastirmak icin
            if (strcmp(i->kelime, j->kelime) > 0) {
                char tempKelime[256];
                int tempSayi;
                //eger alfabetik olarak ondeyse temp yardimiyla yer degistirdim.

                strcpy(tempKelime, i->kelime);
                tempSayi = i->sayi;

                strcpy(i->kelime, j->kelime);
                i->sayi = j->sayi;

                strcpy(j->kelime, tempKelime);
                j->sayi = tempSayi;
            }
        }
    }
}

void kelimeleriYazdir() {
    if (head == NULL) {
        printf("Liste bos.\n");
        return;
    }
    Node* temp = head;
    do {
        printf("Frekans: %d,  Kelime: %s \n", temp->sayi, temp->kelime);
        temp = temp->next;
    } while (temp != head);
}

void kelimeler() {
    if (head == NULL) {
        printf("Liste bos.\n");
        return;
    }
    Node* temp = head;
    do {
        printf("%s ", temp->kelime);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
} //cift yonlu bagli liste oldugundan bir sonraki basi gosterene kadar devam etsin.


void kelimeleriSil(const char* arananHarf) {
    if (head == NULL) return; // liste bossa, silmeye gerek kalmadan fonkdan cikilir.

    Node* temp = head; //arayacak degeri basa esitledim.
    char silinenKelimeler[100][256];
    int silinenSayisi = 0;

    Node* sonraki = NULL; //silinen dugumden sonraki dugumu tutmak için kullandim.

    do {
        if (strncmp(temp->kelime, arananHarf, strlen(arananHarf)) == 0) {//dugumdeki kelime aradigimizla basliyor mu diye kontrol.
            strcpy(silinenKelimeler[silinenSayisi++], temp->kelime);

            if (temp == head && temp->next == head) {
                head = NULL;
            } else {
                if (temp == head) {
                    head = temp->next;
                }
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            sonraki = temp->next;
            free(temp);
            temp = sonraki;
        } else {
            temp = temp->next;  //  kelime silinmiyorsa, temp'i bir sonraki dugume guncelledim.
        }
    } while (temp != head);

    printf("Silinen kelimeler:\n");
    for (int i = 0; i < silinenSayisi; i++) {
        printf("'%s' ", silinenKelimeler[i]); //silinen kelimeleri ekrana yazdirdim.
    }

    if (head == NULL) {
        printf("\nListe bos.\n");
    } else {
        printf("\nKalan kelimeler:\n"); //kalan kelimeleri listeden ekrana yazdirdim.
        temp = head;
        do {
            printf("%s, ", temp->kelime);
            temp = temp->next;
        } while (temp != head);
    }
}

void kelimeleriYogunlugaGoreSirala() {
    if (head == NULL) return;

    for (Node* i = head; i->next != head; i = i->next) { //i'en basa esitleyip i'nin nexti bası gosterene kadar devam ettim.
        for (Node* j = i->next; j != head; j = j->next) { //j'yi i next'e esitliyoruz j bası gosterene kadar devam.
            if (i->sayi < j->sayi) { //ic ice for kullanarak kelimelerin kac tane gectigini takip ettim.
                char tempKelime[256];
                int tempSayi;

                strcpy(tempKelime, i->kelime); //strcpy fonksiyonu, yeni dugum olustururken string verisini kopyalamami sagladi.
                tempSayi = i->sayi;

                strcpy(i->kelime, j->kelime);
                i->sayi = j->sayi;

                strcpy(j->kelime, tempKelime);
                j->sayi = tempSayi;
            }
        }
    }
}

void yeniMetinEkle() {
    char yeniMetin[1000];
    printf("Yeni metni girin: ");
    scanf(" %[^\n]", yeniMetin); //kullanicidan yeni metin almamizi saglar.

    char* kelime = strtok(yeniMetin, " ");
    while (kelime != NULL) {
        kelimeEkle(kelime);
        kelime = strtok(NULL, " ");
    }
}
void listeyiTemizle() {
    if (head == NULL) return; // liste bossa, temizlemeye kalmadan fonkdan cikilir.

    Node* temp = head;
    Node* silinecek;

    while (temp != NULL) {
        silinecek = temp;
        temp = temp->next;

        if (silinecek == head && silinecek->next == head) {
            head = NULL;
            break;
        } else if (silinecek == head) {
            head = temp;
        }

        free(silinecek);

        if (temp == head) {
            head = NULL;
            break;
        }
    }
}


int main() {
    int secim; //switch case secimi icin int deger olusturdum kullanicidan alarak caselere giris yapilacak.
    dosyadanKelimeOku("yildizlar.txt");

    while (1) {
        printf("\n-*-*-*-*-*-*-*- MENU -*-*-*-*-*-*-*-\n");
        printf("1- Metinde Gecen Kelimeler\n");
        printf("2- Kelimeleri Alfabetik Siralama\n");
        printf("3- Kelimeleri Frekansina Gore Siralama\n");
        printf("4- Silmek Istediginiz Kelime Ya da Harfle Baslayan Kelimeler\n");
        printf("5- Yeni Metin Ekle\n");
        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        printf("Istediginiz islemi girin (0 ile ciksin): ");
        scanf("%d", &secim);
        switch (secim) {
            case 1:
                printf("Metinde Gecen Kelimeler:\n");
                kelimeler();
                break;
            case 2:
                kelimeleriAlfabetikSirala();
                printf("Kelimeler alfabetik olarak siralandi:\n");
                kelimeler();
                break;
            case 3:
                kelimeleriYogunlugaGoreSirala();
                printf("Kelimelerin frekansina gore siralanmis hali:\n");
                kelimeleriYazdir();
                break;
            case 4: {
                char arananHarf[100];
                printf("Silmek istediginiz kelimenin baslangicini girin: ");
                scanf("%s", arananHarf);
                kelimeleriSil(arananHarf);
                break;
            }
            case 5: {
                yeniMetinEkle();
                printf("Yeni metin eklendi ve isleme alindi.\n");
                break;
            }
            case 0:
                listeyiTemizle();
                printf("Cikis yapiliyor.\n");
                return 0;
            default:
                printf("Gecersiz secim, lutfen tekrar deneyin.\n");
        }
    }
}
