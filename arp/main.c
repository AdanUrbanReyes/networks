#include "red.h"
#include "arp.h"
unsigned char tuip[4],tumac[6];
sred *cabr=NULL;
void *esvia(void *args)
{
	estructuraarp(cabr,tuip);
	return 0;
}
int main(int ari,char **arc)//./a.out wlan0 -i 192.168.1.95
{
        int paquete=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)),ciclo=1,j;
        if(paquete==-1)
                {puts("error al abrir el socket");return 1;}
        else
        {
                parametros(ari,arc,&ciclo,tuip);
                cabr=datosred(arc[1],paquete);
                putdatos(cabr);
		pthread_t hilo[ciclo];
		if(ciclo>1)
		{
			for(j=0;j<ciclo;j++)
				pthread_create(&hilo[ciclo],NULL,esvia,NULL);
		}
		else
			estructuraarp(cabr,tuip);
		pthread_join(hilo[ciclo],NULL);
        }
        return 0;
}
