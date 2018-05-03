# CVI版本modbus移植说明（20180426）

## 文件结构

![文件结构](http://ols5yckz1.bkt.clouddn.com/CVI_modbus%E6%96%87%E4%BB%B6%E7%BB%93%E6%9E%84.png)

* source中文件，直接移植，无需更改。

* cfg中文件夹，mb_cfg.h需配置是否开启主机模式，从机模式；MB_DATA.c文件需明确需要输出数据区。

* Port文件夹。MB_BSP.c（主要移植层）在CVI软件中，实现串口底层（启动多线程，在线程中判断OLen数据长度，确定收发）及定时器底层（异步定时器）。注：串口收发不能采用串口回调函数（不能并行执行）。

* OS文件夹。（主要移植层）无操作系统，采用全局变量模拟信号量（启动多线程）。

  ## 移植实现

  * port文件夹。MB_BSP.c（串口部分）

  1. MB_CommTx1 函数，放入ComWrtByte函数

  2. MB_CommTxIntDis，MB_CommTxIntEn空函数

  3. MB_CommPortCfg，安CVI串口初始化，并用CmtScheduleThreadPoolFunction 函数启动动多线程处理函数。线程处理函数如下（模拟中断处理函数），完成modbus接收和发送处理。

     static int CVICALLBACK Thread_CommCallback (void *functionData)
     {

     ```
     char	rx_data;	
     while(1)
     {
     	if(GetOutQLen(mb_com1config.port))									//发送数据
     	{
     		MB_ChPortMap[0]->TxCtr++;
     	    MB_TxByte(MB_ChPortMap[0]);                                             /* Send next byte                                       */
     	}
     ```

     ```
     	while(GetInQLen(mb_com1config.port))						//有数据未取
     	{
     		rx_data = (char)ComRdByte (mb_com1config.port);
     		MB_ChPortMap[0]->RxCtr++;
     		MB_RxByte(MB_ChPortMap[0], rx_data);                     			/* Pass character to Modbus to process                  */
     	}
     }
     return 1;
     ```

     }

  * port文件夹。MB_BSP.c（定时器部分）

    1. 在 MB_RTU_TmrInit函数中，启用异步定时器（NewAsyncTimer）；
    2. 在异步定时器回调函数中，调用MB_RTU_TmrISR_Handler；

  * OS文件夹。

    1. 将MB_OS_RxWait，MB_OS_TxWait调整为根据全局变量等待的函数。如

       > > > void  MB_OS_RxWait (MODBUS_CH   *pch,
       > > >
       > > > ```
       > > >                 CPU_INT16U  *perr)
       > > > ```
       > > >
       > > > {
       > > >
       > > > ```
       > > > uint32	i = 1000000000;
       > > > i = 1000000000; 
       > > > while(i-- && (RxSignalFlg == 0)) ;			//数据接收完成，退出
       > > > *perr = MODBUS_ERR_NONE;
       > > > //while(1);
       > > > ```
       > > >
       > > > }

    2. 在MB_OS_InitSlave中，启动多线程，CmtScheduleThreadPoolFunction，在多线程处理函数中，循环调用MB_OS_RxTask（模拟任务调度，MB_OS_RxTask执行条件是RxSignalFlg=1（接收结束））；

    3. 在MB_OS_RxSignal中，将全局变量MB_OS_RxSignal置1，代表接收结束。

  * cfg文件夹。

    1. MB_DATA.c根据要输出的数据，设置具体数值。

    ## 使用说明

    * 从机模式

      1. 配置。将mb_cfg.h中

         define  MODBUS_CFG_SLAVE_EN       配置为       DEF_ENABLED      

      2. 初始化。将工作模式设置为从机。

         ```
         MB_Init(1000);								//初始化modbus频率					
         ```

         ```
         pch         = MB_CfgCh( ModbusNode,        	// ... Modbus Node # for this slave channel
                             MODBUS_SLAVE,           // ... This is a MASTER
                             500,                    // ... 0 when a slave
                             MODBUS_MODE_RTU,        // ... Modbus Mode (_ASCII or _RTU)
                             0,                      // ... Specify UART #2
                             57600,                  // ... Baud Rate
                             8,         				// ... Number of data bits 7 or 8
                             0,       				// ... Parity: _NONE, _ODD or _EVEN
                             1,         				// ... Number of stop bits 1 or 2
                             MODBUS_WR_EN);          // ... Enable (_EN) or disable (_DIS) writes
         ```

      3. 在MB_BSP中，指定数据区。

    ​

    * 主机模式

      1. 将mb_cfg.h中

         define  MODBUS_CFG_MASTER_EN       配置为       DEF_ENABLED  

      2. 初始化。

      3. 主动调用MBM_Core.c中相关函数，执行操作。


  ##  20180503说明

  * 主从模式。

    装置只能设置为MODBUS_SLAVE模式，设置为MASTER模式后，接收定时器禁用，不能接收数据。

  * 在NO_MB_OS.c文件中，定义PollRxSignalFlg全局变量。进行master操作时，在MB_OS_RxWait函数，将PollRxSignalFlg置1，在定时器溢出时，PollRxSignalFlg清零（不处理RxSignalFlg（SLAVE使用）变量），退出MB_OS_RxWait函数（模拟OS接收等待）。

  * MODBUS协议实现的是F03和F16的功能，其他功能位开放。

  ​



