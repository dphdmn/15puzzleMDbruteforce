#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "mtwister.h"

int d;
int cap;
unsigned long long int max;


int board[31][31];
MTRand r;
int tmp;
int newX;
int newY;
int dmoves;
int rmoves;
unsigned long long int globali;
int h;
int w;
int mdsum;
int original_w=0;
int original_h=0;
int current_md=0;
int number=0;
int total;

int randomInt(int, int);
void init(void);
void draw(void);
void randomize(void);
void check_md(void);

int main(int argc, char *argv[])
{
    sscanf(argv[1],"%d",&d);
    sscanf(argv[2],"%d",&cap);
    sscanf(argv[3],"%llu",&max);

    r = seedRand(time(NULL));
    total = d * d - 1;
    globali = 0;
    for (globali = 1; globali <= max; globali++){
        init();
        check_md();
        if ((globali % 10000000) == 0){
            printf("%llu scrambles checked...\n", globali);
        }
        if (mdsum < cap){
            draw();
        }
    }
}

void check_md(void)
{
  mdsum=0;
  for (h = 0; h<=d-1;h++){
      for(w = 0; w<=d-1;w++){
          number = board[h][w];
          if (number != 0){
              original_h = floor((number-1) / d);
              original_w = (number-1) % d;
              current_md = abs(original_h - h) + abs(original_w - w);
              mdsum += current_md;
          }
      }
  }
}


void init(void)
{
    board[d-1][d-1] = 0;
    randomize();
}

int randomInt(int min, int max)
{
    return (min + floor((max-min) * genRand(&r)));
}

void randomize(void)
{
    int flat_board[total];
    for (int i = 0; i < total; i++){
        flat_board[i] = i+1;
    }
    int foo;
    for (int counter = total-1; counter > 0; counter--){
        int randt = genRand(&r) * (counter + 1);
        foo = flat_board[counter];
        flat_board[counter] = flat_board[randt];
        flat_board[randt] = foo;
    }

    int inversions = 0;
    
    int checking;
    for (int i = 0; i < total - 1; i++){
        checking = flat_board[i];
        for (int j = i + 1; j < total; j++){
            if (flat_board[j] < checking){
                inversions++;
            }
        }
    }
    if (inversions % 2 != 0){
        foo = flat_board[0];
        flat_board[0] = flat_board[1];
        flat_board[1] = foo;
    }

    for (int i = 0; i < d; i++){
        for (int j = 0; j < d; j++){
            if(i < d-1 || j < d-1){
                board[i][j] = flat_board[i*d + j];
            }
        }
    }
    int currentY = d-1;
    int currentX = d-1;
    rmoves = randomInt(0, d);
    dmoves = randomInt(0, d);

    for (int i = 1; i <= rmoves; i++){
        newX = currentX - 1;
        board[currentX][currentY] = board[newX][currentY];
        board[newX][currentY] = 0;
        currentX = newX;
    }
    for (int i = 1; i <= dmoves; i++){
        newY = currentY - 1;
        board[currentX][currentY] = board[currentX][newY];
        board[currentX][newY] = 0;
        currentY = newY;
    }
}    

void draw(void)
{
    for (int i = 0; i < d; i++) 
    {
        for (int j = 0; j < d; j++)
        {
            printf("%i", board[i][j]);
            if (j == d - 1)
            {
                printf("/");
            }
            else
            {
                printf(" ");
            }
        }

    }
    printf("// mdsum = %d//id = %%llu\n", mdsum, globali);
}