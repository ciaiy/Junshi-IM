package com.example.myapplication.activity;

import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;

import androidx.appcompat.app.AppCompatActivity;

import com.example.myapplication.Connector;
import com.example.myapplication.R;
import com.example.myapplication.constant.QueryType;
import com.example.myapplication.service.UserService;

public class LoginActivity extends AppCompatActivity {

    public static LoginActivity loginActivity;

    public Handler handler = new Handler()
    {
        @Override
        public void handleMessage(Message msg) {
            System.out.println("handle Message");
            if(msg.what == QueryType.LOGIN) {
                LinearLayout loading = findViewById(R.id.loginLoading);
                loading.setVisibility(View.INVISIBLE);
                Intent intent = new Intent(LoginActivity.this, MainViewActivity.class);
                startActivity(intent);
            }
        }
    };//不加这个分号则不能自动添加代码

    private UserService userService = UserService.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        loginActivity = this;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login);
        // 绑定网络情况监听模块
        MyReceiver networkReceiver = new MyReceiver();
        IntentFilter filter = new IntentFilter();
        filter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
        registerReceiver(networkReceiver, filter);
        // 检测是否可以连接服务器
        final boolean[] online = {true};
        final Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                online[0] = new Connector().checkOnline();
            }
        });
        thread.start();
        try {
            thread.join(1000);
        }catch (Exception e) {
            ;
        }
        // 初始化界面，绑定各种逻辑
        initView();
        // 如果连接不上服务器，则报出错误
        if(online[0] == false) {
            createDialog("服务器暂时无法连接，请稍后再试！").show();
        }
    }

    private void initView() {
        displayLoading(false);
        Button login = findViewById(R.id.loginLogin);
        login.setBackgroundColor(getResources().getColor(R.color.lightDingtalkBlue));

        final EditText userId = findViewById(R.id.loginUserId);
        final EditText password = findViewById(R.id.loginPassword);
        setLoginButtonAutoDisplay(userId, password);
        setLoginOnclick();
    }

    private void setLoginOnclick() {
        Button login = findViewById(R.id.loginLogin);
        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("onclick");
                final EditText userId = findViewById(R.id.loginUserId);
                final EditText password = findViewById(R.id.loginPassword);
                Button login = findViewById(R.id.loginLogin);
                displayLoading(true);
//                if(NoneInputFiledEmpty(userId, password)) {
                    // todo 登录逻辑
                  Thread thread = new Thread(new Runnable() {
                      @Override
                      public void run() {
                          System.out.println("thread login");
                          userService.login(userId.getText().toString(), password.getText().toString());
                      }
                  });
                  thread.start();

//                }else if(NoneInputFiledEmpty(userId, password) == false) {
//                    createAlertEmptyDialog().show();
//                }
            }
        });
    }

    private void displayLoading(boolean switcher) {
        LinearLayout loading = findViewById(R.id.loginLoading);
        if(switcher) {
            loading.setVisibility(View.VISIBLE);
        }else {
            loading.setVisibility(View.INVISIBLE);
        }
    }

    private AlertDialog createAlertOfflineDialog() {
        return createDialog("目前处于离线状态，请检查网络！");
    }

    private AlertDialog createAlertEmptyDialog() {
        return createDialog("请输入账号和密码！");
    }

    private boolean NoneInputFiledEmpty(EditText userId, EditText password) {
        return userId.getText().length() > 0 && password.getText().length() > 0;
    }

    private AlertDialog createDialog(String Message) {
        AlertDialog.Builder builder = new AlertDialog.Builder(LoginActivity.this);
        builder.setMessage(Message);
        builder.setPositiveButton("确定", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {}
        });
        return builder.create();
    }

    private void setLoginButtonAutoDisplay(EditText userId, EditText password) {
        userId.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                EditText userId = findViewById(R.id.loginUserId);
                EditText password = findViewById(R.id.loginPassword);
                Button login = findViewById(R.id.loginLogin);
                if(NoneInputFiledEmpty(userId, password)) {
                    login.setBackgroundColor(getResources().getColor(R.color.dingtalkBlue));
                }else {
                    login.setBackgroundColor(getResources().getColor(R.color.lightDingtalkBlue));
                }
            }
        });
        password.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                EditText userId = findViewById(R.id.loginUserId);
                EditText password = findViewById(R.id.loginPassword);
                Button login = findViewById(R.id.loginLogin);
                if(NoneInputFiledEmpty(userId, password)) {
                    login.setBackgroundColor(getResources().getColor(R.color.dingtalkBlue));
                }else {
                    login.setBackgroundColor(getResources().getColor(R.color.lightDingtalkBlue));
                }
            }
        });
    }

    public class MyReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent.getAction().equals("android.net.conn.CONNECTIVITY_CHANGE")){
                ConnectivityManager connManger = (ConnectivityManager) getSystemService(CONNECTIVITY_SERVICE);
                NetworkInfo activeNetworkInfo = connManger.getActiveNetworkInfo();
                if(activeNetworkInfo == null || activeNetworkInfo.isConnected() == false) {
                    createAlertOfflineDialog().show();
                }
            }
        }
    }
}
