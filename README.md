#### TCP三次握手以及状态转换：
①第一次握手前：服务器端和客户端都在CLOSED状态，服务器端调用socket()创建一个文件描述符，调用bind()绑定ip/端口号，调用listen()声明当前这个文件描述符作为一个服务器的文件描述符，调用accept()进入阻塞，等待客户端连接，服务器端由CLOSED进入LISTEN状态。
②第一次握手：客户端调用socket()创建文件描述符，调用connect()函数，发送SYN同步报文段，并阻塞等待服务器端应答，客户端进入SYN_SENT状态。
③第二次握手：服务器端收到SYN，发送SYN+ACK表示同意建立连接，自身进入SYN_RCVD状态。
④第三次握手：客户端收到ACK，从connect()返回，同时发送一个ACK，自身进入established状态，服务器端收到ACK之后，也会进入established状态，此时TCP三次握手结束，连接建立成功。

#### TCP可以是两次握手吗：
不可以，为了实现可靠性传输，双方必须维护一个确认序号，以标识发送出去的数据包哪些是已经被对方收到的。三次握手其实包含了双方协商确认序号的起始值，并确定对方收到确认序号的过程。
如果只有两次握手，那必定只有客户端的确认序号能被确认，服务器端的确认序号就无法被确认。

#### 如果服务器端出现大量调用 close_wait 状态，是为什么？
代码中忘记调close，代码有bug。

#### 从输入一个网址到显示页面过程中发生了什么？
1.输入网址过程中，浏览器会做一些预处理，比如chrome会根据访问历史预估你要访问的网址，比如输入ba的时候，浏览器知道你大概率要访问百度，那么在你按下回车之前，浏览器可能就开始建立TCP连接甚至渲染网页了。
更多细节：http://aosabook.org/en/posa/high-performance-networking-in-chrome.html
2.按下回车之后，浏览器开始检查url，首先判断协议，如果是http就按照web来处理，然后查看本地hosts文件，如果有的话直接使用hosts对应的IP地址。
3.通过DNS查询IP：DNS是基于UDP实现的，查询是一个逐渐缩小范围的过程，首先向DNS根节点查询负责.com区域的服务器，然后通过其中一个负责.com的服务器查询负责 baidu.com的服务器然后找到地址。
4.建立TCP连接，通过socket发送数据：查询到IP地址，就可以通过socket API发送数据，可以选择TCP或者UDP，一般HTTP使用TCP（延申：谷歌QUIC协议，基于UDP的可靠传输，比起TCP减少了很多round back次数）
5.建立好TCP连接之后，发送HTTP请求：请求一般分为三个部分1.url协议/版本 2.header 3.正文body
6.收到请求之后，http服务器解析请求，然后根据请求去调度哪些资源文件，并且处理用户的请求和数据，调用数据库信息，最终将结果返回给浏览器。
