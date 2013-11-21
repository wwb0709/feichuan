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

//获取输出流，用于客户端向服务器端发送数据

DataOutputStream dos = new DataOutputStream(socket.getOutputStream());

//获取输入流，用于接收服务器端发送来的数据

DataInputStream dis = new DataInputStream(socket.getInputStream());


System.out.println("send request!");
dos.write("leave".getBytes());
//客户端向服务器端发送数据
//while(true)
//{
////打印出从服务器端接收到的数据
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

//不需要继续使用此连接时，记得关闭哦



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
