#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdio>

using namespace std;

int main(int argc,char *argv[]){
  
  if(argc < 4){
    cout<<"Usage: "<<argv[0]<<" Ip Starting_Port Ending_Port\n";
    return 1;
  }

  string IP = argv[1];
  int start_port = atoi(argv[2]);
  int end_port = atoi(argv[3]);
  int valid_ports[65535];

  int socketfd = socket(AF_INET,SOCK_STREAM,0);

  if(socketfd <= 0){
    cerr<<"[*] Skill issue by socket"<<endl;
    return -1;
  }

  struct sockaddr_in address;
  address.sin_family= AF_INET;
  address.sin_addr.s_addr = inet_addr(IP.c_str());
  int current = 0 ;
  for(int i = start_port ; i <= end_port ; i++){
    address.sin_port = htons(i);     
    if(connect(socketfd,(struct sockaddr*)&address,sizeof(address)) == 0 ){
      cout<<"[*] Port "<<i<<" is open"<<endl;
      valid_ports[current]=i;
      current++;
    }

    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd < -1){
      cout<<"[*] Failed creating socket!\n";
      return -1;
    }

  }
  FILE * fptr = NULL;
  fptr = fopen("out.log","w");
  
  if(NULL == fptr){
      cout<<"[*] fatal error:  writting to file"<<endl;
    return -1;
  }



  for(int i = 0 ; i < current ; i++){
    fprintf(fptr,"[*] Open Port: %d\n",valid_ports[i]);
    cout<<valid_ports[i]<<endl;
  }
  cout<<"[+] Do you want to do more enum on those ports? (y/n)"<<endl;
  char t;

  cin>>t;
  if(t == 'n'){
    cout<<"[+] Exiting!"<<endl;
    fclose(fptr);
    close(socketfd);
    return 1;
  }
  

  fclose(fptr);
  close(socketfd);
  
  return 0;
}