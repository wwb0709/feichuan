package test.bwl;



import java.io.DataInputStream;

import java.io.DataOutputStream;

import java.io.IOException;

import java.io.OutputStream;

import java.net.Socket;

import java.net.UnknownHostException;

public class ClientDemo {

/**

* @param args

*/

public static void main(String[] args) {

Socket socket = null;

try {

socket = new Socket("localhost",8000);

//��ȡ����������ڿͻ�����������˷�������

DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

//��ȡ�����������ڽ��շ������˷�����������

DataInputStream dis = new DataInputStream(socket.getInputStream());


System.out.println("send request!");
dos.write("leave".getBytes());
//�ͻ�����������˷�������
//while(true)
//{
////��ӡ���ӷ������˽��յ�������
//
////byte bytesRead[]=new byte[20];
////
////dis.read(bytesRead);
////
////
////
////String strValue=new String(bytesRead);
//
//System.out.println("client receiveValue="+dis.readByte());
//}

//����Ҫ����ʹ�ô�����ʱ���ǵùر�Ŷ



} catch (UnknownHostException e) {

e.printStackTrace();

} catch (IOException e) {
e.printStackTrace();

}

try {
	socket.close();
} catch (IOException e) {
	// TODO Auto-generated catch block
	e.printStackTrace();
}
}

}
