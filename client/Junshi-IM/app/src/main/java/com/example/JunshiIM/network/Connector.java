package com.example.JunshiIM.network;

import com.example.JunshiIM.entity.Query;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;

public class Connector {
    private static Socket socket = new Socket();
    
    
    public static boolean checkOnline() {
        System.out.println("checkOnline");
        try {
            socket.connect(new InetSocketAddress("47.94.149.37", 2333), 1000);
            System.out.println("连接成功");
            return true;
        } catch (SocketTimeoutException e) {
            System.out.println("连接超时");
            return false;
        } catch (IOException e) {
            System.out.println("连接错误" + e.getMessage());
            return false;
        }
        }

    public void send(Query query) {

    }


}
