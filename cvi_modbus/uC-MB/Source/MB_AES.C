#include <global.h>
#include <aes.h>

#if MB_AES_EN == DEF_ENABLED
static INT8U       mbszIvec[] = {0X12, 0x34, 0x56, 0x78,0X87, 0x65, 0x56, 0x78,
                                 0x87, 0x65, 0x43, 0x21,0x12, 0x34, 0x43, 0x21};
static AES_KEY     mbaesKey;
static INT8U       mbuserIvec[16];
#endif
/*******************************************************************************
 * 名    称： MB_AESCbcDecrypt()
 * 功    能： 接收数据加密码
 * 入口参数： buf 输入接收缓冲区,len 输入要加密的缓冲区长度
 * 出口参数： 解密后的长度
 * 作　 　者： 无名沈
 * 创建日期： 2014-03-28
 * 修    改：
 * 修改日期：
 *******************************************************************************/
INT16U MB_AESCbcDecrypt(INT8U *buf, INT16U len)
{
#if MB_AES_EN == DEF_ENABLED    
    memset(mbaesKey.rd_key, 0, sizeof(mbaesKey.rd_key));// 清零扩展密钥
    AES_SetDecryptKey(  "scw->ll->zs->scw",         // 密钥
                        128, 		                // 128位方式，还有192和256位方式
                       &mbaesKey);			        // 扩展密钥
    /***********************************************
    * 描述： 设置密钥向量
    */
    memcpy((INT8U*)mbuserIvec,(INT8U*)&mbszIvec[0], 16);// 向量
    /***********************************************
    * 描述： 更改密钥向量（为增加安全性，可使向量自动与发送端进行同步）
    *
    if (++mbszIvec[6] > 10)
      mbszIvec[6]  = 0;
    *//***********************************************
    * 描述： 检查数据长度是否为16的整数倍
    */
    if ( (len & 0x0f) != 0  )
      return (DEF_FALSE);
    
    AES_CbcEnOrDecrypt((INT8U*)buf,                 // 待解密缓冲区
                       (INT8U*)buf,                 // 解密后的缓冲区
                        len,				        // 缓冲区长度
                       (AES_KEY*)&mbaesKey, 		// 扩展密钥
                       (INT8U*)mbuserIvec, 		    // 向量
                        AES_DECRYPT);		        // 加密
    /***********************************************
    * 描述： 检查最后一个字节是否为1，为1则表示填充位字节数为1
    */
    if ( buf[len-1] == 1) {                         // 如果最后字节为1
      len--;                                        // 有效数据数-1
    /***********************************************
    * 描述： 检查>1的填充字节数
    */
    } else if ( buf[len-1] < 16 && buf[len-1] > 1) {
      INT8U i   = buf[len-1];                       // 获取填充值
      INT8U *p  = &buf[len-i];                      // 指向开始填充的字节地址
      for (i-=1;i > 0;i--,p++) {
        if ( *p != *(p+1) )                         // 如果相邻两个字节的值不相等
          break;                                    // 说明不是填充值，直接跳出
      }
      if (i==0)                                     // 如果较完成，说明是填充字节
        len -= buf[len-1];                          // 获取有效数据帧字节数
    }
#endif
    return      len;                                // 重新赋值给接收计数器
}
/*******************************************************************************
 * 名    称： MB_AESCbcEncrypt()
 * 功    能： 发送数据加密码
 * 入口参数： buf 输入发送缓冲区,len 输入要加密的缓冲区长度
 * 出口参数： 加密后的长度
 * 作　 　者： 无名沈
 * 创建日期： 2014-03-28
 * 修    改：
 * 修改日期：
 *******************************************************************************/
INT16U MB_AESCbcEncrypt(INT8U *buf, INT16U len)
{
#if MB_AES_EN == DEF_ENABLED
    INT8U       temp;
    
    memset(mbaesKey.rd_key, 0, sizeof(mbaesKey.rd_key));// 清零扩展密钥
    AES_SetEncryptKey(  "scw->ll->zs->scw",         // 密钥
                        128, 		                // 128位方式，还有192和256位方式
                       &mbaesKey);			        // 扩展密钥
    /***********************************************
    * 描述： 设置密钥向量
    */
    memcpy((INT8U*)mbuserIvec,(INT8U*)&mbszIvec[0], 16);// 向量
    temp    = len & 0x0f;
    if ( temp != 0) {
      temp    = 16 - temp;
      memset((INT8U*)&buf[len],temp,temp);
      len = len + temp;
    }
    AES_CbcEnOrDecrypt((INT8U*)&buf[0],             // 待解密缓冲区
                       (INT8U*)&buf[0],             // 解密后的缓冲区
                        len,	                    // 缓冲区长度
                       (AES_KEY*)&mbaesKey, 		// 扩展密钥
                       (INT8U*)mbuserIvec, 		    // 向量
                        AES_ENCRYPT);		        // 加密
#endif
    return len;
}
