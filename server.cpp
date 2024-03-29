
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUFFER_SIZE 100 
#pragma comment(lib, "ws2_32")
int
main() {
  /* ポート番号、ソケット */
  unsigned short port = 21;//your server port
  int srcSocket;  // 自分
  int dstSocket;  // 相手

  /* sockaddr_in 構造体 */
  struct sockaddr_in srcAddr;
  static struct sockaddr_in dstAddr;
  int dstAddrSize = sizeof(dstAddr);

  /* 各種パラメータ */
  int numrcv;
  char buffer[BUFFER_SIZE];
  //char *buffer;

  /************************************************************/
  /* Windows 独自の設定 */
  WSADATA data;
  WSAStartup(MAKEWORD(2,0), &data); 

  /* sockaddr_in 構造体のセット */
  memset(&srcAddr, 0, sizeof(srcAddr));
  srcAddr.sin_port = htons(port);
  srcAddr.sin_family = AF_INET;
  srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* ソケットの生成 */
  srcSocket = socket(AF_INET, SOCK_STREAM, 0);

  /* ソケットのバインド */
  bind(srcSocket, (struct sockaddr *) &srcAddr, sizeof(srcAddr));

  /* 接続の許可 */
  listen(srcSocket, 1);

  /* 接続の受付け */
  printf("Waiting for connection ...\n");
  dstSocket = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
  printf("Connected from %s\n", inet_ntoa(dstAddr.sin_addr));

  /* パケット受信 */
  while(true) {
    numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0); 
    if(numrcv == 0 || numrcv == -1) {
      int status = closesocket(dstSocket); 
    }
    printf("received: %s\n", buffer);
  }

  /* Windows 独自の設定 */
      WSACleanup();
      
}