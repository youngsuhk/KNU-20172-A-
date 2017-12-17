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
//fclose(f);}
