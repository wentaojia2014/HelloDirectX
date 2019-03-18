# Hello Dx
## Build status

|[Windows][win-link] |
| :---------------: |
| ![win-badge]      |

[win-badge]: https://ci.appveyor.com/api/projects/status/gup0dy0cc2d25m7o?svg=true "AppVeyor build status"
[win-link]: https://ci.appveyor.com/project/jiawentao/hellodirectx "AppVeyor build status"

## License
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/wentaojia2014/HelloDirectX/blob/master/LICENSE)

## 简介

用来学习DirectX11/12图形编程的一些项目。

参考 http://www.rastertek.com/tutdx11.html

将其中旧的功能换成新的,包括XMMath 取代 D3DXMath,ComPtr和std智能指针管理内存,使用DirectXTK和DirectXTEX,以及其它一些优化。

## 目录结构
- Base
 
  公用的部分，单独的库

- HelloDx

  DirectX的基本功能使用

- 2DRender

  3D场景中渲染2D纹理

- FontEngine
  
  字体渲染

- ObjConvert

  命令行工具，用来转换obj格式模型文件为txt格式

## 安装依赖

  使用vcpkg
  vcpkg install directxtk:x64-windows directxtex:x64-windows

#### 联系方式:
***
|作者|贾文涛|
|---|---|
|QQ|759378563|
|微信|xsd2410421|
|邮箱|jared2020@163.com|
|blog|https://wentaojia2014.github.io/|

###### 请放心联系我，乐于提供相关帮助
***
#### **打赏**
<img src="https://github.com/wentaojia2014/wentaojia2014.github.io/blob/master/img/weixin.jpg?raw=true" width="30%" height="30%" /><img src="https://github.com/wentaojia2014/wentaojia2014.github.io/blob/master/img/zhifubao.jpg?raw=true" width="30%" height="30%" />

###### 觉得分享的内容还不错, 就请作者喝杯奶茶吧~~
***