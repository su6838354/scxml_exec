# scxml_exec
scxm转化为图形的工具，C++编写，图形实现基于MFC，xml基于tinyxpath


整个模块由下而上分为 5部分

1.Scxml 脚本

2.Parser 层（依赖Tinyxpath）

3.Model 层

4.Layout 层 (Model转化为虚拟图形对象)

5.View 图形（MFC实现）

## 具体说明 ##

## tinyxpath对xpath支持报告 ##

## 展示效果如下 ##

下面为一个相对复杂的scxml，包含了并行、多层的嵌套关系
![](http://images2015.cnblogs.com/blog/564050/201703/564050-20170311121905576-895615723.png)