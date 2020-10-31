import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.fastjson.JSONPatch;
import com.sun.javafx.collections.MappingChange;
import javafx.beans.property.adapter.JavaBeanBooleanProperty;
import org.jcp.xml.dsig.internal.SignerOutputStream;

import java.io.*;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

public class testJson {

    public static String streamToString(InputStream inputStream){
            ByteArrayOutputStream outputStream=null;
            try {
                outputStream = new ByteArrayOutputStream();
                byte[] b=new byte[1024];
                int len;
                while ((len=inputStream.read(b))!=-1){
                    outputStream.write(b,0,len);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            return outputStream.toString();
        }

    class JavaBean{
        private String dataAck;
        private String[] queryBody = new String[2];

        public void setdataAck(String data){
            this.dataAck = data;
        }
        public String getdataAck(){
            return this.dataAck;
        }
    }

    public static void main(String[] args) throws IOException {
        //要链接的服务端IP地址和端口
        String host = "47.94.149.37";//10.21.87.190
        int port = 2333;
        //调制字符串
        String send = "{\"dataAck\": \"123\",\"queryBody\":[{\"key1\":\"data1\",\"key2\":\"data2\"}]}";
        JSONObject jsonObject = JSON.parseObject(send);
//        String test = jsonObject.getString("dataAck");
//        System.out.print(test);
        //与服务器建立连接
        Socket socket = new Socket(host, port);
        //建立连接后获得输出流
        //先输出字符串的长度
        int len = send.length();
        OutputStream outputStream = socket.getOutputStream();
        DataOutputStream dataSend = new DataOutputStream(outputStream);
        dataSend.write(len);
        //输出完毕

        //再发送json的string格式
//        byte[] buf = new byte[1024];
//        int length = 0;
//        while((length = dataSend.write();))
//        dataSend.write();
        socket.getOutputStream().write(send.getBytes());
        //发送完毕

        //接收并解析服务器发来的json
        //法一
        InputStream in = socket.getInputStream();
        String jsonStr = streamToString(in);
        JSONObject jsonRev = JSON.parseObject(jsonStr);
        JSONArray array = JSON.parseArray(jsonStr);
        JSONObject json = jsonRev.getJSONObject("dataAck");
        System.out.print("dataAck: " + json);//输出服务器返回的值
        //法二,不懂
//        byte[] buf = new byte[1024];
//        int length = 0;
//        while((length = in.read(buf)) != -1){
//            System.out.println(new String(buf, 0, length));
//        }

        outputStream.close();
        socket.close();
    }
}
