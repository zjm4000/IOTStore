﻿// =================================================================== 
// 项目说明
//====================================================================
// 张家铭。@Copy Right 2016
// 文件： Tbl_Article_TypeFindPage.c
// 作用：CGI文件源码
// 项目名称：物联仓储项目
// 创建时间：2016-10-19
// 负责人：张家铭
// ===================================================================
#include <stdio.h>
#include "cgic.h"
#include "../SQLite3/Tbl_Article_TypeDAL.h"

int cgiMain(){
    char sCon[128];
	char sSort[128];
	char iPageSize[128];
	char iCurrentPageIndex[128];
	cgiFormString("sCon",sCon,128);
	cgiFormString("sSort",sSort,128);
	cgiFormString("iPageSize",iPageSize,128);
	cgiFormString("iCurrentPageIndex",iCurrentPageIndex,128);
	SqlLinkQueue list=init_linkqueue();
	int count=Tbl_Article_TypeFindPage(list,sCon,sSort,atoi(iPageSize),atoi(iCurrentPageIndex));
	char strJson[1024]="";
	char str[128];
	if (count>0)
	{
		strcat(strJson,"{\"jsn\":[");
		INode p=list->front;
		while (p!=list->rear) {
			char str[128];
			p=p->next;
			Tbl_Article_Type _Tbl_Article_Type=p->data->_Tbl_Article_Type;
			sprintf(str,"{\"TypeID\":\"%d\",\"TypeName\":\"%s\"},",_Tbl_Article_Type.TypeID,_Tbl_Article_Type.TypeName);
			strcat(strJson,str);
		}
		strJson[strlen(strJson)-1]='\0';
		sprintf(str,"],\"iTotalPageCount\":%d}",Tbl_Article_TypeGetTotalPageCount(sCon,atoi(iPageSize)));
		strcat(strJson,str);
	}
	else
	{
		sprintf(strJson,"{\"jsn\":[],\"iTotalPageCount\":0}");
	}
	free_linkqueue(list);
	printf("Content-Type:text/html;charset=UTF-8\n\n");
	printf("%s",strJson);

}

