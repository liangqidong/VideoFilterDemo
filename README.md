VideoFilterDemo
一、工程介绍
	本工程使用VS2015编译，目前项目属性配置只配置x86-Debug编译属性；
	本工程在Dshow基础上实现的，Filter继承了CBaseFilter；InputPin继承了CBaseInputPin；OutputPin继承了CBaseOutputPin；继承CBase的目的是为了实现Filter，PIN的动态创建；
	
二、文件描述
	baseclasses文件夹：为dshow 的依赖库的源码；不需要额外修改编译选项；
	VideoFilterDemo文件夹：VideoFilter的具体实现包括Filter、InputPin、OutputPin；
	
	1）IVideoFilter.h 接口暴露层，主要是把Filter的接口暴露出来；
	2）Setup.cpp com组件初始化层，初始化dll
	3）VideoFilterDemo.h filter的实现成层，继承了CBaseFilter并实现相应的Filter接口、继承CCritSec为了集成dshow的锁，继承ISpecifyPropertyPage实现属性页的功能；
	4）VideoFilterInputPin.h
	Inputpin的实现层，继承了CBaseInputPin并实现相应的InputPin接口