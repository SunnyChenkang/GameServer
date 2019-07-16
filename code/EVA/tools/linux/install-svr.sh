#!/bin/bash
# @author:chenkang
# @date:2019-07-11
###############################################
echo ""
echo ""
echo "**************************************"
echo "*                                    *"
echo "*                                    *"
echo "*   游戏服务自动安装部署             *"
echo "*                                    *"
echo "*                                    *"
echo "**************************************"

# 声明服务器运行目录
local_service_dir=/$HOME/service


# 声明远端拷贝文件目录
remote_dir=/home/service
# 声明远端服务器HOST
remote_host=123.126.123.123
# 声明远端服务器PORT
remote_port=2009
# 声明远端服务器密码
remote_passwd=chenkang

# 检查是否运行目录!
echo "【创建服务器运行目录】"
echo ""

if [ -d $local_service_dir ]
then
echo "" 
else
mkdir -p $local_service_dir
echo ""
fi

# yum 依赖程序

# 检查yum是否可用
[ $(yum repolist | awk '/repolist/{print$2}' | sed 's/,//') -eq 0 ] && ‘ YUM源有问题’ && exit 2

# 通过 &{i%%.*} 提前 screen.1.1.2  .前面字段 = screen
# &>/dev/null output送到无底洞
# [ $? -eq 0 ] 判断上条执行命令是否成功
# $? 来显示上一条命令执行的返回值 0 = 成功 其它表示失败
# -eq 【等于】
# -ne 【不等于】
# -gt 【大于】

echo -e "【开始检查依赖插件】" 

for i in expect screen cmake gcc gcc-c++ libxml2-devel.x86_64 openssl-devel.x86_64 lua-devel.x86_64 libcurl-devel.x86_64 mysql-devel e2fsprogs-devel uuid-devel libuuid-devel libpng-devel.x86_64
do
rpm -qa | grep ${i%%.*} &>/dev/null
[ $? -eq 0 ] || yum install -y  $i&>/dev/null
if [ $? -eq 0 ]
then 
echo '插件安装完成 :' $i
else
echo'安装插件失败 ： ' $i && exit 3
fi
done

echo ""
echo -e "【开始下载服务器依赖库】"
remote_file_libs=lib.tar.gz
remote_file_inc=include.tar.gz

expect -c "
spawn scp -P $remote_port service@$remote_host:/$remote_dir/\{$remote_file_libs,$remote_file_inc\} /home/ 
expect \"password:\"
send \"${remote_passwd}\r\"
expect "100%"
expect eof
"

echo ""
echo -e "【开始解压远程文件】"
#@1
mv /home/$remote_file_libs /usr/local/lib
cd /usr/local/lib
tar zxvf $remote_file_libs
#@2
mv /home/$remote_file_inc  /usr/local/include
cd /usr/local/include
tar zxvf $remote_file_inc

# 修改环境变量
echo ""
echo -e "【开始配置环境变量】"  
# 删除全部
sed -i '2,$d' /$HOME/$name/.bash_profile
# 写入新的
sed -i '$a\# Get the aliases and functions' /$HOME/$name/.bash_profile
sed -i '$a\if [ -f ~/.bashrc ]; then' /$HOME/$name/.bash_profile
sed -i '$a\        . ~/.bashrc' /$HOME/$name/.bash_profile
sed -i '$a\fi' /$HOME/$name/.bash_profile
sed -i '$a\# User specific environment and startup programs' /$HOME/$name/.bash_profile
sed -i '$a\MT_PATH=$HOME' /$HOME/$name/.bash_profile
sed -i '$a\export MT_PATH' /$HOME/$name/.bash_profile
sed -i '$a\PATH=$PATH:$HOME/bin:$HOME/tools/scripts/linux/:$HOME/server' /$HOME/$name/.bash_profile
sed -i '$a\export PATH' /$HOME/$name/.bash_profile
source /$HOME/$name/.bash_profile

# 修改hostname
echo ""
echo -e "【开始配置网络环境】"  
local_host=$(/sbin/ifconfig -a|grep inet|grep -v 127.0.0.1|grep -v inet6|awk '{print $2}'|tr -d "addr:")
local_name=$(hostname)
cd /etc
sed -i '$a\'$local_host' '$local_name'' hosts
sleep 2

echo ""
echo -e "【部署环境完成】" 

#重启机器
echo "是否需要重启机器"


exit 0

# 重启机器
#echo ""
#echo "是否需要重启机器（YES/NO）"
#read cmd
#if [ $cmd == 'YES' ]
#then
#reboot
#else
#echo "退出"
#fi





