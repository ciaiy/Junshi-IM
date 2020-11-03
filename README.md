# Junshi-IM
君识


## IM数据格式字典：

### 登录

 - client发送数据格式
```json
{
    "dataAck" : 123, // 随机值
    "queryBody" : {
        "queryType": "optionQuery",
        "queryInfo" : {
            "uid" : "uid",
            "cid" : "cid",
            "optid" : "optid",
            "type" : 1,  // LOGIN == 1
            "message" : "password",
            "ext" : ""
        }
    }  
}
```

 - processorToSender数据格式
 
```json
{
    "optid" : "123", // optid
    "type" :"USER_ONLINE",
    "data" : {
        "userInfo" : {  // mysql的allUser表数据
            "account":"124",
            "user_passwd":"123456",
            "sculputre":"123123",
            "nickName":"qizhou2",
            "birthday":"",
            "sign":"",
            "email":"",
            "sex":"",
            "tel":"",
            "occupation":"",
            "onlineState":"",
            "isFreeze":"",
            "nation":"",
            "privince":"",
            "city":""
        }
    },
    "mustDeliver"  : "false"
}
```

 -  客户端接收数据格式
```json
{
    "dataAck" : 123, // 随机值
    "resultBody" : {
        "optid" : "123", // optid
        "sendId" : "",
        "cid" : "",
        "type" :"USER_ONLINE",
        "data" : {
            "userInfo" : {  // mysql的allUser表数据
                "account":"124",
                "user_passwd":"123456",
                "sculputre":"123123",
                "nickName":"qizhou2",
                "birthday":"",
                "sign":"",
                "email":"",
                "sex":"",
                "tel":"",
                "occupation":"",
                "onlineState":"",
                "isFreeze":"",
                "nation":"",
                "privince":"",
                "city":""
            }
        },
    }
}
```

    