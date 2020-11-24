# Junshi-IM
君识


## IM数据格式字典：

### 登录

 - client发送数据格式
```json
{
    "sourceType" : "client",
    "dataAck" : 123, // 随机值
    "context":{
        "queryId" : "randomID",
        "authToken" : "uid + deviceId",
        "token" : "deviceId"
    },
    "queryBody" : {
        "queryType": "optionQuery",
        "queryInfo" : {
            "uid" : "uid",
            "cid" : "cid",
            "optid" : "optid",
            "type" : 1,  // LOGIN == 1
            "message" : "password",
            "ext":""
        }
    }  
}
```

 - connectorToProcessor数据格式

```json
{
        "queryType": "optionQuery",
        "context":{
            "uid" : "uid",
            "queryId" : "randomID",
            "authToken" : "tokenTemp assigned by connector",
            "token" : "deviceId"
        },
        "queryInfo" : {
            "uid" : "uid",
            "cid" : "cid",
            "optid" : "optid",
            "type" : 1,  // LOGIN == 1
            "message" : "password",
            "ext" : ""
        },
        "ext" : ""
}
```

 - processorToSender数据格式
 
```json
{
    "optid" : "123", // optid
    "type" : "USER_ONLINE",
    "context":{
            "uid" : "uid",
            "queryId" : "randomID",
            "authToken" : "tokenTemp assigned by connector",
            "token" : "deviceId"
    },
    "data" : {
        "loginResult" : 1,
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
    "mustDeliver"  : "false",
    "ext" : ""
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

    