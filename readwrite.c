void player_read(struct client_socket c_sock){
read(c_sock.c_socket, &p_x, sizeof(int));
read(c_sock.c_socket, &p_y, sizeof(int));
printf("player%d (%d, %d)\n",c_sock.player,p_x,p_y);
putting(p_x,p_y,c_sock.player);
drawBoard();
if(endGame(c_sock.player) == END){
gameresult.end[0]='e';
printf("result : %c",gameresult.end[0]);
gameresult.player = c_sock.player;
}}void player_write(struct client_socket c_sock){
write(c_sock.c_socket, &p_x, sizeof(int));
write(c_sock.c_socket, &p_y, sizeof(int));
}
