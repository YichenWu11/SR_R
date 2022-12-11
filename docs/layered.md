# *分层*

<img src="assets/../../assets/images/00.png">

* ***engine***
  * 整个项目的核心类，主要功能为 `start` 和 `shundown`
* ***core***
  * 一些通用的, 核心的, 底层的功能模块
  * 如 `Color` 的封装, 计时器的封装，一些宏以及日志系统等
* ***function***
  * `engine` 核心功能部分的实现
* ***platform***
  * 平台相关的一些模块, 现在只包含 `windows` 下窗口的创建
  * 后续可能加入`文件路径管理`等
* ***manager***
  * `asset_manager` and `config_manager`
