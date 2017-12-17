int main(int ac, char *av[]){        //server&client        
int port = atoi(av[1]);        
struct sockaddr_in c_addr;        
int c_addr_size = sizeof(c_addr);        
struct client_socket cl_socket[2];        
int sock;        //program        
int i,turn;//        
int s_num;//socket number        
if((sock = make_server_socket(port)) ==-1)
oops("socket");        
printf("                OmokGo\n\n      waiting for player..\n\n");        //client accept
for(i=0; i<2; i++){
if((cl_socket[i].c_socket = accept(sock,(struct sockaddr*)&c_addr, &c_addr_size))==-1)
break;
cl_socket[i].player = i+1;
printf("player : %d connected\n", cl_socket[i].player);
cl_socket[i].turn = i+3;
}         //client login
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
close(cl_socket[0].c_socket); close(cl_socket[1].c_socket);}
