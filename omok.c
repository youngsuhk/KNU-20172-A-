#include <stdioh>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include <curses.h>
#define WIDTH 11 //width size
#define HEIGHT 11 //height size
#define oops(msg) {perror(msg); exit(1);}#define ch_t(turn,next,temp) {temp=turn; turn=next; next=temp;}
#define CONTINUE 10
#define END 11struct p_information{//player information        
char id[5];
int play_num,win_record,recent_time;//win record};
struct client_socket{        int c_socket, player;
struct p_information p_info;
int turn;};
struct g_result{        char end[1];        int player;};
int board[WIDTH][HEIGHT];
struct p_information p_info[2];
struct g_result gameresult;
int p_x,p_y;
void login(int fd, int s_num);
void drawBoard();
int endGame(int c);
int putting(int x, int y, int c);
void player_write(struct client_socket c_sock);
void player_read(struct client_socket c_sock);
