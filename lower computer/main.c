#include <REGX52.H>

typedef unsigned int u16;
typedef unsigned char u8;


void uart_init(u8 baud)
{
    TMOD|=0X20; //���ü�����������ʽ2
    SCON=0X50;  //����Ϊ������ʽ1
    PCON=0X80;  //�����ʼӱ�
    TH1=baud;   //��������ʼֵ����
    TL1=baud;
    ES=1;       //�򿪽����ж�
    EA=1;       //�����ж�
    TR1=1;      //�򿪼����� 
}

void UART_SendByte(unsigned char Byte)
{
    SBUF=Byte;
    while(TI==0);
    TI=0;
}

void main()
{
    uart_init(0XFA);        //������Ϊ9600
    
    while(1)
    {
    }
}

void uart() interrupt 4 //����ͨ���жϺ���
{
    u8 rec_data;
    
    if(RI==1)
    {
        RI = 0;         //��������жϱ�־λ
        rec_data=SBUF;  //�洢���յ�������
        SBUF=rec_data;  //�����յ������ݷ��뵽���ͼĴ���
        while(!TI);     //�ȴ������������
        TI=0;           //���������ɱ�־λ     
    }
}