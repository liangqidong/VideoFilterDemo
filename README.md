VideoFilterDemo
һ�����̽���
	������ʹ��VS2015���룬Ŀǰ��Ŀ��������ֻ����x86-Debug�������ԣ�
	��������Dshow������ʵ�ֵģ�Filter�̳���CBaseFilter��InputPin�̳���CBaseInputPin��OutputPin�̳���CBaseOutputPin���̳�CBase��Ŀ����Ϊ��ʵ��Filter��PIN�Ķ�̬������
	
�����ļ�����
	baseclasses�ļ��У�Ϊdshow ���������Դ�룻����Ҫ�����޸ı���ѡ�
	VideoFilterDemo�ļ��У�VideoFilter�ľ���ʵ�ְ���Filter��InputPin��OutputPin��
	
	1��IVideoFilter.h �ӿڱ�¶�㣬��Ҫ�ǰ�Filter�Ľӿڱ�¶������
	2��Setup.cpp com�����ʼ���㣬��ʼ��dll
	3��VideoFilterDemo.h filter��ʵ�ֳɲ㣬�̳���CBaseFilter��ʵ����Ӧ��Filter�ӿڡ��̳�CCritSecΪ�˼���dshow�������̳�ISpecifyPropertyPageʵ������ҳ�Ĺ��ܣ�
	4��VideoFilterInputPin.h
	Inputpin��ʵ�ֲ㣬�̳���CBaseInputPin��ʵ����Ӧ��InputPin�ӿ�