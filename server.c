#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<strings.h>
#include<curses.h>

#define WIDTH 20 //width size
#define HEIGHT 20 //height size
#define oops(msg) {perror(msg); exit(1);}
#define ch_t(turn,next,temp) {temp=turn; turn=next; next=temp;}
#define CONTINUE 10
#define END 11

struct p_information{//player information
        char id[5];
        int play_num,win_record,recent_time;//win record
};

struct client_socket{
        int c_socket, player;
        struct p_information p_info;
        int turn;
};

struct g_result{
        char end[1];
        int player;
};

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

int main(int ac, char *av[])
{
        //server&client
        int port = atoi(av[1]);
        struct sockaddr_in c_addr;
        int c_addr_size = sizeof(c_addr);
        struct client_socket cl_socket[2];
        int sock;
        //program
        int i,turn;//
        int s_num;//socket number
        
        if((sock = make_server_socket(port)) ==-1)
                oops("socket");
        printf("                OmokGo\n\n      waiting for player..\n\n");

        //client accept
        for(i=0; i<2; i++){
                if((cl_socket[i].c_socket = accept(sock,(struct sockaddr*)&c_addr, &c_addr_size))==-1)
                        break;
                cl_socket[i].player = i+1;
                printf("player : %d connected\n", cl_socket[i].player);
                cl_socket[i].turn = i+3;
        }
         //client login
        for(i=0; i<2; i++){
                login(cl_socket[i].c_socket,i);
                write(cl_socket[i].c_socket,&cl_socket[i].player,sizeof(int));
                }
        while(1){
                //whose turn
                gameresult.player = 77;
                player_read(cl_socket[0]);
                if(gameresult.end[0] =='e'){
                        printf("game over. player %d win.\n",gameresult.player);
                }
                player_write(cl_socket[1]);
                player_read(cl_socket[1]);
                if(gameresult.end[0] =='e'){
                        printf("game over. player %d win.\n",gameresult.player);
                }
                player_write(cl_socket[0]);
                //add
                write(cl_socket[0].c_socket,&gameresult.player,sizeof(int));
                write(cl_socket[1].c_socket,&gameresult.player,sizeof(int));
                if(gameresult.end[0] == 'e')
                        break;

        }
        close(cl_socket[0].c_socket); close(cl_socket[1].c_socket);
}
void player_read(struct client_socket c_sock)
{
        read(c_sock.c_socket, &p_x, sizeof(int));
        read(c_sock.c_socket, &p_y, sizeof(int));
        printf("player%d (%d, %d)\n",c_sock.player,p_x,p_y);
        putting(p_x,p_y,c_sock.player);
        drawBoard();
        if(endGame(c_sock.player) == END){
                gameresult.end[0]='e';
                printf("result : %c",gameresult.end[0]);
                gameresult.player = c_sock.player;
        }
}
void player_write(struct client_socket c_sock)
{
        write(c_sock.c_socket, &p_x, sizeof(int));
        write(c_sock.c_socket, &p_y, sizeof(int));
}
//return information about player id
void login(int fd, int s_num){//new -> add id to user.txt, member->check
       // FILE *f = fopen("user_info.txt","a+");
        int new;
        char buf[BUFSIZ],id[5];
        if(read(fd,&new,sizeof(new))==-1)
                oops("read");
        if(read(fd,p_info[s_num].id, BUFSIZ)==-1)
                 oops("read id");
        /*if(new ==1)
                fprintf(l_file,"%s 0 0\n",id);*/
        printf("login id : %s\n",p_info[s_num].id);
        //add : fclose, fopen, fprintf 00
        //fclose(f);
}
void drawBoard(){
        int i,j;
	printf("  ");
	 for(i=0;i<WIDTH;i++)
        {
                if(i<10)
                        printf("%d ",i);
                else
                        printf("%d",i);
        }
	printf("\n");
        for(i=0; i<WIDTH; i++){
		
        {
                if(i<10)
                        printf("%d ",i);
                else
                        printf("%d",i);
        }

                for(j=0; j<HEIGHT; j++){
                        if(board[i][j] == 1) {printf("○-");}//player1's
                        else if(board[i][j] == 2) {printf("●-");}//player2's
                        else if(board[i][j] == 0){
                                if(i==0){
                                        if(j!=0&&j!=HEIGHT-1) {printf("┬-");}
                                }
                                else if(i==WIDTH-1){
                                        if(j!=0 && j!= HEIGHT-1)  {printf("┴-");}
                                }
                                if(j == 0){
                                        if(i==0) {printf("┌-");} //(0,0)
                                        else if(i==WIDTH-1) {printf("└-");}
                                        else printf("├-");
                                }
                                else if(j== HEIGHT-1){
                                        if(i==0) {printf("┐");}
                                        else if(i==WIDTH-1) {printf("┘");}
                                        else printf("┤");
                                }
                                if(i*j!=0&&i!=WIDTH-1&& j!=HEIGHT -1)printf("┼-");
                        }
                }
                printf("\n");
        }
}

int endGame(int c)//c == player num, if game end return END(1)
{
        const int NOD=8;
        //const int CONTINUE=0;
        //const int NOD=8;
        int x,y,player,d,i;
        int dx[]={1,1,0,-1,-1,-1,0,1};
        int dy[]={0,1,1,1,0,-1,-1,-1};
        for(x=0;x<WIDTH;x++)
                for(y=0; y<HEIGHT;y++){
                        player=board[x][y];//check board pebble
                        if(player==c){
                                for(d=0; d<NOD; d++){
                                        i=1;
                                        for(i=1; i<5; i++){
                                                int tx=x+(dx[d]*i);
                                                int ty=y+(dy[d]*i);
                                                if(board[tx][ty]!=c)
                                                        break;
                                        }
                                        if(i==5)
                                                return END;
                                }
                        }
                }
        return CONTINUE;
}
int putting(int x, int y, int c){
        if(board[x][y]==0){
                board[x][y]=c;
        }
}
