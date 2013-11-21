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

* ע�⣺Socket�ķ������������Ҫͬ�����еģ����ͻ��˷���һ����Ϣ�������������Ƚ���������Ϣ��

* ����ſ�����ͻ��˷�����Ϣ�����򽫻�������ʱ����

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
    System.out.println("�����������������ڵȴ��ͻ�������...");
    try
    {
        //����Server�����˿ں�Ϊ8000, ������ֱ���
        //�ͳ���ChatClient�е�port����һ�¡�
        socket=new ServerSocket(8000);
    }
    catch(Exception e)
    {
        System.out.println("����ӿڽ���ʧ��!");
        return;
    }
    try
    {
        int nid=0;
        while(true)
        {
            //�����Ƿ�����Chat Applet���ӵ�Server,
            //�߳����е������������ֱ�����µ����Ӳ�����
            Socket s=socket.accept();
            //����һ���µ�ServerThread.
            TCPClientThread  st =new TCPClientThread(s,m_threads);
            //Ϊ���߳�����һ��ID�š�
            st.setID(nid++);
            //�����̼߳��뵽m_threads Vector�С�
            m_threads.addElement(st);
            //���������̡߳�
            new Thread(st). start();
            //֪ͨ����Chat Applet��һ���µ����Ѽ��롣
            for(int i=0;i<m_threads.size();i++)
            {
            	TCPClientThread st1=(TCPClientThread)m_threads.elementAt(i);
                st1.write("welcom "+st.getID()+"friend");
            }
            System.out.println("����"+st.getID()+"�ſͻ�����");
            System.out.println("�����ȴ������ͻ�������...\n");
        }
    }
    catch(Exception e)
    {
        System.out.println("�������ѹر�...");
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
    //��ʼ�����̡߳�
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
    	
    	
        System.out.println("�ȴ�������������");
        try
        {
            while(true)
            {
            	  System.out.println("while");
                //������Ӧ��Applet�Ƿ�����Ϣ
                //�������뵽m_in.readUTF()�У�ֱ������Ϣ�����ŷ��ء�
                
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
//                //���Chat Applet��������ϢΪ"leave",
//                //��֪ͨ���������ĵ�Chat Applet�Լ��˳��ˡ�
//                if  (s.trim().equals ("leave"))
//                  for (int i=0;i<m_threads.size();i++)
//                    {
//                	  TCPClientThread st=(TCPClientThread)m_threads.elementAt(i);
//                      st.write("all�� "+getID()+"leave"+"��*");
//                    }
//                else
//                //������Chat Applet�㲥����Ϣ��
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
        //��m_threads Vector��ɾ�����̣߳���ʾ���߳��Ѿ��뿪�����ҡ�
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
////                dos.writeUTF("���������������ӳɹ�!");
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

    //��msg�ͻض�Ӧ��Applet
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
    public int getID()  //��ø��̵߳�ID.
    {
        return m_nid;
    }
    public void setID(int nid)  // //�����̵߳�ID.
    {
        m_nid=nid;
    }

}