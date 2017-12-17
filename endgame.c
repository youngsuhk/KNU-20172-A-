int endGame(int c)//c == player num, if game end return END(1){
const int NOD=8;    
//const int CONTINUE=0;    
//const int NOD=8;      
int x,y,player,d,i;    
int dx[]={1,1,0,-1,-1,-1,0,1};     
int dy[]={0,1,1,1,0,-1,-1,-1};       
for(x=0;x        
for(y=0; y                 
player=board[x][y];//check board pebble            
if(player==c){                       
for(d=0; d                            
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
return CONTINUE;}int putting(int x, int y, int c){ 
if(board[x][y]==0){       
board[x][y]=c;    
} 
}
