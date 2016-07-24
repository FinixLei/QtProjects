# MyWindowsService  
This is a Windows Service or Unix Daemon. It monitors users' log on/log off, lock/unlock, sleep/awake Windows events, and writes to the log.  
The log locates at C:/ProgramData/MyWindowsService/mws.log.  
This project also gives several tries to get the specific user's (the active user's) user name and environment variable.  
It seems the user name of the active user can be got, but it's hard to get the environment variables.  
