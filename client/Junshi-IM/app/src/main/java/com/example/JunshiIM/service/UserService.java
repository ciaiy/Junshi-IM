package com.example.JunshiIM.service;

import android.os.Message;

import com.example.JunshiIM.activity.LoginActivity;
import com.example.JunshiIM.constant.JunshiPns;
import com.example.JunshiIM.constant.QueryType;
import com.example.JunshiIM.entity.Query;
import com.example.JunshiIM.entity.QueryInfo;
import com.example.JunshiIM.network.Connector;

public class UserService {
    private static UserService userService = null;
    private Connector connector;
    private UserService(){

    }

    public static UserService getInstance() {
        if(userService == null) {
            userService = new UserService();
        }
        return userService;
    }

    public boolean login(String userId, String password) {
        if(userId.length() == 0 || password.length() == 0) {
            return false;
        }
        System.out.println("UserService login");
        QueryInfo query = new QueryInfo.Builder()
                .queryType("optionQuery")
                .uid(userId)
                .optid(userId)
                .type(1)
                .message(password)
                .ext(userId + ":" + JunshiPns.deviceId)
                .build();
        Query message = new Query();
//        connector.send(message);
        Message msg = new Message();
        msg.what = QueryType.LOGIN;
        if(LoginActivity.loginActivity == null) {
            System.out.println("loginActivity null");
        }
        Message message1 = new Message();
        message1.what = QueryType.LOGIN;
        LoginActivity.loginActivity.handler.sendMessage(message1);
        return true;
    }
}
