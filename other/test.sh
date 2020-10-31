if [ ! $1 ] then 
    echo "ip为空"
    echo "sh install.sh IPaddress"
else
    # 安装必要插件
    yum install java -y
    yum -y install java-1.8.0-openjdk*
    yum install unzip -y
    yum install git -y
    yum install maven -y
    yum install make gcc gcc-c++ automake libtool cmake bzip2 bzip2-devel zlib zlib-devel -y

    # 获取apacheRocketmq源代码并进行编译
    wget 'https://mirrors.tuna.tsinghua.edu.cn/apache/rocketmq/4.7.1/rocketmq-all-4.7.1-source-release.zip'
    unzip rocketmq-all-4.7.1-source-release.zip
    mv rocketmq-all-4.7.1-source-release /opt/
    cd /opt/rocketmq-all-4.7.1-source-release/
    mvn -Prelease-all -DskipTests clean install -U
    # 修改配置信息
    vim bin/runserver.sh
    # JAVA_OPT="${JAVA_OPT} -server -Xms256m -Xmx256m -Xmn512m -XX:MetaspaceSize=128m -XX:MaxMetaspaceSize=320m"　
    vim bin/runbroker.sh
    # JAVA_OPT="${JAVA_OPT} -server -Xms256m -Xmx256m -Xmn128m"

    # 获取rocketmq-client-c++源代码并编译
    cd /opt
    git clone https://github.com/apache/rocketmq-client-cpp.git
    cd rocketmq-client-cpp
    sh build.sh
    cp /opt/rocketmq-client-cpp/bin/* /usr/local/lib

    ## 获取log4cppu源代码并编译
    cd /opt
    git clone https://github.com/meihao1203/log4cpp
    cd log4cpp
    tar -zxvf log4cpp-1.1.1.tar.gz

    ./configure
    make
    make check
    make install
    # 没有将动态依赖写入
    cp /opt/log4cpp/log4cpp/include/log4cpp/* /usr/include
    # 在/etc/profile中写入
    # export LD_LIBRARY_PATH=/usr/lib/:/usr/local/lib/
    vim /etc/profile

    # 获取rocketmq控制台源代码并编译
    git clone -b release-rocketmq-console-1.0.0 https://github.com/apache/rocketmq-externals.git
    vim /opt/rocketmq-externals/rocketmq-console/src/main/resources/application.properties
    # 写入
    # server.port=8181
    # rocketmq.config.namesrvAddr= IPAddress:9876
    cd /opt/rocketmq-externals/rocketmq-console
    mvn clean package -Dmaven.test.skip=true
    
    # 启动
    cd /opt/rocketmq-all-4.7.1-source-release/distribution/target/rocketmq-4.7.1/rocketmq-4.7.1
    nohup sh bin/mqnamesrv & 
    nohup sh bin/mqbroker -n 0.0.0.0:9876 &
    cd /opt/rocketmq-externals/rocketmq-console
    mvn clean package -Dmaven.test.skip=true
    cd /opt/rocketmq-externals/rocketmq-console/
    java -jar target/rocketmq-console-ng-1.0.0.jar > ~/rocket-console.log &
fi