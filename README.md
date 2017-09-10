# draughts_online

## 实现功能：

1. 实现网络对战功能。
 - 显示 IP，能自定义端口号并进行监听；
 - 能够填写对方 IP 及端口号并进行连接；
 - 能够实时对对方的走棋在棋盘上做出响应，同时本方的走棋对方也能看到。

2. 实现[完整功能的国际跳棋](https://github.com/nzpznk/draughts_online/blob/master/rule.pdf)
3. 认输功能及求和功能
4. 下棋时的音效


## 运行效果：

### 极为朴素的欢迎与网络配置界面

![](./show/show1.png)
<!-- ![](https://github.com/nzpznk/draughts_online/blob/master/show/show1.PNG) -->

### <del>巧克力饼干一样的</del> 棋盘格子与 <del>蒙了马赛克一样的</del> 棋子

![](./show/show2.png)
<!-- ![](https://github.com/nzpznk/draughts_online/blob/master/show/show2.PNG) -->

### 纯黄色边框的可选中棋子与大红色的提示（<del> 忽略这配色 </del>）

![](./show/show3.png)
<!-- ![](https://github.com/nzpznk/draughts_online/blob/master/show/show3.PNG) -->

### 到达底线加冕后的白方棋子

![](./show/show4.png)
<!-- ![](https://github.com/nzpznk/draughts_online/blob/master/show/show4.PNG) -->

### 胜不骄，败不馁

![](./show/show5.png)
<!-- ![](https://github.com/nzpznk/draughts_online/blob/master/show/show5.PNG) -->

## 模块划分：

### `client/Client`

- 负责收发消息，控制界面绘制与消息提醒

### `server/Server`

- 只负责转发消息，双方棋子颜色

### `logic/Game`

- 游戏算法部分，计算可移动的棋子以及移动路径

### `UI/DraughtsBoard`

- 棋盘界面

### `UI/Welcome`

- 欢迎与网络配置界面

## 主要算法

- 通过DFS将每个棋子的可走路径存储QVector, 通过QMap与起点棋子进行对应

## 大作业感想与心路历程

1. <del> 用户界面：从入门到放弃 </del>

2. 非常感谢课上某位同学(实在记不起是谁了)分享的用socket传输结构体的方法，节省了我大量的网络部分debug时间

## Acknowledgement:

王冠图标全部来自：[https://www.flaticon.com/](https://www.flaticon.com/)

棋子图标来自网页：[https://www.playok.com/zh/draughts10x10/](https://www.playok.com/zh/draughts10x10/)

本项目中使用的图标为上述二者修饰而成
