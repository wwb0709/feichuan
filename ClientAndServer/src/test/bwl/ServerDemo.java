package test.bwl;


import java.io.DataInputStream;

import java.io.DataOutputStream;

import java.io.IOException;

import java.net.ServerSocket;

import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Vector;

public class ServerDemo {

/**

* 注意：Socket的发送与接收是需要同步进行的，即客户端发送一条信息，服务器必需先接收这条信息，

* 而后才可以向客户端发送信息，否则将会有运行时出错。

* @param args

*/
	
//	public void start(){
//
//        ServerSocket ss=null;
//
//        try {
//
//            ss=new ServerSocket(8000);
//
//        } catch (Exception e) {
//
//            e.printStackTrace();
//
//        }
//
//       
//
//        while(true){
//
//            Socket clientSocket=null;
//
//            try {
//
//                clientSocket=ss.accept();
//
//                System.out.println("a client connected!");
//
//                DataInputStream dis=new DataInputStream(clientSocket.getInputStream());
//
//               
//
//                byte bytesRead[]=new byte[20];
//
//                dis.read(bytesRead);
//
//
//
//                String strValue=new String(bytesRead);
//
//                System.out.println("receiveValue="+strValue);
//
//                DataOutputStream dos  = new DataOutputStream(clientSocket.getOutputStream());
//                
//                dos.write("connect success".getBytes());
//
//                new Thread(new TCPClientThread(clientSocket)).start();
//
//
//
//            } catch (IOException e) {
//
//                // TODO Auto-generated catch block
//
//                e.printStackTrace();
//
//            }
//
//           
//
//        }
//	}







public static void main(String[] args) {
//	ServerDemo demo = new ServerDemo();
//	demo.start();
	
	
	
	
	
	 


    ServerSocket socket=null;
    Vector m_threads=new Vector();
    System.out.println("服务器已启动，正在等待客户的请求...");
    try
    {
        //设置Server监听端口号为8000, 这个数字必须
        //和程序ChatClient中的port参数一致。
        socket=new ServerSocket(8000);
    }
    catch(Exception e)
    {
        System.out.println("服务接口建立失败!");
        return;
    }
    try
    {
        int nid=0;
        while(true)
        {
            //监听是否有新Chat Applet连接到Server,
            //线程运行到该语句会封锁，直到有新的连接产生。
            Socket s=socket.accept();
            //创建一个新的ServerThread.
            TCPClientThread  st =new TCPClientThread(s,m_threads);
            //为该线程设置一个ID号。
            st.setID(nid++);
            //将该线程加入到m_threads Vector中。
            m_threads.addElement(st);
            //启动服务线程。
            new Thread(st). start();
            //通知所有Chat Applet有一个新的网友加入。
            for(int i=0;i<m_threads.size();i++)
            {
            	TCPClientThread st1=(TCPClientThread)m_threads.elementAt(i);
                st1.write("welcom "+st.getID()+"friend");
            }
            System.out.println("接受"+st.getID()+"号客户请求");
            System.out.println("继续等待其他客户的请求...\n");
        }
    }
    catch(Exception e)
    {
        System.out.println("服务器已关闭...");
    }


}

}
class TOOL{
	
    public byte[] intToBytes(int n) {  
        byte[] b = new byte[4];  
        b[3] = (byte) (n & 0xff);  
        b[2] = (byte) (n >> 8 & 0xff);  
        b[1] = (byte) (n >> 16 & 0xff);  
        b[0] = (byte) (n >> 24 & 0xff);  
        return b;  
    }  
  
    public  void intToBytes(int n, byte[] array, int offset) {  
        array[3 + offset] = (byte) (n & 0xff);  
        array[2 + offset] = (byte) (n >> 8 & 0xff);  
        array[1 + offset] = (byte) (n >> 16 & 0xff);  
        array[offset] = (byte) (n >> 24 & 0xff);  
    }  
  
    /** 
     * @param b 
     * @return 
     */  
    public  int bytesToInt(byte b[]) {  
        return b[3] & 0xff | (b[2] & 0xff) << 8 | (b[1] & 0xff) << 16 | (b[0] & 0xff) << 24;  
    }  
    
    public  byte[] shortToBytes(short n) {  
        byte[] b = new byte[2];  
        b[1] = (byte) (n & 0xff);  
        b[0] = (byte) ((n >> 8) & 0xff);  
        return b;  
    }  
  
    public  void shortToBytes(short n, byte[] array, int offset) {  
        array[offset + 1] = (byte) (n & 0xff);  
        array[offset] = (byte) ((n >> 8) & 0xff);  
    }  
  
    public  short bytesToShort(byte[] b) {  
        return (short) (b[1] & 0xff | (b[0] & 0xff) << 8);  
    }  
	
}
class TCPClientThread implements Runnable {

    Socket cSocket=null;

    Vector m_threads;
    DataInputStream dis=null;
    DataOutputStream dos =null;
    int m_nid;
    TOOL tool = new TOOL();

//    public TCPClientThread(Socket cliSocket) {
//
//        super();
//
//        this.cSocket = cliSocket;
//
//    }
    //初始化该线程。
    public TCPClientThread(Socket s,Vector threads)
    {
    	cSocket=s;
        m_threads=threads;
        try
        {
        	dis=new DataInputStream(cSocket.getInputStream());
        	dos=new DataOutputStream(cSocket.getOutputStream());
        }
        catch(Exception e)
        {
        }
    }



    public void run() {
    	
    	
        System.out.println("等待进程正在运行");
        try
        {
            while(true)
            {
            	  System.out.println("while");
                //监听对应的Applet是否传来消息
                //程序陷入到m_in.readUTF()中，直到有信息传来才返回。
                
              byte buf[]=new byte[1024];
              dis.read(buf);
              System.out.println(new String(buf));
              SimpleDateFormat tempDate = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
              String datetime = tempDate.format(new java.util.Date());
              
              this.write(datetime);
              String s=new String(buf);
              int len = s.trim().length();
              System.out.println("buf length:"+len);
                if (s==null||len==0)
                  break;
//                //如果Chat Applet传来的信息为"leave",
//                //则通知所有其他的的Chat Applet自己退出了。
//                if  (s.trim().equals ("leave"))
//                  for (int i=0;i<m_threads.size();i++)
//                    {
//                	  TCPClientThread st=(TCPClientThread)m_threads.elementAt(i);
//                      st.write("all， "+getID()+"leave"+"！*");
//                    }
//                else
//                //向所有Chat Applet广播该信息。
//                for(int i=0;i<m_threads.size();i++)
//                {
//                	TCPClientThread st=(TCPClientThread)m_threads.elementAt(i);
//                    st.write("----"+getID()+"said hello");
//                }
            }
        }
        catch(Exception e)
        {  e.printStackTrace();
        }
        //从m_threads Vector中删除该线程，表示该线程已经离开聊天室。
        m_threads.removeElement(this);
        try
        { cSocket.close();
        }
        catch (Exception e){}
    	
    	

//        while(cSocket!=null){
//
//          
//
//            try {
//
//                dis=new DataInputStream(cSocket.getInputStream());
//                dos = new DataOutputStream(cSocket.getOutputStream());
//
//                byte buf[]=new byte[1000];
//
//                dis.read(buf);
//
//                System.out.println(new String(buf));
////                dos.writeUTF("接受连接请求，连接成功!");
//                dos.write("connect success".getBytes());
//
//            } catch (IOException e) {
//
//                // TODO Auto-generated catch block
//
//                e.printStackTrace();
//                break;
//
//            }
//
//           
//
//        }

    }

    //将msg送回对应的Applet
    public void write (String msg)
    {
        synchronized(dos)
        {
            try
            {
            	
            	int len = msg.getBytes().length;
            	short commond = 10;
            	byte[] c = msg.getBytes();
            	byte[] ib = tool.intToBytes(len+6);
            	byte[] cb = tool.shortToBytes(commond);
            	int totallength = cb.length+ib.length+len;
            	byte[] b = new byte[totallength]; 
            	
            	System.out.println("commond:"+commond+"cb.length:"+cb.length+"-----ib.length:"+ib.length+"msg len:"+len+"msg:"+msg);
            	
            	 System.arraycopy(cb, 0, b, 0, cb.length);
                 System.arraycopy(ib, 0, b, cb.length, ib.length);
                 System.arraycopy(c, 0, b, cb.length+ib.length, c.length);
                dos.write( b);
//                dos.write( msg.getBytes());
            }
            catch(IOException e){}
        }
    }
    public int getID()  //获得该线程的ID.
    {
        return m_nid;
    }
    public void setID(int nid)  // //设置线程的ID.
    {
        m_nid=nid;
    }

}