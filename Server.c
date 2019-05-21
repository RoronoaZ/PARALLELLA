#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
 
int main(int argc , char *argv[])
{
   
    int socket_desc , new_socket , c;
    struct sockaddr_in server , client;
    char *message;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8777 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
   int cpt=0;
  #pragma omp_set_num_threads(2)
  #pragma omp parallel
{ 
  while(1){  
    //Accept an incoming connection
    
    puts("Waiting for incoming connections Server 0");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    //if (new_socket<0)
    //{
     //   perror("accept failed");
      //  return 1;
    //}
     
    puts("Connection accepted");
    cpt+=1;
    printf("Response to websocket from thread %d ", omp_get_thread_num());
    printf("\n");
    
//Reply to the client
    //message = "Hello Client , I have received your connection. But I have to go now, bye %d \n", cpt;
    message = "Hello Client , I have received your connection. But I have to go now, bye";
    send(new_socket , message , strlen(message), 0);
    close(new_socket);

//break;
     
}

}
    return 0;

}
