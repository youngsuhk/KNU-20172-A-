#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <curses.h>
#include <string.h>

//player information
struct information_p{
  char id[5];
  int num_p, win, time;
};

//client information
sturct client_2{
  int socket, player;
  struct information_p info_p;
  int num;
};

struct information_p info_p[2];

void write_p(struct); // client info write
void read_p(struct);

int main(int ac,char *av[])
{

}
