# OpenGL-Programming-Guide-8th-Edition-Code
这是OpenGL编程指南（第八版）书中代码，使用VS2015建立的工程。

## 第三方库
1. Freegult 地址[https://sourceforge.net/projects/freeglut/](https://sourceforge.net/projects/freeglut/) ,这个库已经编译成静态库文件，Debug版本：lib/freeglut_staticd.lib， release版本：freeglut_static.lib
2. Glew 地址[http://glew.sourceforge.net/](http://glew.sourceforge.net/) 这个库文件代码文件只有一个glew.c，程序中直接使用了源码


## 代码说明
1.	所有程序都在Debug x86 下编译的 
2.	原书中1-12章节提供的代码都已整理，并修改了其中的一些错误，在“Chapter**-OG”命名的项目中
3.	增加了一些更加简单易理解的代码，实现了书中未给代码的例子。
4.	9-12章节也实现了书中未给代码的例子，但还未整理完成在“TestChapter**”命名的项目中，后续会整理并更新。


在“TestChapter**”项目中一个文件就是 一个程序，一个项目有多个文件时，只会有一个文件会被编译，其他文件会被忽略
如果要更换其他文件，按如下步骤：
1.	右击要忽略或启用的文件
2.	选择忽略或者启用
 

