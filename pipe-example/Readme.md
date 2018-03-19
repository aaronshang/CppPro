### 1简介

C语言进程间通信的例子。

### 2场景

抓包程序需要调用`USBPcapCMD`程序，其是个控制台程序。启动后，需要依次输入过滤器、文件名，然后可以实现抓包功能。本例便是尝试通过进程间通信的方式模拟`输入`。

### 3问题

如果是自建控制台应用程序，可以实现命令模拟发送。但是USBPcapCMD程序不可以。通过源码分析，其控制台程序是新建的控制台。

```c
    FreeConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    /* If we are running interactive then we should show console window.
     * We are not automatically allocated a console window because the
     * application type is set to windows. This prevents console
     * window from showing when USBPcapCMD is used as extcap.
     * Since extcap is recommended cmd.exe users will notice a slight
     * inconvenience that USBPcapCMD opens new window.
     *
     * Please note that is it impossible to get parent's cmd.exe stdin
     * handle if application type is not console. The difference is
     * that in case of console application cmd.exe waits until the
     * process finishes and in case of windows applications there is
     * no wait for process termination and the cmd.exe console immadietely
     * regains standard input functionality.
     */
    if (AllocConsole() == FALSE)
    {
        return -1;
    }
```

### 4结论

通过自建模拟程序`hello`，验得在新控制台下，也不能收到管道通知。