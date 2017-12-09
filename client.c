#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#define LEN 256
#define WIDTH 11 //width size
#define HEIGHT 11 //height size
#define SUCCESS 7
#define FAIL 4
#define oops(msg)       {perror(msg); exit(1);}
struct p_information{
	char id[5];
	int win_record,recent_time;
	int player_num, com_player_num;
};
void login(int fd);
void drawBoard();
void putting(int x, int y, int c);
void player1(int fd);
void player2(int fd);
struct  p_information p_info;
int board[WIDTH][HEIGHT];
main(int argc, char *argv[])
{
	//client
	int fd,port = atoi(argv[1]);
	//program
	int x,y;
	char end[1];
	int turn, winplayer;
	fd = connect_to_server(argv[2], port);
	if(fd == -1)
		exit(1);
	//login
	printf("connected to server\n please login for omokGo\n");
	login(fd);
	printf("your id is %s.",p_info.id);
	if(read(fd,&p_info.player_num,sizeof(int))==-1)
		oops("read");
	printf("you are player%d\n",p_info.player_num);
	if(p_info.player_num ==1)
		p_info.com_player_num = 2;
	else if(p_info.player_num == 2)
		p_info.com_player_num =1;
	//what to do
	while(1){
		//whose turn
		if(p_info.player_num == 1)
			player1(fd);
		else if(p_info.player_num == 2)
			player2(fd);
		//add
		read(fd,&winplayer,sizeof(int));
		if(winplayer !=77){
			printf("player%d win.\n",winplayer);
			break;
		}
	}
	//close socket
	close(fd);
}
void player1(int fd)
{
	int x,y,r_x,r_y;
	while(1)
	{
		printf("player %d turn (x,y) : ",p_info.player_num);
		scanf("%d %d",&x,&y);
		write(fd, &x, sizeof(int));
		write(fd, &y, sizeof(int));
		putting(x,y,p_info.player_num);
		drawBoard();
		read(fd, &r_x, sizeof(int));
		read(fd, &r_y, sizeof(int));
		printf("player %d turn (x,y) : (%d, %d)\n",p_info.com_player_num,r_x,r_y);
		if(board[r_x][r_y]==0)
		{
			board[r_x][r_y]=p_info.com_player_num;
			break;
		}
		else
		{
			printf("you are miss turn\n");
			printf("check again\n");
		}
		//putting(r_x,r_y,p_info.com_player_num);
	}
	drawBoard();
}
void player2(int fd)
{
	int x,y;
	read(fd, &x, sizeof(int));
	read(fd, &y, sizeof(int));
	printf("player %d turn (x,y) : (%d, %d)\n",p_info.com_player_num,x,y);
	putting(x,y,p_info.com_player_num);
	drawBoard();

	while(1)
	{
		printf("player %d turn (x,y) : ",p_info.player_num);
		scanf("%d %d",&x,&y);
		write(fd, &x, sizeof(int));
		write(fd, &y, sizeof(int));
		if(board[x][y]==0)
		{
			board[x][y]=p_info.player_num;
			break;
		}
		else
		{
			printf("you are miss turn\n");
			printf("check again\n");
		}

		//        putting(x,y,p_info.player_num);
	}
	drawBoard();
}
void login(int fd){
	int new;
	char id[5];
	printf("please enter if you are new member 1,or 2 : ");
	scanf("%d",&new);
	write(fd,&new,sizeof(new));
	printf("please enter your id(id -> 4 letters) : ");
	scanf("%s",p_info.id);
	printf("%s\n",p_info.id);
	write(fd,p_info.id,BUFSIZ);
}
void drawBoard(){
	int i,j;
	for(i=0; i<WIDTH; i++){
		for(j=0; j<HEIGHT; j++){
			if(board[i][j] == 1)
			{
				printf(" O");
			}//player1's
			else if(board[i][j] == 2) {printf(" X");}//player2's
			else if(board[i][j] == 0){
				if(i==0){
					if(j!=0&&j!=HEIGHT-1) {printf("¤Ì");}
				}
				else if(i==WIDTH-1){
					if(j!=0 && j!= HEIGHT-1)  {printf("¤Ç");}
				}
				if(j == 0){
					if(i==0) {printf("¦£-");} //(0,0)
					else if(i==WIDTH-1) {printf("¦¦-");}
					else printf("¤¿");
				}
				else if(j== HEIGHT-1){
					if(i==0) {printf("¦¤");}
					else if(i==WIDTH-1) {printf("¦¥");}
					else printf("¦©");
				}
				if(i*j!=0&&i!=WIDTH-1&& j!=HEIGHT -1)printf(" +");
			}
		}
		printf("\n");
	}
}
void putting(int x, int y, int c){
	if(board[x][y]==0){
		board[x][y]=c;
	}
}
