/*
 * Muallif: Ravshanov Rustamjon, SRM001-3 guruh
 * OS_T1_V18 - 1-topshiriq, B qism, 18-variant
 * Siklli kalkulyator: q kiritilguncha ikki son va amal (+ - * / %) so'raladi.
 * 1-masala (C asoslari): sikl, switch/if, kiritishni tekshirish.
 * 2-masala (pointerlar): amal belgisiga qarab funksiya pointeri tanlanadi
 *                        va shu pointer orqali chaqiriladi; % amali fmod() orqali.
 *
 * Kompilyatsiya: gcc -Wall -Wextra -o main main.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUF 128

/* Funksiya pointeri turi: ikki double qabul qilib, double qaytaradi */
typedef double (*Amal)(double, double);

/* ---------- Amallar ---------- */
static double qosh(double a, double b)    { return a + b; }
static double ayir(double a, double b)    { return a - b; }
static double kopaytir(double a, double b){ return a * b; }
static double bol(double a, double b)     { return a / b; }
static double qoldiq(double a, double b)  { return fmod(a, b); }

/* Amal belgisiga mos funksiya pointerini qaytaradi; noto'g'ri belgi uchun NULL */
static Amal tanla_amal(char belgi)
{
    switch (belgi) {
        case '+': return qosh;
        case '-': return ayir;
        case '*': return kopaytir;
        case '/': return bol;
        case '%': return qoldiq;
        default:  return NULL;
    }
}

/* Satrdan oxiridagi '\n' ni olib tashlaydi */
static void yangi_qator_olib_tashla(char *s)
{
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n')
        s[n - 1] = '\0';
}

/* Satrni double ga o'giradi. To'liq son bo'lsa 1, aks holda 0 qaytaradi.
 * nan va inf (masalan "nan", "inf") ham rad etiladi. */
static int son_tekshir(const char *s, double *natija)
{
    char *oxiri;
    double v;

    if (*s == '\0')
        return 0;
    v = strtod(s, &oxiri);
    while (*oxiri == ' ' || *oxiri == '\t')   /* oxiridagi bo'shliqlar mumkin */
        oxiri++;
    if (*oxiri != '\0' || oxiri == s)
        return 0;
    if (isnan(v) || isinf(v))
        return 0;
    *natija = v;
    return 1;
}

/* Foydalanuvchidan bitta son so'raydi.
 * Qaytaradi: 1 - son olindi, 0 - 'q' (chiqish) yoki kiritish tugadi.
 * Noto'g'ri kiritilsa xabar berib, qayta so'raydi. */
static int son_oqi(const char *taklif, double *son)
{
    char satr[BUF];

    for (;;) {
        printf("%s", taklif);
        if (fgets(satr, sizeof satr, stdin) == NULL)
            return 0;                              /* EOF */
        if (strchr(satr, '\n') == NULL) {          /* juda uzun satr: qolganini tashlaymiz */
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Xato: satr juda uzun. Qaytadan kiriting.\n");
            continue;
        }
        yangi_qator_olib_tashla(satr);
        if (strcmp(satr, "q") == 0 || strcmp(satr, "Q") == 0)
            return 0;
        if (son_tekshir(satr, son))
            return 1;
        printf("Xato: \"%s\" son emas. Qaytadan kiriting (chiqish uchun q).\n", satr);
    }
}

/* Amal belgisini so'raydi. Qaytaradi: 1 - to'g'ri belgi, 0 - 'q' yoki EOF. */
static int amal_oqi(char *belgi)
{
    char satr[BUF];

    for (;;) {
        printf("Amalni kiriting (+ - * / %%): ");
        if (fgets(satr, sizeof satr, stdin) == NULL)
            return 0;
        if (strchr(satr, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Xato: satr juda uzun. Qaytadan kiriting.\n");
            continue;
        }
        yangi_qator_olib_tashla(satr);
        if (strcmp(satr, "q") == 0 || strcmp(satr, "Q") == 0)
            return 0;
        if (strlen(satr) == 1 && tanla_amal(satr[0]) != NULL) {
            *belgi = satr[0];
            return 1;
        }
        printf("Xato: \"%s\" noma'lum amal. Faqat + - * / %% ruxsat etiladi.\n", satr);
    }
}

int main(void)
{
    double a, b, natija;
    char belgi;
    Amal amal;                  /* funksiya pointeri */

    printf("=== Siklli kalkulyator (chiqish uchun istalgan so'rovda q kiriting) ===\n");

    for (;;) {
        if (!son_oqi("\nBirinchi sonni kiriting: ", &a))
            break;
        if (!son_oqi("Ikkinchi sonni kiriting: ", &b))
            break;
        if (!amal_oqi(&belgi))
            break;

        /* nolga bo'lishni tekshirish: faqat / va % uchun */
        if ((belgi == '/' || belgi == '%') && b == 0.0) {
            printf("Xato: nolga bo'lish mumkin emas.\n");
            continue;
        }

        amal = tanla_amal(belgi);          /* belgiga qarab funksiya pointeri tanlanadi */
        natija = amal(a, b);               /* pointer orqali chaqiriladi */

        printf("Natija: %g %c %g = %g\n", a, belgi, b, natija);
        /* %p: natija o'zgaruvchisining xotiradagi manzili */
        printf("[%%p] natija o'zgaruvchisi manzili: %p\n", (void *)&natija);
    }

    printf("\nDastur tugadi.\n");
    return 0;
}
