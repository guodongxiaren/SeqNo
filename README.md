# SeqNo
分布式全局序列号发生器
## 背景介绍
在大型的分布式的系统架构中，很多需要一个全局的、保证一段时间内唯一的序列号发生器。
比如用户的内部用户id，电商和支付系统的订单流水号等。

## 项目介绍
本Repo分别使用MySQL，ZooKeeper，Redis来实现这一个功能
