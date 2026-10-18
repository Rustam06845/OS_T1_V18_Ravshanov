# OS_T1_V18 — 1-topshiriq (18-variant)

Fan: Operatsion tizimlar. Mavzu: C tili asoslari, kompilyatsiya va pointerlar.
Talaba: Ravshanov Rustamjon (SRM001-3 guruh), ustoz: Bekimmetova Durdona.

## Fayllar

| Fayl | Mazmuni |
|------|---------|
| `hello.c` | A qism: "Hello World" manba kodi |
| `hello.i` | `gcc -E` natijasi (preprotsessor) |
| `hello.s` | `gcc -S` natijasi (assembler kodi) |
| `hello.o` | `gcc -c` natijasi (obyekt fayl) |
| `hello` | linking natijasi (bajariluvchi fayl) |
| `main.c` | B qism: 18-variant, siklli kalkulyator |
| `tests.txt` | `main` dasturining test natijalari |

## A qism: 4 bosqichli kompilyatsiya

```bash
gcc -E hello.c -o hello.i     # 1) preprotsessor
gcc -S hello.i -o hello.s     # 2) assembler kodiga o'tkazish
gcc -c hello.s -o hello.o     # 3) obyekt faylga o'tkazish
gcc hello.o -o hello          # 4) linking (bajariluvchi fayl)
./hello
```

## B qism: kalkulyator

Kompilyatsiya (`%` amali uchun `fmod()` ishlatilgani sababli `-lm` kerak):

```bash
gcc -Wall -Wextra -o main main.c -lm
./main
```

Dastur ketma-ket: birinchi son, ikkinchi son, amal (`+ - * / %`) so'raydi.
Istalgan so'rovda `q` kiritilsa dastur tugaydi.

Tekshiriladigan xatolar: son o'rniga harf/matn, noma'lum amal belgisi,
`/` va `%` da nolga bo'lish, juda uzun satr.

Test uchun tayyor kiritish bilan ishga tushirish:

```bash
./main < tests_input.txt
```
