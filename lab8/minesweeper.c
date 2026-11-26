#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n, m, mines_total;
int *hidden;
int *visible;
int flags = 0;
int opened = 0;

int idx(int r, int c) { return r * m + c; }

int count_mines(int r, int c) {
    int cnt = 0;
    int dr, dc, nr, nc;
    for (dr = -1; dr <= 1; dr++)
        for (dc = -1; dc <= 1; dc++) {
            nr = r + dr;
            nc = c + dc;
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && hidden[idx(nr, nc)])
                cnt++;
        }
    return cnt;
}

void open_cell(int r, int c) {
    int dr, dc;
    if (r < 0 || r >= n || c < 0 || c >= m) return;
    if (visible[idx(r, c)]) return;
    visible[idx(r, c)] = 1;
    opened++;
    if (count_mines(r, c) == 0)
        for (dr = -1; dr <= 1; dr++)
            for (dc = -1; dc <= 1; dc++)
                open_cell(r + dr, c + dc);
}

void print_board(int show_mines) {
    int r, c, k;
    printf("\n   ");
    for (c = 0; c < m; c++) printf("%2d", c);
    printf("\n");
    for (r = 0; r < n; r++) {
        printf("%2d ", r);
        for (c = 0; c < m; c++) {
            if (visible[idx(r, c)] == 2)
                printf(" F");
            else if (visible[idx(r, c)] == 1) {
                if (hidden[idx(r, c)])
                    printf(" *");
                else {
                    k = count_mines(r, c);
                    if (k) printf(" %d", k);
                    else printf(" ."); 
                }
            } else if (show_mines && hidden[idx(r, c)])
                printf(" *");
            else
                printf(" #"); 
        }
        printf("\n");
    }
}

void place_mines(int safe_r, int safe_c) {
    int placed = 0;
    int r, c;
    while (placed < mines_total) {
        r = rand() % n;
        c = rand() % m;
        if (hidden[idx(r, c)] || (r == safe_r && c == safe_c))
            continue;
        hidden[idx(r, c)] = 1;
        placed++;
    }
}

int win() {
    return opened == n * m - mines_total;
}

int main(void) {
    int r, c, i;
    char cmd;
    srand(time(NULL));
    printf("Введите строки, столбцы и число мин: ");
    if (scanf("%d %d %d", &n, &m, &mines_total) != 3)
        return 1;
    if (mines_total < 1 || mines_total > n * m - 1) {
        printf("Некорректное число мин\n");
        return 1;
    }
    hidden = (int *)malloc(n * m * sizeof(int));
    visible = (int *)malloc(n * m * sizeof(int));
    if (!hidden || !visible)
        return 1;
    for (i = 0; i < n * m; i++) {
        hidden[i] = 0;
        visible[i] = 0;
    }

    printf("Первый ход (строка столбец): ");
    scanf("%d %d", &r, &c);
    place_mines(r, c);
    open_cell(r, c);
    print_board(0);

    while (!win()) {
        printf("Команда (o открыть / f флаг / q выход), строка столбец: ");
        scanf(" %c", &cmd);
        if (cmd == 'q')
            break;
        if (scanf("%d %d", &r, &c) != 2)
            continue;
        if (r < 0 || r >= n || c < 0 || c >= m) {
            printf("Вне поля\n");
            continue;
        }
        if (cmd == 'f') {
            if (visible[idx(r, c)] == 0) {
                visible[idx(r, c)] = 2;
                flags++;
            } else if (visible[idx(r, c)] == 2) {
                visible[idx(r, c)] = 0;
                flags--;
            }
        } else if (cmd == 'o') {
            if (visible[idx(r, c)] == 1) {
                printf("Клетка уже открыта\n");
                continue;
            }
            if (visible[idx(r, c)] == 2)
                flags--;
            if (hidden[idx(r, c)]) {
                print_board(1);
                printf("Вы попали на мину!\n");
                break;
            }
            open_cell(r, c);
        }
        print_board(0);
    }
    if (win())
        printf("Вы победили!\n");
    printf("Открыто клеток: %d, флажков: %d, мин осталось: %d\n",
           opened, flags, mines_total - flags);
    free(hidden);
    free(visible);
    return 0;
}