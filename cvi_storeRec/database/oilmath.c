/*******************************************************************************
 *   Revised:        All copyrights reserved to redmorningcn.
 *   Revision:       v1.0
 *   Writer:	     redmorningcn.
 *
 *   Description:    2017-10-16
 *   Notes:
 *     				 E-mail: redmorningcn@qq.com
 *
 *******************************************************************************/

/********************************************************************************************/
/* Include files																			*/
/********************************************************************************************/
#include "oilmodel_db.h"
#include "databaseoperate.h"
#include "modeltable.h"

/*******************************************************************************
* LOCAL VARIABLES
*/

/*******************************************************************************
 * 名    称：       GetMathOilVal
 * 功    能：       计算油量。根据高度值，油箱容积表，修正系数等计算油量.
 * 入口参数：       无
 * 出口参数： 	    无
 * 作　 　者： 	    redmornigcn
 * 创建日期： 	    2017-05-16
 * 修    改：
 * 修改日期：
 *******************************************************************************/
uint16    GetMathOilVal(int16   hig)
{
  	float 		DipVal = 0;                  		
  	float 		Hight;                  			
	float		MinHig,MaxHig;	
	float		MinDip,MaxDip;					
    
	uint8		ModelPotNum;
	uint8		i;
    
	//模型有效才处理
	if(		gsSetModelTable.Operate.rdModel.PotNum  == 0
	|| 		gsSetModelTable.Operate.rdModel.ModelNum== 0)
	{
		return 0;
	}
	
	ModelPotNum = gsSetModelTable.Operate.rdModel.PotNum;           	//模型点数

	Hight = hig;                                        				//高度值

	Hight += ((float)gsOilPara.Hig );              						//加入补偿高度	
  	
  	for(i = 1; i <  ModelPotNum; i++)                   				//计算点的个数
  	{
		MinHig 	= gsSetModelTable.Operate.rdModel.sModPot[i-1].HigVal; 	//第1个点的高度值
		MaxHig 	= gsSetModelTable.Operate.rdModel.sModPot[i].HigVal;   	//第2个点的高度值

		MinDip 	= gsSetModelTable.Operate.rdModel.sModPot[i-1].DipVal; 	//第1个点的油量值
		MaxDip 	= gsSetModelTable.Operate.rdModel.sModPot[i].DipVal;   	//第2个点的油量值
						
		if(MinHig == MaxHig  || MinDip == MaxDip)       				//计算模型中出现两个相同点
		{
			//DisplaySet(60,1,"E-OL");                    				//显示油量值
			return	0;                                  				//油箱模型错误，显示0
		}

		if(MinHig <= Hight && Hight < MaxHig)		    				//计算油量,在模型值中，按两点值计算
		{	
			DipVal = MinDip + ((Hight - MinHig)  * (MaxDip - MinDip)) / (MaxHig - MinHig);

			break;
		}
	
		if(i == 1)														//小于最小高度，按最低点斜率
		{			
			if(Hight < MinHig)
			{
				DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
				
				break;
			}
		}
		
		if(i == (ModelPotNum - 1))										//高度值大于最后一点，按最后点计算
		{
			
			if(Hight >= MaxHig)
			{
				DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
			}
		}
	}
        
    DipVal *= gsOilPara.Slope;                 					//计算修正斜率
    DipVal /= 10000;
	DipVal += gsSetModelTable.Operate.rdModel.StartOil;        	//计算值 加 模型起始油量值
    
    return  (uint16)DipVal;
}


/*******************************************************************************
 * 功    能：       计算高度值。根据油量，油箱容积表，修正系数等计算油量.
 * 入口参数：       无
 * 出口参数： 	    无
 * 作　 　者： 	    redmornigcn
 * 创建日期： 	    2017-10-16
 * 修    改：
 * 修改日期：
 *******************************************************************************/
uint16    GetMathHigVal(int16   oil)
{
  	float 		DipVal = 0;    
  	float 		Hight  = 0;                  			
	float		MinHig,MaxHig;	
	float		MinDip,MaxDip;					
    
	uint8		ModelPotNum;
	uint8		i;
	
	//模型有效才处理  
	if(		gsSetModelTable.Operate.rdModel.PotNum  == 0
		|| 	gsSetModelTable.Operate.rdModel.ModelNum== 0)
	{
		return 0;
	}
	
	DipVal = oil;
			 
    DipVal -= gsSetModelTable.Operate.rdModel.StartOil;        	//计算值 加 模型起始油量值 
    
	DipVal *=10000;
	DipVal /= gsOilPara.Slope;                 					//计算修正斜率
	
	ModelPotNum = gsSetModelTable.Operate.rdModel.PotNum;              //模型点数
  	
  	for(i = 1; i <  ModelPotNum; i++)                   //计算点的个数
  	{
		MinHig 	= gsSetModelTable.Operate.rdModel.sModPot[i-1].HigVal; //第1个点的高度值
		MaxHig 	= gsSetModelTable.Operate.rdModel.sModPot[i].HigVal;   //第2个点的高度值

		MinDip 	= gsSetModelTable.Operate.rdModel.sModPot[i-1].DipVal; //第1个点的油量值
		MaxDip 	= gsSetModelTable.Operate.rdModel.sModPot[i].DipVal;   //第2个点的油量值
						
		if(MinHig == MaxHig  || MinDip == MaxDip)       				//计算模型中出现两个相同点
		{
			//DisplaySet(60,1,"E-OL");                    				//显示油量值
			return	0;                                  				//油箱模型错误，显示0
		}

		if(MinDip <= DipVal && DipVal < MaxDip)		    				//计算油量,在模型值中，按两点值计算
		{	
			//DipVal = MinDip + ((Hight - MinHig)  * (MaxDip - MinDip)) / (MaxHig - MinHig);
			Hight = MinHig + ( ((DipVal - MinDip)  * (MaxHig - MinHig)) / (MaxDip - MinDip));
			break;
		}
	
		if(i == 1)														//小于最小高度，按最低点斜率
		{			
			if(DipVal < MinDip)
			{
				//DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
				Hight = MinHig + ( ((DipVal - MinDip)  * (MaxHig - MinHig)) / (MaxDip - MinDip)); 
				break;
			}
		}
		
		if(i == (ModelPotNum - 1))										//高度值大于最后一点，按最后点计算
		{
			if(DipVal >= MaxDip)
			{
				//DipVal = MinDip + ((Hight - MinHig)  * ((MaxDip - MinDip)) / (MaxHig - MinHig));
				Hight = MinHig + ( ((DipVal - MinDip)  * (MaxHig - MinHig)) / (MaxDip - MinDip)); 
			}
		}
	}
        
	Hight -= ((float)gsOilPara.Hig );              					//补偿高度	
    
    return  (uint16)Hight;
}

