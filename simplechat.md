

# TODO

* model<-->xml

* model<-->db

* signup

* config

* login

* mainWindow

  > * 好友列表
  >
  >   > QListView
  >
  > * 在线好友列表
  >
  > * 双击在线好友



# 后续改进

* 当前：采用base64+xml方式发送文件。

  后续：使用协议http【基于libcurl】。

  客户端、服务端的xml只用于传输文本。

  且修改服务器自定义的xml解析为使用【cereal库】，客户端使用qt的xml解析而不用拼字符串方式。

  

# 协议

这些结构体、类，**只是xml层面、数据传输层面的抽象**，主要功能是传输数据。

## enum msgtype

| msgtype     | 描述     |
| ----------- | -------- |
| heartbeat=0 | 心跳报文 |
| request=1   | 请求报文 |
| response=2  | 响应报文 |
| ack=3       | ACK报文  |

## struct identify

| identify | 描述                        | 最大长度 |
| -------- | --------------------------- | -------- |
| account  | 账号                        | 20       |
| password | 密码                        | 20       |
| token    | login后服务器返回的身份标识 | 50       |

## enum bizcode

| bizcode | 描述           |
| ------- | -------------- |
| 0       | do nothing     |
| 1       | 注册请求signup |
| 2       | 登录请求login  |
| 3       | 登出请求logout |
| 4       | 聊天请求chat   |
| 5       | 获取在线好友   |
|         |                |

## struct data

| data     | 描述                                                        |
| -------- | ----------------------------------------------------------- |
| datatype | text=0、token=1、image_png=10、audio_mp3=20、video_mp4=30、 |
| datasize | databody的字节数                                            |
| databody | 数据体                                                      |

> 1. 音频文件：MP3、WAV、AAC、FLAC、OGG等。
> 2. 视频文件：MP4、AVI、MOV、MKV、FLV等。
> 3. 文档文件：PDF、DOCX、TXT、RTF、ODT等。
> 4. 电子表格文件：XLSX、CSV、ODS、XLS等。
> 5. 数据库文件：SQLite、MySQL、PostgreSQL、MongoDB等。
> 6. 压缩文件：ZIP、RAR、7z、GZIP等。
> 7. 图像文件：JPEG、PNG、GIF、BMP、SVG等。
> 8. 3D模型文件：OBJ、FBX、DAE、STL等。
> 9. CAD文件：DWG、DXF等。
> 10. 编程语言源代码文件：C++ (.cpp, .h), Java (.java, .class), Python (.py), JavaScript (.js)等。
> 11. 网页文件：HTML、CSS、JS等。
> 12. 字体文件：TTF、OTF、WOFF等。
> 13. 电子书文件：EPUB、MOBI、AZW等。
> 14. 幻灯片演示文稿：PPTX、KEY、ODP等。
> 15. 日志文件：LOG、TXT等。
> 16. 配置文件：INI、JSON、XML等。
> 17. 邮件附件：PST、MBOX等。
> 18. 游戏资源文件：Unity的AssetBundles、Unreal Engine的资源包等。
> 19. CAD设计文件：STEP、IGES等。
> 20. 科学数据文件：HDF5、MATLAB文件等。

## struct forw

| forw      | 描述       |
| --------- | ---------- |
| forwcode  | 转发行为   |
| rececount | 接收者个数 |
| receivers | 接收者     |



## enum forwcode

| forwcode | 描述             |
| -------- | ---------------- |
| 0        | no forward       |
| 1        | forward to all   |
| 2        | forward to one   |
| 3        | forward to group |
|          |                  |

## struct retcode

根据具体业务增加

| X    | 描述    |
| ---- | ------- |
| 0    | succeed |
| 1    | failed  |

| signup retcode：1X | 描述         |
| ------------------ | ------------ |
| 10                 | 注册成功     |
| 11                 | 注册失败     |
| 12                 | 用户名已存在 |
|                    |              |

| login retcode:2X | 描述     |
| ---------------- | -------- |
| 20               | 登录成功 |
| 21               | 登录失败 |
| 22               | 已登录   |
|                  |          |

| logout retcode:3X | 描述     |
| ----------------- | -------- |
| 30                | 登出成功 |
| 31                | 登出失败 |

| chat retcode:4X | 描述     |
| --------------- | -------- |
| 40              | 转发成功 |
| 41              | 转发失败 |
|                 |          |



# client

> 在即时聊天软件中，将用户的好友与socketfd（socket文件描述符）对应起来，通常涉及到以下几个关键步骤：
>
> 1. **用户注册与登录**：用户在使用聊天软件时首先需要注册和登录，这时服务器会为每个用户生成一个唯一的标识，如用户ID或用户名。
> 2. **建立WebSocket连接**：用户登录后，客户端（如网页或移动应用）会与服务器建立一个WebSocket连接，这个连接会被分配一个唯一的socketfd。
> 3. **用户状态管理**：服务器需要维护一个用户状态列表，记录每个用户ID与其对应的socketfd，以及他们的在线状态。这样，当有消息需要发送给用户时，服务器可以根据用户ID快速找到其socketfd进行消息推送。
> 4. **好友关系维护**：用户的好友列表通常存储在数据库中，当用户添加或删除好友时，好友关系会更新在数据库里。服务器可以根据这些数据来提供好友在线状态查询、消息推送等功能。
> 5. **消息路由**：当用户发送消息给好友时，客户端将消息发送到服务器，服务器根据消息的接收者ID查找到对应的socketfd，然后将消息通过这个socketfd发送给目标用户。
>
> 在实现好友列表与socketfd对应时，可以参考以下两种方案：
>
> - **方案一**：建立一个好友表，记录用户与好友之间的关系，每次用户登录时查询这个表来建立好友列表 1。
> - **方案二**：在用户详情表中加一项存储好友的list，可以是好友的ID列表，每次添加或删除好友时更新这个list，并存储回数据库 8。
>
> 服务器端可以通过监听WebSocket连接事件来管理用户的登录与断开，例如，在用户登录时将用户ID和socketfd存入一个映射表中，在用户断开连接时从映射表中移除对应的条目 2。
>
> 此外，**为了实现不在线好友的消息发送，服务器可以维护一个消息队列**，当好友不在线时，先将消息存储在队列中，待好友上线后再进行消息的推送 8。
>
> 在实际开发中，还需要考虑到WebSocket的全双工通信特性，服务器和客户端都可以主动向对方发送消息，实现实时通信和聊天功能 5。同时，为了提高系统的并发处理能力，可能需要使用更高效的通信框架和数据库优化策略 8。

## 0. 方案选择

###  （1）图片发送

* 二进制数据使用base64编码，嵌入xml/json发送
* 使用http



## 1. 架构设计

---

* Model

  协议

  对应数据中的表的实体类

  > protocol.cpp
  >
  > 

* DAL

  对数据库的操作API封装：DBHelper

  封装对model的增删改查API

  ORM

  构建xml

  

* Utils

  基础的、底层的、公用的一些类

* UI

  页面





## 2. 数据库设计

---

### （1）表设计

* User-用户基本信息

  uid（NO.）、account、password（md5)、nickname

* UserLogin（实时变化的）-已登录用户

  User、status（在线状态：在线、勿扰等）、clientfd、token

* Friends

  > 选择一个用户一张好友表还是所有人的好友关系存在一张表，主要取决于应用的具体需求、预期用户规模、查询效率和数据库维护等方面。以下是两种方案的优缺点：
  >
  > ### 所有人的好友关系存在一张表（单一好友表）
  >
  > **优点**：
  >
  > 1. **简化查询**：所有好友关系都在一个地方，查询两个用户是否是好友关系非常简单。
  > 2. **减少冗余**：避免每个用户都有自己的好友表，减少了数据冗余。
  > 3. **易于维护**：数据库结构简单，维护和扩展容易。
  > 4. **节省空间**：对于好友较少的用户，不需要为其创建多余的存储空间。
  >
  > **缺点**：
  >
  > 1. **扩展性问题**：当用户量非常大时，好友表可能会变得非常大，影响性能。
  > 2. **写入性能**：如果好友关系频繁变动，单一表可能会成为写入瓶颈。
  > 3. **并发问题**：高并发情况下，表锁定和事务可能会成为性能瓶颈。
  >
  > ### 一个用户一张好友表（用户独立好友表）
  >
  > **优点**：
  >
  > 1. **写入性能**：每个用户的好友关系写入自己的表，分散了写入操作，可能提高性能。
  > 2. **并发处理**：并发写入时，不会影响到其他用户的好友表。
  > 3. **灵活性**：可以针对不同用户定制不同的好友关系存储方案。
  >
  > **缺点**：
  >
  > 1. **数据冗余**：如果用户之间有共同好友，相同的好友信息会在多个表中重复存储。
  > 2. **查询复杂**：确定两个用户是否是好友需要联合多个表进行查询，增加了查询的复杂性。
  > 3. **维护困难**：随着用户数量的增加，管理大量的表会带来维护上的挑战。
  > 4. **空间浪费**：如果用户好友很少，很多表的存储空间会被浪费。
  >
  > ### 推荐方案
  >
  > 对于大多数应用，推荐使用**单一好友表**的方案。这是因为它在查询效率、数据维护和扩展性方面更为优越。现代关系型数据库系统通常能够很好地处理具有数百万行的表，而且通过合理的索引和查询优化，可以保持良好的性能。
  >
  > 如果应用具有以下特点，可以考虑**用户独立好友表**：
  >
  > - 用户之间的好友关系非常独立，很少有共同好友。
  > - 用户的好友数量差异极大，且大多数用户好友很少。
  > - 对于写入性能有极端要求，且并发写入非常高。
  >
  > 在实际应用中，还需要考虑其他因素，如数据库的扩展性、分布式数据库的使用、缓存策略等，以确保整个系统的高性能和可维护性。

  选定【单一好友表】

  > 设计用户的好友表，主要目的是存储用户之间的好友关系。以下是设计好友表时需要考虑的关键点：
  >
  > 1. **好友表的基本结构**：
  >    - `friendship_id`: 主键，好友关系的ID。
  >    - `user_id`: 表示参与好友关系的一方用户ID。
  >    - `friend_id`: 表示参与好友关系的另一方用户ID。
  >    - `status`: 表示好友关系的状态（如：已请求、已接受、已拒绝）。
  >
  > 2. **避免重复**：
  >    - 通常，好友关系是双向的，但存储时应该只记录一条记录，避免 `(user_id1, friend_id2)` 和 `(user_id2, user_id1)` 同时存在。
  >    - 可以通过在插入数据时检查 `user_id` 和 `friend_id` 的顺序，确保只存一种。
  >
  > 3. **处理好友关系的唯一性**：
  >    - 可以使用一个唯一索引来确保每对用户之间只存在一条好友关系记录。
  >
  > 4. **索引优化**：
  >    - 在 `user_id` 和 `friend_id` 上设置索引，可以加快查询速度。
  >
  > 5. **扩展字段**：
  >    - 根据需要，可以添加额外的字段，如 `request_date`（好友请求发送时间）、`confirmed_date`（好友关系确认时间）等。
  >
  > 6. **数据完整性**：
  >    - 确保 `user_id` 和 `friend_id` 存在于用户表中，可以通过外键约束来实现。
  >
  > 7. **好友关系的类型**：
  >    - 如果系统支持不同类型的好友关系（如：普通好友、亲密好友等），可以在表中添加一个 `type` 字段。
  >
  > 8. **好友请求功能**：
  >    - 如果系统需要支持好友请求，可以在好友表中添加一个 `request_message` 字段，用于存储请求时的消息。
  >
  > 9. **删除好友**：
  >    - 删除好友关系时，应从好友表中删除对应的记录。
  >
  > 10. **隐私和安全**：
  >     - 确保好友关系数据的隐私和安全，避免未授权访问。
  >
  > 一个简单的好友表SQL创建示例如下：
  >
  > ```sql
  > CREATE TABLE friendships (
  >     friendship_id INT AUTO_INCREMENT PRIMARY KEY,
  >     user_id INT NOT NULL,
  >     friend_id INT NOT NULL,
  >     status ENUM('requested', 'accepted', 'rejected') NOT NULL DEFAULT 'requested',
  >     request_date DATETIME,
  >     confirmed_date DATETIME,
  >     request_message TEXT,
  >     UNIQUE INDEX unique_friendship (user_id, friend_id),
  >     FOREIGN KEY (user_id) REFERENCES users(user_id),
  >     FOREIGN KEY (friend_id) REFERENCES users(user_id)
  > );
  > ```
  >
  > 请注意，这只是一个基础的设计示例。根据实际应用的需求，可能需要进一步的调整和优化。

### （2）DAL











## 2. 业务报文格式

### 心跳

* 发送

  ```xml
  <msgtype>0</msgtype>
  ```

* 响应

  ```xml
  <msgtype>0</msgtype>
  <retcode>0</retcode>  
  ```

### ack

```xml
<msgtype>3</msgtype>
<bizcode>3</bizcode>
<datatype>0</datatype>
<receivesize>5</receivesize>
```

### 注册

```xml
<msgtype>1</msgtype>
<bizcode>1</bizcode>
<identify>
	<account>12345</account>
    <password>111</password>
    <token></token>
</identify>
```

```xml
<msgtype>2</msgtype>
<bizcode>1</bizcode>
<retcode>10</retcode>  
```

### 登录

```xml
<msgtype>1</msgtype>
<bizcode>2</bizcode>
<identify>
    <account>123456</account>
    <password>111</password>
    <token></token>
</identify>
```

```xml
<msgtype>2</msgtype>
<bizcode>2</bizcode>
<retcode>20</retcode>
<data>
	<datatype>1</datatype>
    <datasize>50</datasize>
	<databody>?????????????????????????????????????????????????????????????????????????????</databody>
</data>
```

### 登出

```xml
<msgtype>1</msgtype>
<bizcode>3</bizcode>
<identify>
    <account>123456</account>
    <password></password>
    <token>???</token>
</identify>
```

```xml
<msgtype>2</msgtype>
<bizcode>3</bizcode>
<retcode>30</retcode>
```

### 聊天

* 发送报文

```xml
<msgtype>1</msgtype>
<bizcode>4</bizcode>
<identify>
	<account>123456</account>
	<password></password>
    <token>???</token>
</identify>
<data>
	<datatype>0</datatype>
    <datasize>5</datasize>
	<databody>HELLO</databody>
</data>
<forw>
	<forwcode>2</forwcode>
	<rececount>3</rececount>
	<receiver1>account1</receiver1>
	<receiver2>account2</receiver2>
	<receiver3>account3</receiver3>
</forw>
```

* 响应报文

```xml
<msgtype>2</msgtype>
<bizcode>4</bizcode>
<retcode>40</retcode>    
```

## （3）类设计

### Client

只要服务器需要管理很多Client，需要Client类与DB交互。

客户端中Client就1个自己，作为Utilis全局使用。

* hostname(serverIP)
* port
* clientfd

### User

* account
* password
* token
* nickname
* createdTime
* avatarPath

### UserLogin

* User
* status（在线状态：在线、勿扰等）



## （4）设置setting菜单：

* 服务器配置页面：

  可以输入【服务器IP】、【服务器端口】，【应用】按钮，连接服务器，重新启动。

  第一次打开软件弹出，点击【应用】后，写入配置到文件。

  读取配置。自动连接服务器，执行心跳。

## （4）注册

* 输入用户名（字符串<=50）、密码（字符串<=50，密文、2次确认）、用户昵称、注册按钮

* 发送username、password（md5)、nickname到server

  ```cpp
  <bizcode>001</bizcode><forwcode>000</forwcode><message><username></username><password></password><nickname></nickname></message>
  ```

* server以business001处理

  解析出username、password、nickname，写入表User，返回：

  ```cpp
  <retcode></retcode>
  ```


## （5）登陆：

* 输入账号、密码
* 可保存，密码（存储的是加密后）。
* 发送username、password。对password md5计算，用username和数据库中查询password，对比。返回：

## （6）消息加密发送

发送端对构建的的xml通过rsa加密

接收端对接收的数据进行解密得到明文

## （7）主页面

登录成功进入主页面。

取消【最大化按钮】

### 好友列表

* 显示好友：头像、nickname、username、签名

* 滑动显示。悬停效果。单击选中效果。
* 显示所有好友，在线的按照username首字母顺序排列，离线靠后
* 双击：顶部【聊天对象】修改名称、修改【当前聊天对象】（即：消息发送对象）

### 聊天记录

* 显示【聊天对象】的聊天记录。格式：时间-nickname-内容
* 对方：绿色。自己：蓝色。

### 聊天框

* enter、点击【发送按钮】发送

* 限定文本内容字符数<=MAXLEN。根据服务器设定。

  限定输入字符数，输入时字符数减少。

* 选择图片，打开文件选择框，过滤图片格式。点击【打开】按钮后，发送图片。

  暂定，聊天记录框显示图片名称+进度，如：111.png    100%，进度刷新直到100。

  发送失败则显示：111.png     失败。

  是否用直接显示图片替代显示图片名，后续论证。

## （7）关闭主页面



## （8）样式

UI美化后面再说

# server

## （1）初始化

从配置文件./config/server.xml中读取：

* 监听端口号
* 日志路径
* MySQL连接池参数
* 线程池参数

