//Leyuza Koksoken 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

struct Dugum {
    char data;
    struct Dugum* sonraki;
};

struct Yigin {
    struct Dugum* ust;
};

void yiginaEkle(struct Yigin* yigin, char data) {
    struct Dugum* yenidugum = (struct Dugum*)malloc(sizeof(struct Dugum));
    yenidugum->data = data;
    yenidugum->sonraki = yigin->ust;
    yigin->ust = yenidugum;
}

char yigindanCikar(struct Yigin* yigin) {
    if (yigin->ust == NULL) {
        return '\0';
    }
    char data = yigin->ust->data;
    struct Dugum* gecici = yigin->ust;
    yigin->ust = yigin->ust->sonraki;
    free(gecici);
    return data;
}

int oncelik(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '*' || operator == '/') {
        return 2;
    }
    return 0;
}

void infixiPostYap(char* infix, char* postfix) {
    struct Yigin yigin;
    yigin.ust = NULL;

    int i = 0, j = 0;

    printf("\nInfix islem: %s\n", infix);

    while (infix[i] != '\0') {
        char karakter = infix[i];

        if (karakter >= '0' && karakter <= '9') {
            postfix[j++] = karakter;
            postfix[j] = '\0';
            printf("Operand: %c postfix'e eklendi\n", karakter);
            printf("Postfix ifade: %s\n", postfix);
        } else if (karakter == '(') {
            yiginaEkle(&yigin, karakter);
            printf("Sol parantez yigina eklendi\n");
        } else if (karakter == ')') {
            while (yigin.ust != NULL && yigin.ust->data != '(') {
                postfix[j++] = yigindanCikar(&yigin);
                postfix[j] = '\0';
                printf("Sag parantez, yigindaki islec postfix'e eklendi: %c\n", postfix[j-1]);
                printf("Postfix ifade: %s\n", postfix);
            }
            if (yigin.ust != NULL && yigin.ust->data == '(') {
                yigindanCikar(&yigin);
                printf("Sol parantez yigindan cikarildi\n");
            }
        } else {
            while (yigin.ust != NULL && oncelik(karakter) <= oncelik(yigin.ust->data)) {
                postfix[j++] = yigindanCikar(&yigin);
                postfix[j] = '\0';
                printf("Yigindaki daha yuksek/ayni oncelikli islec postfix'e eklendi: %c\n", postfix[j-1]);
                printf("Postfix ifade: %s\n", postfix);
            }
            yiginaEkle(&yigin, karakter);
            printf("Operator %c yigina eklendi\n", karakter);
        }

        i++;
    }

    while (yigin.ust != NULL) {
        postfix[j++] = yigindanCikar(&yigin);
        postfix[j] = '\0';
        printf("Yigindaki islec postfix'e eklendi: %c\n", postfix[j-1]);
        printf("Postfix ifade: %s\n", postfix);
    }

    postfix[j] = '\0';
    printf("Son postfix ifade: %s\n", postfix);
}

int postfixiHesapla(char* postfix) {
    int yigin[MAX];
    int bas = -1;

    for (int i = 0; postfix[i]; i++) {
        if (isdigit(postfix[i])) {
            yigin[++bas] = postfix[i] - '0';
        } else {
            int sonuc1 = yigin[bas--];
            int sonuc2 = yigin[bas--];
            switch (postfix[i]) {
                case '+': yigin[++bas] = sonuc2 + sonuc1; break;
                case '-': yigin[++bas] = sonuc2 - sonuc1; break;
                case '*': yigin[++bas] = sonuc2 * sonuc1; break;
                case '/': yigin[++bas] = sonuc2 / sonuc1; break;
            }
        }
    }
    return yigin[bas];
}

void dosyadanOku(char *dosyaAdi, char *infix) {
    FILE *file = fopen(dosyaAdi, "r");
    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        exit(1);
    }
    fgets(infix, MAX, file);
    fclose(file);
}

void dosyayaYaz(char *dosyaAdi, char *infix) {
    FILE *file = fopen(dosyaAdi, "w");
    if (file == NULL) {
        printf("Dosya acilamadi.\n");
        exit(1);
    }
    fprintf(file, "%s", infix);
    fclose(file);
}

int main() {
    int secim;
    char infix[MAX];
    char postfix[MAX];
    char dosyaAdi[] = "infix.txt";

    do {
        printf("-----------------------------------\n");
        printf("-*-*-*-*-*-*-*-*MENU*-*-*-*-*-*-*-*\n");
        printf("-1. Dosyadaki infix ifadesini oku:\n");
        printf("-2. Infix ifadesini postfixe cevir:\n");
        printf("-3. Postfix ifadeyi hesapla:\n");
        printf("-4. Infix ifadeyi al, dosyaya yaz:\n");
        printf("-5. Cikis\n");
        printf("-Seciminiz:\n");
        printf("-----------------------------------\n");
        scanf("%d", &secim);
        getchar();

        switch (secim) {
            case 1:
                dosyadanOku(dosyaAdi, infix);
                printf("Dosyadan okunan infix: %s\n", infix);
                break;
            case 2:
                infixiPostYap(infix, postfix);
                printf("Postfix ifade: %s\n", postfix);
                break;
            case 3:
                printf("Postfix ifadenin sonucu: %d\n", postfixiHesapla(postfix));
                break;
            case 4:
                printf("Yeni infix ifadesini girin: ");
                fgets(infix, MAX, stdin);
                infix[strcspn(infix, "\n")] = '\0';
                dosyayaYaz(dosyaAdi, infix);
                break;
            case 5:
                printf("Programdan cikildi.\n");
                break;
            default:
                printf("Hatali bir secim yaptiniz.\n");
        }
    } while (secim != 5);

    return 0;
}
