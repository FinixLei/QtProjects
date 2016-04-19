In TestQtService, a Windows service can be installed, uninstalled, start, paused, or stopped. 
In this service, PluginOne's signal is connected to PluginTwo's slot. 

How to handle the service? 
-i install 
-u uninstal
-s start
-t stop/terminate
-p pause
-h help

In the folder "qtservice", we use the 3rd party library/source qtsolution/qtservice. 
You can refer to qtsolution here: https://github.com/qtproject/qt-solutions

Log is at C:\Windows\System32\MyService.log

-----------------------------

Note:
Since Windows Vista, Windows Service does not support start a GUI application. Actually, the application has been started, and you can find it in TaskManager, but you cannot see its GUI. That's just because its GUI and the service are in session 0 where GUI cannot be seen. See the articles below for more details. 
http://stackoverflow.com/questions/5063731/is-there-any-way-to-start-a-gui-application-from-a-windows-service-on-windows-7
https://msdn.microsoft.com/en-us/library/windows/desktop/ms683502(v=vs.85).aspx

This article also contains interesting points: http://blog.csdn.net/nirendao/article/details/51194003
